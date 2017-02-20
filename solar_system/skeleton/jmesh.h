/*
 * Jacob Massengill -- jmesh.h -- February 2017
 * This file defines the jmesh object, which represents a mesh of triangles.
 */

#ifndef JMESH_H
#define JMESH_H

#include <stdio.h>

//gives the xyz component of vertex i
#define getX(jm, i) &jm->vertices[i*3]
#define getY(jm, i) &jm->vertices[i*3+1]
#define getZ(jm, i) &jm->vertices[i*3+2]

//gives the vertices of triangle i
#define getV1(jm, i) &jm->triangles[i*3]
#define getV2(jm, i) &jm->triangles[i*3+1]
#define getV3(jm, i) &jm->triangles[i*3+2]

//gets the value of the surface normal for triangle i
#define getSurfaceNormX(jm, i) &jm->normals[jm->nvert*3+3*i]
#define getSurfaceNormY(jm, i) &jm->normals[jm->nvert*3+3*i+1]
#define getSurfaceNormZ(jm, i) &jm->normals[jm->nvert*3+3*i+2]

//gets the vertex normal of vertex i
#define getVertexNormX(jm, i) &jm->normals[i*3]
#define getVertexNormY(jm, i) &jm->normals[i*3+1]
#define getVertexNormZ(jm, i) &jm->normals[i*3+2]

//gets the center of the mesh
#define getCenterX(jm) &jm->center[0]
#define getCenterY(jm) &jm->center[1]
#define getCenterZ(jm) &jm->center[2]

typedef struct {
    int nvert;
    int ntri;
    float *vertices;
    float *normals;
    int *triangles;
    float center[3];
} jmesh;


/* return value: pointer to jmesh upon success, NULL upon failure
 * mesh_loader must return the number of vertices on true, -1 on false
 * mesh_loader must allocate memory for vertices, normals, and triangles*/
jmesh * new_jmesh(FILE*, int (*mesh_loader)(FILE*, jmesh*));

void free_jmesh(jmesh *);
void get_bounding_box(jmesh *jm, float *minmax);
void get_centroid(jmesh *jm, float *center);
void print_stats(jmesh *jm);

#endif //JMESH_H

