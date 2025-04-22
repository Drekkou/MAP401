#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"image.h"
#include"test_image.h"

int main(int argc, char** argv) {
    Image image;
    /*initialisation de l'image*/
    image = creer_image(10,10);
    /*appel de la fonction lire_fichier_image*/
    image = lire_fichier_image(argv[1]);

    /*affichage de l'image non modifié*/
    ecrire_image(image);

    Image image2;
    printf("\n\n");
    /*négation de l'image*/
    image2 = negatif_image(image);
    supprimer_image(&image);
    /*affichage de la négation de l'image*/
    ecrire_image(image2);

    supprimer_image(&image2);
}