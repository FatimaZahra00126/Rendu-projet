#ifndef CONVERSION_BINAIRE_H
#define CONVERSION_BINAIRE_H

#include "lecteur_ppm.h"

Image convertir_en_binaire(const Image& image_entree, int seuil = 128);

#endif

