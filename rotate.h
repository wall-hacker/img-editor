// Copyright 2021 Andrei Calin-Mihail 311CA
#pragma once
#include <stdio.h>
#include <stdlib.h>
#include "image.h"
#include "utils.h"

void rotate_90_right_rectangle(image * img, image cpy);
void rotate_90_left_rectangle(image *img, image cpy);
void rotate_180_rectangle(image *img, image cpy);
void rotate_90_left(image *img, image cpy);
void rotate_90_right(image *img, image cpy);
void rotate_180(image *img, image cpy);
void rotate_0(image *img, image cpy);
int ROTATE(image *img, int *nr);
