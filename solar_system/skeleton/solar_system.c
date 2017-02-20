/*
 * Jacob Massengill -- solar_system.c -- February 2017
 * This program renders a solar system using openGL.
 * it takes a single argument, a .off file that will represent 
 * the planets and sun within the rendering
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "utils.h"

int main(int argc, char **argv) {

    if(argc < 2){
        printf("Usage: ./solar_system off_file\n");
        exit(1);
    }

    FILE* mesh_file = fopen(argv[1], "r");
    if(!mesh_file){
        fprintf(stderr, "Could not render %s\n", argv[1]);
        exit(1);
    }

    graphics_state gs;

    gs.height=1024;
    gs.width =1024;

    gs.mesh = new_jmesh(mesh_file, &load_off_mesh);
    fclose(mesh_file);

    if(!gs.mesh){
        fprintf(stderr, "could not render %s\n", argv[1]);
        free_jmesh(gs.mesh);
        exit(1);
    }

    { /* GLUT initialization */
        glutInit(&argc,argv);
        glutInitDisplayMode(GLUT_RGB);
        glutInitWindowSize(gs.width,gs.height);
        glutInitWindowPosition(100,100);
        glutCreateWindow(argv[0]);

        glutDisplayFunc(display);
        glutIdleFunc(display);
        glutReshapeFunc(reshape);

        glutKeyboardFunc(keys);
        glutSpecialFunc(special_keys);
        glutMouseFunc(mouse_handler);
        glutMotionFunc(trackMotion);
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);
    }

    /*
     * set the camera to look at the center of the sun
     * slightly  above and to the side from the sun
     */
    gluLookAt(*getCenterX(gs.mesh)-0.5, *getCenterY(gs.mesh)-0.5,0, 
            *getCenterX(gs.mesh),*getCenterY(gs.mesh),
            *getCenterZ(gs.mesh), 0, 1, 0);

    init(&gs);
    print_howto(argv[1]);
    glutMainLoop();

    return 0;
}
