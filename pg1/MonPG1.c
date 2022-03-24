/**
 * @file        MonPG1.c
 *
 * @authors     Dorian Maidon <dorian.maidon@etudiant.univ-lr.fr>, Ilker Soyturk <ilker.soyturk@etudiant.univ-lr.fr>
 * @date        2021-2022
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define SIZE 50

// reverse the string (implemented function in windows)
char *strrevv(char *str)
{
      char *p1, *p2;

      if (! str || ! *str)
            return str;
      for (p1 = str, p2 = str + strlen(str) - 1; p2 > p1; ++p1, --p2)
      {
            *p1 ^= *p2;
            *p2 ^= *p1;
            *p1 ^= *p2;
      }
      return str;
}

/*
 * Function:  find_palindromic_number 
 * display all the palindromic numbers within the range specified by the user
 *  borneMinimale: start of range
 *  borneMaximale: end of range
 */
 
void find_palindromic_number(int borneMinimale, int borneMaximale)
{
	char tmp[SIZE], tmp2[SIZE];
	for(int i = borneMinimale; i<=borneMaximale; i++)
	{
		snprintf(tmp, SIZE, "%d", i); // double to string
		strcpy(tmp2, tmp); 
		strrevv(tmp); // reverse characters
		//
		if(strcmp( tmp, tmp2 ) == 0)
			printf("nb : %s\n", tmp);
	}
}

int main(void) {
  int intervalleMin, intervalleMax;
  printf("Début du programme pour trouver des nombres palindromes entre 2 bornes\n");
  printf("Entrez la borne minimale (incluse) : ");
  
  fflush(stdout); // pour windows
  
  if (!scanf("%d", & intervalleMin)) {
  	printf("Ce n'est pas un entier - le programme va se fermer\n");
  	sleep(1);
  	exit(0);
  }
  
  printf("Entrez la borne maximale (incluse) : ");
  
  fflush(stdout); // pour windows
  
  if (!scanf("%d", & intervalleMax)) {
  	printf("Ce n'est pas un entier - le programme va se fermer\n");
  	sleep(1);
  	exit(0);
  }
  
  if (intervalleMin<0) {
  	printf("Les valeurs negatives ne sont pas acceptees - le programme va se fermer\n");
  	sleep(1);
  	exit(0);
	}
	
  find_palindromic_number(intervalleMin, intervalleMax);
  
  return EXIT_SUCCESS;
}
