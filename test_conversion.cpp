#include <iostream>
#include "lecteur_ppm.h"
#include "ecriture_ppm.h"
#include "conversion_binaire.h"

int main() {
    // chargement de l'image couleur
    Image image_couleur = lire_image_ppm("imgTresSimple.ppm");

    // conversion en binaire avec un seuil de 128
    int seuil = 128;
    Image image_binaire = convertir_en_binaire(image_couleur, seuil);

    // sauvegarde de l'image binaire
    ecrire_image_ppm(image_binaire, "image_binaire.ppm");

    std::cout << "Conversion binaire terminee. Resultat enregistre dans 'image_binaire.ppm'" << std::endl;

    return 0;
}
