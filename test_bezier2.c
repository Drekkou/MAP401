#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<math.h>
#include"simplification.h"



int main(int argc, char** argv){
    Tableau_Point Tp;
    Liste_Point liste;
    Point c0, c1, c2;
    bezier2 sortie, entree;
    double n, i;
    double in;

    c0.x = 1;
    c0.y = 1;
    c2.x = 2;
    c2.y = 2;

    liste = creer_liste_Point_vide();
    liste = ajouter_element_liste_Point(liste, c0);
    liste = ajouter_element_liste_Point(liste, c2);

    Tp = sequence_points_liste_vers_tableau(liste);
    
    printf("\nQuestion 1.1 a)\n");
    printf("Test de approx_bezier quand n = 1 avec P0 = %f %f et P1 = %f %f\n",c0.x,c0.y,c2.x,c2.y);
    sortie = approx_bezier2(Tp,0,1);
    printf("On à comme sortie: C0 = %f %f, C1 = %f %f, C2 = %f %f\n",sortie.c0.x,sortie.c0.y,sortie.c1.x,sortie.c1.y,sortie.c2.x,sortie.c2.y);

    c0.x = 1;
    c0.y = 1;
    c1.x = 1.5;
    c1.y = 1.5;
    c2.x = 2;
    c2.y = 2;

    entree.c0 = c0;
    entree.c1 = c1;
    entree.c2 = c2;
    printf("\nQuestion 1.1 b)\n");
    printf("Quelle valeur de n voulez-vous? \n");
    scanf("%lf",&n);
    liste = supprimer_liste_Point(liste);
    liste = ajouter_element_liste_Point(liste, c0);
    for (i=0; i<=n; i++){
        in = i/n;
        // printf("%f\n",in);   
        liste = ajouter_element_liste_Point(liste, (calcul_point_bezier_2(entree,in)));
    }
    sortie = approx_bezier2(sequence_points_liste_vers_tableau(liste),0,n+1);
    printf("On à comme sortie: C0 = %f %f, C1 = %f %f, C2 = %f %f\n",sortie.c0.x,sortie.c0.y,sortie.c1.x,sortie.c1.y,sortie.c2.x,sortie.c2.y);


    
    printf("\nQuestion 1.1 c)\n");
    //en vrai c'est presque artistique
    Point p0,p1,p2,p3,p4,p5,p6,p7,p8;
    p0 = set_point(0,0);
    p1 = set_point(1,0);
    p2 = set_point(1,1);
    p3 = set_point(1,2);
    p4 = set_point(2,2);
    p5 = set_point(3,2);
    p6 = set_point(3,3);
    p7 = set_point(4,3);
    p8 = set_point(5,3);

    liste = supprimer_liste_Point(liste);
    liste = ajouter_element_liste_Point(liste, p0);
    liste = ajouter_element_liste_Point(liste, p1);
    liste = ajouter_element_liste_Point(liste, p2);
    liste = ajouter_element_liste_Point(liste, p3);
    liste = ajouter_element_liste_Point(liste, p4);
    liste = ajouter_element_liste_Point(liste, p5);
    liste = ajouter_element_liste_Point(liste, p6);
    liste = ajouter_element_liste_Point(liste, p7);
    liste = ajouter_element_liste_Point(liste, p8);

    
    sortie = approx_bezier2(sequence_points_liste_vers_tableau(liste),0,8);
    
    printf("On à comme sortie: C0 = %f %f, C1 = %f %f, C2 = %f %f\n",sortie.c0.x,sortie.c0.y,sortie.c1.x,sortie.c1.y,sortie.c2.x,sortie.c2.y);

    bezier2 b2;
    bezier3 b3;
    b2.c0=set_point(0,0);
    b2.c1=set_point(6,6);
    b2.c2=set_point(12,12);
    b3=convertion_bezier2_3(b2);
    printf("On à comme sortie bezier3: C0 = %f %f, C1 = %f %f, C2 = %f %f C3 =%f %f\n",b3.c0.x,b3.c0.y,b3.c1.x,b3.c1.y,b3.c2.x,b3.c2.y,b3.c3.x,b3.c3.y);

}
