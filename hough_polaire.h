#ifndef HOUGH_POLAIRE_H
#define HOUGH_POLAIRE_H

#include <vector>
#include "lecteur_ppm.h"

struct HoughPolaire {
    int nb_theta;
    int nb_rho;
    double theta_min;
    double theta_max;
    double pas_theta;
    double rho_min;
    double rho_max;
    double pas_rho;
    std::vector<std::vector<int>> accumulateur;
};

HoughPolaire initialiser_hough_polaire(int largeur, int hauteur, double pas_theta, double pas_rho);
void remplir_accumulateur_polaire(HoughPolaire& hough, const Image& image_binaire);

#endif
