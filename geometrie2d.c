#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"geometrie2d.h"
#include<math.h>


Point set_point(double x,double y){
    Point P;
    P.x = x;
    P.y = y;
    return P;
}
Vecteur set_vecteur(double x,double y){
    Vecteur V={x,y};
    return V;
}
Point add_point(Point P1, Point P2){
    return set_point(P1.x+P2.x,P1.y+P2.y);
}
Vecteur add_vecteur(Vecteur V1, Vecteur V2){
    return set_vecteur(V1.x+V2.x,V1.y+V2.y);
}
Vecteur vect_bipoint(Point A,Point B){
    Vecteur V={B.x-A.x,B.y-A.y};
    return V;
}
Vecteur mul_vecteur(Vecteur V, double val){
    return set_vecteur(V.x*val,V.y*val);
}
Point mul_point(Point P, double val){
    return set_point(P.x*val,P.y*val);
}
double sca_vecteur(Vecteur V1, Vecteur V2){
    return V1.x*V2.x+V1.y*V2.y;
}
double norme_vect(Vecteur V){
    return sqrt(V.x*V.y);
}
double dist_point(Point P1,Point P2){
    return sqrt((P1.x-P2.x)*(P1.x-P2.x)+(P1.y-P2.y)*(P1.y-P2.y));
}
double distance_point_seg(Point P, Point A, Point B ){
    double a;

    if( (A.x == B.x) && (A.y == B.y)){
        return dist_point(P,A);
    }
    Vecteur vect_AP, vect_AB;
    vect_AP = vect_bipoint(A,P);
    vect_AB = vect_bipoint(A,B);
    a=sca_vecteur(vect_AP,vect_AB)/sca_vecteur(vect_AB,vect_AB);
    if (a<0){
        return dist_point(A,P);
    }
    else if (a>1){
        return dist_point(B,P);
    }
    else {
        Point Q;
        Q.x= A.x+(a*(B.x-A.x));
        Q.y= A.y+(a*(B.y-A.y));
        return dist_point(Q,P);
    }
}