#include "dessin_droite_aleatoire.h"
#include <cmath>
#include "lecteur_ppm.h" // Pour la structure Image
#include "hough_aleatoire.h" // Pour la structure Droite

// Fonction pour dessiner les droites détectées aléatoirement sur une copie de l'image
Image dessiner_droites_aleatoires(const std::vector<Droite>& liste_droites, const Image& image_originale, int seuil_votes) {
    // Créer une copie de l'image pour y dessiner les droites
    Image image_modifiee = image_originale;

    Couleur rouge = { 255, 0, 0 };

    for (const Droite& d : liste_droites) {
        if (d.votes < seuil_votes) continue;

        double m = d.m;
        double b = d.b;

        if (std::abs(m) <= 1.0) {
            // Si la pente est faible, on parcourt les colonnes x
            for (int x = 0; x < image_modifiee.largeur; ++x) {
                int y = static_cast<int>(std::round(m * x + b));
                if (y >= 0 && y < image_modifiee.hauteur) {
                    image_modifiee.pixels[y][x] = rouge;
                }
            }
        }
        else {
            // Si la pente est forte, on parcourt les lignes y
            for (int y = 0; y < image_modifiee.hauteur; ++y) {
                int x = static_cast<int>(std::round((y - b) / m));
                if (x >= 0 && x < image_modifiee.largeur) {
                    image_modifiee.pixels[y][x] = rouge;
                }
            }
        }
    }

    return image_modifiee;
}
