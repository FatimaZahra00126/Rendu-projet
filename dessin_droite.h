#ifndef DESSIN_DROITE_H
#define DESSIN_DROITE_H

#include "hough_naif.h"
#include "lecteur_ppm.h"

Image dessiner_droites_naives(const HoughNaif& hough, Image image, int seuil);

#endif
