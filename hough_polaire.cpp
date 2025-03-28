#include "hough_polaire.h"
#include <cmath>
#include "extraction_pixels.h"  // Pour l'extration les pixels blancs

// Définition de M_PI (valeur de pi)
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// Fonction pour initialiser la structure HoughPolaire
HoughPolaire initialiser_hough_polaire(int largeur, int hauteur, double pas_theta, double pas_rho) {
    HoughPolaire hough;

    // Définition des bornes de theta (de 0 à pi pour couvrir toutes les orientations de droites)
    hough.theta_min = 0.0;
    hough.theta_max = M_PI;
    hough.pas_theta = pas_theta;

    // Calcul du nombre de divisions pour theta
    hough.nb_theta = static_cast<int>((hough.theta_max - hough.theta_min) / pas_theta) + 1;

    // Calcul de la diagonale de l'image (longueur maximale possible pour rho)
    double diag = std::sqrt(largeur * largeur + hauteur * hauteur);

    // Définition de l'intervalle pour rho (de -diag à +diag)
    hough.rho_min = -diag;
    hough.rho_max = diag;
    hough.pas_rho = pas_rho;

    // Calcul du nombre de divisions pour rho
    hough.nb_rho = static_cast<int>((hough.rho_max - hough.rho_min) / pas_rho) + 1;

    // Initialisation de la matrice accumulateur avec des zéros
    hough.accumulateur.resize(hough.nb_theta, std::vector<int>(hough.nb_rho, 0));

    return hough;
}

// Fonction de remplissage de l'accumulateur de Hough avec les pixels blancs de l'image binaire
void remplir_accumulateur_polaire(HoughPolaire& hough, const Image& image_binaire) {
    // Récupération des coordonnées (x, y) de tous les pixels blancs
    std::vector<std::pair<int, int>> pixels_blancs = extraire_pixels_blancs(image_binaire);

    // Parcours de chaque pixel blanc
    for (size_t k = 0; k < pixels_blancs.size(); ++k) {
        int x = pixels_blancs[k].first;
        int y = pixels_blancs[k].second;

        // Parcours de tous les angles theta discrets
        for (int i = 0; i < hough.nb_theta; ++i) {
            double theta = hough.theta_min + i * hough.pas_theta;

            // Calcul du rho correspondant à ce pixel pour cet angle
            double rho = x * std::cos(theta) + y * std::sin(theta);

            // Transformation de rho en indice j dans l'accumulateur
            int j = static_cast<int>((rho - hough.rho_min) / hough.pas_rho);

            // Vérification que j est dans les bornes de l'accumulateur
            if (j >= 0 && j < hough.nb_rho) {
                // Incrémentation du compteur pour ce couple (theta, rho)
                hough.accumulateur[i][j]++;
            }
        }
    }
}
