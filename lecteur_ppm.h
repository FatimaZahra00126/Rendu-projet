#ifndef LECTEUR_PPM_H
#define LECTEUR_PPM_H

#include <vector>
#include <string>

struct Couleur {
    int r, g, b;
};

struct Image {
    int largeur;
    int hauteur;
    int valeur_max;
    std::vector<std::vector<Couleur>> pixels;
};

Image lire_image_ppm(const std::string& nom_fichier);
void afficheImage(const Image& img);

#endif

