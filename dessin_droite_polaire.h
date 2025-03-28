#ifndef DESSIN_DROITE_POLAIRE_H
#define DESSIN_DROITE_POLAIRE_H

#include "hough_polaire.h"
#include "lecteur_ppm.h"

Image dessiner_droites_polaire(const HoughPolaire& hough, Image image, int seuil);

#endif
