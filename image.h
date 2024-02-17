// Copyright 2021 Andrei Calin-Mihail 311CA
#pragma once

typedef struct {
	double **matrix; // matricea care retine pixelii imaginii grayscale
	double **r, **g, **b; // matricele care retine pixelii imaginii color
	int rows, cols; // dimensiunile matricei curente
	int max_value; // valoarea maxima a pixelilor (de obicei 255)
	char magic_number[3]; // numarul magic care determina formatul imaginii
	int x1, y1, x2, y2; // coordonatele selectiei curente
} image;
