// Copyright 2021 Andrei Calin-Mihail 311CA
#include <stdio.h>
#include <stdlib.h>
#include "image.h"

// functie de alocare dinamica pentru matrice de tip double
double **alloc_matrix(int rows, int cols)
{
	double **mat = (double **)calloc(rows, sizeof(double *));

	if (!mat)
		exit(-1);

	for (int i = 0; i < rows; i++)
		mat[i] = (double *)calloc(cols, sizeof(double));

	return mat;
}

// functie de eliberare a tuturor matricelor din structura image
void free_img(image *img)
{
	for (int i = 0; i < img->rows; i++)
		free(img->matrix[i]);
	free(img->matrix);

	for (int i = 0; i < img->rows; i++)
		free(img->r[i]);
	free(img->r);

	for (int i = 0; i < img->rows; i++)
		free(img->g[i]);
	free(img->g);

	for (int i = 0; i < img->rows; i++)
		free(img->b[i]);
	free(img->b);
}

// o simpla functie de swap :)
void swap(int *x, int *y)
{
	int aux = *x;
	*x = *y;
	*y = aux;
}
