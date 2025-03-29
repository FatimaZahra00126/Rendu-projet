#include "bresenham.h"
#include <cmath>
#include <algorithm>

void tracer_segment_bresenham(Image& image, int x1, int y1, int x2, int y2, Couleur couleur) {
    // Calcul des différences
    int dx = std::abs(x2 - x1);
    int dy = std::abs(y2 - y1);

    // Détermination du sens de progression
    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;

    int err = dx - dy;

    while (true) {
        // Vérifie que le point est dans l’image
        if (x1 >= 0 && x1 < image.largeur && y1 >= 0 && y1 < image.hauteur) {
            image.pixels[y1][x1] = couleur;
        }

        // Arrêt si on est arrivé
        if (x1 == x2 && y1 == y2) break;

        int e2 = 2 * err;
        if (e2 > -dy) { err -= dy; x1 += sx; }
        if (e2 < dx) { err += dx; y1 += sy; }
    }
}
