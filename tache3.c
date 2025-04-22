#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<math.h>
#include"contour.h"

int main(int argc, char** argv){
    if(argc<2){
        printf("./tache3 <adresse fichier>\n");
        exit(1);
    }
    Point p;
    Image image;
    printf("\nlecture du fichier : %s\n",argv[1]);
    image=lire_fichier_image(argv[1]);
    Point pi;
    int xd,yd;
    
    printf("\nRecherche du pixel de depart\n");
    p = trouver_pixel_depart(image, set_point(1,1));
    printf("\nPixel de depart trouvé\n\n");
    Liste_Point l;
    l=creer_liste_Point_vide();
    pi.x=p.x;
    pi.y=p.y;
    xd = pi.x;
    yd = pi.y;
    orientation o=EST;
    bool boucle=true;
    robot r;
    r.p.x=pi.x;
    r.p.y=pi.y;
    r.o=o;
    ecrire_image(image);    
    printf("\n\nDebut de la boucle\n\n");
    while(boucle){
        l = memoriser_position(&r,l);
        avancer(&r);
        nouvelle_orientation(&r,image);
        
        // boucle=false;
        if((r.p.x == xd) && (r.p.y == yd) && (r.o == EST)){
            boucle = false;
        }
    }
    printf("\n\nFin de la boucle \n");
    l = memoriser_position(&r,l);
    int compteur ;
    compteur = longueur_sequence(l);
    printf("Il y à %d segment(s) dans le contour.\n",compteur);

}