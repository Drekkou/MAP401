#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<math.h>
#include"export_eps.h"


int main(int argc, char** argv){
    if(argc<4){
        printf("./tache6 <adresse fichier> <stroke = 0, fill = 1> <distance seuil d>\n");
        exit(1);
    }
    Liste_tableau_point liste_tab, liste_tab_s;
    Cellule_Tableau_Point *cell, *cell_s;
    Tableau_Point tab;
    int i, nb_segment;
    Image image;
    char* nom_fichier;

    image = lire_fichier_image(argv[1]);
    liste_tab.taille = 0;
    liste_tab = trouver_contour_mul(image);
    cell = liste_tab.first;
    nb_segment = nb_seg(liste_tab);

    printf("Nombre segments post simplification totaux : %d \n",nb_segment-liste_tab.taille);
    nb_segment = 0;
    for(i=0;i<liste_tab.taille;i++){
        tab = simplification_douglas_peucker(cell->data,0,cell->data.taille-1,atof(argv[3]));
        // printf("taille tab post simplification n°%d: %d\n",i+1, tab.taille);
        nb_segment += tab.taille;
        cell_s = creer_element_Tableau_Point(tab);
        cell_s->suiv = NULL;
        cell_s->data = tab;
        if(liste_tab_s.taille == 0){
            liste_tab_s.first = cell_s;
            liste_tab_s.taille ++;
        }else{
            cell_s->suiv = liste_tab_s.first;
            liste_tab_s.first = cell_s;
            liste_tab_s.taille ++;
        }
        

        cell = cell->suiv;
    }
    printf("Nombre de contour : %d\n",liste_tab.taille);
    printf("Nombre segments post simplification totaux : %d \n",nb_segment-liste_tab.taille-1);
    nom_fichier = argv[1];
    i=1;
    while(nom_fichier[i]!='.'){
        i++;
    }
    nom_fichier[i+1]='e';
    nom_fichier[i+2]='p';
    nom_fichier[i+3]='s';
    i=0;
    // printf("nom_fichier sortie: %s\n",nom_fichier);
    eps(liste_tab_s,nom_fichier,image,atoi(argv[2]));
    printf("fichier eps cree\n");
}