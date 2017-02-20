/*
 * Jacob Massengill -- utils.h -- February 2017
 * declares objects and operations for creating the solar system rendering 
 */
#ifndef _GRAPHICS_UTILS_
#define _GRAPHICS_UTILS_

#include <GL/gl.h>
#include <GL/glut.h>
#include "jmesh.h"
#include "offreader.h"
#include "rotater.h"

typedef struct {
    int width;        /* width of rendering target */
    int height;       /* height of rendering target */
    jmesh *mesh;
    float *star_pos;
    rotater_t *rotations;
    rotater_t *planet_spin;
} graphics_state;   /* global graphics state */


#ifdef __cplusplus
extern "C" {
#endif

    void print_howto(const char*);

    void init(graphics_state *);
    void set_gs(graphics_state *);
    void cleanup();

    void display(void); 
    void reshape(int w, int h);
    void mouse_handler(int button, int button_state, int x, int y);
    void trackMotion(int x, int y);
    void keys(unsigned char c,int x, int y);
    void special_keys(int key, int x, int y);
#ifdef __cplusplus
}
#endif

#endif //_GRAPHICS_UTILS_
