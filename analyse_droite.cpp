#include "analyse_droite.h"
#include <cmath>

// Fonction qui compte le nombre de pixels blancs situés sur une droite donnée dans une image binaire
int compter_pixels_blancs_sur_droite(double m, double b, const Image& image_binaire) {
    int nb = 0; // Compteur de pixels blancs sur la droite

    // Cas 1 : pente |m| <= 1 → on parcourt l'image horizontalement (plus stable)
    if (std::abs(m) <= 1.0) {
        for (int x = 0; x < image_binaire.largeur; ++x) {
            // Calcul de y à partir de l'équation y = mx + b
            int y = static_cast<int>(std::round(m * x + b));

            // Vérification que y est dans les limites de l'image
            if (y >= 0 && y < image_binaire.hauteur) {
                // Récupération de la couleur du pixel (x, y)
                Couleur px = image_binaire.pixels[y][x];

                // Si le pixel est blanc (255, 255, 255), on incrémente le compteur
                if (px.r == 255 && px.g == 255 && px.b == 255) {
                    nb++;
                }
            }
        }
    }
    // Cas 2 : pente |m| > 1 → on parcourt l'image verticalement pour éviter les sauts de x
    else {
        for (int y = 0; y < image_binaire.hauteur; ++y) {
            // Calcul de x à partir de l'équation inversée : x = (y - b) / m
            int x = static_cast<int>(std::round((y - b) / m));

            // Vérification que x est dans les limites de l'image
            if (x >= 0 && x < image_binaire.largeur) {
                // Récupération de la couleur du pixel (x, y)
                Couleur px = image_binaire.pixels[y][x];

                // Si le pixel est blanc, on l'ajoute au compteur
                if (px.r == 255 && px.g == 255 && px.b == 255) {
                    nb++;
                }
            }
        }
    }

    return nb; // Retourne le nombre total de pixels blancs sur la droite
}
