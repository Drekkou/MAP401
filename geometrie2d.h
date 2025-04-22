/*
Type Point
*/
typedef struct Point_ {
   double x,y;
} Point;
/*
Type Vecteur
*/
typedef struct Vecteur_ 
{
   double x,y;
} Vecteur;


Point set_point(double x,double y);

Vecteur set_vecteur(double x, double y );

Point add_point(Point P1,Point P2);

Vecteur vect_bipoint(Point A,Point B);

Vecteur add_vecteur(Vecteur V1, Vecteur V2);

Vecteur mul_vecteur(Vecteur V, double val);

Point mul_point(Point P, double val);

double sca_vecteur(Vecteur V1, Vecteur V2);

double norme_vect(Vecteur V);

double dist_point(Point P1, Point P2);

double distance_point_seg(Point P, Point A, Point B );
