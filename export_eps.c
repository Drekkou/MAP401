#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<math.h>
#include"export_eps.h"

void eps_tache4(Liste_Point l, char* nom_fichier, Image image,int trace){
    FILE* f;
    f = fopen(nom_fichier, "w");
    int xmax,ymax;
    int i, x, y;
    Point actuel;
    Cellule_Liste_Point *cell;
    int longueur_sequence = l.taille;
    xmax = largeur_image(image);
    ymax = hauteur_image(image);

    fprintf(f,"%c!PS-Adobe-3.0 EPSF-3.0\n",'%');
    fprintf(f,"%c%cBoundingBox: 0 0 %d %d\n",'%','%',xmax,ymax);

    cell = l.first;
    actuel = cell->data;
    x = actuel.x;
    y = actuel.y;
    fprintf(f,"%d %d moveto\n",x,ymax-y);
    for(i=0;i<longueur_sequence;i++){
        actuel = cell->data;
        x = actuel.x;
        y = actuel.y;
        fprintf(f,"%d %d lineto\n",x,ymax-y);
        cell = cell->suiv;
    }
    if(trace){
        fprintf(f,"0.1 setlinewidth stroke\n");
    }else{
        fprintf(f,"fill\n");
    }
    fprintf(f,"showpage\n");
}

void eps(Liste_tableau_point l, char* nom_fichier, Image image,int trace){
    FILE* f;
    printf("nom_fichier sortie: %s\n",nom_fichier);
    f = fopen(nom_fichier, "w");
    int xmax,ymax;
    int i, x, y, longueur_tab;
    Point *tab;
    Cellule_Tableau_Point *cell_tab;
    Tableau_Point *cell;
    cell_tab=l.first;
    
    xmax = largeur_image(image);
    ymax = hauteur_image(image);
    fprintf(f,"%c!PS-Adobe-3.0 EPSF-3.0\n",'%');
    fprintf(f,"%c%cBoundingBox: 0 0 %d %d\n",'%','%',xmax,ymax);

    while(cell_tab!=NULL){
        cell=&cell_tab->data;
        tab = cell->tab;
        x = tab[0].x;
        y = tab[0].y;
        fprintf(f,"%d %d moveto\n",x,ymax-y);
        longueur_tab = cell->taille;
        tab = cell->tab;
        for(i=0;i<longueur_tab;i++){
            x = tab[i].x;
            y = tab[i].y;
            fprintf(f,"%d %d lineto\n",x,ymax-y);
        }
        cell_tab = cell_tab->suiv;
    }
    if(trace){
        fprintf(f,"0.1 setlinewidth stroke\n");
    }else{
        fprintf(f,"fill\n");
    }
    fprintf(f,"showpage\n");
}

void eps_bezier2(Liste_tableau_bezier2 l, char* nom_fichier, Image image,int trace){
    FILE* f;
    printf("adresse fichier de sortie: ./%s\n",nom_fichier);
    f = fopen(nom_fichier, "w");
    bezier3 b3;
    Point c1, c2, c3;
    int xmax,ymax;
    int i, x, y, longueur_tab;
    bezier2 *tab;
    Cellule_Tableau_Bezier2 *cell_tab;
    Tableau_Bezier2 *cell;
    cell_tab = l.first;
    
    xmax = largeur_image(image);
    ymax = hauteur_image(image);

    fprintf(f,"%c!PS-Adobe-3.0 EPSF-3.0\n",'%');
    fprintf(f,"%c%cBoundingBox: 0 0 %d %d\n",'%','%',xmax,ymax);

    while(cell_tab!=NULL){
        cell = &cell_tab->data;
        tab = cell->tab;
        x = tab[0].c0.x;
        y = tab[0].c0.y;
        fprintf(f,"%d %d moveto\n",x,ymax-y);
        longueur_tab = cell->taille;
        tab = cell->tab;
        for(i=0;i<longueur_tab;i++){
            b3 = convertion_bezier2_3(tab[i]);
            c1 = b3.c1;
            c2 = b3.c2;
            c3 = b3.c3;
            fprintf(f,"%f %f %f %f %f %f curveto\n",c1.x,ymax-c1.y,c2.x,ymax-c2.y,c3.x,ymax-c3.y);
        }
        cell_tab = cell_tab->suiv;
    }
    if(trace){
        fprintf(f,"0.1 setlinewidth stroke\n");
    }else{
        fprintf(f,"fill\n");
    }
    fprintf(f,"showpage\n");
}

void eps_bezier3(Liste_tableau_bezier3 l, char* nom_fichier, Image image,int trace){
    FILE* f;
    printf("adresse fichier de sortie: %s\n",nom_fichier);
    f = fopen(nom_fichier, "w");
    bezier3 b3;
    Point c1, c2, c3;
    int xmax,ymax;
    int i, x, y, longueur_tab;
    bezier3 *tab;
    Cellule_Tableau_bezier3 *cell_tab;
    Tableau_bezier3 *cell;
    cell_tab = l.first;
    
    xmax = largeur_image(image);
    ymax = hauteur_image(image);

    fprintf(f,"%c!PS-Adobe-3.0 EPSF-3.0\n",'%');
    fprintf(f,"%c%cBoundingBox: 0 0 %d %d\n",'%','%',xmax,ymax);

    while(cell_tab!=NULL){
        cell = &cell_tab->data;
        tab = cell->tab;
        x = tab[0].c0.x;
        y = tab[0].c0.y;
        fprintf(f,"%d %d moveto\n",x,ymax-y);
        longueur_tab = cell->taille;
        tab = cell->tab;
        for(i=0;i<longueur_tab;i++){
            b3 = tab[i];
            c1 = b3.c1;
            c2 = b3.c2;
            c3 = b3.c3;
            fprintf(f,"%f %f %f %f %f %f curveto\n",c1.x,ymax-c1.y,c2.x,ymax-c2.y,c3.x,ymax-c3.y);
        }
        cell_tab = cell_tab->suiv;
    }
    if(trace){
        fprintf(f,"0.1 setlinewidth stroke\n");
    }else{
        fprintf(f,"fill\n");
    }
    fprintf(f,"showpage\n");
}