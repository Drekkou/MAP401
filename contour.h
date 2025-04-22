#include<stdbool.h>
#include"image.h"

typedef enum{SUD, EST, OUEST, NORD}orientation;

typedef struct robot_{
    Point p;
    orientation o;
}robot ;

robot init_robot();

//fait avancer le robot
void avancer(robot *r);


//mémorise et affiche la position du robot
Liste_Point memoriser_position(robot *r, Liste_Point L);


//calcule et modifie l'orienation du robot
void nouvelle_orientation(robot *r, Image image);



//trouve et renvoie le pixel de départ
Point trouver_pixel_depart(Image image, Point point_start);

//retourne la longueur de la sequence
int longueur_sequence(Liste_Point L);

//trouve et retire un point dans une liste de point 
//puis renvoie la liste de point modifiée
Liste_Point suppression_point_supp(Liste_Point liste, Point p);

Image depart_image(Image I);

bool image_vide(Image I);

Liste_tableau_point creer_liste_tableau_vide();

Cellule_Tableau_Point *creer_element_Tableau_Point(Tableau_Point v);

Liste_tableau_point memoriser_contour(Liste_tableau_point liste_tab, Liste_Point liste );

Liste_tableau_point trouver_contour_mul(Image image);