#ifndef FILTRAGE_DROITES_H
#define FILTRAGE_DROITES_H

#include "hough_aleatoire.h"
#include <vector>

// Filtre les droites proches entre elles (selon tolérances sur m et b)
std::vector<Droite> filtrer_droites_proches(const std::vector<Droite>& liste_droites,
    double epsilon_m, double epsilon_b);

#endif

