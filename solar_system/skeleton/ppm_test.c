/* 
 * Jacob Massengill -- test_ppm.c -- February 2017
 * copies one ppm file to another
 */

#include <stdio.h>
#include "ppm.h"

int main(int argc, char **argv){
    
    if(argc < 3){
        fprintf(stderr, "Usage: ./ppmtest orig.ppm copy.ppm\n");
        return 1;
    }
    PPM image = snew_PPM(argv[1]);
    if(image == NULL){
        fprintf(stderr, "image read fail\n");
        return 1;
    }
    swrite_PPM(argv[2], image);
    free_PPM(image);
    return 0;
}
