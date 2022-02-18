#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#define MAX 3

int main()
{
    printf("Bienvenu sur le module de calcul de vos impots !\n");
    int childNumber;
    bool isMarried;
    char responseIsMarried[MAX];
    char oui[]="OUI";
    char non[]="NON";
    double overallNetIncome;
    //compute numbers of parts
    printf("Êtes-vous marié ?[OUI/NON]\n");
    fgets(responseIsMarried,MAX,stdin);
    while (strcmp(responseIsMarried, oui) != 0 || strcmp(responseIsMarried, non) != 0)
    {
        printf("Êtes-vous marié ?[OUI/NON]\n");
        fgets(responseIsMarried,MAX,stdin);
        printf("%d",strcmp(responseIsMarried, oui) != 0);
        printf("ma rep :::::: %s\n",responseIsMarried);
        printf("base :::::: %s\n",oui);
    }
    printf("Combien d'enfants avez-vous ?\n");
    scanf("%d", &childNumber);
    /*while (strcmp(tolower(responseIsMarried), "oui") != 0 || strcmp(tolower(responseIsMarried), "non") != 0)
    {
        printf("Êtes-vous marié ?");
        scanf("%s", &responseIsMarried);
    }*/
    printf("Quel est votre revenu net global ?");
    scanf("%lf", &overallNetIncome);
    return 0;
}

/*public int impots(double revenuNetGlobal, int nbParts) {
        double revenuNetImposable = revenuNetGlobal * 0.9;
        double quotientFamilial = revenuNetImposable / nbParts;
        double montantImpot = 0.0;
        if (quotientFamilial < 10064) {
            if (quotientFamilial < 0) {
                throw new IllegalArgumentException("Impossible de calculer l'impots sur des valeurs négatives !");
            }
        }
        if (quotientFamilial >= 10064.0 && quotientFamilial >= 25659.0) {
            montantImpot += (25659.0 - 10064.0) * 0.11;
        }
        if (quotientFamilial >= 10064.0 && quotientFamilial <= 25658.0) {
            montantImpot += (quotientFamilial - 10064.0) * 0.11;
        }

        if (quotientFamilial >= 25659.0 && quotientFamilial >= 73369.0) {
            montantImpot += (73369.0 - 25659.0) * 0.3;
        }
        if (quotientFamilial >= 25659.0 && quotientFamilial <= 73368.0) {
            montantImpot += (quotientFamilial - 25659.0) * 0.3;
        }

        if (quotientFamilial >= 73369.0 && quotientFamilial >= 157806.0) {
            montantImpot += (157806.0 - 73369.0) * 0.41;
        }
        if (quotientFamilial >= 73369.0 && quotientFamilial <= 157805.0) {
            montantImpot += (quotientFamilial - 73369.0) * 0.41;
        }

        if (quotientFamilial >= 157806.0) {
            montantImpot += (quotientFamilial - 157806.0) * 0.45;
        }
        return (int) (montantImpot * nbParts);
    }*/
