#ifndef EXTRAIRE_PIXELS_BLANCS_H
#define EXTRAIRE_PIXELS_BLANCS_H

#include "lecteur_ppm.h"
#include <vector>

std::vector<std::pair<int, int>> extraire_pixels_blancs(const Image& image_binaire);

#endif
