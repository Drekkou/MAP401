#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<math.h>
#include"simplification.h"

int nb_seg(Liste_tableau_point liste){
    int nb_seg = 0, i;
    Tableau_Point tab;
    Cellule_Tableau_Point *cell;

    cell = liste.first;
    for(i=0;i<liste.taille;i++){
        tab = cell->data;
        nb_seg += tab.taille;
        cell = cell->suiv;
    }
    return nb_seg;
}

void afficher_tableau_point(Tableau_Point L){
    int taille, i;
    Point *tab;
    tab = L.tab;
    taille = L.taille;
    for(i=0;i<taille;i++){
        printf("tab[%d] : %f %f\n",i,tab[i].x,tab[i].y);
    }
}

Tableau_Point concatenation(Tableau_Point L1, Tableau_Point L2){
    // printf("concaténation\n");
    Point *tab1, *tab2;
    int taille1, taille2,i;
    taille1 = L1.taille;
    taille2 = L2.taille;
    if(taille1 == 0) return L2;
    if(taille2 == 0) return L1;

    tab1 = L1.tab;
    
    tab2 = L2.tab;
    // printf("tab1\n");
    // afficher_tableau_point(L1);
    // printf("tab2\n");
    // afficher_tableau_point(L2);
    

    i=0;
    while(i<taille2){
        // printf("tab1[%d] : %f %f\n",taille1 + i,tab1[taille1 + i].x,tab1[taille1 + i].y);
        // printf("tab2[%d] : %f %f\n",i,tab2[i].x,tab2[i].y);
        tab1[taille1 -1  + i] = tab2[i];
        i++;
    }
    L1.taille = taille1 + taille2-1;

    return L1;
}

Tableau_Point simplification_douglas_peucker(Tableau_Point Tp, int j1, int j2, double d){
    Point s1,s2;
    Point *tab;
    Tableau_Point L, L1, L2;
    Liste_Point liste;
    int k, j;
    double dmax,dj;

    liste = creer_liste_Point_vide();
    tab = Tp.tab;
    s1 = tab[j1];
    s2 = tab[j2];

    
    dmax = 0;
    k = j1;
    for(j=j1+1;j<=j2;j++){
        dj = distance_point_seg(tab[j],s1,s2);
        if(dmax < dj){
            dmax = dj;
            k = j;
        }
    }

    
    if(dmax <= d){
        liste = ajouter_element_liste_Point(liste,s1);
        liste = ajouter_element_liste_Point(liste,s2);
        // printf("s1 : %f %f\n",s1.x,s1.y);
        // printf("s2 : %f %f\n",s2.x,s2.y);
        L = sequence_points_liste_vers_tableau(liste);
    }else{

        L1 = simplification_douglas_peucker(Tp, j1, k, d);
        L2 = simplification_douglas_peucker(Tp, k, j2, d);


        L = concatenation(L1,L2);
        // printf("post concatenation\n");
        // afficher_tableau_point(L);
    }

    return L;
}

Liste_bezier2 simplification_bezier_2(Tableau_Point Tp, int j1, int j2, double d){
    Point *tab;
    Liste_bezier2 L, L1, L2;
    bezier2 B;
    int k, j;
    double dmax,dj,ti,i,n;


    n= j2-j1;
    B = approx_bezier2(Tp, j1, j2);

    tab = Tp.tab;

    dmax = 0;
    k = j1;
    for(j=j1+1;j<j2;j++){
        i=j-j1;
        ti=i/n;
        dj = distance_point_bezier2(tab[j],B,ti);
        if(dmax < dj){
            dmax = dj;
            k = j;
        }
    }

    
    L = creer_liste_bezier2_vide();
    
    if(dmax <= d){
        L = ajouter_element_liste_bezier2(L,B);
    }else{

        L1 = simplification_bezier_2(Tp, j1, k, d);
        L2 = simplification_bezier_2(Tp, k, j2, d);


        L = concatener_liste_bezier2(L1,L2);
    }

    return L;
}

Liste_bezier3 simplification_bezier_3(Tableau_Point T, int j1, int j2, double d){
    bezier3 B3;
    Liste_bezier3 L, L1, L2;
    double dmax;
    int j, k;
    double n = j2-j1;

    B3 = approx_bezier3(T, j1, j2);
    dmax = 0;
    k = j1;
    

    for (j=j1+1;j<j2;j++) {

        double i = j - j1;
        double ti = i/n;
        double dj = distance_point_bezier3(T.tab[j],B3,ti);

        if (dmax < dj) {
            dmax = dj;
            k = j;
        }
    }


    L = creer_liste_bezier3_vide();
    L1 = creer_liste_bezier3_vide();
    L2 = creer_liste_bezier3_vide();
    // printf("Dmax : %lf\n",dmax);
    
    if (dmax <= d) {
        // printf("Plus petit\n");
        L = ajouter_element_liste_bezier3(L, B3);
    }
    else {
        // printf("Plus grand\n");
        L1 = simplification_bezier_3(T, j1, k, d);
        L2 = simplification_bezier_3(T, k, j2, d);

        L = concatener_liste_bezier3(L1, L2);
    }
    return L;
}