#ifndef DESSIN_DROITE_ALEATOIRE_H
#define DESSIN_DROITE_ALEATOIRE_H

#include "lecteur_ppm.h"
#include "hough_aleatoire.h"
#include <vector>

// Fonction pour dessiner les droites détectées par la méthode aléatoire
Image dessiner_droites_aleatoires(const std::vector<Droite>& liste_droites, const Image& image_originale, int seuil_votes);

#endif
