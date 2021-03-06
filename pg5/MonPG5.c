/**
 * @file        MonPG5.c
 *
 * @authors     Dorian Maidon <dorian.maidon@etudiant.univ-lr.fr>, Ilker Soyturk <ilker.soyturk@etudiant.univ-lr.fr>
 * @date        2021-2022
 */

#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    int counter;
    if (argc == 1 || argc == 2)
    {
        printf("Entrez 2 arguments en paramètres\n");
    }
    else if (argc == 3)
    {
        int a=atoi(argv[1]);
        int b=atoi(argv[2]);
        int c=a;
        int d=b;

        while(a!=b){
            if(a>b){
                b+=d;
            }else if(a<b){
                a+=c;
            }
            printf("a : %d, b : %d\n",a,b);
        }
        printf("Le plus petit multiple commun de %d et %d est %d.\n",c,d,a);
    }
    else
    {
        printf("Trop d'arguments lors de l'appel de la fonction !!\n");
    }
    return 0;
}
