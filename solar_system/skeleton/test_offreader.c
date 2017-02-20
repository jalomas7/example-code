/*
 * Jacob Massengill -- test_offreader.c -- February 2017
 * This file loads a jmesh object from stdin and prints it's information to
 * stdout.
 */ 
#include <stdio.h>
#include <stdlib.h>
#include "offreader.h"
#include "jmesh.h"

int main(void) {

    jmesh * mesh = new_jmesh(stdin, &load_off_mesh);
    if (mesh == NULL){
        fprintf(stderr,"load_off_mesh failed\n");
        return 1;
    }

    print_stats(mesh);
    free_jmesh(mesh);

    return 0;
}
