/*
 * Jacob Massengill -- rotater.h -- February 2017
 * this file declares an object for representing the rotation
 * of an object in 3D space along a single plane
 */ 
#ifndef ROTATER_H
#define ROTATER_H

#define PI 3.1415927

typedef struct rotater {
    float angle;
    float da;
} *rotater_t;

rotater_t new_rotater(float da);
void free_rotater(rotater_t r);
float rotater_rotate(rotater_t r);

#endif //ROTATER_H
