/*
 * Jacob Massengill -- offreader.h -- February 2017
 * declares the api for reading off files
 */ 
#ifndef OFFREADER_H
#define OFFREADER_H

#include "utils.h" 
#include "jmesh.h"

/* return value: number of vertices upon success, -1 upon failure*/
int load_off_mesh(FILE *, jmesh *);

#endif //OFFREADER_H
