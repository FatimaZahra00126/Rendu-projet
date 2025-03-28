#include <iostream>
#include "lecteur_ppm.h"
#include "ecriture_ppm.h"
#include "conversion_binaire.h"

int main() {
    // Étape 1 : Lire une image couleur
    Image image_couleur = lire_image_ppm("imgTresSimple.ppm");

    // Étape 2 : Appliquer la conversion binaire avec un seuil (ex. : 128)
    int seuil = 128;
    Image image_binaire = convertir_en_binaire(image_couleur, seuil);

    // Étape 3 : Sauvegarder l’image binaire
    ecrire_image_ppm(image_binaire, "image_binaire.ppm");

    std::cout << "Conversion binaire terminée. Résultat enregistré dans 'image_binaire.ppm'" << std::endl;

    return 0;
}
