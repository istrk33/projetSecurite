#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#include <math.h>


float dist(float x[], float y[], char distanceType[]) {
  float calcul[2], resultat;
  calcul[0] = x[0] - y[0], calcul[1] = x[1] - y[1]; // on realise la différence
  // si le paramètre entier par l'utilisateur est euclidienne
  if (!strcmp(distanceType, "euclidienne")) {
    calcul[0] = pow(calcul[0], 2), calcul[1] = pow(calcul[1], 2); // on met au carré
    for (int i = 0; i < 2; i++) {
      resultat += calcul[i];
    }
    return pow(resultat, 0.5);

  } else if (!strcmp(distanceType, "manhattan")) {
    calcul[0] = fabs(calcul[0]), calcul[1] = fabs(calcul[1]);
    for (int i = 0; i < 2; i++) {
      resultat += calcul[i];
    }
    return resultat;
  }
}
// retourne la distance (euclidienne ou manhattan au choix) entre 2 points (int) (en dimension 2)
int main(int argc, char ** argv) {
  int x1, y1, x2, y2;
  printf("Début du programme pour calculer la distance entre deux points\n");
  printf("Entrez les coordonées du points A au format suivant : x1 y1 \n");
  fflush(stdout); // pour windows
  scanf("%d%d", & x1, & y1);
  printf("Entrez les coordonées du points B au format suivant : x2 y2 \n");
  fflush(stdout); // pour windows
  scanf("%d%d", & x2, & y2);

  float arr1[2], arr2[2];

  //on ajoute les coordonées dans le tableau 1 et 2 qui représentent respectivement les points x et y
  arr1[0] = (float) x1;
  arr1[1] = (float) y1;

  arr2[0] = (float) x2;
  arr2[1] = (float) y2;

  float resultDistance = dist(arr1, arr2, argv[1]);
  printf("Distance : %.6f", resultDistance);
  return EXIT_SUCCESS;
}
