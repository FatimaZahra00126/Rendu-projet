#ifndef BRESENHAM_H
#define BRESENHAM_H

#include "lecteur_ppm.h" // pour Image et Couleur

// Fonction qui trace un segment entre (x1, y1) et (x2, y2) avec l’algorithme de Bresenham
void tracer_segment_bresenham(Image& image, int x1, int y1, int x2, int y2, Couleur couleur);

#endif

