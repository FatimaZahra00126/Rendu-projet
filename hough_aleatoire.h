#ifndef HOUGH_ALEATOIRE_H
#define HOUGH_ALEATOIRE_H

#include "lecteur_ppm.h"
#include <vector>
#include <map>

// Structure représentant une droite détectée
struct Droite {
    double m;       // pente
    double b;       // ordonnée à l'origine
    int votes;      // nombre de votes reçus
};

// Fonction de détection de droites par échantillonnage aléatoire
std::vector<Droite> detecter_droites_aleatoirement(const Image& image_binaire, int nb_iterations_max, double pas_discretisation);

#endif
