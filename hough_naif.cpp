#include "hough_naif.h"
#include <cmath>
#include <iostream>
#include "ecriture_ppm.h"
#include "conversion_binaire.h"
#include "lecteur_ppm.h"
#include "extraction_pixels.h"  // pour extraire_pixels_blancs

// Fonction pour initialiser les paramètres et l'accumulateur de Hough
HoughNaif initialiser_hough_naif(const Image& image, double m_min, double m_max, double pas_m, double pas_b) {
    HoughNaif hough;

    // Définir les bornes et les pas pour la pente m
    hough.m_min = m_min;
    hough.m_max = m_max;
    hough.pas_m = pas_m;

    // Définir les bornes pour l'ordonnée à l'origine b (en fonction de la hauteur de l'image)
    hough.b_min = -image.hauteur;
    hough.b_max = image.hauteur;
    hough.pas_b = pas_b;

    // Calculer le nombre de valeurs discrètes possibles pour m et b
    hough.nb_m = static_cast<int>((m_max - m_min) / pas_m) + 1;
    hough.nb_b = static_cast<int>((hough.b_max - hough.b_min) / pas_b) + 1;

    // Initialiser l'accumulateur (matrice de votes) avec des zéros
    hough.accumulateur.resize(hough.nb_m, std::vector<int>(hough.nb_b, 0));

    return hough;
}

// Fonction pour remplir l'accumulateur de Hough à partir des pixels blancs de l'image binaire
void remplir_accumulateur_naif(HoughNaif& hough, const Image& image_binaire) {
    // Extraire les coordonnées (x, y) des pixels blancs de l'image binaire
    std::vector<std::pair<int, int>> pixels_blancs = extraire_pixels_blancs(image_binaire);

    // Pour chaque pixel blanc
    for (size_t k = 0; k < pixels_blancs.size(); ++k) {
        int x = pixels_blancs[k].first;
        int y = pixels_blancs[k].second;

        // Pour chaque valeur discrète de pente m
        for (int i = 0; i < hough.nb_m; ++i) {
            double m = hough.m_min + i * hough.pas_m;

            // Calculer l'ordonnée à l'origine b pour cette pente et ce point
            double b = y - m * x;

            // Vérifier que b est dans les bornes de l'accumulateur
            if (b < hough.b_min || b > hough.b_max) continue;

            // Calculer l'indice j correspondant à b dans l'accumulateur
            int j = static_cast<int>((b - hough.b_min) / hough.pas_b);

            // Si l'indice j est valide, incrémenter le compteur de votes
            if (j >= 0 && j < hough.nb_b) {
                hough.accumulateur[i][j]++;
            }
        }
    }
}

// Fonction pour afficher les droites ayant reçu un nombre de votes supérieur ou égal à un seuil
void afficher_droites_significatives(const HoughNaif& hough, int seuil) {
    std::cout << "---- Droites détectées (seuil = " << seuil << ") ----" << std::endl;

    // Parcourir tous les éléments de l'accumulateur
    for (int i = 0; i < hough.nb_m; ++i) {
        for (int j = 0; j < hough.nb_b; ++j) {
            int votes = hough.accumulateur[i][j];

            // Si le nombre de votes dépasse le seuil, afficher la droite correspondante
            if (votes >= seuil) {
                double m = hough.m_min + i * hough.pas_m;
                double b = hough.b_min + j * hough.pas_b;

                std::cout << "Droite : y = " << m << " * x + " << b
                    << "   (" << votes << " votes)" << std::endl;
            }
        }
    }
}
