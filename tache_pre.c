#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<math.h>
#include"tache_pre.h"

void tache6(char *nom_fichier_entrant, int mode, double d ){
    Liste_tableau_point liste_tab, liste_tab_s;
    Cellule_Tableau_Point *cell, *cell_s;
    Tableau_Point tab;
    int i, nb_segment;
    Image image;

    image = lire_fichier_image(nom_fichier_entrant);
    liste_tab.taille = 0;
    liste_tab = trouver_contour_mul(image);
    cell = liste_tab.first;
    nb_segment = nb_seg(liste_tab);
    nb_segment = 0;
    for(i=0;i<liste_tab.taille;i++){
        tab = simplification_douglas_peucker(cell->data,0,cell->data.taille-1,d);
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
    char nom_fichier_sortant;
    sprintf(&nom_fichier_sortant,"%s",nom_fichier_entrant);
    i=1;
    while((&nom_fichier_sortant)[i]!='.'){
        i++;
    }
    (&nom_fichier_sortant)[i] = '\0';
    printf("nom_fichier_entrant: %s\n",nom_fichier_entrant);
    sprintf(&nom_fichier_sortant,"%s-seg-%.1f.eps",nom_fichier_entrant,d);
    eps(liste_tab_s,&nom_fichier_sortant,image,mode);
    printf("fichier eps cree\n");
}


void tache7_1(char *nom_fichier_entrant, int mode, double d ){
    Liste_tableau_point  liste_tab;
    Cellule_Tableau_Point *cell;
    Liste_tableau_bezier2 liste_tab_s;
    Cellule_Tableau_Bezier2 *cell_s;
    Liste_bezier2 liste_be2;
    Tableau_Bezier2 tab;
    int i, nb_segment;
    Image image;

    image = lire_fichier_image(nom_fichier_entrant);
    liste_tab.taille = 0;
    liste_tab = trouver_contour_mul(image);
    cell = liste_tab.first;
    nb_segment = nb_seg(liste_tab);

    nb_segment = 0;
    for(i=0;i<liste_tab.taille;i++){
        liste_be2 = simplification_bezier_2(cell->data,0,cell->data.taille-1,d);
        // printf("sortie de simplification\n");
        tab = sequence_bezier2_liste_vers_tableau(liste_be2);
        // printf("tableau créer\n");
        // printf("taille tab post simplification n°%d: %d\n",i+1, tab.taille);
        nb_segment += tab.taille;
        cell_s = creer_element_Tableau_Bezier2(tab);
        // printf("elt tableau\n");
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
    printf("Nombre courbe post simplification totaux : %d \n",nb_segment-liste_tab.taille-1);
    char nom_fichier_sortant;
    sprintf(&nom_fichier_sortant,"%s",nom_fichier_entrant);
    i=1;
    while((&nom_fichier_sortant)[i]!='.'){
        i++;
    }
    (&nom_fichier_sortant)[i] = '\0';
    sprintf(&nom_fichier_sortant,"%s-b2-%.1f.eps",nom_fichier_entrant,d);
    // printf("nom_fichier sortie: %s\n",nom_fichier);
    eps_bezier2(liste_tab_s,&nom_fichier_sortant,image,mode);
    printf("fichier eps cree\n");
}

void tache7_2(char *nom_fichier_entrant, int mode, double d ){
    Liste_tableau_point  liste_tab;
    Cellule_Tableau_Point *cell;
    Liste_tableau_bezier2 liste_tab_s;
    Cellule_Tableau_Bezier2 *cell_s;
    Liste_bezier2 liste_be2;
    Tableau_Bezier2 tab;
    int i, nb_segment;
    Image image;

    image = lire_fichier_image(nom_fichier_entrant);
    liste_tab.taille = 0;
    liste_tab = trouver_contour_mul(image);
    cell = liste_tab.first;
    nb_segment = nb_seg(liste_tab);

    nb_segment = 0;
    for(i=0;i<liste_tab.taille;i++){
        liste_be2 = simplification_bezier_2(cell->data,0,cell->data.taille-1,d);
        // printf("sortie de simplification\n");
        tab = sequence_bezier2_liste_vers_tableau(liste_be2);
        // printf("tableau créer\n");
        // printf("taille tab post simplification n°%d: %d\n",i+1, tab.taille);
        nb_segment += tab.taille;
        cell_s = creer_element_Tableau_Bezier2(tab);
        // printf("elt tableau\n");
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
    printf("Nombre courbe post simplification totaux : %d \n",nb_segment-liste_tab.taille-1);
    char nom_fichier_sortant;
    sprintf(&nom_fichier_sortant,"%s",nom_fichier_entrant);
    i=1;
    while((&nom_fichier_sortant)[i]!='.'){
        i++;
    }
    (&nom_fichier_sortant)[i] = '\0';
    sprintf(&nom_fichier_sortant,"%s-b3-%.1f.eps",nom_fichier_entrant,d);
    // printf("nom_fichier sortie: %s\n",nom_fichier);
    eps_bezier2(liste_tab_s,&nom_fichier_sortant,image,mode);
    printf("fichier eps cree\n");
}
