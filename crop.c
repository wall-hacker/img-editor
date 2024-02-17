// Copyright 2021 Andrei Calin-Mihail 311CA
#include <stdio.h>
#include <stdlib.h>
#include "image.h"
#include "utils.h"

// functia care executa comanda care reduce poza la selectia curenta
int CROP(image *img, int *nr)
{
	if (*nr == 0) {
		printf("No image loaded\n");
	} else {
		// facem o copie a imaginii
		image cpy = *img;

		// realocam matricele imaginii cu dimensiunile selectiei
		img->rows = img->y2 - img->y1;
		img->cols = img->x2 - img->x1;
		img->matrix = alloc_matrix(img->rows, img->cols);
		img->r = alloc_matrix(img->rows, img->cols);
		img->g = alloc_matrix(img->rows, img->cols);
		img->b = alloc_matrix(img->rows, img->cols);

		// mutam elementele selectiei din copie in matricea realocata
		for (int i = 0; i < img->rows; i++)
			for (int j = 0; j < img->cols; j++) {
				img->matrix[i][j] = cpy.matrix[i + img->y1][j + img->x1];
				img->r[i][j] = cpy.r[i + img->y1][j + img->x1];
				img->g[i][j] = cpy.g[i + img->y1][j + img->x1];
				img->b[i][j] = cpy.b[i + img->y1][j + img->x1];
			}

		// schimbam selectia in asa fel incat toata imaginea sa fie selectata
		img->x1 = 0;
		img->y1 = 0;
		img->x2 = img->cols;
		img->y2 = img->rows;

		// eliberam copia si afisam mesajul corespunzator
		free_img(&cpy);
		printf("Image cropped\n");
	}
	return 0;
}
