/*
 * Jacob Massengill -- ppm.h -- February 2017
 * declares objects and operations for creating and editing ppm files
 */ 
#ifndef PPM_H
#define PPM_H

#include <stdio.h>
typedef unsigned char uchar;
typedef struct rgb {
    uchar R,G,B;
} RGB;

typedef struct ppm {
    int width, height;
    RGB *data;
}* PPM;

RGB new_RGB(uchar R, uchar G, uchar B);

//generates a PPM object from the file fp
PPM fnew_PPM(FILE *fp);
PPM snew_PPM(const char *fn);

//generate a PPM object from scratch
PPM dnew_PPM(int w, int h);

//clears image to color
void apply_color(PPM image, RGB color);
void free_PPM(PPM image);
void fread_PPM(FILE *fp, PPM image);
void sread_PPM(const char *fn, PPM image);
void fwrite_PPM(FILE *fp, PPM image);
void swrite_PPM(const char *fn, PPM image);

#endif //PPM_H
