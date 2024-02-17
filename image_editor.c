// Copyright 2021 Andrei Calin-Mihail 311CA
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "image.h"
#include "utils.h"
#include "load.h"
#include "select.h"
#include "rotate.h"
#include "crop.h"
#include "apply.h"
#include "save.h"

int main(void)
{
	FILE *input = NULL, *output = NULL; // fisierele de input/output
	image img; // structura care retine informatiile legate de o imagine
	int nr = 0, ok = 0; // ok verifica validitatea unei comenzi
					// nr verifica daca exista o imagine incarcata in memorie
	char cmnd[100], dump[100];
	scanf("%s", cmnd); // se citeste o comanda

	// cat timp nu se citeste comanda EXIT
	while (strcmp("EXIT", cmnd) != 0) {
		ok = 0;

		// se apeleaza comanda de incarcare a unei imagini in memorie
		if (strcmp("LOAD", cmnd) == 0) {
			LOAD(input, &img, &nr);
			ok = 1;
		}

		// se apeleaza comanda care schimba selectia curenta
		if (strcmp("SELECT", cmnd) == 0) {
			SELECT(&img, &nr);
			ok = 1;
		}

		// se apeleaza comanda care roteste selectia curenta
		if (strcmp("ROTATE", cmnd) == 0) {
			ROTATE(&img, &nr);
			ok = 1;
		}

		// se apeleaza comanda care reduce poza la selectia curenta
		if (strcmp("CROP", cmnd) == 0) {
			CROP(&img, &nr);
			ok = 1;
		}

		// se apeleaza comanda care aplica un anumit filtru selectiei curente
		if (strcmp("APPLY", cmnd) == 0) {
			APPLY(&img, &nr);
			ok = 1;
		}

		// se apeleaza comanda care salveaza intr-un fisier imaginea curenta
		if (strcmp("SAVE", cmnd) == 0) {
			SAVE(output, &img, &nr);
			ok = 1;
		}

		// in cazul in care comanda este invalida tot ce este scris pe randul
		// respectiv este irelevant
		if (ok == 0 && nr != 0) {
			printf("Invalid command\n");
			fgets(dump, 100, stdin);
		}

		// se citeste o noua comanda
		scanf("%s", cmnd);
	}

	// tratam si cazul in care se apeleaza comanda EXIT fara o imagine incarcata
	if (strcmp("EXIT", cmnd) == 0 && nr == 0)
		printf("No image loaded\n");

	// in cazul in care este o imagine incarcata in memorie se elibereaza
	// toate resursele
	if (nr != 0)
		free_img(&img);
	return 0;
}
