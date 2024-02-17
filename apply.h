// Copyright 2021 Andrei Calin-Mihail 311CA
#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "image.h"
#include "utils.h"
#include "rotate.h"

double clamp(double x);
double multir(int i, int j, image cpy, double kern[3][3]);
double multig(int i, int j, image cpy, double kern[3][3]);
double multib(int i, int j, image cpy, double kern[3][3]);
void copy_kern(double kern[3][3], double source[3][3]);
int APPLY(image *img, int *nr);
