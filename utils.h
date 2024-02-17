// Copyright 2021 Andrei Calin-Mihail 311CA
#pragma once
#include <stdio.h>
#include <stdlib.h>
#include "image.h"

double **alloc_matrix(int rows, int cols);
void free_img(image *img);
void swap(int *x, int *y);
