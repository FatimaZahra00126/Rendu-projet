#include <iostream>
#include "lecteur_ppm.h"
#include "ecriture_ppm.h"
#include "conversion_binaire.h"
#include "hough_aleatoire.h"
#include "dessin_droite_aleatoire.h"
#include "filtrage_droites.h"

int main() {
    // === �tape 1 : Lecture de l'image d'entr�e ===
    std::string nom_image_entree = "imageM1.ppm"; // Remplace par ton fichier r�el
    Image image_originale = lire_image_ppm(nom_image_entree);

    // === �tape 2 : Conversion en image binaire (noir et blanc) ===
    int seuil_binarisation = 128;
    Image image_binaire = convertir_en_binaire(image_originale, seuil_binarisation);

    // === �tape 3 : D�tection de droites par m�thode al�atoire ===
    int nb_iterations = 10000;
    double pas_discretisation = 0.1;
    std::vector<Droite> droites = detecter_droites_aleatoirement(image_binaire, nb_iterations, pas_discretisation);

    std::cout << "Nombre de droites d�tect�es avant filtrage : " << droites.size() << std::endl;

    // === �tape 4 : Filtrage des droites proches (doublons) ===
    double epsilon_m = 0.05; // tol�rance sur la pente
    double epsilon_b = 2.0;  // tol�rance sur l�ordonn�e � l�origine
    droites = filtrer_droites_proches(droites, epsilon_m, epsilon_b);

    std::cout << "Nombre de droites apr�s filtrage : " << droites.size() << std::endl;

    // === �tape 5 : Dessin des droites sur une copie de l'image originale ===
    int seuil_votes = 30; // seuil pour ne dessiner que les droites significatives
    Image image_resultat = dessiner_droites_aleatoires(droites, image_originale, seuil_votes);

    // === �tape 6 : Sauvegarde de l�image r�sultat ===
    std::string nom_image_sortie = "image_avec_droites_aleatoires.ppm";
    ecrire_image_ppm(image_resultat, nom_image_sortie);

    std::cout << "Image finale enregistr�e dans : " << nom_image_sortie << std::endl;

    return 0;
}
