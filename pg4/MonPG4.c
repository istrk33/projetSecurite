/**
 * @file        MonPG4.c
 *
 * @authors     Dorian Maidon <dorian.maidon@etudiant.univ-lr.fr>, Ilker Soyturk <ilker.soyturk@etudiant.univ-lr.fr>
 * @date        2021-2022
 */
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>

double nbParts(int nbChildren, bool isMarried);
double taxes(double income,double nbparts);


int main()
{
    printf("Bienvenue sur le module de calcul de vos impots !\n");
    int childNumber = 0;
    bool isMarried;
    bool isCorrectResponse = false;
    char o = 'O';
    char n = 'N';
    char responseIsMarried;
    double overallNetIncome;
    // compute numbers of parts
    printf("Êtes-vous marié ?[\"O\" pour oui/\"N\" pour non]\n");
    while (!isCorrectResponse)
    {
        if (scanf(" %c", &responseIsMarried))
        {
            if (responseIsMarried == o)
            {
                isCorrectResponse = true;
                isMarried = true;
            }
            else if (responseIsMarried == n)
            {
                isCorrectResponse = true;
                isMarried = false;
            }
            else
            {
                printf("Réponse incorrecte, entrez les valeurs \'O\' ou \'N\'\n");
            }
        }
    }
    isCorrectResponse = false;
    printf("Combien d'enfants avez-vous ?(Entrez une valeur entière)\n");
    while (!isCorrectResponse)
    {
        if (scanf("%d", &childNumber))
        {
            if (childNumber < 0)
            {
                printf("Entrez une valeur au moins égale à 0 !!!\n");
            }
            else
            {
                isCorrectResponse = true;
            }
        }
        else
        {
            getchar();
            printf("Entrez une valeur entière !!!\n");
        }
    }
    isCorrectResponse = false;
    printf("Quel est votre revenu net global ?\n");
    while (!isCorrectResponse)
    {
        if (scanf("%lf", &overallNetIncome))
        {
            if (overallNetIncome < 0.0)
            {
                printf("Entrez une valeur au moins égale à 0.0 !!!\n");
            }
            else
            {
                isCorrectResponse = true;
            }
        }
        else
        {
            getchar();
            printf("Entrez un nombre avec une virgule flottante !!!\n");
        }
    }
    //total taxes
    printf("Vos impôts s'élèvent à hauteur de : %.2f €\n",taxes(overallNetIncome,nbParts(childNumber, isMarried)));
    return 0;
}

double nbParts(int nbChildren, bool isMarried)
{
    double nbparts = 0;
    if (isMarried)
    {
        nbparts += 1;
    }
    if (nbChildren == 1)
    {
        nbparts += 0.5;
    }
    else if (nbChildren > 1)
    {
        nbparts += nbChildren;
    }
    return nbparts;
}

double taxes(double revenuNetGlobal,double nbParts)
{
    double revenuNetImposable = revenuNetGlobal * 0.9;
    double quotientFamilial = revenuNetImposable / nbParts;
    double montantImpot = 0.0;
    if (quotientFamilial >= 10064.0 && quotientFamilial >= 25659.0)
    {
        montantImpot += (25659.0 - 10064.0) * 0.11;
    }
    if (quotientFamilial >= 10064.0 && quotientFamilial <= 25658.0)
    {
        montantImpot += (quotientFamilial - 10064.0) * 0.11;
    }

    if (quotientFamilial >= 25659.0 && quotientFamilial >= 73369.0)
    {
        montantImpot += (73369.0 - 25659.0) * 0.3;
    }
    if (quotientFamilial >= 25659.0 && quotientFamilial <= 73368.0)
    {
        montantImpot += (quotientFamilial - 25659.0) * 0.3;
    }

    if (quotientFamilial >= 73369.0 && quotientFamilial >= 157806.0)
    {
        montantImpot += (157806.0 - 73369.0) * 0.41;
    }
    if (quotientFamilial >= 73369.0 && quotientFamilial <= 157805.0)
    {
        montantImpot += (quotientFamilial - 73369.0) * 0.41;
    }

    if (quotientFamilial >= 157806.0)
    {
        montantImpot += (quotientFamilial - 157806.0) * 0.45;
    }
    return (montantImpot * nbParts);
}
