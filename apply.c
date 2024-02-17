// Copyright 2021 Andrei Calin-Mihail 311CA
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "image.h"
#include "utils.h"
#include "rotate.h"

// functia de clamp explicata in cerinta
double clamp(double x)
{
	if (x < 0)
		x = 0;
	if (x > 255)
		x = 255;
	return x;
}

// functia care efectueaza calculele de aplicare a filtrului pentru pixelii
// corespunzatori componentei rosii din cadrul imaginii color
double multir(int i, int j, image cpy, double kern[3][3])
{
	double result = 0;
	result += cpy.r[i - 1][j - 1] * 1.0 * kern[0][0];
	result += cpy.r[i - 1][j] * 1.0 * kern[0][1];
	result += cpy.r[i - 1][j + 1] * 1.0 * kern[0][2];
	result += cpy.r[i][j - 1] * 1.0 * kern[1][0];
	result += cpy.r[i][j] * 1.0 * kern[1][1];
	result += cpy.r[i][j + 1] * 1.0 * kern[1][2];
	result += cpy.r[i + 1][j - 1] * 1.0 * kern[2][0];
	result += cpy.r[i + 1][j] * 1.0 * kern[2][1];
	result += cpy.r[i + 1][j + 1] * 1.0 * kern[2][2];
	result = clamp(result);
	return result;
}

// functia care efectueaza calculele de aplicare a filtrului pentru pixelii
// corespunzatori componentei verzi din cadrul imaginii color
double multig(int i, int j, image cpy, double kern[3][3])
{
	double result = 0;
	result += cpy.g[i - 1][j - 1] * 1.0 * kern[0][0];
	result += cpy.g[i - 1][j] * 1.0 * kern[0][1];
	result += cpy.g[i - 1][j + 1] * 1.0 * kern[0][2];
	result += cpy.g[i][j - 1] * 1.0 * kern[1][0];
	result += cpy.g[i][j] * 1.0 * kern[1][1];
	result += cpy.g[i][j + 1] * 1.0 * kern[1][2];
	result += cpy.g[i + 1][j - 1] * 1.0 * kern[2][0];
	result += cpy.g[i + 1][j] * 1.0 * kern[2][1];
	result += cpy.g[i + 1][j + 1] * 1.0 * kern[2][2];
	result = clamp(result);
	return result;
}

// functia care efectueaza calculele de aplicare a filtrului pentru pixelii
// corespunzatori componentei albastre din cadrul imaginii color
double multib(int i, int j, image cpy, double kern[3][3])
{
	double result = 0;
	result += cpy.b[i - 1][j - 1] * 1.0 * kern[0][0];
	result += cpy.b[i - 1][j] * 1.0 * kern[0][1];
	result += cpy.b[i - 1][j + 1] * 1.0 * kern[0][2];
	result += cpy.b[i][j - 1] * 1.0 * kern[1][0];
	result += cpy.b[i][j] * 1.0 * kern[1][1];
	result += cpy.b[i][j + 1] * 1.0 * kern[1][2];
	result += cpy.b[i + 1][j - 1] * 1.0 * kern[2][0];
	result += cpy.b[i + 1][j] * 1.0 * kern[2][1];
	result += cpy.b[i + 1][j + 1] * 1.0 * kern[2][2];
	result = clamp(result);
	return result;
}

// o functie care copiaza o matrice de 3x3
void copy_kern(double kern[3][3], double source[3][3])
{
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			kern[i][j] = source[i][j];
}

// functia care executa comanda care aplica un anumit filtru selectiei curente
int APPLY(image *img, int *nr)
{
	image cpy = *img; // facem o copie a imaginii
	int ok = 0;
	if (*nr == 0) {
		printf("No image loaded\n");
	} else {
		char opt[100];
		fgets(opt, 100, stdin); // citim optiunea de APPLY (numele filtrului)
		if (strstr("P2P5", img->magic_number)) { // in cazul grayscale
			if (strcmp(" EDGE\n", opt) == 0)
				ok = 1;
			if (strcmp(" SHARPEN\n", opt) == 0)
				ok = 1;
			if (strcmp(" BLUR\n", opt) == 0)
				ok = 1;
			if (strcmp(" GAUSSIAN_BLUR\n", opt) == 0)
				ok = 1;
			// variabila ok verifica daca filtrul este valid
			if (ok == 1)
				printf("Easy, Charlie Chaplin\n");
			else
				printf("Invalid command\n");
			return 0;
		}
		// in cazul unei imagini color realocam matricea
		img->matrix = alloc_matrix(img->rows, img->cols);
		img->r = alloc_matrix(img->rows, img->cols);
		img->g = alloc_matrix(img->rows, img->cols);
		img->b = alloc_matrix(img->rows, img->cols);

		// initializam kernel-urile filtrelor
		double b = 1.0 / 9, g = 1.0 / 16, g2 = 2.0 / 16, kern[3][3];
		double edge[3][3] = {{-1, -1, -1}, {-1, 8, -1}, {-1, -1, -1}};
		double sharp[3][3] = {{0, -1, 0}, {-1, 5, -1}, {0, -1, 0}};
		double blur[3][3] = {{b, b, b}, {b, b, b}, {b, b, b}};
		double gur[3][3] = {{g, g2, g}, {g2, 4 * g, g2}, {g, g2, g}};

		// in cazul in care gasim o comanda valida copiem kernelul in "kern"
		if (strcmp(" EDGE\n", opt) == 0) {
			copy_kern(kern, edge);
			ok = 1;
		}
		if (strcmp(" SHARPEN\n", opt) == 0) {
			copy_kern(kern, sharp);
			ok = 1;
		}
		if (strcmp(" BLUR\n", opt) == 0) {
			copy_kern(kern, blur);
			ok = 1;
		}
		if (strcmp(" GAUSSIAN_BLUR\n", opt) == 0) {
			copy_kern(kern, gur);
			ok = 1;
		}
		rotate_0(img, cpy); // copiem matricea
		int row = img->rows - 1, col = img->cols - 1;
		// daca filtrul e valid il aplicam in cadrul selectiei, dar nu
		// pe marginile imaginii
		if (ok == 1) {
			for (int i = img->y1; i < img->y2; i++)
				for (int j = img->x1; j < img->x2; j++)
					if (i != 0 && j != 0 && i != row && j != col) {
						img->r[i][j] = multir(i, j, cpy, kern);
						img->g[i][j] = multig(i, j, cpy, kern);
						img->b[i][j] = multib(i, j, cpy, kern);
					}
		// afisam mesajele corespunzatoare si eliberam copia imaginii
		opt[strlen(opt) - 1] = '\0';
		printf("APPLY%s done\n", opt);
		free_img(&cpy);
		return 0;
		}
		printf("APPLY parameter invalid\n");
		free_img(&cpy);
		return 0;
	}
	return 0;
}
