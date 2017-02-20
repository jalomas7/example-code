/*
 * Jacob Massengill -- offreader.c -- February 2017
 * this file defines operations for reading and writing .off files
 */

#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "offreader.h"
#include "jmesh.h"

#define NTRIVERTS 3

//chews through a line until it reaches a new line
void skip_line(FILE* fp){
    while(fgetc(fp) != '\n');
}

//checks that the first line in the file is "OFF"
int is_off_file(FILE* fp){
    char off[4];
    char *temp = fgets(off, 4, fp);
    return strcmp(off, "OFF");
}

//gets nverts nfaces nedges from the file
//ignores the edges
int get_verts_faces(FILE *fp, jmesh *jm){
    int temp;
    int i = fscanf(fp, "%d %d %d\n", &jm->nvert, &jm->ntri, &temp); 
    jm->vertices = malloc(jm->nvert*3*sizeof(float));
    return i;
}

//gets the x,y,z coordinates from the off file
int get_tuples(FILE *fp, jmesh *jm){
    int status, line=0;
    for(int i=0; i < jm->nvert; i++){
        status=fscanf(fp, "%f %f %f", getX(jm, i), getY(jm, i), getZ(jm, i)); 
        line++;
        if(status != 3){
            return line;
        }
        skip_line(fp);
    }
    return line;
}

//returns the number of tris in the file
int get_tris(FILE *fp, jmesh *jm){
    fpos_t pos;
    fgetpos(fp, &pos); //get the start of the faces section
    int nVerts, sum_tris = 0;
    for(int i=0; i < jm->ntri; i++){
        int temp = fscanf(fp, "%d", &nVerts);
        sum_tris+= nVerts-2; 
        skip_line(fp); //we only care about the number of vertices
    }

    fsetpos(fp, &pos); //go back to the start of the start of the faces section
    return sum_tris;
}

//splits the current line into triangles. 
//returns the number of triangles this line creates
int split_polygon(FILE *fp, jmesh *jm){
    int nVerts;
    static int which_tri=0;
    int temp=fscanf(fp, "%d", &nVerts); //how many vertices do we have for this face?
    if(temp != 1){
        return -1;
    }

    //get the vertices
    int verts[nVerts];
    for(int i=0; i < nVerts; i++){
        temp=fscanf(fp, "%d", &verts[i]);
        if(temp != 1){
            return -1;
        }
    }

    //put these into triangles
    for(int i=1; i < nVerts-1; i++, which_tri++){
        *getV1(jm, which_tri) = verts[0];
        *getV2(jm, which_tri) = verts[i];
        *getV3(jm, which_tri) = verts[i+1];
    }

    return nVerts - 2;
}

//gets the faces from the off file
int get_faces(FILE *fp, jmesh *jm){
    int iter = jm->ntri, line=0;
    jm->ntri = get_tris(fp, jm); //figure out how many triangles there are
    jm->triangles = malloc(3*jm->ntri*sizeof(int));

    for(int i=0; i < iter; i++){
        int temp = split_polygon(fp, jm);
        line++;
        if( temp == -1){
            return line;
        }
        skip_line(fp);
    }

    return jm->ntri;
}

//fills edges with two displacement vectors
//from face i
void get_edges(jmesh *jm, int i, float *edges){
    float v1[3], v2[3], v3[3];

    //get the xyz of each vertex of the triangle
    v1[0] = *getX(jm, *getV1(jm, i));
    v2[0] = *getX(jm, *getV2(jm, i));
    v3[0] = *getX(jm, *getV3(jm, i));
    v1[1] = *getY(jm, *getV1(jm, i));
    v2[1] = *getY(jm, *getV2(jm, i));
    v3[1] = *getY(jm, *getV3(jm, i));
    v1[2] = *getZ(jm, *getV1(jm, i));
    v2[2] = *getZ(jm, *getV2(jm, i));
    v3[2] = *getZ(jm, *getV3(jm, i));

    //compute V2-V1, V3-V1
    edges[0] = v2[0]-v1[0];
    edges[1] = v2[1]-v1[1];
    edges[2] = v2[2]-v1[2];
    edges[3] = v3[0]-v1[0];
    edges[4] = v3[1]-v1[1];
    edges[5] = v3[2]-v1[2];
}

//returns the cross product of the two vectors stored in edges
//in the vector normal
void cross_product(float *edges, float* normal){
    normal[0] = (edges[4]*edges[2])-(edges[5]*edges[1]);
    normal[1] = (edges[5]*edges[0])-(edges[3]*edges[2]);
    normal[2] = (edges[3]*edges[1])-(edges[4]*edges[0]);
}

//returns the length of a 3d vector
float length(float *normal){
    return sqrt(pow(normal[0],2) + pow(normal[1],2) + pow(normal[2],2));
}

//computes the surface norms of a mesh
void get_surface_norms(jmesh *jm){

    //must have a vector for each vertex and for each face
    jm->normals = malloc((3*jm->nvert+3*jm->ntri)*sizeof(float));

    float edges[6]; //will hold two edge vectors
    float normal[3];//will hold the cross product of edges
    float len;
    for(int i=0; i < jm->ntri; i++){
        get_edges(jm, i, edges);
        cross_product(edges, normal);

        //normalize the cross-product
        len = length(normal);
        normal[0] = normal[0]/len;
        normal[1] = normal[1]/len;
        normal[2] = normal[2]/len;

        //put the normalized vector into jm

        *getSurfaceNormX(jm, i) = normal[0];
        *getSurfaceNormY(jm, i) = normal[1];
        *getSurfaceNormZ(jm, i) = normal[2];

    }
}

//TODO: implement
void get_vertex_norms(jmesh *jm){
    /*for each surface in jm:
     * for each vertex in surface:
     *   add surface normal to vertex normal
     *for each vertex in jm:
     * normalize normal
     */
}

//computes the normals for the faces and vertices
void get_normals(jmesh* jm){
    get_surface_norms(jm);
    get_vertex_norms(jm);
}

//returns -1 on fail, number of vertices on success
int load_off_mesh(FILE* fp, jmesh *jm){
    fseek(fp, 0, SEEK_SET); //ensure we are at the start of the file

    if(is_off_file(fp) != 0){
        fprintf(stderr, "not an off file\n");
        return -1;
    }

    int i;
    i=get_verts_faces(fp, jm);
    if(i != 3){
        fprintf(stderr,"off file corrupt on line 2\n");
        return -1;
    }
    i=get_tuples(fp, jm);
    if(i != jm->nvert){
        fprintf(stderr,"off file corrupt on tuple line %d\n", i);
        return -1;
    }
    i=get_faces(fp, jm);
    if(i != jm->ntri){
        fprintf(stderr,"off file corrupt on polygon line %d\n", i);
        return -1;
    }
    get_normals(jm);
    get_centroid(jm, jm->center);
    return i;
}
