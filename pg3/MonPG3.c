/**
 * @file        MonPG3.c
 *
 * @authors     Dorian Maidon <dorian.maidon@etudiant.univ-lr.fr>, Ilker Soyturk <ilker.soyturk@etudiant.univ-lr.fr>
 * @date        2021-2022
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include "supportLib.h"
#include "pbPlots.h"

/*
 * Function:  display_functions 
 * display all the available options 
 */
void display_functions()
{ 
	printf("1-Fonction affine du type : ax + b\n");
	printf("2-Fonction du second degré du type : ax² + bx + c\n");
	printf("3-Fonction cosinus du type : cos(x)\n");
	printf("4-Fonction sinus du type : sin(x)\n");
	printf("5-Fonction logarithmique du type : log(x)\n");
	printf("6-Fonction exponentielle du type : e(x)\n");
}

/*
 * Function:  initialize_array 
 *  nombre : type of curve/function
 *  intervalleMin : start range
 *  intervalleMax : end range
 *  size : precision of the curve
 */
 
double** initialize_array(int nombre, double intervalleMin, double intervalleMax, int size)
{
	int a, b ,c;
	double tmp = intervalleMin;
	double** x = (double**)malloc(2 * sizeof(double*)); // 2 lignes necessaire

	for(int i = 0; i < size; i++) {
		 x[i] = (double*)malloc(size * sizeof(double)); // pour les elements de la ligne 
	}
	
	for (int i = 0; i < size; i++) {
		x[0][i] = tmp;
		tmp += 0.1;
	}
	
	switch(nombre)
	{
		case 1:
			printf("Entrez a : ");
			scanf("%d", &a);
			
			printf("Entrez b : ");
			scanf("%d", &b);
			
			for (int i=0; i < size; i++) {
				x[1][i] = a * x[0][i] + b ;
			}
			
			break;
			
		case 2:
			printf("Entrez a : ");
			scanf("%d", &a);
			
			printf("Entrez b : ");
			scanf("%d", &b);
			
			printf("Entrez c: ");
			scanf("%d", &c);
			
			for (int i=0; i < size; i++) {
				x[1][i] = a * pow(x[0][i], 2) + b * x[0][i] + c;
			}
			
			break;
			
		case 3:
			for (int i=0; i < size; i++) {
				x[1][i] = cos(x[0][i]);
			}
			break;
			
		case 4:
			for (int i=0; i < size; i++) {
				x[1][i] = sin(x[0][i]);
			}
			
			break;
			
		case 5:
			for (int i=0; i < size; i++) {
				if(x[0][i] == 0) 
					x[0][i] = 0.00001;
				x[1][i] = log(x[0][i]);
			}
			
			break;
			
		case 6:
			for (int i=0; i < size; i++) {
				x[1][i] = exp(x[0][i]);
			}
			
			break;
			
		default:
			printf("Valeur incorrecte");
	}
	
	return x;
}

/*
 * Function:  drawing 
 *  array : containg x and y values 
 *  size : precision of the curve
 *	filename: specified by user 
 */
 
void drawing(double** array, int size, char* filename)
{
	double x[size], y[size];
	
	for(int i =0; i < size; i++) {
		x[i] = array[0][i]; // x
	}
		for(int i =0; i < size; i++) {
		y[i] = array[1][i]; // f(x)
	}
	
	strcat(filename, ".png"); // png extension

	RGBABitmapImageReference *imageRef = CreateRGBABitmapImageReference();
	StringReference *error = (StringReference *) malloc(sizeof(StringReference));
	
	/* draw with x and f(x) values and output a 600x400 image */
	DrawScatterPlot(imageRef, 600, 400 , x , size, y ,size, error);
	
	size_t len;
	double *pngData = ConvertToPNG(&len, imageRef->image);
	WriteToFile(pngData, len, filename);
	
	printf("Sauvegarde faite\n");
	
}

/*
 * Function:  gere_input 
 * erreur : string containing the error
 */
 
void gere_input(char *erreur) {
 	printf("%s\n", erreur);
	sleep(1);
	exit(0);
}

int main(void)
{

	int nombre, size;
	double intervalleMin, intervalleMax;
	double **array;
	char filename[20]; // max size for the name of the file
	
 	printf("Debut du programme pour afficher les courbes des fonctions basiques en mathematiques\n");
  printf("Entrez un nombre correspondant à la courbe que vous souhaitez voir\n");
  
  display_functions();
  
  fflush(stdout); // pour windows
  
  if(!scanf("%d", & nombre) || (nombre<1 || nombre>6)) {
   	gere_input("Ce n'est pas un entier compris entre 1 et 6 - le programme va se fermer");
  }
  
  printf("Entrez la borne minimale pour visualiser la courbe : ");
  
  if(!scanf("%lf", & intervalleMin)) {
   	gere_input("Ce n'est pas un entier - le programme va se fermer");
  }
  
  printf("Entrez la borne maximale pour visualiser la courbe : ");
  
  if(!scanf("%lf", & intervalleMax)) {
   	gere_input("Ce n'est pas un entier - le programme va se fermer");	
  }
  
   printf("Entrez le nom du fichier image sortant : ");
  
  scanf("%s", filename);
  
  size = (intervalleMax - intervalleMin) * 10 + 1;
  
  array = initialize_array(nombre,intervalleMin,intervalleMax, size);
  
  drawing(array, size, filename);
  
  free(array);
  
	return EXIT_SUCCESS;
}
