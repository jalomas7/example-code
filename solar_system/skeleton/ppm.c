/*
 * Jacob Massengill -- ppm.c -- February 2017
 * defines operations for creating and altering PPM files
 */ 
#include "ppm.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

RGB new_RGB(uchar R, uchar G, uchar B){
    RGB rgb;
    rgb.R = R; rgb.G = G; rgb.B = B;
    return rgb;
}

//creates a new PPM object from fp, assumes 
//only the P6 file format of maxsize 255
PPM fnew_PPM(FILE *fp){ 
    int width, height, maxsize;
    char type[2];
    PPM image;

    int temp = fscanf(fp, "%s\n%d %d\n%d\n", type,  &width, &height, &maxsize);

    if(strcmp(type, "P6") != 0){
        fputs("not a PPM file\n", stderr);
        image = NULL;
        return image;
    }

    image = malloc(sizeof(struct ppm));
    image->width = width;
    image->height = height;
    image->data = malloc(width*height*sizeof(struct rgb));

    if(fread(image->data, sizeof(struct rgb), width*height, fp) != width*height){
        fputs("could not read PPM file\n", stderr);
        image = NULL;
    }

    return image;
}

PPM snew_PPM(const char *fn){
    FILE *fp;
    if((fp = fopen(fn, "r"))==NULL) return NULL;
    PPM image = fnew_PPM(fp);
    fclose(fp); return image;
}

//create a ppm object with width w and height h
PPM dnew_PPM(int w, int h){
    PPM image = malloc(sizeof(struct ppm));
    image->width = w;
    image->height = h;
    image->data = malloc(w*h*3*sizeof(uchar));
    RGB black = new_RGB(0,0,0);

    //initialize to black
    for(int i=0; i < w*h; i++){
        image->data[i].R = black.R; 
    }
    return image;
}

void free_PPM(PPM image){
    if(!image) return;
    if(image->data){
        free(image->data);
    }
    free(image);
}

void fread_PPM(FILE *fp, PPM image){
    free_PPM(image);
    image = fnew_PPM(fp);
}

void sread_PPM(const char *fn, PPM image){
    free_PPM(image);
    image = snew_PPM(fn);
}

//write image to fp, assumes fp is good
void fwrite_PPM(FILE *fp, PPM image){
    fprintf(fp, "P6\n%d %d\n255\n", image->width, image->height);
    fwrite(image->data, sizeof(RGB), image->width*image->height, fp);
}

void swrite_PPM(const char *fn, PPM image){
    FILE *fp;
    if((fp=fopen(fn, "w"))==NULL) return;
    fwrite_PPM(fp, image);
    fclose(fp);
}

//clears the entire ppm object to color
void apply_color(PPM image, RGB color){
    for(int i=0; i < image->width*image->height; i++){
        image->data[i] = color;
    }
}
