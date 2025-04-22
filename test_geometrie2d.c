#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"geometrie2d.h"

int main(int argc, char** argv){
  Vecteur V1,V2;
  Point P1,P2;
  
  P1 = set_point(1,1);
  P2 = set_point(3,3);
  
  V1 = set_vecteur(2,2);
  V2 = set_vecteur(4,4);
  
  printf("coordonee de P1: %f %f \n",P1.x,P1.y);
  printf("coordonee de P2: %f %f \n",P2.x,P2.y);
  printf("coordonee de V1: %f %f \n",V1.x,V1.y);
  printf("coordonee de V2: %f %f \n",V2.x,V2.y);
  
  printf("addition de P1 et P2 : %f %f\n", add_point(P1,P2).x, add_point(P1,P2).y);
  printf("addition de V1 et V2 : %f %f\n", add_vecteur(V1,V2).x, add_vecteur(V1,V2).y);
  
  printf("vect bipoint : %f %f\n", vect_bipoint(P1,P2).x, vect_bipoint(P1,P2).y);
  
  printf("multiplication de P1 par 3 : %f %f\n", mul_point(P1,3).x, mul_point(P1,3).y);
  printf("multiplication de V1 par 3: %f %f\n", mul_vecteur(V1,3).x, mul_vecteur(V1,3).y);
  
  printf("produit scalaire de V1 et V2 : %f\n", sca_vecteur(V1,V2));
  
  printf("norme du vecteur V1 : %f\n", norme_vect(V1));
  
  printf("distance entre le point P1 et P2: %f\n", dist_point(P1,P2));
}