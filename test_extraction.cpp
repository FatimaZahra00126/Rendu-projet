#include <iostream>
#include "lecteur_ppm.h"
#include "ecriture_ppm.h"
#include "conversion_binaire.h"

int main() {
    // Chargement de l’image couleur
    Image image_couleur = lire_image_ppm("imgTresSimple.ppm");

    // Conversion en binaire avec un seuil défini (ex. : 128)
    int seuil = 128;
    Image image_binaire = convertir_en_binaire(image_couleur, seuil);

    // Sauvegarde de l’image binaire
    ecrire_image_ppm(image_binaire, "image_binaire.ppm");

    std::cout << "Conversion terminée. Résultat enregistré dans 'image_binaire.ppm'." << std::endl;

    return 0;
}
