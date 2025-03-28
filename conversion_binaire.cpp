#include "conversion_binaire.h" // Inclusion de l'en-tête contenant la définition de la fonction et des structures nécessaires

// Fonction pour convertir une image en noir et blanc (binaire) à partir d'un seuil
Image convertir_en_binaire(const Image& image_entree, int seuil) {
    Image image_sortie; // Déclaration de l'image de sortie (résultat de la conversion)

    // Copie des métadonnées de l'image (dimensions et valeur maximale)
    image_sortie.largeur = image_entree.largeur;
    image_sortie.hauteur = image_entree.hauteur;
    image_sortie.valeur_max = image_entree.valeur_max;

    // Redimensionnement du vecteur de pixels pour correspondre à la taille de l'image
    image_sortie.pixels.resize(
        image_sortie.hauteur,
        std::vector<Couleur>(image_sortie.largeur)
    );

    // Parcours de tous les pixels de l'image d'entrée
    for (int y = 0; y < image_entree.hauteur; ++y) {
        for (int x = 0; x < image_entree.largeur; ++x) {
            Couleur pixel = image_entree.pixels[y][x]; // Récupère le pixel à la position (x, y)

            // Conversion du pixel en niveaux de gris avec la formule de luminance
            int gris = static_cast<int>(0.299 * pixel.r + 0.587 * pixel.g + 0.114 * pixel.b);

            // Seuil : si la valeur de gris est inférieure au seuil, on met du noir ; sinon, du blanc
            if (gris < seuil) {
                image_sortie.pixels[y][x] = { 0, 0, 0 };       // Pixel noir
            }
            else {
                image_sortie.pixels[y][x] = { 255, 255, 255 }; // Pixel blanc
            }
        }
    }

    // On retourne l'image binaire obtenue
    return image_sortie;
}
