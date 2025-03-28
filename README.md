# Projet INFO802 : Détection de Droites avec la Transformation de Hough

Ce projet implémente la **transformée de Hough** qui est une technique utilisée pour détecter des formes géométriques dans des images, en particulier les lignes droites. Le code permet de lire une image en format **PPM**, de la convertir en binaire puis d'appliquer la transformée de Hough pour détecter les lignes. Il fournit également des outils pour enregistrer les résultats sous forme de nouvelles images.

## Description du projet

Le but de ce projet est de montrer comment appliquer la transformée de Hough sur une image en format **PPM**. Il est composé de plusieurs étapes :
- **Lecture d’une image PPM** avec la structure appropriée pour les couleurs.
- **Conversion de l’image en binaire** à l’aide d’un seuil.
- **Application de la transformée de Hough** pour détecter les lignes dans l’image binaire.
- **Visualisation des résultats** : l’image transformée est ensuite enregistrée et peut être visualisée.

Le projet comprend également des outils de **gestion de version** avec **Git**.

Durant ce projet, nous allons appliquer 2 types de méthodes: 
- **méthode naive**:
  - détection de droite à partir de l'équation *y = mx + b* et conversion dans l'espace de Hough
  - utilisation d'un accumulateur pour détecter les intersections dznd l'espace de Hough

- **méthode moins naive**:
  - utilisation de l'équation polaire y = -(cos(theta)/sin(theta))x + rho/sin(theta), permettant une meilleure gestion des droites
  - visualisation de la sinusoidale dans l'espace de Hough pour chaque pixel du contour. 

## Fonctionnalités principales

- **Lecture d’image PPM** : Chargement d’une image avec la gestion des en-têtes, commentaires et pixels RGB (rouge-vert-bleu).
- **Conversion binaire** : Conversion des pixels d’une image en binaire selon un seuil de gris.
- **Transformée de Hough** :
  - **Méthode naïve** : Utilisation d’un espace d’accumulation pour détecter les lignes droites dans l’image.
  - **Méthode polaire** : Détection de lignes dans un espace polaire en utilisant les paramètres `rho` et `theta`.
- **Sauvegarde des résultats** : Enregistrement de l'image traitée dans un nouveau fichier PPM.

## Structure du projet

Le projet est organisé de la manière suivante :

- `lecteur_ppm.h` et `lecteur_ppm.cpp` : Fonction pour lire une image en format PPM.
  - définition des structures (couleur et image)
  - lire_image_ppm(): ouvre et lit l'image au format PPM; ignore les commentaires et extrait la largeur/hauteur/valeur maximale; stocke les pixels dans une matrice
  - afficheImage(): affiche les pixels de l'image sous forme de valeurs RGB pour effecteur la vérification
- `conversion_binaire.h` et `conversion_binaire.cpp` : Fonction pour convertir une image en binaire à l’aide d’un seuil.
  - convertir_en_binaire(): convertit chaque pixel en niveau de gris (Formule niveau de gris : 0.299R + 0.587G + 0.114B)
  - application d'un seuil (Noir (0,0,0) si valeur < seuil et Blanc (255,255,255) sinon)
  - retourne l'image binaire 
- `ecriture_ppm.h` et `ecriture_ppm.cpp` : Fonction pour écrire une image en format PPM.
  - vérifie si le fichier peut être ouvert avant
  - écrit de l'en-tête avec la largeur/hauteur/valeur maximale des pixels
  - parcourt des pixels et écriture des valeurs RGB dans le fichier
  - affichage d'un message de confirmation une fois l'image enregistrée
- `hough_naif.h` et `hough_naif.cpp` : Implémentation d’une approche naïve de la transformée de Hough pour détecter les lignes.
  - initialisation de la transformée de Hough
  - création d'un accumulateur (une matrice) pour stocker les votes des droites détectées
  - parcourt des pixels blancs de l'image binaire pour identifier les points d'intérêt
  - calcul des paramètres de la droite pour chaque pixel blanc et incrémentation de l'accumulateur en conséquence
  - Attention, on ignore les pixels noirs
  - vérification que les valeurs calculées restent dans les bornes définies pour éviter les erreurs d'accès à l'accumulateur 
