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

    Point p;
    Image image;
    printf("\nlecture du fichier : %s\n",argv[1]);
    image=lire_fichier_image(argv[1]);
    Point pi;
    int xd,yd;
    char* nom_fichier;
    nom_fichier = argv[1];
    int i=0;
    while(nom_fichier[i]!='.'){
        i++;
    }
    nom_fichier[i+1]='e';
    nom_fichier[i+2]='p';
    nom_fichier[i+3]='s';
    int trace = atoi(argv[2]);
    
    printf("\nRecherche du pixel de depart\n");
    p=trouver_pixel_depart(image, set_point(1,1));
    printf("\nPixel de depart trouvé\n\n");
    Liste_Point l;
    l=creer_liste_Point_vide();
    printf("depart en x: %f y: %f\n",p.x,p.y);
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
    while(boucle){
        l = memoriser_position(&r,l);
        avancer(&r);
        nouvelle_orientation(&r,image);
        
        if((r.p.x == xd) && (r.p.y == yd) && (r.o == EST)){
            boucle = false;
        }
    }
    l = memoriser_position(&r,l);
    int compteur ;
    compteur = longueur_sequence(l);
    printf("Il y à %d segment(s) dans le contour.\n",compteur);

    eps_tache4(l, nom_fichier, image, trace);

}