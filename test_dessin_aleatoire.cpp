#include <iostream>
#include "lecteur_ppm.h"
#include "ecriture_ppm.h"
#include "conversion_binaire.h"
#include "hough_aleatoire.h"
#include "dessin_droite_aleatoire.h"

int main() {
    // === �tape 1 : Lire l'image d'entr�e ===
    std::string nom_image_entree = "imageM1.ppm"; 
    Image image_originale = lire_image_ppm(nom_image_entree);

    // === �tape 2 : Convertir en noir et blanc (image binaire) ===
    int seuil_binarisation = 128;
    Image image_binaire = convertir_en_binaire(image_originale, seuil_binarisation);

    // === �tape 3 : D�tection des droites par m�thode al�atoire ===
    int nb_iterations = 10000;
    double pas_discretisation = 0.1;
    std::vector<Droite> droites = detecter_droites_aleatoirement(image_binaire, nb_iterations, pas_discretisation);

    std::cout << "Nombre de droites d�tect�es : " << droites.size() << std::endl;

    // === �tape 4 : Dessiner les droites sur une copie de l�image ===
    int seuil_votes = 30; // � ajuster selon ton image
    Image image_resultat = dessiner_droites_aleatoires(droites, image_originale, seuil_votes);

    // === �tape 5 : Sauvegarder l�image r�sultat ===
    std::string nom_image_sortie = "image_avec_droites_aleatoire.ppm";
    ecrire_image_ppm(image_resultat, nom_image_sortie);

    std::cout << "Image finale enregistree dans : " << nom_image_sortie << std::endl;

    return 0;
}
