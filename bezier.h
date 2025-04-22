#include<stdbool.h>
#include"contour.h"
/*

Debut déclaration strucutre de donnee bezier degre 2

*/
/*Type bezier2*/
typedef struct bezier2_ {
    Point c0;
    Point c1;
    Point c2;
} bezier2;

/*---- le type cellule de liste de bezier2 ----*/
typedef struct Cellule_Liste_bezier2_
{
	bezier2 data;    /* donnee de l'element de liste */
	struct Cellule_Liste_bezier2_* suiv; /* pointeur sur l'element suivant */
} Cellule_Liste_bezier2;

/*---- le type liste de bezier2 ----*/
typedef struct Liste_bezier2_
{
	unsigned int taille;        /* nombre d'elements dans la liste */
	Cellule_Liste_bezier2 *first; /* pointeur sur le premier element de la liste */
	Cellule_Liste_bezier2 *last;  /* pointeur sur le dernier element de la liste */
	                       /* first = last = NULL et taille = 0 <=> liste vide */
} Liste_bezier2;

/*---- le type tableau de bezier2 ----*/
typedef struct Tableau_Bezier2_
{
	int taille; /* nombre d'elements dans le tableau */
	bezier2 *tab;          /* (pointeur vers) le tableau des elements */
} Tableau_Bezier2;

/*---- le type cellule de tableau de bezier2 ----*/
typedef struct Cellule_Tableau_Bezier2_
{
	Tableau_Bezier2 data;    /* donnee de l'element de liste */
	struct Cellule_Tableau_Bezier2_ *suiv; /* pointeur sur l'element suivant */
} Cellule_Tableau_Bezier2;

/*---- le type liste de tableau de bezier 2 ----*/
typedef struct liste_tableau_bezier2_
{
   unsigned int taille;
   Cellule_Tableau_Bezier2 *first; 
} Liste_tableau_bezier2;


/*


Debut déclaration strucutre de donnee bezier degre 3


*/


typedef struct bezier3_ {
   Point c0;
   Point c1;
   Point c2;
   Point c3;
} bezier3;

/*---- le type cellule de liste de bezier3 ----*/
typedef struct Cellule_Liste_bezier3_
{
	bezier3 data;    /* donnee de l'element de liste */
	struct Cellule_Liste_bezier3_* suiv; /* pointeur sur l'element suivant */
} Cellule_Liste_bezier3;

/*---- le type liste de bezier3 ----*/
typedef struct Liste_bezier3_
{
	unsigned int taille;        /* nombre d'elements dans la liste */
	Cellule_Liste_bezier3 *first; /* pointeur sur le premier element de la liste */
	Cellule_Liste_bezier3 *last;  /* pointeur sur le dernier element de la liste */
	                       /* first = last = NULL et taille = 0 <=> liste vide */
} Liste_bezier3;

/*---- le type tableau de bezier3 ----*/
typedef struct Tableau_bezier3_
{
	int taille; /* nombre d'elements dans le tableau */
	bezier3 *tab;          /* (pointeur vers) le tableau des elements */
} Tableau_bezier3;

/*---- le type cellule de tableau de bezier3 ----*/
typedef struct Cellule_Tableau_bezier3_
{
	Tableau_bezier3 data;    /* donnee de l'element de liste */
	struct Cellule_Tableau_bezier3_ *suiv; /* pointeur sur l'element suivant */
} Cellule_Tableau_bezier3;

/*---- le type liste de tableau de bezier3 ----*/
typedef struct liste_tableau_bezier3_
{
   unsigned int taille;
   Cellule_Tableau_bezier3 *first; 
} Liste_tableau_bezier3;


/*


Debut declaration fonction bezier 2


*/


/* creer une cellule de liste avec l'element v 
   renvoie le pointeur sur la cellule de liste creee
   la fonction s'arrete si la creation n'a pas pu se faire */
Cellule_Liste_bezier2 *creer_element_liste_bezier2(bezier2 v);

/* creer une liste vide */
Liste_bezier2 creer_liste_bezier2_vide();

/* ajouter l'element e en fin de la liste L, renvoie la liste L modifiee */
Liste_bezier2 ajouter_element_liste_bezier2(Liste_bezier2 L, bezier2 e);

/* supprimer tous les elements de la liste, renvoie la liste L vide */
Liste_bezier2 supprimer_liste_bezier2(Liste_bezier2 L);

/* concatener L2 a la suite de L1, renvoie la liste L1 modifiee */
Liste_bezier2 concatener_liste_bezier2(Liste_bezier2 L1, Liste_bezier2 L2);

/* si la liste est non vide, la fonction supprime le premier element de L 
   si la liste est vide, la fonction ne fait rien 
   la fonction renvoie la liste (eventuellement) modifiee */
Liste_bezier2 supprimer_premier_element_liste_bezier2(Liste_bezier2 L);


/* creer une sequence de bezier2 sous forme d'un tableau de bezier2 
   a partir de la liste de bezier2 L */
Tableau_Bezier2 sequence_bezier2_liste_vers_tableau(Liste_bezier2 L);


Cellule_Tableau_Bezier2 *creer_element_Tableau_Bezier2(Tableau_Bezier2 v);


/*


Debut declaration fonction bezier 3


*/


/* creer une cellule de liste avec l'element v 
renvoie le pointeur sur la cellule de liste creee
la fonction s'arrete si la creation n'a pas pu se faire */
Cellule_Liste_bezier3 *creer_element_liste_bezier3(bezier3 v);

/* creer une liste vide */
Liste_bezier3 creer_liste_bezier3_vide();

/* ajouter l'element e en fin de la liste L, renvoie la liste L modifiee */
Liste_bezier3 ajouter_element_liste_bezier3(Liste_bezier3 L, bezier3 e);

/* supprimer tous les elements de la liste, renvoie la liste L vide */
Liste_bezier3 supprimer_liste_bezier3(Liste_bezier3 L);

/* concatener L2 a la suite de L1, renvoie la liste L1 modifiee */
Liste_bezier3 concatener_liste_bezier3(Liste_bezier3 L1, Liste_bezier3 L2);

/* si la liste est non vide, la fonction supprime le premier element de L 
   si la liste est vide, la fonction ne fait rien 
   la fonction renvoie la liste (eventuellement) modifiee */
Liste_bezier3 supprimer_premier_element_liste_bezier3(Liste_bezier3 L);


/* creer une sequence de bezier3 sous forme d'un tableau de bezier3 
   a partir de la liste de bezier3 L */
Tableau_bezier3 sequence_bezier3_liste_vers_tableau(Liste_bezier3 L);

Cellule_Tableau_bezier3 *creer_element_Tableau_bezier3(Tableau_bezier3 v);

Liste_tableau_bezier3 trouver_contour_mul_bezier3(Image image);


/*


Debut declaration fonction calcul sur bezier 2 et bezier 3


*/

Point calcul_point_bezier_2(bezier2 b2, double t);

Point calcul_point_bezier_3(bezier3 b3, double t);

bezier3 convertion_bezier2_3(bezier2);

bezier2 approx_bezier2(Tableau_Point tab, int j1, int j2);

double distance_point_bezier2(Point P, bezier2 b2,double ti);

double distance_point_bezier3(Point P, bezier3 b3,double ti);

/*Calcul de la valeur de lambda en fonction de k et de n */
double fonction_lambda(double k, double n);

/*Approximation d'une ligne polygonale par une courbe de Bezier de degre 3*/
bezier3 approx_bezier3(Tableau_Point Tp, int j1, int j2);

