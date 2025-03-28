#include <iostream>
#include "lecteur_ppm.h"
#include "ecriture_ppm.h"
#include "conversion_binaire.h"
#include "hough_polaire.h"
#include "extraction_pixels.h"

int main() {
    // Charger l'image PPM
    Image image = lire_image_ppm("imgTresSimple.ppm");

    // Convertir l'image en binaire (noir et blanc)
    Image binaire = convertir_en_binaire(image, 128);
    ecrire_image_ppm(binaire, "image_binaire_polaire.ppm");

    // Initialiser l'espace de Hough polaire
    double pas_theta = 0.05;
    double pas_rho = 1.0;
    HoughPolaire hough = initialiser_hough_polaire(image.largeur, image.hauteur, pas_theta, pas_rho);

    // Remplir l'accumulateur avec les données binaires
    remplir_accumulateur_polaire(hough, binaire);

    // Afficher les droites détectées avec un seuil minimal de votes
    int seuil_votes = 1;
    std::cout << "\n---- Droites détectées (méthode polaire) ----\n";
    for (int i = 0; i < hough.nb_theta; ++i) {
        for (int j = 0; j < hough.nb_rho; ++j) {
            if (hough.accumulateur[i][j] >= seuil_votes) {
                double theta = hough.theta_min + i * hough.pas_theta;
                double rho = hough.rho_min + j * hough.pas_rho;
                std::cout << "Droite : rho = " << rho << ", theta = " << theta
                    << " (" << hough.accumulateur[i][j] << " votes)" << std::endl;
            }
        }
    }

    return 0;
}
