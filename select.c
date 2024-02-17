// Copyright 2021 Andrei Calin-Mihail 311CA
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "image.h"
#include "utils.h"

// functia care executa comanda care schimba selectia curenta
int SELECT(image *img, int *nr)
{
	char opt[100];
	int ind = 0, x1, y1, x2, y2;
	fgets(opt, 100, stdin);
	// pentru citirea parametrilor comenzii SELECT folosim strtok
	// pentru a separa in "termeni" variabila opt
	char *term;
	term = strtok(opt, "\n ");
	while (term) {
		// pentru "ALL", daca este incarcata, se va selecta intreaga imagine
		if (strcmp("ALL", term) == 0) {
			img->x1 = 0;
			img->y1 = 0;
			img->x2 = img->cols;
			img->y2 = img->rows;
			if (*nr == 0)
				printf("No image loaded\n");
			else
				printf("Selected ALL\n");
			return 0;
		}
		// daca parametrul nu este "ALL", dar incepe cu o litera
		// comanda este invalida
		if (isalpha(term[0]) > 0) {
			printf("Invalid command\n");
			return 0;
		}
		// in cazul numerelor vom retine cele 4 "coordonate"
		if (ind == 0)
			x1 = atoi(term);
		if (ind == 1)
			y1 = atoi(term);
		if (ind == 2)
			x2 = atoi(term);
		if (ind == 3)
			y2 = atoi(term);
		ind++;
		term = strtok(NULL, "\n ");
	}
	// daca sunt mai mult sau mai putin de 4 parametrii comanda este invalida
	if (ind != 4) {
		printf("Invalid command\n");
		return 0;
	}
	// interschimbam coordonatele astfel incat x1 < x2 si y1 < y2 pentru a
	// putea parcurge selectia mai usor
	if (x1 > x2)
		swap(&x1, &x2);
	if (y1 > y2)
		swap(&y1, &y2);
	// afisam pe ecran mesajele conform cerintei tratand separat cazurile in
	// care coordonatele selectiei nu sunt valide
	if (*nr == 0) {
		printf("No image loaded\n");
	} else {
		if (x1 < 0 || y1 < 0 || x2 > img->cols || y2 > img->rows) {
			printf("Invalid set of coordinates\n");
			return 0;
		}
		if (x1 == x2 && y1 == y2 && x1 == y1) {
			printf("Invalid set of coordinates\n");
			return 0;
		}
		if (y1 == y2) {
			printf("Invalid set of coordinates\n");
			return 0;
		}
		if (x1 == x2) {
			printf("Invalid set of coordinates\n");
			return 0;
		}
		printf("Selected %d %d %d %d\n", x1, y1, x2, y2);
		img->x1 = x1;
		img->y1 = y1;
		img->x2 = x2;
		img->y2 = y2;
	}
	return 0;
}
