#include <stdio.h>

#include <stdlib.h>

#include <math.h>

#include "supportLib.h"

#include "pbPlots.h"

//gcc MonPG3.c -o MonPG3 pbPlots.c supportLib.c -lm

void display_functions()
{ 
	printf("1-Fonction affine du type : ax + b\n");
	printf("2-Fonction du second degré du type : ax² + bx + c\n");
	printf("3-Fonction cosinus du type : cos(x)\n");
	printf("4-Fonction sinus du type : sin(x)\n");
	printf("5-Fonction logarithmique du type : log(x)\n");
	printf("6-Fonction exponentielle du type : e(x)\n");
}

double** initialize_array(int nombre, double intervalleMin, double intervalleMax, int size)
{
	int a, b ,c;
	double tmp = intervalleMin;
	double** x = (double**)malloc(2 * sizeof(double*));

	for(int i = 0; i < size; i++) {
		 x[i] = (double*)malloc(size * sizeof(double));
	}
	
	for (int i = 0; i < size; i++) {
		x[0][i] = tmp;
		tmp += 0.1;
	}
	
	switch(nombre)
	{
		case 1:
			printf("Entrez a : ");
		  fflush(stdout); // pour windows
			scanf("%d", &a);
			printf("Entrez b : ");
		  fflush(stdout); // pour windows
			scanf("%d", &b);
			
			for (int i=0; i < size; i++) {
				x[1][i] = a * x[0][i] + b ;
			}
			break;
		case 2:
			printf("Entrez a : ");
		  fflush(stdout); // pour windows
			scanf("%d", &a);
			printf("Entrez b : ");
			fflush(stdout); // pour windows
			scanf("%d", &b);
			printf("Entrez c: ");
		  fflush(stdout); // pour windows
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

void drawing(double** array, int size)
{
	printf("ok");
	double x[size], y[size];
	
	for(int i =0; i < size; i++) {
		x[i] = array[0][i];
	}
		for(int i =0; i < size; i++) {
		y[i] = array[1][i];
	}

	RGBABitmapImageReference *imageRef = CreateRGBABitmapImageReference();
	StringReference *errorMessage = (StringReference *)malloc(sizeof(StringReference));
	
	DrawScatterPlot(imageRef, 600, 400 , x , size, y ,size, errorMessage);
	
	size_t length;
	double *pngData = ConvertToPNG(&length, imageRef->image);
	WriteToFile(pngData, length, "plot.png");
	printf("test");
}

int main(void)
{
	int nombre, size;
	double intervalleMin, intervalleMax;
	double **array;
  printf("Début du programme pour afficher les courbes des fonctions basiques en mathématiques\n");
  printf("Entrez un nombre correspondant à la courbe que vous souhaitez voir\n");
  display_functions();
  fflush(stdout); // pour windows
  scanf("%d", & nombre);
  
  printf("Entrez la borne minimale pour visualiser la courbe : ");
  fflush(stdout); // pour windows
  scanf("%lf", & intervalleMin);
  printf("Entrez la borne maximale pour visualiser la courbe : ");
  fflush(stdout); // pour windows
  scanf("%lf", & intervalleMax);
  
  size = (intervalleMax - intervalleMin) * 10 + 1;
  array = initialize_array(nombre,intervalleMin,intervalleMax, size);
  drawing(array, size);
	return EXIT_SUCCESS;
}
