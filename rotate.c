// Copyright 2021 Andrei Calin-Mihail 311CA
#include <stdio.h>
#include <stdlib.h>
#include "image.h"
#include "utils.h"

// functia care roteste intreaga imagine 90 de grade la dreapta
void rotate_90_right_rectangle(image *img, image cpy)
{
	for (int i = 0; i < img->rows; i++)
		for (int j = 0; j < img->cols; j++) {
			img->matrix[i][j] = cpy.matrix[img->y2 - 1 - j][i];
			img->r[i][j] = cpy.r[img->y2 - 1 - j][i];
			img->g[i][j] = cpy.g[img->y2 - 1 - j][i];
			img->b[i][j] = cpy.b[img->y2 - 1 - j][i];
		}
}

// functia care roteste intreaga imagine 90 de grade la stanga
void rotate_90_left_rectangle(image *img, image cpy)
{
	for (int i = 0; i < img->rows; i++)
		for (int j = 0; j < img->cols; j++) {
			img->matrix[i][j] = cpy.matrix[j][img->x2 - 1 - i];
			img->r[i][j] = cpy.r[j][img->x2 - 1 - i];
			img->g[i][j] = cpy.g[j][img->x2 - 1 - i];
			img->b[i][j] = cpy.b[j][img->x2 - 1 - i];
		}
}

// functia care roteste intreaga imagine 180 de grade
void rotate_180_rectangle(image *img, image cpy)
{
	for (int i = 0; i < img->rows; i++)
		for (int j = 0; j < img->cols; j++) {
			img->matrix[i][j] =
				cpy.matrix[img->rows - 1 - i][img->cols - 1 - j];
			img->r[i][j] = cpy.r[img->rows - 1 - i][img->cols - 1 - j];
			img->g[i][j] = cpy.g[img->rows - 1 - i][img->cols - 1 - j];
			img->b[i][j] = cpy.b[img->rows - 1 - i][img->cols - 1 - j];
		}
}

// functia care roteste o selectie 90 de grade la dreapta
void rotate_90_right(image *img, image cpy)
{
	for (int i = 0; i < img->rows; i++)
		for (int j = 0; j < img->cols; j++) {
			img->matrix[i][j] = cpy.matrix[i][j];
			img->r[i][j] = cpy.r[i][j];
			img->g[i][j] = cpy.g[i][j];
			img->b[i][j] = cpy.b[i][j];
		}
	for (int i = 0; i < img->y2 - img->y1; i++)
		for (int j = 0; j < img->x2 - img->x1; j++) {
			img->matrix[i + img->y1][j + img->x1] =
				cpy.matrix[img->y2 - j - 1][i + img->x1];
			img->r[i + img->y1][j + img->x1] =
				cpy.r[img->y2 - j - 1][i + img->x1];
			img->g[i + img->y1][j + img->x1] =
				cpy.g[img->y2 - j - 1][i + img->x1];
			img->b[i + img->y1][j + img->x1] =
				cpy.b[img->y2 - j - 1][i + img->x1];
			}
}

// functia care roteste o selectie 90 de grade la stanga
void rotate_90_left(image *img, image cpy)
{
	for (int i = 0; i < img->rows; i++)
		for (int j = 0; j < img->cols; j++) {
			img->matrix[i][j] = cpy.matrix[i][j];
			img->r[i][j] = cpy.r[i][j];
			img->g[i][j] = cpy.g[i][j];
			img->b[i][j] = cpy.b[i][j];
		}
	for (int i = 0; i < img->y2 - img->y1; i++)
		for (int j = 0; j < img->x2 - img->x1; j++) {
			img->matrix[i + img->y1][j + img->x1] =
				cpy.matrix[j + img->y1][img->x2 - i - 1];
			img->r[i + img->y1][j + img->x1] =
				cpy.r[j + img->y1][img->x2 - i - 1];
			img->g[i + img->y1][j + img->x1] =
				cpy.g[j + img->y1][img->x2 - i - 1];
			img->b[i + img->y1][j + img->x1] =
				cpy.b[j + img->y1][img->x2 - i - 1];
			}
}

