/*
 * Jacob Massngill -- utils.c -- February 2017
 * this file declares operations for rendering a solar system  
 */
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include "ppm.h"
#include "utils.h"
#include "rotater.h"

#define NPLANETS 8
#define DISTANCE 3
#define ROTATE_SPEED 0.0001
#define SPEED_MULT 1.05
#define SPIN_MAX 0.5
#define NSTARS 50

static graphics_state *current_gs;

void rotate_scene_up(){
    glRotatef(1, 1.0,0.0,0);
}

void rotate_scene_down(){
    glRotatef(-1, 1.0,0.0,0);
}

void rotate_scene_left(){
    glRotatef(1, 0.0,1.0,0);
}

void rotate_scene_right(){
    glRotatef(-1, 0.0,1.0,0);
}

void zoom_in(){
    glScalef(1.02,1.02,1.02);
}

void zoom_out(){
    glScalef(0.98,0.98, 0.98);
}

void speed_up(){
    for(int i=0; i < NPLANETS; i++){
        current_gs->rotations[i]->da*=SPEED_MULT;
        current_gs->planet_spin[i]->da*=SPEED_MULT;
    }
}

void slow_down(){
    for(int i=0; i < NPLANETS; i++){
        current_gs->rotations[i]->da/=SPEED_MULT;
        current_gs->planet_spin[i]->da/=SPEED_MULT;
    }
}

//return the view to the original setting
void reset_view(){
    glPopMatrix();
    glPushMatrix();
}

//draws the loaded mesh as a bunch of triangles
void draw_mesh(){
    graphics_state *gs = current_gs;
    for(int i =0; i < gs->mesh->ntri; i++){
        glBegin(GL_TRIANGLES);
        glVertex3f(*getX(gs->mesh, *getV1(gs->mesh, i)),
                *getY(gs->mesh, *getV1(gs->mesh, i)),
                *getZ(gs->mesh, *getV1(gs->mesh, i)));
        glVertex3f(*getX(gs->mesh, *getV2(gs->mesh, i)),
                *getY(gs->mesh, *getV2(gs->mesh, i)),
                *getZ(gs->mesh, *getV2(gs->mesh, i)));
        glVertex3f(*getX(gs->mesh, *getV3(gs->mesh, i)),
                *getY(gs->mesh, *getV3(gs->mesh, i)),
                *getZ(gs->mesh, *getV3(gs->mesh, i)));
        glEnd();
    }
}

//draw a field of "stars" around the planets
void draw_stars(){
    float *star_pos = current_gs->star_pos;
    for(int i =0; i < NSTARS; i++){
        float x,y,z;
        x = star_pos[i];
        y = star_pos[i+1];
        z = star_pos[i+2];

        glPushMatrix();
        glTranslatef(x,y,z);
        glColor3f(1,1,1);
        glutSolidSphere(0.03,10,10);
        glPopMatrix();
    }

}

//draw the mesh in the center of the viewing space
void draw_sun(){
    glPushMatrix();
    glTranslatef(-*getCenterX(current_gs->mesh),
            -*getCenterY(current_gs->mesh),
            -*getCenterZ(current_gs->mesh));
    glColor3f(1, 1, 0);
    draw_mesh();
    glPopMatrix();
}

//change to a specific color to draw a planet as
void change_color(int i){
    switch(i){
        case 0:
            glColor3f(1,0.5,0); //mecury is orange
            break;
        case 1:
            glColor3f(1,0.5, 0.1); //venus
            break;
        case 2:
            glColor3f(0,0,1); //earth is blue
            break;
        case 3:
            glColor3f(1,0,0); //mars is red
            break;
        case 4:
            glColor3f(1,0.2,0);//Jupiter
            break;
        case 5:
            glColor3f(1,0.85,0);//Saturn
            break;
        case 6:
            glColor3f(1,0.4,0.5);//Uranus
            break;
        case 7:
            glColor3f(1,0.4,0.4);//Neptune
            break;
        default:
            glColor3f(1,1,1);
            break;
    }
}

//draws the mesh at a certain distance from the sun
void draw_planet(int i){
    rotater_t *rotations = current_gs->rotations;
    rotater_t *planet_spin = current_gs->planet_spin;
    rotater_rotate(rotations[i]);
    rotater_rotate(planet_spin[i]);

    glPushMatrix();
        change_color(i);
        glTranslatef((1+i)*DISTANCE*cos(rotations[i]->angle), 0,
                (1+i)*DISTANCE*sin(rotations[i]->angle));
        glRotatef(planet_spin[i]->angle, 0, 1,0);
        glTranslatef(-*getCenterX(current_gs->mesh),
                -*getCenterY(current_gs->mesh), -*getCenterZ(current_gs->mesh));
        draw_mesh(); 
    glPopMatrix();
}

