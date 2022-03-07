#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#define SIZE 50

void find_palindromic_number(int borneMinimale, int borneMaximale)
{
	char tmp[SIZE], tmp2[SIZE];
	for(int i = borneMinimale; i<=borneMaximale; i++)
	{
		snprintf(tmp, SIZE, "%d", i); // double to string
		strcpy(tmp2, tmp); 
		strrev(tmp); // reverse characters
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
  scanf("%d", & intervalleMin);
  printf("Entrez la borne maximale (incluse) : ");
  fflush(stdout); // pour windows
  scanf("%d", & intervalleMax);

	find_palindromic_number(intervalleMin, intervalleMax);
  return EXIT_SUCCESS;
}
