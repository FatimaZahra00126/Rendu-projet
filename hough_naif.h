#ifndef HOUGH_NAIF_H
#define HOUGH_NAIF_H

#include "lecteur_ppm.h"
#include <vector>

struct HoughNaif {
    double m_min;
    double m_max;
    double pas_m;
    double b_min;
    double b_max;
    double pas_b;
    int nb_m;
    int nb_b;
    std::vector<std::vector<int>> accumulateur;  // L'accumulateur pour stocker les votes
};

// Déclaration des fonctions
HoughNaif initialiser_hough_naif(const Image& image, double m_min, double m_max, double pas_m, double pas_b);
void remplir_accumulateur_naif(HoughNaif& hough, const Image& image_binaire);
void afficher_droites_significatives(const HoughNaif& hough, int seuil);
Image dessiner_droites_naives(const HoughNaif& hough, Image image, int seuil);

#endif
