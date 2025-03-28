#include <iostream>
#include "lecteur_ppm.h"
#include "ecriture_ppm.h"
#include "conversion_binaire.h"
#include "hough_polaire.h"
#include "extraction_pixels.h"
#include "dessin_droite_polaire.h"

int main() {
    // Chargement de l'image d'origine
    Image image = lire_image_ppm("img4-ab.ppm");

    // Conversion en noir et blanc
    Image binaire = convertir_en_binaire(image, 128);
    ecrire_image_ppm(binaire, "image_binaire_polaire.ppm");

    // Initialisation de la transformée de Hough en mode polaire
    double pas_theta = 0.05;
    double pas_rho = 1.0;
    HoughPolaire hough = initialiser_hough_polaire(image.largeur, image.hauteur, pas_theta, pas_rho);

    // Remplissage de l'accumulateur
    remplir_accumulateur_polaire(hough, binaire);

    // Détection des droites avec un seuil de votes
    int seuil_votes = 2;
    Image image_droites = dessiner_droites_polaire(hough, image, seuil_votes);

    // Sauvegarde de l'image avec les droites tracées
    ecrire_image_ppm(image_droites, "image_droites_polaire.ppm");

    std::cout << "Image avec droites tracees (polaire) enregistree.\n";

    return 0;
}
