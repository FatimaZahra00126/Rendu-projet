#include <iostream>
#include "lecteur_ppm.h"
#include "ecriture_ppm.h"
#include "conversion_binaire.h"
#include "extraction_pixels.h"
#include "hough_naif.h"

int main() {
    // Chargement de l'image
    Image image = lire_image_ppm("imgTresSimple.ppm");

    // Conversion de l'image en binaire (noir et blanc)
    Image binaire = convertir_en_binaire(image, 128);
    ecrire_image_ppm(binaire, "image_binaire.ppm");

    // Initialisation de l'espace de Hough naïf
    double m_min = -5.0, m_max = 5.0, pas_m = 0.1, pas_b = 1.0;
    HoughNaif hough = initialiser_hough_naif(binaire, m_min, m_max, pas_m, pas_b);

    // Remplissage de l'accumulateur avec les pixels blancs de l'image
    remplir_accumulateur_naif(hough, binaire);

    // Affichage des droites détectées qui ont au moins 1 vote
    afficher_droites_significatives(hough, 1);

    return 0;
}
