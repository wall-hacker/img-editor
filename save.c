// Copyright 2021 Andrei Calin-Mihail 311CA
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "image.h"
#include "utils.h"

// functia care executa comanda care salveaza intr-un fisier imaginea curenta
int SAVE(FILE *output, image *img, int *nr)
{
	if (*nr == 0) {
		printf("No image loaded\n");
	} else {
		int x = 0;
		char file_name[100];
		char buf;
		scanf("%c", &buf);
		// separam stringul "file_name" folosind strtok si determinam daca
		// avem sau nu parametrul "ascii"
		fgets(file_name, 100, stdin);
		char *opt;
		opt = strtok(file_name, "\n ");
		while (opt) {
			x++;
			if (x == 2)
				if (strcmp("ascii", opt) == 0)
					x = -1; // x devine -1 doar daca se regaseste "ascii"
			opt = strtok(NULL, "\n ");
		}

		if (x == -1) { // in cazul "ascii" deschidem fisierul pentru scriere
			output = fopen(file_name, "wt");
			if (strstr("P2P5", img->magic_number)) {
				fprintf(output, "P2\n"); // scriem nr magic corespunzator
				fprintf(output, "%d %d\n", img->cols, img->rows);
				fprintf(output, "%d\n", img->max_value);
				for (int i = 0; i < img->rows; i++) { // scriem grayscale
					for (int j = 0; j < img->cols; j++)
						fprintf(output, "%d ", (int)(round(img->matrix[i][j])));
					fprintf(output, "\n");
				}
			}
			if (strstr("P3P6", img->magic_number)) {
				fprintf(output, "P3\n"); // scriem nr magic corespunzator
				fprintf(output, "%d %d\n", img->cols, img->rows);
				fprintf(output, "%d\n", img->max_value);
				for (int i = 0; i < img->rows; i++) { // scriem color
					for (int j = 0; j < img->cols; j++) {
						fprintf(output, "%d ", (int)(round(img->r[i][j])));
						fprintf(output, "%d ", (int)(round(img->g[i][j])));
						fprintf(output, "%d ", (int)(round(img->b[i][j])));
					}
					fprintf(output, "\n");
				}
			}
			fclose(output);
		} else { // in cazul "ascii" deschidem fisierul pentru scriere in binar
			output = fopen(file_name, "wb");
			if (strstr("P2P5", img->magic_number)) {
				fprintf(output, "P5\n"); // scriem nr magic corespunzator
				fprintf(output, "%d %d\n", img->cols, img->rows);
				fprintf(output, "%d\n", img->max_value);
				for (int i = 0; i < img->rows; i++) // scriem grayscale binar
					for (int j = 0; j < img->cols; j++) {
						int aux = (int)(round(img->matrix[i][j]));
						fwrite(&aux, sizeof(unsigned char), 1, output);
					}
			}
			if (strstr("P3P6", img->magic_number)) {
				fprintf(output, "P6\n"); // scriem nr magic corespunzator
				fprintf(output, "%d %d\n", img->cols, img->rows);
				fprintf(output, "%d\n", img->max_value);
				for (int i = 0; i < img->rows; i++) // scriem color binar
					for (int j = 0; j < img->cols; j++) {
						int aux = (int)(round(img->r[i][j]));
						fwrite(&aux, sizeof(unsigned char), 1, output);
						aux = (int)(round(img->g[i][j]));
						fwrite(&aux, sizeof(unsigned char), 1, output);
						aux = (int)(round(img->b[i][j]));
						fwrite(&aux, sizeof(unsigned char), 1, output);
					}
			}
			fclose(output); // inchidem fisierul de output
		}
		printf("Saved %s\n", file_name); // afisam mesajul corespunzator
	}
	return 0;
}

// folosim functia round pentru a face aproximarile necesare, si prin variabila
// aux dam cast la tipul int
