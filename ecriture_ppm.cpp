#include "ecriture_ppm.h"
#include <fstream>
#include <iostream>

// Fonction pour ecrire une image au format PPM 
void ecrire_image_ppm(const Image& image, const std::string& nom_fichier) {
    // Ouverture du fichier en ecriture 
    std::ofstream fichier(nom_fichier);
    if (!fichier.is_open()) {
        std::cerr << "Erreur : impossible d ecrire dans le fichier " << nom_fichier << std::endl;
        return;
    }

    std::cout << "ecriture en cours ..." << std::endl;

    // ETAPE 1 : ecriture de l'en-tete du fichier PPM
    fichier << "P3\n"; // P3 indique qu'on ecrit une image en ASCII (et non binaire)
    fichier << image.largeur << " " << image.hauteur << "\n"; // dimensions de l'image
    fichier << image.valeur_max << "\n"; // valeur maximale pour les couleurs (ex : 255)

    // ETAPE 2 : ecriture des donnees de chaque pixel
    for (int y = 0; y < image.hauteur; ++y) {
        for (int x = 0; x < image.largeur; ++x) {
            Couleur pixel = image.pixels[y][x]; // Recuperation du pixel (x, y)

            // Affichage dans la console pour suivi/debug
            std::cout << "pixel = " << pixel.r << "," << pixel.g << "," << pixel.b << " ; " << std::endl;

            // Ecriture des trois composantes du pixel dans le fichier (une par ligne)
            fichier << pixel.r << "\n" << pixel.g << "\n" << pixel.b << "\n";
        }
        fichier << "\n"; // Retour a la ligne apres chaque ligne de pixels
    }

    // Fermeture du fichier
    fichier.close();
    std::cout << "Image enregistree dans : " << nom_fichier << std::endl;
}
