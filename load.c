// Copyright 2021 Andrei Calin-Mihail 311CA
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "image.h"
#include "utils.h"

// functia care executa comanda de incarcare a unei imagini in memorie
int LOAD(FILE *input, image *img, int *nr)
{
	int cur_pos;
	char file_name[100];
	// deschidem fisierul pentru citire si aplicam programarea defensiva
	scanf("%s", file_name);
	input = fopen(file_name, "rt");
	if (!input) {
		printf("Failed to load %s\n", file_name);
		if (*nr != 0)
			free_img(img);
		*nr = 0;
		return 0;
	}
	// in caz ca avem o imagine incarcata o vom elibera
	if (*nr != 0)
		free_img(img);
	// citim numarul magic, dimensiunile si valoarea maxima a imaginii
	fgets(img->magic_number, 3, input);
	fscanf(input, "%d %d", &img->cols, &img->rows);
	fscanf(input, "%d", &img->max_value);
	cur_pos = ftell(input); // retinem pozitia cursorului
	// alocam dinamic matricele care stocheaza pixelii imaginii
	img->matrix = alloc_matrix(img->rows, img->cols);
	img->r = alloc_matrix(img->rows, img->cols);
	img->g = alloc_matrix(img->rows, img->cols);
	img->b = alloc_matrix(img->rows, img->cols);
	// in cazul in care imaginea este binara vom deschide fisierul in modul
	// de citire din binar
	if (strstr("P5P6", img->magic_number)) {
		fclose(input);
		input = fopen(file_name, "rb");
		if (!input) {
			printf("Failed to load %s\n", file_name);
			fclose(input);
			return 0;
		}
		fseek(input, cur_pos + 1, SEEK_SET); //  ne mutam la pozitia retinuta
		// citim matricea in functie de magic number (grayscale / color)
		if (strcmp("P5", img->magic_number) == 0) // grayscale
			for (int i = 0; i < img->rows; i++)
				for (int j = 0; j < img->cols; j++) {
					unsigned char aux;
					fread(&aux, sizeof(unsigned char), 1, input);
					img->matrix[i][j] = aux;
				}
		if (strcmp("P6", img->magic_number) == 0) // color
			for (int i = 0; i < img->rows; i++)
				for (int j = 0; j < img->cols; j++) {
					unsigned char aux;
					fread(&aux, sizeof(unsigned char), 1, input);
					img->r[i][j] = aux;
					fread(&aux, sizeof(unsigned char), 1, input);
					img->g[i][j] = aux;
					fread(&aux, sizeof(unsigned char), 1, input);
					img->b[i][j] = aux;
				}
	} else {
		// in cazul in care matricele sunt de tip ascii doar le citim
		// in functie de magic number (grayscale / color)
		if (strcmp("P2", img->magic_number) == 0) // grayscale
			for (int i = 0; i < img->rows; i++)
				for (int j = 0; j < img->cols; j++)
					fscanf(input, "%le", &img->matrix[i][j]);
		if (strcmp("P3", img->magic_number) == 0) // color
			for (int i = 0; i < img->rows; i++)
				for (int j = 0; j < img->cols; j++) {
					fscanf(input, "%le", &img->r[i][j]);
					fscanf(input, "%le", &img->g[i][j]);
					fscanf(input, "%le", &img->b[i][j]);
				}
	}
	// initializam selctia in asa fel incat toata imaginea este selectata
	img->x1 = 0;
	img->y1 = 0;
	img->x2 = img->cols;
	img->y2 = img->rows;
	fclose(input);
	*nr = *nr + 1; // avem o imagine incarcata in memorie
	printf("Loaded %s\n", file_name);
	return 0;
}
