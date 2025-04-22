#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<math.h>
#include"contour.h"


Point trouver_pixel_depart(Image image, Point point_start){
    int x,y;
    x=largeur_image(image);
    y=hauteur_image(image);
    int i,j;
    i=point_start.y;
    for (j=point_start.x;j<=x;j++){
        if(get_pixel_image(image,j,i)==1){
            return set_point(j-1,i-1);
        }
    }
    for (i=point_start.y+1; i<=y;i++){
        for (j=1;j<=x;j++){
            if(get_pixel_image(image,j,i)==1){
                return set_point(j-1,i-1);
            }
        }
    }
    printf("erreur, pas de pixels noir\n");
    exit(1);
}


void avancer(robot *r){
    // printf("avance\n");
    Point p; 
    orientation o;
    o = r->o;
    p = r->p;
    switch (o){
        case NORD : 
            p = set_point(p.x,p.y - 1);
            break;
        case EST :
            p = set_point(p.x + 1,p.y);

            break;   
        case SUD :
            p = set_point(p.x,p.y + 1);
            break;
        case OUEST :
            p = set_point(p.x - 1, p.y);
            break;
    }
    r->p = p;
}

Liste_Point memoriser_position(robot *r, Liste_Point L){
    Point p;
    p = r->p;
    // printf("Le robots est en x: %f et y: %f\n",p.x,p.y);
    L = ajouter_element_liste_Point(L, p);
    return L;
}

void ecrire_orientation(orientation o){
    switch (o){
        case NORD :
            printf("Nord \n");
            break;
        case EST :
            printf("Est \n");
            break;
        case SUD :
            printf("Est \n");
            break;
        case OUEST :
            printf("Ouest \n");
            break;
        default : 
            printf("Erreur, verifier orientation. \n");
            break;
    }
}

void nouvelle_orientation(robot *r, Image image){
    Point p;
    orientation o;
    Pixel pixd,pixg;
    p = r->p;
    o = r->o;

    switch(o){
        case EST:
            pixd = get_pixel_image(image, p.x+1, p.y+1);
            pixg = get_pixel_image(image, p.x+1, p.y);
            break;
        case OUEST:
            pixd = get_pixel_image(image, p.x, p.y);
            pixg = get_pixel_image(image, p.x, p.y+1);
            break;
        case SUD:
            pixd = get_pixel_image(image, p.x, p.y+1);
            pixg = get_pixel_image(image, p.x+1, p.y+1);
            break;
        case NORD:
            pixd = get_pixel_image(image, p.x+1, p.y);
            pixg = get_pixel_image(image, p.x, p.y);
            break;
    }

    if(pixg == NOIR){
        switch(o){
        case EST:
            o = NORD;
            break;
        case OUEST:
            o = SUD;
            break;
        case SUD:
            o = EST;
            break;
        case NORD:
            o = OUEST;
            break;
        }
    }else if(pixd == BLANC ){
        switch(o){
        case EST:
            o = SUD;
            break;
        case OUEST:
            o = NORD;
            break;
        case SUD:
            o = OUEST;
            break;
        case NORD:
            o = EST;
            break;
        }
    }
    r->o = o;
}

int longueur_sequence(Liste_Point L){
	Cellule_Liste_Point *el=L.first;
	int i=0;
	while (el){		
		i=i+1;
		el = el->suiv;
    }
	return i-1;
}


bool image_vide(Image I) {
    for (int i = 0; i<=hauteur_image(I); i++){
        for (int j = 0; j<=largeur_image(I); j++){
            if (get_pixel_image(I,j,i) == NOIR ) {
                return false;
                break;
            }
        }
    }
    return true;
}

Image depart_image(Image I){
    Image Calque = creer_image(largeur_image(I), hauteur_image(I));
    for (int i = 0; i<=hauteur_image(I); i++){
        for (int j = 0; j<=largeur_image(I); j++){
            if (get_pixel_image(I,j,i) == NOIR && get_pixel_image(I,j,i-1)==BLANC) {
                set_pixel_image(Calque, j, i, NOIR);
            }
        }
    }
    // ecrire_image(Calque);
    return(Calque);
}

Liste_tableau_point creer_liste_tableau_vide(){
    Liste_tableau_point liste_tab = {0,NULL};
    return liste_tab;   
}

Cellule_Tableau_Point *creer_element_Tableau_Point(Tableau_Point v)
{
	Cellule_Tableau_Point *el;

    // printf("bbbs%lu\n",sizeof(Cellule_Tableau_Point));
	el = (Cellule_Tableau_Point *)malloc(sizeof(Cellule_Tableau_Point));
	if (el==NULL)
	{
		fprintf(stderr, "creer_element_Tableau_Point : allocation impossible\n");
		exit(-1);
	}
	el->data = v;
	el->suiv = NULL;
	return el;
}




Liste_tableau_point memoriser_contour(Liste_tableau_point liste_tab, Liste_Point liste ){
    Tableau_Point tab = sequence_points_liste_vers_tableau(liste);
    Cellule_Tableau_Point *cell;
    cell = creer_element_Tableau_Point(tab);
    cell->suiv = NULL;
    cell->data = tab;
    if(liste_tab.taille == 0){
        liste_tab.first = cell;
    }else{
        cell->suiv = liste_tab.first;
        liste_tab.first = cell;
    }
    liste_tab.taille ++;
    return liste_tab;
}

Liste_tableau_point trouver_contour_mul(Image image){
    Point p;
    Liste_Point l;
    int xd,yd;
    int nbr_contour = 0;
    Point point_start;
    point_start = set_point(1,1);
    Liste_tableau_point liste_tab = creer_liste_tableau_vide();
    l = creer_liste_Point_vide();
    Image copie = depart_image(image);
    printf("intitialisation valeur contour mul fini \n");

    while(!image_vide(copie)){
  
        // printf("contour n°%d\n",nbr_contour);
        
        nbr_contour++;
        l = creer_liste_Point_vide();
        p = trouver_pixel_depart(copie,point_start);
        point_start = p;
        // printf("point_start : %f %f\n",point_start.x,point_start.y);
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
        
    }
    return liste_tab;
}
