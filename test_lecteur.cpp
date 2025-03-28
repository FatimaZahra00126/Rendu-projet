#include "lecteur_ppm.h"
#include <iostream>

int main() {
    Image mon_image = lire_image_ppm("imgTresSimple.ppm");

    std::cout << "Image lue : " << mon_image.largeur << " x " << mon_image.hauteur << std::endl;
    std::cout << "Valeur max : " << mon_image.valeur_max << std::endl;

    return 0;
}
