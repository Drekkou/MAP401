#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<math.h>
#include"bezier.h"
#include <sys/resource.h>
#include <malloc.h>

/*

Debut declaration fonction bezier 2

*/


/* creer une cellule de liste avec l'element v 
   renvoie le pointeur sur la cellule de liste creee
   la fonction s'arrete si la creation n'a pas pu se faire */
Cellule_Liste_bezier2 *creer_element_liste_bezier2(bezier2 v){
	Cellule_Liste_bezier2 *el;
	el = (Cellule_Liste_bezier2 *)malloc(sizeof(Cellule_Liste_bezier2));
	if (el==NULL)
	{
		fprintf(stderr, "creer_element_liste_bezier2 : allocation impossible\n");
		exit(-1);
	}
	el->data = v;
	el->suiv = NULL;
	return el;
}

/* creer une liste vide */
Liste_bezier2 creer_liste_bezier2_vide(){
	Liste_bezier2 L = {0, NULL, NULL};
	return L;
}

/* ajouter l'element e en fin de la liste L, renvoie la liste L modifiee */
Liste_bezier2 ajouter_element_liste_bezier2(Liste_bezier2 L, bezier2 e){
	Cellule_Liste_bezier2 *el;
	
	el = creer_element_liste_bezier2(e);
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
Liste_bezier2 supprimer_liste_bezier2(Liste_bezier2 L){
	Cellule_Liste_bezier2 *el=L.first;
	
	while (el) 
	{		
		Cellule_Liste_bezier2 *suiv=el->suiv;
		free(el);
		el = suiv;
	}
	L.first = L.last = NULL; L.taille = 0;
	return L;
}

/* concatener L2 a la suite de L1, renvoie la liste L1 modifiee */
Liste_bezier2 concatener_liste_bezier2(Liste_bezier2 L1, Liste_bezier2 L2){
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
Liste_bezier2 supprimer_premier_element_liste_bezier2(Liste_bezier2 L){
	/* cas d'une liste L vide : ne rien faire */
	if (L.taille == 0) return L;
	
	Cellule_Liste_bezier2 *e1=L.first;  /* pointeur vers le premier element  */ 
	Cellule_Liste_bezier2 *e2=e1->suiv; /* pointeur vers le deuxieme element */ 
	
	/* supprimer l'element pointe par e1 */
	free(e1);
	
	/* mettre a jour la structure L */
	L.first = e2;
	if (e2 == NULL)    /* cas d'une liste L avec un seul element */
		L.last = NULL; /* --> la liste L devient une liste vide  */
	L.taille--;
	return L;
}


/* creer une sequence de bezier2 sous forme d'un tableau de bezier2 
   a partir de la liste de bezier2 L */
Tableau_Bezier2 sequence_bezier2_liste_vers_tableau(Liste_bezier2 L){
	   Tableau_Bezier2 T;
	   
	   /* taille de T = taille de L */
	   T.taille = L.taille;
	   
	   /* allocation dynamique du tableau de bezier2 */
	   T.tab = malloc(sizeof(bezier2) * T.taille);
	   if (T.tab == NULL)
	   {
		   /* allocation impossible : arret du programme avec un message */
		   fprintf(stderr, "sequence_bezier2s_liste_vers_tableau : ");
		   fprintf(stderr, " allocation impossible\n");
		   exit(-1);
	   }
	   
	   /* remplir le tableau de bezier2s T en parcourant la liste L */
	   int k = 0; /* indice de l'element dans T.tab */
	   Cellule_Liste_bezier2 *el = L.first; /* pointeur sur l'element dans L */
	   while (el) 
	   {
		   T.tab[k] = el->data;
		   k++; /* incrementer k */
		   el = el->suiv; /* passer a l'element suivant dans la liste chainee */
	   }
	   
	   return T;
}


Cellule_Tableau_Bezier2 *creer_element_Tableau_Bezier2(Tableau_Bezier2 v){
    Cellule_Tableau_Bezier2 *el;
	
	el = calloc(1, sizeof(Cellule_Tableau_Bezier2));

	if (el==NULL)
	{
		fprintf(stderr, "creer_element_Tableau_bezier2 : allocation impossible\n");
		exit(-1);
	}
	el->data = v;
	el->suiv = NULL;
	return el;
}


/*


Debut declaration fonction bezier 3


*/


/* creer une cellule de liste avec l'element v 
   renvoie le pointeur sur la cellule de liste creee
   la fonction s'arrete si la creation n'a pas pu se faire */
Cellule_Liste_bezier3 *creer_element_liste_bezier3(bezier3 v){
	Cellule_Liste_bezier3 *el;
	el = (Cellule_Liste_bezier3 *)malloc(sizeof(Cellule_Liste_bezier3));
	if (el==NULL)
	{
		fprintf(stderr, "creer_element_liste_bezier3 : allocation impossible\n");
		exit(-1);
	}
	el->data = v;
	el->suiv = NULL;
	return el;
}

/* creer une liste vide */
Liste_bezier3 creer_liste_bezier3_vide(){
	Liste_bezier3 L = {0, NULL, NULL};
	return L;
}

/* ajouter l'element e en fin de la liste L, renvoie la liste L modifiee */
Liste_bezier3 ajouter_element_liste_bezier3(Liste_bezier3 L, bezier3 e){
	Cellule_Liste_bezier3 *el;
	
	el = creer_element_liste_bezier3(e);
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
Liste_bezier3 supprimer_liste_bezier3(Liste_bezier3 L){
	Cellule_Liste_bezier3 *el=L.first;
	
	while (el) 
	{		
		Cellule_Liste_bezier3 *suiv=el->suiv;
		free(el);
		el = suiv;
	}
	L.first = L.last = NULL; L.taille = 0;
	return L;
}

/* concatener L2 a la suite de L1, renvoie la liste L1 modifiee */
Liste_bezier3 concatener_liste_bezier3(Liste_bezier3 L1, Liste_bezier3 L2){
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
Liste_bezier3 supprimer_premier_element_liste_bezier3(Liste_bezier3 L){
	/* cas d'une liste L vide : ne rien faire */
	if (L.taille == 0) return L;
	
	Cellule_Liste_bezier3 *e1=L.first;  /* pointeur vers le premier element  */ 
	Cellule_Liste_bezier3 *e2=e1->suiv; /* pointeur vers le deuxieme element */ 
	
	/* supprimer l'element pointe par e1 */
	free(e1);
	
	/* mettre a jour la structure L */
	L.first = e2;
	if (e2 == NULL)    /* cas d'une liste L avec un seul element */
		L.last = NULL; /* --> la liste L devient une liste vide  */
	L.taille--;
	return L;
}


Cellule_Tableau_bezier3 *creer_element_Tableau_bezier3(Tableau_bezier3 v){
    Cellule_Tableau_bezier3 *el;
	
	el = calloc(1, sizeof(Cellule_Tableau_bezier3));

	if (el==NULL)
	{
		fprintf(stderr, "creer_element_Tableau_bezier3 : allocation impossible\n");
		exit(-1);
	}
	el->data = v;
	el->suiv = NULL;
	return el;
}


/* creer une sequence de bezier3 sous forme d'un tableau de bezier3 
   a partir de la liste de bezier3 L */
   Tableau_bezier3 sequence_bezier3_liste_vers_tableau(Liste_bezier3 L){
	Tableau_bezier3 T;
	
	/* taille de T = taille de L */
	T.taille = L.taille;
	
	/* allocation dynamique du tableau de Bezier3 */
	T.tab = malloc(sizeof(bezier3) * T.taille);
	if (T.tab == NULL)
	{
		/* allocation impossible : arret du programme avec un message */
		fprintf(stderr, "sequence_Bezier3s_liste_vers_tableau : ");
		fprintf(stderr, " allocation impossible\n");
		exit(-1);
	}
	
	/* remplir le tableau de Bezier3s T en parcourant la liste L */
	int k = 0; /* indice de l'element dans T.tab */
	Cellule_Liste_bezier3 *el = L.first; /* Pointeur sur l'element dans L */
	while (el) 
	{
		T.tab[k] = el->data;
		k++; /* incrementer k */
		el = el->suiv; /* passer a l'element suivant dans la liste chainee */
	}
	
	return T;
}
/*


Debut declaration fonction calcul sur bezier 2 et bezier 3


*/


Point calcul_point_bezier_2(bezier2 b2, double t){
    Point ct ,c0 , c1, c2;
    c0=b2.c0;
    c1=b2.c1;
    c2=b2.c2;
    ct.x = (c0.x*(1-t)*(1-t))+ (c1.x*2*t*(1-t))+(c2.x*t*t);
    ct.y = (c0.y*(1-t)*(1-t))+ (c1.y*2*t*(1-t))+(c2.y*t*t);
    return ct;
}

Point calcul_point_bezier_3(bezier3 b3, double t){
    Point a,b,c,d;

    a = mul_point(b3.c0, (1-t)*(1-t)*(1-t));
    b = mul_point(b3.c1,(3*(1-t)*(1-t)*t));
    c = mul_point(b3.c2,(3*(1-t)*t*t));
    d = mul_point(b3.c3,(t*t*t));
 
    return add_point(a, add_point(b, add_point(c, d)));
}

bezier3 convertion_bezier2_3(bezier2 b2){
    bezier3 b3;
    b3.c0=b2.c0;
    b3.c1.x=(2*(b2.c1.x)+b2.c0.x)/3;
    b3.c1.y=(2*(b2.c1.y)+b2.c0.y)/3;
    b3.c2.x=(2*(b2.c1.x)+b2.c2.x)/3;
    b3.c2.y=(2*(b2.c1.y)+b2.c2.y)/3;
    b3.c3=b2.c2;
    return  b3;
}


bezier2 approx_bezier2(Tableau_Point Tp, int j1, int j2){
    Point pj1, pj2, C0, C1, C2;
    Point *tab;
    int taille, i;
    double n;
    bezier2 sortie;


    taille = Tp.taille;
    tab = Tp.tab;

    pj1 = tab[j1];
    pj2 = tab[j2];

    n = j2-j1;

    C0 = pj1;
    C2 = pj2;

    if(n==1){
        C1.x = (pj1.x+pj2.x)/2;
        C1.y = (pj1.y+pj2.y)/2;
    }else{
        double alpha = (3*n)/((n*n)-1);
        double beta = (1-(2*n))/(2*(n+1));
        Point somme;
		somme = set_point(0,0);
        for(i=1; i<n; i++){
            somme.x += tab[i+j1].x;
            somme.y += tab[i+j1].y;
        }

        C1.x = alpha*somme.x + beta*(pj1.x+pj2.x);
        C1.y = alpha*somme.y + beta*(pj1.y+pj2.y);
    }

    sortie.c0 = C0;
    sortie.c1 = C1;
    sortie.c2 = C2;
    return sortie;
}


double distance_point_bezier2(Point P, bezier2 b2,double ti){
    Point Cti;
    Cti.x = (b2.c0.x*(1-ti)*(1-ti))+ (b2.c1.x*2*ti*(1-ti))+(b2.c2.x*ti*ti);
    Cti.y = (b2.c0.y*(1-ti)*(1-ti))+ (b2.c1.y*2*ti*(1-ti))+(b2.c2.y*ti*ti);

    return dist_point(P,Cti);
}

double distance_point_bezier3(Point P, bezier3 b3, double ti){
    Point C = calcul_point_bezier_3(b3,ti);
	Vecteur V = vect_bipoint(P ,C);
	double N = norme_vect(V);
	return N;
}

/*Calcul de la valeur de lambda en fonction de k et de n */
double fonction_lambda(double k, double n){
    return (6*k*k*k*k - 8*n*k*k*k + 6*k*k - 4*n*k + n*n*n*n - n*n);
}

/*Approximation d'une ligne polygonale par une courbe de Bezier de degre 3*/
bezier3 approx_bezier3(Tableau_Point Tp, int j1, int j2){
    Point pj1, pj2, somme1, somme2;
    double n = j2-j1;
    bezier3 sortie;


	

    if(n<3){
        sortie = convertion_bezier2_3(approx_bezier2(Tp,j1,j2));
    }else{
		// printf("else\n");


		somme1 = set_point(0, 0);
		somme2 = set_point(0, 0);

		pj1 = Tp.tab[j1];
		pj2 = Tp.tab[j2];
		sortie.c0 = pj1;
		sortie.c3 = pj2;


        // calcul des valeurs d'alpha, de beta et gamma 
        double alpha = (-15.*n*n*n + 5.*n*n + 2.*n + 4.)/(3.*(n + 2.)* (3.*n*n + 1.));
        double beta = (10.*n*n*n - 15.*n*n + n + 2.) / (3.*(n + 2.)*(3.*n*n + 1.));
        double gamma = (70.*n) / (3.*(n*n - 1)*(n*n - 4.)*(3*n*n + 1.));


        // boucle pour C1
        for (int i=1;i < n;i++){
			somme1.x = somme1.x + fonction_lambda(i,n)*(Tp.tab[j1 + i]).x;
			somme1.y = somme1.y + fonction_lambda(i,n)*(Tp.tab[j1 + i]).y;
			somme2.x = somme2.x + fonction_lambda(n-i,n)*(Tp.tab[j1 + i]).x;
			somme2.y = somme2.y + fonction_lambda(n-i,n)*(Tp.tab[j1 + i]).y;
        }
        
        //attribution des valeurs pour C1 et C2 en utilisant les formules donnees dans le cours
		sortie.c1 = add_point(mul_point(Tp.tab[j1], alpha), 
					add_point(mul_point(somme1, gamma), 
							mul_point(Tp.tab[j2], beta)));

		sortie.c2 = add_point(mul_point(Tp.tab[j1], beta), 
					add_point(mul_point(somme2, gamma), 
							mul_point(Tp.tab[j2], alpha)));
        
    }

    return sortie;
}

