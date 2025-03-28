#include "lecteur_ppm.h"
#include "ecriture_ppm.h"
#include "bresenham.h"
#include <iostream>

int main() {
    // === Étape 1 : Lire une image existante ===
    std::string nom_image_entree = "imageM1.ppm";
    Image image = lire_image_ppm(nom_image_entree);

    // === Étape 2 : Choisir une couleur ===
    Couleur rouge = { 255, 0, 0 };

    // === Étape 3 : Tracer quelques segments par Bresenham ===
    tracer_segment_bresenham(image, 0, 0, image.largeur - 1, 0, rouge);             // Bord haut
    tracer_segment_bresenham(image, 0, 0, 0, image.hauteur - 1, rouge);             // Bord gauche
    tracer_segment_bresenham(image, 0, image.hauteur - 1, image.largeur - 1, 0, rouge); // Diagonale montante
    tracer_segment_bresenham(image, 0, 0, image.largeur - 1, image.hauteur - 1, rouge); // Diagonale descendante

    // === Étape 4 : Enregistrer le résultat ===
    std::string nom_image_sortie = "image_test_bresenham.ppm";
    ecrire_image_ppm(image, nom_image_sortie);

    std::cout << "Image modifiée enregistrée : " << nom_image_sortie << std::endl;

    return 0;
}
