/****************************************************************************** 
  Implementation du module image_pbm
******************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"image.h"

/* macro donnant l'indice du pixel de coordonnees (_x,_y) de l'image _I 
   dans le tableau de pixels de l'image _I */
#define INDICE_PIXEL(_I,_x,_y) ((_x)-1)+(_I).la_largeur_de_l_image*((_y)-1)

/* creation d'une image PBM de dimensions L x H avec tous les pixels blancs */
Image creer_image(UINT L, UINT H)
{
	Image I;
	UINT i;
	
	I.la_largeur_de_l_image = L;
	I.la_hauteur_de_l_image = H;
	
	/* allocation dynamique d'un tableau de L*H Pixel*/
	I.pointeur_vers_le_tableau_de_pixels = (Pixel *)malloc(sizeof(Pixel)*L*H);
	
	/* test si le tableau a ete correctement alloue */
	if (I.pointeur_vers_le_tableau_de_pixels == (Pixel *)NULL)
	{
		ERREUR_FATALE("Impossible de creer une image");
	}
	
	/* remplir le tableau avec des pixels blancs */
	for (i=0; i<L*H; i++)
		I.pointeur_vers_le_tableau_de_pixels[i] = BLANC;
		
	return I;
}

/* suppression de l'image I = *p_I */
void supprimer_image(Image *p_I)
{
	free(p_I->pointeur_vers_le_tableau_de_pixels);
	p_I->la_largeur_de_l_image = 0;
	p_I->la_hauteur_de_l_image = 0;
}

/* renvoie la valeur du pixel (x,y) de l'image I
   si (x,y) est hors de l'image la fonction renvoie BLANC */
Pixel get_pixel_image(Image I, int x, int y)
{
	if (x<1 || x>I.la_largeur_de_l_image || y<1 || y>I.la_hauteur_de_l_image)
		return BLANC;
	return I.pointeur_vers_le_tableau_de_pixels[INDICE_PIXEL(I,x,y)];
}

/* change la valeur du pixel (x,y) de l'image I avec la valeur v
   si (x,y) est hors de l'image la fonction ne fait rien */
void set_pixel_image(Image I, int x, int y, Pixel v)
{
	if (x<1 || x>I.la_largeur_de_l_image || y<1 || y>I.la_hauteur_de_l_image)
		return;
	I.pointeur_vers_le_tableau_de_pixels[INDICE_PIXEL(I,x,y)] = v;
}

/* renvoie la largeur de l'image I */
UINT largeur_image(Image I)
{
	return I.la_largeur_de_l_image;
}

/* renvoie la hauteur de l'image I */
UINT hauteur_image(Image I)
{
	return I.la_hauteur_de_l_image;
}


/* lire l'image dans le fichier nomme nom_f
   s'il y a une erreur dans le fichier le programme s'arrete en affichant
   un message 
   version acceptant les fichiers avec 
   - ligne 1 : P1
   - zero, une ou plusieurs lignes commen�ant toutes par #
   - zero, un ou plusieurs separateurs
   - la largeur
   - un ou plusieurs separateurs
   - la hauteur
   - un ou plusieurs separateurs
   - les pixels de l'image
   */

/* teste si le fichier d'identificateur f debute par un en-tete
   valide pour un fichier PBM :
   - ligne 1 : P1
   - suivie de zero, une ou plusieurs lignes commen�ant toutes par #
   La fonction se termine correctement si le fichier est correct, 
   et le pointeur de fichier se trouve � la suite de l'entete.
   Sinon, l'execution du programme est arretee avec l'affichage d'un message
   d'erreur (appel � ERREUR_FATALE)
    */ 
