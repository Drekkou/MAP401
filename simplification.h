#include"bezier.h"

int nb_seg(Liste_tableau_point liste);

void afficher_tableau_point(Tableau_Point L);

Tableau_Point concatenation(Tableau_Point L1, Tableau_Point L2);

Tableau_Point simplification_douglas_peucker(Tableau_Point tp, int j1, int j2, double d);

Liste_bezier2 simplification_bezier_2(Tableau_Point Tp, int j1, int j2, double d);

Liste_bezier3 simplification_bezier_3(Tableau_Point Tp, int j1, int j2, double d);