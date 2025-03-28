#include <iostream>
#include "lecteur_ppm.h"
#include "ecriture_ppm.h"
#include "conversion_binaire.h"
#include "extraction_pixels.h"
#include "hough_naif.h"

int main() {
    // Étape 1 : Lire l’image
    Image image = lire_image_ppm("imgTresSimple.ppm");

    // Étape 2 : Conversion en binaire
    Image binaire = convertir_en_binaire(image, 128);
    ecrire_image_ppm(binaire, "image_binaire.ppm");

    // Étape 3 : Initialiser l’espace de Hough naïf
    double m_min = -5.0, m_max = 5.0, pas_m = 0.1, pas_b = 1.0;
    HoughNaif hough = initialiser_hough_naif(binaire, m_min, m_max, pas_m, pas_b);

    // Étape 4 : Remplir l’accumulateur avec les pixels blancs
    remplir_accumulateur_naif(hough, binaire);

    // Étape 5 : Afficher les droites détectées (si elles ont au moins 1 vote)
    afficher_droites_significatives(hough, 1);

    return 0;
}
