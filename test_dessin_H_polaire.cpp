#include <iostream>
#include "lecteur_ppm.h"
#include "ecriture_ppm.h"
#include "conversion_binaire.h"
#include "hough_polaire.h"
#include "extraction_pixels.h"
#include "dessin_droite_polaire.h"

int main() {
    // 1. Lire l'image originale
    Image image = lire_image_ppm("img4-ab.ppm");

    // 2. Convertir en image binaire (noir et blanc)
    Image binaire = convertir_en_binaire(image, 128);
    ecrire_image_ppm(binaire, "image_binaire_polaire.ppm");

    // 3. Initialiser Hough polaire
    double pas_theta = 0.05;
    double pas_rho = 1.0;
    HoughPolaire hough = initialiser_hough_polaire(image.largeur, image.hauteur, pas_theta, pas_rho);

    // 4. Remplir l'accumulateur
    remplir_accumulateur_polaire(hough, binaire);

    // 5. Dessiner les droites ayant au moins 2 votes (ou 1 pour test)
    int seuil_votes = 2;
    Image image_droites = dessiner_droites_polaire(hough, image, seuil_votes);

    // 6. Sauvegarder l'image avec les droites
    ecrire_image_ppm(image_droites, "image_droites_polaire.ppm");

    std::cout << "Image avec droites tracées (polaire) enregistrée.\n";

    return 0;
}