void entete_fichier_pbm(FILE *f)
{
	char *ligne;
	size_t n;
	size_t l_ligne;

	/* se positionner en debut de fichier */
	fseek(f, 0, SEEK_SET);
	
	/* lecture et test de la ligne 1 */
	ligne = (char *)NULL;
	n = 0;
	l_ligne = getline(&ligne, &n, f);
	
	/* la ligne est correcte si et ssi 
	   cas - fichier cree sous Linux : ligne = {'P','1',10} 
	     soit une chaine de 3 caracteres (le dernier est le caractere nul) 
	   cas - fichier cree sous Windows : ligne = {'P','1',13, 10} 
	     soit une chaine de 4 caracteres (le dernier est le caractere nul) 
	   */
	if (l_ligne < 3)
	{
		ERREUR_FATALE("entete_fichier_pbm : ligne 1 incorrecte\n");
	}
	if ((ligne[0] != 'P') || (ligne[1] != '1'))
	{
		ERREUR_FATALE("entete_fichier_pbm : ligne 1 incorrecte\n");
	}
	free(ligne);
	
	/* lecture des eventuelles lignes commen�ant par # */
	BOOL boucle_ligne_commentaire = TRUE;
	do
	{
		/* tester d'abord la fin de fichier */
		if (feof(f))
		{
			ERREUR_FATALE("entete_fichier_pbm : fin fichier inattendue\n");
		}
		
		/* lire un caractere et tester par rapport � '#' */
		char c;
		fscanf(f, "%c", &c);
		if (c=='#')
		{
			/* lire le reste de la ligne */
			ligne = (char *)NULL;
			n = 0;
			l_ligne = getline(&ligne, &n, f);
			free(ligne);
		}
		else
		{
			/* reculer d'un caract�re dans f */
			fseek(f, -1, SEEK_CUR);
			boucle_ligne_commentaire = FALSE;
		}
	} while (boucle_ligne_commentaire);
	
}
  
/* lire l'image dans le fichier dont le nom est nom_f
   s'il y a une erreur dans le fichier le programme s'arrete en affichant
   un message */
Image lire_fichier_image(char *nom_f)
{
	FILE *f;
	UINT L,H;
	UINT x,y;
	int res_fscanf;
	Image I;
	
	/* ouverture du fichier nom_f en lecture */
	f = fopen(nom_f, "r");
	if (f == (FILE *)NULL)
	{
		ERREUR_FATALE("lire_fichier_image : ouverture du fichier impossible\n");
	}
	
	/* traitement de l'en-tete et arret en cas d'erreur */
	entete_fichier_pbm(f);
	
	/* lecture des dimensions */
	res_fscanf = fscanf(f, "%d", &L);
	if (res_fscanf != 1)
	{
		ERREUR_FATALE("lire_fichier_image : dimension L incorrecte\n");
	}
	res_fscanf = fscanf(f, "%d", &H);
	if (res_fscanf != 1)
	{
		ERREUR_FATALE("lire_fichier_image : dimension H incorrecte\n");
	}
	
	/* creation de l'image de dimensions L x H */
	I = creer_image(L,H);
	
	/* lecture des pixels du fichier 
	   seuls les caracteres '0' (BLANC) ou '1' (NOIR) 
	   doivent etre pris en compte */
	x = 1; y = 1;
	while (!feof(f) && y<=H)
	{
		char c;
		int res;
		
		/* lire un caractere en passant les caracteres differents de '0' et '1' */
		res = fscanf(f, "%c", &c);
		while (!feof(f) && !(c == '0' || c == '1'))
		{
			res = fscanf(f, "%c", &c);
		}
		if (!feof(f))
		{
			set_pixel_image(I,x,y,c=='1' ? NOIR : BLANC );
			x++;
			if (x>L)
			{
				x = 1; y++;
			}
		}
	}   
	
	/* fermeture du fichier */
	fclose(f);
	
	return I;
}

/* ecrire l'image I � l'ecran */
void ecrire_image(Image I)
{
	int largeur, hauteur;
	int i ,j ;
	Pixel v;
	largeur = largeur_image(I);
	hauteur = hauteur_image(I);

	for(j=1;j <= hauteur; j++){
		for(i=1;i <= largeur; i++){
			v = get_pixel_image(I,i,j);
			if(v==0){
				printf(".");
			}else{
				printf("#");
			}
		}
		printf("\n");
	}
}

/* creer et calculer l'image "negatif" de l'image I */
/* l'image I n'est pas modifiee par cette fonction */
/* la fonction renvoie l'image "negatif" de I */
Image negatif_image(Image I)
{
	int largeur, hauteur;
	int i ,j ;
	Pixel v;

	Image I2;
	largeur = largeur_image(I);
	hauteur = hauteur_image(I);
	I2 = creer_image(largeur,hauteur);

	for(j=1;j <= hauteur; j++){
		for(i=1;i <= largeur; i++){
			v = get_pixel_image(I,i,j);
			//printf("%u mhhh\n",v);
			set_pixel_image(I2,i,j,v==BLANC ? NOIR : BLANC );

			}
	}
	return I2;
}




/* creer une cellule de liste avec l'element v 
   renvoie le pointeur sur la cellule de liste creee
   la fonction s'arrete si la creation n'a pas pu se faire */