// functia care roteste o selectie 180 de grade
void rotate_180(image *img, image cpy)
{
	for (int i = 0; i < img->rows; i++)
		for (int j = 0; j < img->cols; j++) {
			img->matrix[i][j] = cpy.matrix[i][j];
			img->r[i][j] = cpy.r[i][j];
			img->g[i][j] = cpy.g[i][j];
			img->b[i][j] = cpy.b[i][j];
		}
	for (int i = 0; i < img->y2 - img->y1; i++)
		for (int j = 0; j < img->x2 - img->x1; j++) {
			img->matrix[i + img->y1][j + img->x1] =
				cpy.matrix[img->y2 - i - 1][img->x2 - j - 1];
			img->r[i + img->y1][j + img->x1] =
				cpy.r[img->y2 - i - 1][img->x2 - j - 1];
			img->g[i + img->y1][j + img->x1] =
				cpy.g[img->y2 - i - 1][img->x2 - j - 1];
			img->b[i + img->y1][j + img->x1] =
				cpy.b[img->y2 - i - 1][img->x2 - j - 1];
			}
}

// functia care roteste o selectie 0 de grade (in esenta o functie de copiere)
void rotate_0(image *img, image cpy)
{
	for (int i = 0; i < img->rows; i++)
		for (int j = 0; j < img->cols; j++) {
			img->matrix[i][j] = cpy.matrix[i][j];
			img->r[i][j] = cpy.r[i][j];
			img->g[i][j] = cpy.g[i][j];
			img->b[i][j] = cpy.b[i][j];
		}
}

// functia care executa comanda care roteste selectia curenta
int ROTATE(image *img, int *nr)
{
	if (*nr == 0) {
		printf("No image loaded\n");
		return 0;
	}
	int angle, ok = 0;
	scanf("%d", &angle); // citim unghiul de rotire
	image cpy = *img; // facem o copie a imaginii
	int col = img->cols, row = img->rows;
	if ((img->x2 - img->x1) != (img->y2 - img->y1)) { // selectie dreptunghi
		if (img->x1 == 0 && img->y1 == 0 && img->x2 == col && img->y2 == row) {
			if (angle == -90 || angle == 270 || angle == 90 || angle == -270)
				swap(&img->cols, &img->rows);
			// realocam matricele imaginii
			img->matrix = alloc_matrix(img->rows, img->cols);
			img->r = alloc_matrix(img->rows, img->cols);
			img->g = alloc_matrix(img->rows, img->cols);
			img->b = alloc_matrix(img->rows, img->cols);
			if (angle == -90 || angle == 270) {
				rotate_90_left_rectangle(img, cpy);
				ok = 1;
				swap(&img->x2, &img->y2);
			}
			if (angle == 90 || angle == -270) {
				rotate_90_right_rectangle(img, cpy);
				ok = 1;
				swap(&img->x2, &img->y2);
			}
			if (angle == -180 || angle == 180) {
				rotate_180_rectangle(img, cpy);
				ok = 1;
			}
			if (angle == 0 || angle == -360 || angle == 360) {
				rotate_0(img, cpy);
				ok = 1;
			}
			if (ok == 1) // daca rotirea a fost efectuata eliberam copia
				free_img(&cpy);
			} else {
				printf("The selection must be square\n");
				return 0;
			}
		} else { // selectie patrata
			// realocam matricele imaginii
			img->matrix = alloc_matrix(img->rows, img->cols);
			img->r = alloc_matrix(img->rows, img->cols);
			img->g = alloc_matrix(img->rows, img->cols);
			img->b = alloc_matrix(img->rows, img->cols);
			if (angle == -90 || angle == 270) {
				rotate_90_left(img, cpy);
				ok = 1;
			}
			if (angle == 90 || angle == -270) {
				rotate_90_right(img, cpy);
				ok = 1;
			}
			if (angle == -180 || angle == 180) {
				rotate_180(img, cpy);
				ok = 1;
			}
			if (angle == 0 || angle == -360 || angle == 360) {
				rotate_0(img, cpy);
				ok = 1;
			}
			if (ok == 1) // daca rotirea a fost efectuata eliberam copia
				free_img(&cpy);
		}
		// daca rotirea a/(nu a fost) efectuata afisam mesajul corespunzator
		if (ok == 1) {
			printf("Rotated %d\n", angle);
		} else {
			rotate_0(img, cpy);
			printf("Unsupported rotation angle\n");
			free_img(&cpy);
		}
	return 0;
}
