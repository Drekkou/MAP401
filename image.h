/****************************************************************************** 
  Interface du module image
******************************************************************************/

#include"geometrie2d.h"
#ifndef _IMAGE_H_
#define _IMAGE_H_

/* type booleen */
typedef char BOOL;
#define FALSE 0
#define TRUE  1

/* type entier positif */
#ifndef UINT
#define UINT unsigned int
#endif

/* macro affichant le message _m_ et s'arretant */
#ifndef ERREUR_FATALE
#define ERREUR_FATALE(_m_) \
{ \
fprintf(stderr, "%s\n", _m_); \
exit(1); \
}
#endif

/* 
 Type enum�r� Pixel �quivalent au char avec BLANC=0 et NOIR=1
 */
typedef enum {BLANC=0,NOIR=1} Pixel;


/* 
 Type Image
 */
typedef struct Image_
{
	UINT la_largeur_de_l_image; 
	UINT la_hauteur_de_l_image; 
	Pixel* pointeur_vers_le_tableau_de_pixels; 
} Image;

/*---- le type cellule de liste de point ----*/
typedef struct Cellule_Liste_Point_
{
	Point data;    /* donnee de l'element de liste */
	struct Cellule_Liste_Point_* suiv; /* pointeur sur l'element suivant */
} Cellule_Liste_Point;

/*---- le type liste de point ----*/
typedef struct Liste_Point_
{
	unsigned int taille;        /* nombre d'elements dans la liste */
	Cellule_Liste_Point *first; /* pointeur sur le premier element de la liste */
	Cellule_Liste_Point *last;  /* pointeur sur le dernier element de la liste */
	                       /* first = last = NULL et taille = 0 <=> liste vide */
} Liste_Point;

typedef Liste_Point Contour; /* type Contour = type Liste_Point */

/*---- le type tableau de point ----*/
typedef struct Tableau_Point_
{
	int taille; /* nombre d'elements dans le tableau */
	Point *tab;          /* (pointeur vers) le tableau des elements */
} Tableau_Point;

/*---- le type cellule de tableau de point ----*/
typedef struct Cellule_Tableau_Point_
{
	Tableau_Point data;    /* donnee de l'element de liste */
	struct Cellule_Tableau_Point_ *suiv; /* pointeur sur l'element suivant */
} Cellule_Tableau_Point;

/*---- le type liste de tableau de point ----*/
typedef struct liste_tableau_point_
{
   unsigned int taille;
   Cellule_Tableau_Point *first; 
} Liste_tableau_point;

/* cr�ation d'une image PBM de dimensions L x H avec tous les pixels blancs */
Image creer_image(UINT L, UINT H);

/* suppression de l'image I = *p_I */
void supprimer_image(Image *p_I);

/* renvoie la valeur du pixel (x,y) de l'image I
   si (x,y) est hors de l'image la fonction renvoie BLANC */
Pixel get_pixel_image(Image I, int x, int y);

/* change la valeur du pixel (x,y) de l'image I avec la valeur v
   si (x,y) est hors de l'image la fonction ne fait rien */
void set_pixel_image(Image I, int x, int y, Pixel v);

/* renvoie la largeur de l'image I */
UINT largeur_image(Image I);

/* renvoie la hauteur de l'image I */
UINT hauteur_image(Image I);

/* lire l'image dans le fichier nomm� nom_f
   s'il y a une erreur dans le fichier le programme s'arrete en affichant
   un message 
   version acceptant les fichiers avec 
   - ligne 1 : P1
   - zero, une ou plusieurs lignes commen�ant toutes par #
   - zero, un ou plusieurs s�parateurs
   - la largeur
   - un ou plusieurs s�parateurs
   - la hauteur
   - un ou plusieurs s�parateurs
   - les pixels de l'image
   */
Image lire_fichier_image(char *nom_f);

/* �crire l'image I � l'�cran */
void ecrire_image(Image I);

Image negatif_image(Image I);


Point set_point(double x,double y);

Point add_point(Point P1,Point P2);

Vecteur vect_bipoint(Point A,Point B);

/* calculer l'image "negatif" de l'image I */
/* l'image I n'est pas modifiee et */
/* la fonction renvoie l'image "negatif" de I */

Point set_point(double x, double y);

/* creer une cellule de liste avec l'element v 
   renvoie le pointeur sur la cellule de liste creee
   la fonction s'arrete si la creation n'a pas pu se faire */
Cellule_Liste_Point *creer_element_liste_Point(Point v);

/* creer une liste vide */
Liste_Point creer_liste_Point_vide();

/* ajouter l'element e en fin de la liste L, renvoie la liste L modifiee */
Liste_Point ajouter_element_liste_Point(Liste_Point L, Point e);

/* supprimer tous les elements de la liste, renvoie la liste L vide */
Liste_Point supprimer_liste_Point(Liste_Point L);

/* concatener L2 a la suite de L1, renvoie la liste L1 modifiee */
Liste_Point concatener_liste_Point(Liste_Point L1, Liste_Point L2);

/* si la liste est non vide, la fonction supprime le premier element de L 
   si la liste est vide, la fonction ne fait rien 
   la fonction renvoie la liste (eventuellement) modifiee */
Liste_Point supprimer_premier_element_liste_Point(Liste_Point L);

/* creer une sequence de points sous forme d'un tableau de points 
   a partir de la liste de points L */
Tableau_Point sequence_points_liste_vers_tableau(Liste_Point L);

/* ecrire le contour L a l'ecran 
   cette fonction montre un exemple de conversion d'une liste de points en
   tableau de points afin de pouvoir par la suite acceder aux elements d'une
   sequence de points par indice */
void ecrire_contour(Liste_Point L);

#endif /* _IMAGE_H_ */