- `hough_polaire.h` et `hough_polaire.cpp` : Implémentation de la transformée de Hough dans l’espace polaire pour détecter les lignes.
  - définition des plages de theta et rho puis initialisation de l'accumulateur
  - remplissage de l'accumulateur (calcul de rho et theta pour chaque pixel et mise à jour de l'accumulateur)
  - affichage des droites détectées (droites dont le nombre de votes dans l'accumulateur dépasse le seuil donné)

### Fichiers principaux

- **lecteur_ppm.h / lecteur_ppm.cpp** : Ces fichiers contiennent les fonctions pour lire une image en format PPM et stocker ses informations dans une structure.
- **conversion_binaire.h / conversion_binaire.cpp** : Ces fichiers définissent la fonction qui convertit l'image en niveaux de gris en une image binaire (noir et blanc) selon un seuil de gris.
- **ecriture_ppm.h / ecriture_ppm.cpp** : Ces fichiers contiennent la fonction pour sauvegarder l’image résultante dans un fichier PPM.
- **hough_naif.h / hough_naif.cpp** : Implémentation de l'algorithme de la transformée de Hough. Ce fichier inclut des fonctions pour initialiser l’espace d’accumulation et y insérer les données issues des pixels de l’image binaire.
- **hough_polaire.h / hough_polaire.cpp** : Implémentation de l’algorithme de la transformée de Hough dans l’espace polaire. Ce fichier inclut des fonctions pour initialiser l’accumulateur polaire, y insérer les données des pixels blancs et afficher les lignes détectées avec un certain seuil de votes.

### Ajout : Extraction et Dessin des Droites

Le projet inclut également des fonctionnalités pour extraire les pixels blancs d’une image binaire et dessiner les droites détectées par la transformée de Hough :

- **Dessin des droites naïves** :
  - Sélection des 10 droites ayant le plus de votes.
  - Tri des droites détectées par leur nombre de votes décroissant.
  - Traçage des droites détectées sur l’image originale en rouge.

- **Dessin des droites dans l’espace polaire** :

  - Détection des droites avec un accumulateur polaire.
  - Dessin des lignes sur l’image d’entrée.

- **Extraction des pixels blancs** :

  - Lecture d’une image binaire pour récupérer les coordonnées des pixels blancs.
  - Stockage des points sous forme de paires `(x, y)`.

Ces fonctionnalités sont implémentées dans les fichiers suivants :

- `dessin_droite.h` et `dessin_droite.cpp` : Contiennent les fonctions permettant de dessiner les droites détectées.

- `extraction_pixels.h` et `extraction_pixels.cpp` : Définissent les fonctions permettant d’extraire les pixels blancs d’une image binaire.

## Difficultés rencontrées 

- gestion de Git puisque c'était un nouvel outil pour nous
- problèmes de coordination des fichiers entre nous avec VisualStudio Code et VisualStudio
- perte de temps sur la gestion des codes (nous avancions mais nous ne testions pas toujours)
- manque de temps dans la conception de notre projet pour finaliser

## Perspective : Détection de Cercles
Bien que ce projet se concentre principalement sur la détection de droites, il est également possible d'étendre l’algorithme pour tenter de détecter des formes circulaires. En ajustant la transformée de Hough pour travailler avec des cercles plutôt qu’avec des lignes, on peut détecter des arcs ou des cercles dans une image en utilisant des paramètres spécifiques à cette forme.

## Cas d'Utilisation
Ce projet peut être appliqué dans différents domaines où la détection de droites est nécessaire, tels que :
- **Navigation autonome** : Utilisation pour détecter des routes ou des lignes sur la route pour la conduite autonome.
- **Analyse d'images satellites** : Détection des infrastructures linéaires comme les routes, les chemins de fer, ou les réseaux électriques.
- **Vision industrielle** : Identification des défauts dans des matériaux ou produits fabriqués à l’aide de la détection des bords.
- **Analyse d’architecture** : Détection de lignes et de bords dans des images d’architectures ou de plans de bâtiments.

## Optimisation et Performances
Le projet a été optimisé pour traiter des images de tailles variées. Toutefois, il est important de noter que la complexité de la transformée de Hough peut augmenter considérablement avec la taille de l'image et la résolution de l'accumulateur. Des techniques d'optimisation supplémentaires pourraient être explorées pour améliorer les performances sur de grandes images.

## Dépendances et Configuration
Ce projet utilise les outils suivants :
- **C++**
- **Bibliothèque Standard C++**
- **Python** pour avoir transformé les images PPM en JPG (programme directement trouvé sur internet)


