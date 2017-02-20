/* 
 * Jacob Massengill -- jmesh.c -- February 2017
 * This file defines the necessary functions for jmesh operations.
 */
#include <stdlib.h>
#include <limits.h>
#include "jmesh.h"
#include "offreader.h"

//returns a pointer to a new jmesh object or null on failure
jmesh * new_jmesh(FILE * fp, int (*mesh_loader)(FILE*, jmesh*)) {
    jmesh *jm;

    jm = malloc(sizeof(jmesh));

    if(!jm)return NULL;
    if(mesh_loader(fp, jm) == -1) return NULL;

    return jm;
}

//free vertices, triangles, and normals
void free_jmesh(jmesh *mesh){
    if(!mesh) return;
    if(mesh->vertices)  free(mesh->vertices);
    if(mesh->triangles) free(mesh->triangles);
    if(mesh->normals)   free(mesh->normals);
    free(mesh);
}

//fills minmax with the max/min xyz in that order
void get_bounding_box(jmesh *jm, float *minmax){

    //initialize minmax
    minmax[0] = LONG_MIN;
    minmax[1] = LONG_MIN;
    minmax[2] = LONG_MIN;
    minmax[3] = LONG_MAX;
    minmax[4] = LONG_MAX;
    minmax[5] = LONG_MAX;

    //find minimum and maximum values
    for(int i=0; i < jm->nvert; i++){
        float vert[3];

        //get this vertex
        vert[0] = *getX(jm, i);
        vert[1] = *getY(jm, i);
        vert[2] = *getZ(jm, i);

        if(vert[0] > minmax[0]) minmax[0] = vert[0];
        if(vert[1] > minmax[1]) minmax[1] = vert[1];
        if(vert[2] > minmax[2]) minmax[2] = vert[2];
        if(vert[0] < minmax[3]) minmax[3] = vert[0];
        if(vert[1] < minmax[4]) minmax[4] = vert[1];
        if(vert[2] < minmax[5]) minmax[5] = vert[2];

    }
}

//returns the center point of jm in center
void get_centroid(jmesh *jm, float *center){
    float minmax[6];
    get_bounding_box(jm, minmax);
    center[0] = (minmax[0]+minmax[3])/2;
    center[1] = (minmax[1]+minmax[4])/2;
    center[2] = (minmax[2]+minmax[5])/2;
}


//print nverts, ntris, bounding box, and centroid
void print_stats(jmesh *jm){
    float minmax[6];
    get_bounding_box(jm, minmax);


    printf(
            "Number of vertices = %d\n"
            "Number of triangles = %d\n"
            "Bounding box: \n"
            "  Top-Right:    (%.4f, %.4f, %.4f)\n"
            "  Bottom-Left:  (%.4f, %.4f, %.4f)\n"
            "  Center:       (%.4f, %.4f, %.4f)\n",
            jm->nvert, jm->ntri,
            minmax[0], minmax[1], minmax[2], minmax[3], minmax[4], minmax[5],
            (minmax[0]+minmax[3])/2, (minmax[1]+minmax[4])/2,
            (minmax[2]+minmax[5])/2);
}
