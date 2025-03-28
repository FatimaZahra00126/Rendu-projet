#ifndef HOUGH_ALEATOIRE_H
#define HOUGH_ALEATOIRE_H

#include "lecteur_ppm.h"
#include <vector>
#include <map>

// Structure repr�sentant une droite d�tect�e
struct Droite {
    double m;       // pente
    double b;       // ordonn�e � l'origine
    int votes;      // nombre de votes re�us
};

// Fonction de d�tection de droites par �chantillonnage al�atoire
std::vector<Droite> detecter_droites_aleatoirement(const Image& image_binaire, int nb_iterations_max, double pas_discretisation);

#endif
