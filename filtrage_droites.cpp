#include "filtrage_droites.h"
#include <cmath>
#include <vector>
#include <algorithm>

// Fonction pour filtrer les droites trop proches (doublons ou variantes proches)
std::vector<Droite> filtrer_droites_proches(const std::vector<Droite>& liste_droites,
    double epsilon_m, double epsilon_b) {
    std::vector<Droite> resultat;

    // Copie locale triée par nombre de votes décroissant
    std::vector<Droite> tri = liste_droites;

    std::sort(tri.begin(), tri.end(), [](const Droite& d1, const Droite& d2) {
        return d1.votes > d2.votes;
        });

    for (const Droite& nouvelle : tri) {
        bool est_trop_proche = false;

        // Comparer avec les droites déjà gardées
        for (const Droite& gardee : resultat) {
            if (std::abs(nouvelle.m - gardee.m) < epsilon_m &&
                std::abs(nouvelle.b - gardee.b) < epsilon_b) {
                est_trop_proche = true;
                break;
            }
        }

        // Si elle est suffisamment différente, on l'ajoute
        if (!est_trop_proche) {
            resultat.push_back(nouvelle);
        }
    }

    return resultat;
}
