#include "lecteur_ppm.h"           // Inclusion du fichier d'en-tête (où sont définies les structures Image et Couleur)
#include <fstream>                 // Pour lire un fichier
#include <sstream>                 // Pour manipuler les flux de texte (conversion de string ? int par ex.)
#include <iostream>                // Pour les entrées/sorties (cout, cerr…)
#include <array>                   // Pour utiliser des tableaux fixes (std::array)

// Fonction qui lit une image PPM (format P3) et la stocke dans une structure Image
Image lire_image_ppm(const std::string& imgTresSimple) {
    std::ifstream fichier(imgTresSimple);  // Ouvre le fichier en lecture
    Image image;                           // Crée une structure Image vide
    std::string ligne;                     // Chaîne temporaire pour lire chaque ligne

    // Vérifie que le fichier a bien été ouvert
    if (!fichier.is_open()) {
        std::cerr << "Erreur : impossible d’ouvrir le fichier " << imgTresSimple << std::endl;
        exit(1);  // Arrêt du programme en cas d’erreur
    }

    // Lire la première ligne non commentée contenant "P3"
    do {
        std::getline(fichier, ligne);     // Lecture d'une ligne
    } while (ligne[0] == '#');            // Ignorer les lignes de commentaire commençant par #

    std::istringstream flux_entete(ligne);  // Conversion de la ligne lue en flux
    std::string entete;
    flux_entete >> entete;

    std::cout << "entete = " << entete << std::endl;
    if (entete != "P3") {
        std::cerr << "Erreur : format non pris en charge (doit etre P3)." << std::endl;
        exit(1);
    }

    // Lire la largeur, hauteur et valeur maximale des couleurs
    int compteur = 0;
    int valeur[3] = { 0, 0, 0 };  // Stockage de la largeur, de la hauteur, et de la val_max

    while (compteur < 3 && std::getline(fichier, ligne)) {
        // Ignore les lignes vides ou les commentaires
        if (ligne.empty() || ligne[0] == '#') continue;

        std::istringstream flux(ligne);
        while (flux >> valeur[compteur]) {
            compteur++;
            if (compteur == 3) break;
        }
    }

    int largeur = valeur[0];
    int hauteur = valeur[1];
    int val_max = valeur[2];

    if (largeur <= 0 || hauteur <= 0) {
        std::cerr << "Erreur : largeur ou hauteur invalide (valeurs <= 0)." << std::endl;
        exit(1);
    }

    std::cout << "Image lue : " << largeur << " x " << hauteur << std::endl;
    std::cout << "Valeur max : " << val_max << std::endl;

    // Enregistrement des dimensions dans l'objet image
    image.largeur = largeur;
    image.hauteur = hauteur;
    image.valeur_max = val_max;

    // Initialisation de la grille de pixels avec des couleurs vides (0,0,0)
    image.pixels.resize(image.hauteur, std::vector<Couleur>(image.largeur));

    // Variables de lecture des pixels
    int x = 0, y = 0;
    int idxLigne = 0;
    std::array<int, 3> troisValeurs = { 0, 0, 0 };  // Pour stocker R, G, B

    // Lecture pixel par pixel
    while (std::getline(fichier, ligne)) {
        if (ligne.empty() || ligne[0] == '#') continue; // Ignore les lignes vides ou commentaires

        troisValeurs[idxLigne] = stoi(ligne);  // Convertit la ligne lue en entier
        if (idxLigne == 2) {
            idxLigne = 0;  // On a les trois valeurs (R, G, B)

            // Vérifie qu’on ne depasse pas les dimensions de l’image
            if (y >= image.hauteur) break;

            // Stockage du pixel dans la matrice
            image.pixels[y][x] = { troisValeurs[0], troisValeurs[1], troisValeurs[2] };
            x++;  // Avancer dans la ligne

            if (x >= image.largeur) {
                x = 0;
                y++;  // Passage à la ligne suivante
            }
        }
        else {
            idxLigne += 1;  // Passage à la composante suivante (G ou B)
        }
    }

    fichier.close();  // Ferme le fichier
    return image;     // Retourne la structure image complète
}

// Fonction d'affichage de l’image dans la console (en mode texte)
void afficheImage(const Image& img) {
    for (int i = 0; i < img.pixels.size(); ++i) {
        for (int j = 0; j < img.pixels[0].size(); ++j) {
            std::cout << img.pixels[i][j].r << "," << img.pixels[i][j].g << "," << img.pixels[i][j].b << " ";
        }
        std::cout << "\n";  // Nouvelle ligne après chaque ligne de pixels
    }
}
