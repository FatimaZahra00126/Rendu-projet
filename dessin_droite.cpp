#include "dessin_droite.h"
#include <cmath>
#include <vector>
#include <tuple>
#include <algorithm>
#include "analyse_droite.h" // pour utiliser la fonction de comptage

Image dessiner_droites_naives(const HoughNaif& hough, Image image, int seuil) {
    Couleur rouge = { 255, 0, 0 };

    // Étape 1 : collecter toutes les droites avec votes >= seuil
    std::vector<std::tuple<double, double, int>> droites; // (m, b, votes)

    for (int i = 0; i < hough.nb_m; ++i) {
        for (int j = 0; j < hough.nb_b; ++j) {
            int votes = hough.accumulateur[i][j];
            if (votes >= seuil) {
                double m = hough.m_min + i * hough.pas_m;
                double b = hough.b_min + j * hough.pas_b;
                droites.emplace_back(m, b, votes);
            }
        }
    }

    // Étape 2 : trier les droites par nombre de votes décroissant
    std::sort(droites.begin(), droites.end(),
        [](const auto& a, const auto& b) {
            return std::get<2>(a) > std::get<2>(b);
        });

    // Étape 3 : définir un seuil intelligent selon la taille de l’image
    int taille_image = image.largeur * image.hauteur;
    int nb_max = droites.size(); // Par défaut, toutes les droites

    if (taille_image >= 90) {
        nb_max = std::min(10, static_cast<int>(droites.size())); // Limite à 10 si image grande
    }

    // Étape 4 : tracer les droites sélectionnées
    for (int k = 0; k < nb_max; ++k) {
        double m = std::get<0>(droites[k]);
        double b = std::get<1>(droites[k]);

        // Ne dessine que si la droite traverse au moins 2 pixels blancs
        if (compter_pixels_blancs_sur_droite(m, b, image) < 1) {
            continue;
        }

        if (std::abs(m) <= 1.0) {
            for (int x = 0; x < image.largeur; ++x) {
                int y = static_cast<int>(std::round(m * x + b));
                if (y >= 0 && y < image.hauteur)
                    image.pixels[y][x] = rouge;
            }
        }
        else {
            for (int y = 0; y < image.hauteur; ++y) {
                int x = static_cast<int>(std::round((y - b) / m));
                if (x >= 0 && x < image.largeur)
                    image.pixels[y][x] = rouge;
            }
        }
    }

    return image;
}
