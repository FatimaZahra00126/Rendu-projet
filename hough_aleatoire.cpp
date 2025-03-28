#include "lecteur_ppm.h"           // Pour la structure Image et la couleur
#include "extraction_pixels.h"     // Pour extraire_pixels_blancs
#include "hough_aleatoire.h"
#include <random>
#include <cmath>
#include <iostream>
#include <map>
#include <vector>

// Fonction pour d�tecter des droites par �chantillonnage al�atoire
std::vector<Droite> detecter_droites_aleatoirement(const Image& image_binaire, int nb_iterations_max, double pas_discretisation) {
    // Extraire tous les pixels blancs de l'image
    std::vector<std::pair<int, int>> pixels_blancs = extraire_pixels_blancs(image_binaire);

    // Accumulateur de votes pour chaque couple (m, b) discr�tis�
    std::map<std::pair<int, int>, int> accumulateur;

    // Si on n'a pas assez de points blancs, on arr�te
    if (pixels_blancs.size() < 2) return {};

    // Initialisation du g�n�rateur de nombres al�atoires
    std::random_device rd;
    std::mt19937 generateur(rd());
    std::uniform_int_distribution<> distribution(0, pixels_blancs.size() - 1);

    // R�p�ter plusieurs fois : choisir deux points au hasard
    for (int i = 0; i < nb_iterations_max; ++i) {
        int indice1 = distribution(generateur);
        int indice2 = distribution(generateur);

        // �viter de tirer deux fois le m�me point
        if (indice1 == indice2) continue;

        // R�cup�rer les coordonn�es des deux points
        int x1 = pixels_blancs[indice1].first;
        int y1 = pixels_blancs[indice1].second;
        int x2 = pixels_blancs[indice2].first;
        int y2 = pixels_blancs[indice2].second;

        // Ignorer les droites verticales pour �viter les divisions par z�ro
        if (x1 == x2) continue;

        // Calcul de la pente m et de l'ordonn�e � l'origine b
        double m = static_cast<double>(y2 - y1) / (x2 - x1);
        double b = y1 - m * x1;

        // Discr�tisation des param�tres m et b
        int indice_m = static_cast<int>(std::round(m / pas_discretisation));
        int indice_b = static_cast<int>(std::round(b / pas_discretisation));

        // Incr�menter le compteur de votes pour cette droite
        accumulateur[{indice_m, indice_b}]++;
    }

    // Construire le vecteur de droites � partir de l'accumulateur
    std::vector<Droite> liste_droites;

    for (const auto& element : accumulateur) {
        int indice_m = element.first.first;
        int indice_b = element.first.second;
        int score = element.second;

        double m = indice_m * pas_discretisation;
        double b = indice_b * pas_discretisation;

        // Cr�er la droite et l'ajouter � la liste
        Droite d = { m, b, score };
        liste_droites.push_back(d);
    }

    return liste_droites;
}