//draws the stars, sun, and planets
void draw_system(){
    draw_stars();
    draw_sun();

    for(int i=0; i < NPLANETS; i++){
        draw_planet(i);
    }
}

//prints instructions and mesh information
void print_howto(const char* fn){
    printf("Up Arrow:     Rotate Up\n"
            "Down Arrow:   Rotate Down\n"
            "Left Arrow:   Rotate Left\n"
            "Right Arrow:  Rotate Right\n"
            "Page UP:      Zoom In\n"
            "Page Down:    Zoom Out\n"
            "Home:         Reset View\n"
            "+:            Speed Up\n"
            "-:            Slow Down\n"
            "Q or q:       Exit Program\n\n");
    printf("%s\n", fn);
    print_stats(current_gs->mesh);
}

void set_gs(graphics_state * gs){
    current_gs = gs;
}

//create a set of points representing the location of the stars
void star_init(){
    float *star_pos = malloc(NSTARS*sizeof(float)*3);
    for(int i =0; i < NSTARS; i++){
        float s, t;
        s = (float) rand()/(float)RAND_MAX *2*PI;
        t = (float) rand()/(float)RAND_MAX *2*PI;

        star_pos[i] = (NPLANETS*DISTANCE) * cos(s) * sin(t);
        star_pos[i+1] = (NPLANETS*DISTANCE) * sin(s) * sin(t);
        star_pos[i+2] = (NPLANETS*DISTANCE) * cos(t);
    }
    current_gs->star_pos = star_pos;
}

//give each planet a random spin, and make it rotate around the sun
//at a rate proportional to it's distance
void rotation_init(){
    rotater_t *rotations = malloc( NPLANETS*sizeof(rotater_t));
    rotater_t *planet_spin = malloc( NPLANETS*sizeof(rotater_t));
    for(int i=0; i < NPLANETS; i++){
        rotations[i] = new_rotater(ROTATE_SPEED*(NPLANETS-i));
        planet_spin[i] = new_rotater((float) rand()/(float)RAND_MAX * SPIN_MAX);
    }
    current_gs->rotations = rotations;
    current_gs->planet_spin = planet_spin;

}

//initialize random number generation, the graphics state, and constants
void init(graphics_state * gs){
    current_gs = gs;
    srand(time(0));
    star_init();
    rotation_init();
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); 
    glScalef(0.05,0.05,0.05);
    glPushMatrix();

    //free all used memory when the window closes
    atexit(cleanup);
}

void display(void){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    draw_system();
    glutSwapBuffers();
}

void reshape(int w, int h){

}

void mouse_handler(int button, int button_state, int x, int y){

}

void trackMotion(int x, int y) {

}

//take a screenshot of the window and save to framebuffer.ppm
void save_to_ppm(int w, int h, const char* fn){
    PPM image = dnew_PPM(w,h);
    RGB *data = malloc(w*h*sizeof(struct rgb));
    glReadPixels(0,0,w,h,GL_RGB,GL_UNSIGNED_BYTE, data);

    /*
     * copy data to image->data with the rows swaped.
     * i.e. row 1 in data maps to row N in image->data.
     */
    for(int i=0; i < w*h; i++){
        image->data[(i/h)*w+i%w] = data[(w-(i/h))*w+i%w];
    }

    swrite_PPM(fn, image);
    free_PPM(image); 
    free(data);
}


void keys(unsigned char c, int x, int y) {

    switch(c){
        case 'q':
        case 'Q':
            exit(EXIT_SUCCESS);
            break;
        case 's':
        case 'S':
            save_to_ppm(current_gs->width, current_gs->height, "framebuffer.ppm");
            break;
        case '+':
            speed_up();
            break;
        case '-':
            slow_down();
            break;
        default:
            break;
    }

} 

void special_keys(int key, int x, int y){
    switch(key){
        case GLUT_KEY_UP:
            rotate_scene_up();
            break;
        case GLUT_KEY_DOWN:
            rotate_scene_down();
            break;
        case GLUT_KEY_LEFT:
            rotate_scene_left();
            break;
        case GLUT_KEY_RIGHT:
            rotate_scene_right();
            break;
        case GLUT_KEY_PAGE_UP:
            zoom_in();
            break;
        case GLUT_KEY_PAGE_DOWN:
            zoom_out();
            break;
        case GLUT_KEY_HOME:
            reset_view();
            break;
    }

}

//free all allocated memory
void cleanup(){
    for(int i=0; i < NPLANETS; i++){
        if(current_gs->rotations[i])   free_rotater(current_gs->rotations[i]);
        if(current_gs->planet_spin[i]) free_rotater(current_gs->planet_spin[i]);
    }
    if(current_gs->rotations) free(current_gs->rotations);
    if(current_gs->planet_spin) free(current_gs->planet_spin);
    if(current_gs->star_pos) free(current_gs->star_pos);
    free_jmesh(current_gs->mesh);
    glPopMatrix();
}