Cellule_Liste_Point *creer_element_liste_Point(Point v)
{
	Cellule_Liste_Point *el;
	el = (Cellule_Liste_Point *)malloc(sizeof(Cellule_Liste_Point));
	if (el==NULL)
	{
		fprintf(stderr, "creer_element_liste_Point : allocation impossible\n");
		exit(-1);
	}
	el->data = v;
	el->suiv = NULL;
	return el;
}
/* creer une liste vide */
Liste_Point creer_liste_Point_vide()
{
	Liste_Point L = {0, NULL, NULL};
	return L;
}

/* ajouter l'element e en fin de la liste L, renvoie la liste L modifiee */
Liste_Point ajouter_element_liste_Point(Liste_Point L, Point e)
{
	Cellule_Liste_Point *el;
	
	el = creer_element_liste_Point(e);
	if (L.taille == 0)
	{
		/* premier element de la liste */
		L.first = L.last = el;
	}
	else
	{
		L.last->suiv = el;
		L.last = el;
	}
	L.taille++;
	return L;
}

/* supprimer tous les elements de la liste, renvoie la liste L vide */
Liste_Point supprimer_liste_Point(Liste_Point L)
{
	Cellule_Liste_Point *el=L.first;
	
	while (el) 
	{		
		Cellule_Liste_Point *suiv=el->suiv;
		free(el);
		el = suiv;
	}
	L.first = L.last = NULL; L.taille = 0;
	return L;
}

/* concatener L2 a la suite de L1, renvoie la liste L1 modifiee */
Liste_Point concatener_liste_Point(Liste_Point L1, Liste_Point L2)
{
	/* cas o� l'une des deux listes est vide */
	if (L1.taille == 0) return L2; 
	if (L2.taille == 0) return L1;
	
	/* les deux listes sont non vides */
	L1.last->suiv = L2.first; /* lien entre L1.last et L2.first */
	L1.last = L2.last;        /* le dernier element de L1 est celui de L2 */
	L1.taille += L2.taille;   /* nouvelle taille pour L1 */
	return L1;
}

/* si la liste est non vide, la fonction supprime le premier element de L 
   si la liste est vide, la fonction ne fait rien 
   la fonction renvoie la liste (eventuellement) modifiee */
Liste_Point supprimer_premier_element_liste_Point(Liste_Point L)
{
	/* cas d'une liste L vide : ne rien faire */
	if (L.taille == 0) return L;
	
	Cellule_Liste_Point *e1=L.first;  /* pointeur vers le premier element  */ 
	Cellule_Liste_Point *e2=e1->suiv; /* pointeur vers le deuxieme element */ 
	
	/* supprimer l'element pointe par e1 */
	free(e1);
	
	/* mettre a jour la structure L */
	L.first = e2;
	if (e2 == NULL)    /* cas d'une liste L avec un seul element */
		L.last = NULL; /* --> la liste L devient une liste vide  */
	L.taille--;
	return L;
}


/* creer une sequence de points sous forme d'un tableau de points 
   a partir de la liste de points L */
Tableau_Point sequence_points_liste_vers_tableau(Liste_Point L)
{
	Tableau_Point T;
	
	/* taille de T = taille de L */
	T.taille = L.taille;
	
	/* allocation dynamique du tableau de Point */
	T.tab = malloc(sizeof(Point) * T.taille);
	if (T.tab == NULL)
	{
		/* allocation impossible : arret du programme avec un message */
		fprintf(stderr, "sequence_points_liste_vers_tableau : ");
		fprintf(stderr, " allocation impossible\n");
		exit(-1);
	}
	
	/* remplir le tableau de points T en parcourant la liste L */
	int k = 0; /* indice de l'element dans T.tab */
	Cellule_Liste_Point *el = L.first; /* pointeur sur l'element dans L */
	while (el) 
	{
		T.tab[k] = el->data;
		k++; /* incrementer k */
		el = el->suiv; /* passer a l'element suivant dans la liste chainee */
	}
	
	return T;
}

/* ecrire le contour L a l'ecran 
   cette fonction montre un exemple de conversion d'une liste de points en
   tableau de points afin de pouvoir par la suite acceder aux elements d'une
   sequence de points par indice */
void ecrire_contour(Liste_Point L)
{
	Tableau_Point TP = sequence_points_liste_vers_tableau(L);
	int k;
	int nP = TP.taille;
	
	printf("Contour avec %d points\n[", nP);
	for (k = 0; k < nP; k++)
	{	
		Point P = TP.tab[k]; /* recuperer le point d'indice k */
		printf(" (%5.1f,%5.1f)", P.x, P.y);
	} 
	printf("]\n");
	
	free(TP.tab); /* supprimer le tableau de point TP */
}