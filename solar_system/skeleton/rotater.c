/*
 * Jacob Massengill -- rotater.c -- February 2017
 * decleares operations for an object which represents
 * spinning for another object
 */

#include <stdlib.h>
#include <math.h>
#include "rotater.h"

rotater_t new_rotater(float da){
    rotater_t r = malloc(sizeof(struct rotater));
    r->da = da;
    r->angle = 0;
    return r;
}

void free_rotater(rotater_t r){
    free(r);
}

//returns the new value of r->angle
float rotater_rotate(rotater_t r){
    return fmodf(r->angle+=r->da, 2*PI);
}

