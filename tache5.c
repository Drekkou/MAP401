#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<math.h>
#include"export_eps.h"


int main(int argc, char** argv){
    if(argc<3){
        printf("./tache4 <adresse fichier> <stroke = 0, fill = 1>\n");
        exit(1);
    }
    Image image;
    Point p;
    Liste_Point l;
    int xd,yd,i=0;
    int compteur=0,nbr_contour = 0;
    char* nom_fichier;
    Liste_tableau_point liste_tab = creer_liste_tableau_vide();

    printf("\nlecture du fichier : %s\n",argv[1]);
    image=lire_fichier_image(argv[1]);


    nom_fichier = argv[1];
    
    while(nom_fichier[i]!='.'){
        i++;
    }
    nom_fichier[i+1]='e';
    nom_fichier[i+2]='p';
    nom_fichier[i+3]='s';
    i=0;
    int trace = atoi(argv[2]);

    // Liste_Point liste_contour[10000];
    l = creer_liste_Point_vide();

    Image copie = depart_image(image);

    while(!image_vide(copie)){
        nbr_contour++;
        l = creer_liste_Point_vide();
        // printf("nouveau contour\n");
        p = trouver_pixel_depart(copie,set_point(1,1));
        // printf("depart en x: %f y: %f\n",p.x,p.y);

        xd = p.x;
        yd = p.y;

        orientation o=EST;
        bool boucle=true;
        robot r;
        r.p.x=xd;
        r.p.y=yd;
        r.o=o;   
        while(boucle){
            l = memoriser_position(&r,l);
            if(r.o == EST){
                set_pixel_image(copie, r.p.x+1, r.p.y+1, BLANC);
            }
            avancer(&r);
            nouvelle_orientation(&r,image);


            if((r.p.x == xd) && (r.p.y == yd) && (r.o == EST)){
                boucle = false;
            }
        }
        l = memoriser_position(&r,l);
        set_pixel_image(copie, r.p.x+1, r.p.y+1, BLANC);
        liste_tab = memoriser_contour(liste_tab, l);
        // printf("memorise \n");
        // printf("impression liste\n");
        // ecrire_contour(l);
        // liste_contour[i] = l;
        // i++;
        compteur = compteur + longueur_sequence(l);
        
    }
    printf("Nombre de segments : %d\n",compteur);
    printf("%d\n",liste_tab.first->data.taille);  
    eps(liste_tab,nom_fichier,image,trace);
    printf("Il y à %d contour(s) dans cette image.\n",nbr_contour);
    printf("fichier eps cree\n");
}