#include <iostream>
#include "lecteur_ppm.h"
#include "ecriture_ppm.h"
#include "conversion_binaire.h"
#include "extraction_pixels.h"
#include "hough_naif.h"
#include "dessin_droite.h"

int main() {
    // Chargement de l’image d’origine
    std::string nom_image = "imgTresSimple.ppm";  
    Image image = lire_image_ppm(nom_image);

    // Conversion en binaire avec un seuil
    int seuil_binarisation = 128;
    Image binaire = convertir_en_binaire(image, seuil_binarisation);
    ecrire_image_ppm(binaire, "image_binaire.ppm");

    // Initialisation de la transformée de Hough (méthode naïve)
    double m_min = -2.0, m_max = 2.0, pas_m = 0.05, pas_b = 0.5;
    HoughNaif hough = initialiser_hough_naif(binaire, m_min, m_max, pas_m, pas_b);

    // Remplissage de l’accumulateur
    remplir_accumulateur_naif(hough, binaire);

    // Détection et dessin des droites avec un seuil de votes
    int seuil_votes = 1;  // Peut être ajusté selon les besoins
    Image image_avec_droites = dessiner_droites_naives(hough, binaire, seuil_votes);

    // Sauvegarde de l’image avec les droites détectées
    std::string nom_image_resultat = "image_avec_droites.ppm";
    ecrire_image_ppm(image_avec_droites, nom_image_resultat);
    std::cout << "Image avec droites enregistrée dans : " << nom_image_resultat << "\n";

    // Affichage des droites détectées
    std::cout << "\n---- Droites détectées (votes >= " << seuil_votes << ") ----\n";
    for (int i = 0; i < hough.nb_m; ++i) {
        for (int j = 0; j < hough.nb_b; ++j) {
            int votes = hough.accumulateur[i][j];
            if (votes >= seuil_votes) {
                double m = hough.m_min + i * hough.pas_m;
                double b = hough.b_min + j * hough.pas_b;
                std::cout << "Droite : y = " << m << " * x + " << b << "   (" << votes << " votes)" << std::endl;
            }
        }
    }

    return 0;
}

