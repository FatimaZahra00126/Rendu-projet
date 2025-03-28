#include <iostream>
#include "lecteur_ppm.h"
#include "ecriture_ppm.h"
#include "conversion_binaire.h"
#include "hough_polaire.h"
#include "extraction_pixels.h"

int main() {
    // 1. Charger l’image PPM
    Image image = lire_image_ppm("imgTresSimple.ppm");

    // 2. Convertir en image binaire (noir/blanc)
    Image binaire = convertir_en_binaire(image, 128);
    ecrire_image_ppm(binaire, "image_binaire_polaire.ppm");

    // 3. Initialiser Hough polaire
    double pas_theta = 0.05;
    double pas_rho = 1.0;
    HoughPolaire hough = initialiser_hough_polaire(image.largeur, image.hauteur, pas_theta, pas_rho);

    // 4. Remplir l’accumulateur
    remplir_accumulateur_polaire(hough, binaire);

    // 5. Afficher les droites ayant un seuil minimal de votes
    int seuil_votes = 1;
    std::cout << "\n---- Droites detectees (methode polaire) ----\n";
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
