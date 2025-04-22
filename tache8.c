#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<math.h>
#include"tache_pre.h"

int main(int argc, char** argv){
    int cont1, cont2, cont3; //cont1: nom_fichier
    // cont2: type de simplification; cont3: distance-seuil
    char *nom_fichier;
    char nom_file_entree[3][25]={"Asterix3.pbm","lettre-L-cursive.pbm","ColombesDeLaPaix.pbm"};
    printf("Début de la routine de test\n");

    for(cont1=0;cont1<=2;cont1++){
        nom_fichier=nom_file_entree[cont1];
        for(cont2=0;cont2<=2;cont2++){
            double d=0;
            for(cont3=0;cont3<7;cont3++){
                printf("\nnom_fichier: %s \ndistance: %f\n",nom_file_entree[cont1],d);
                if(cont2==0){
                    //appel simplification segment
                    tache6(nom_fichier,0, d);
                }
                if(cont2==1){
                    //appel simplification bezier2
                    tache7_1(nom_fichier,0, d);
                }
                if(cont2==2){
                    //appel simplification bezier 3
                    tache7_2(nom_fichier,0, d);
                }
                else {}
                if (cont3==0){d=0.5;}
                else {d=d*2;}                
            }
        }
    }
}
