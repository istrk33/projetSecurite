#include <stdio.h>

#include <stdlib.h>

int calculPGCD(int a, int b) {
  int reste = a % b;
  while (reste != 0) {
    a = b;
    b = reste;
    reste = a % b;
  }
  return b;
}

int main(void) {
  int entierUn, entierDeux;
  printf("Début du programme pour calculer le pgcd de deux entiers\n");
  printf("Entrez l'entier A : \n");
  fflush(stdout); // pour windows
  scanf("%d", & entierUn);
  printf("Entrez l'entier B : \n");
  fflush(stdout); // pour windows 
  scanf("%d", & entierDeux);

  // calcul le pgcd de deux nombres avec l'algorithme d'euclide
  int resultat = calculPGCD(entierUn, entierDeux);
  printf("PGCD(%d,%d) = %d", entierUn, entierDeux, resultat);
  return EXIT_SUCCESS;
}
