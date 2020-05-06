#include <iostream>

#include "GL/glut.h"

/**
 * I think GLUT must no be used to generate window for several reasons:
 * 1- Once in GLUT loop, you cannot escape it. In other word everything must be initialized BEFORE GLUT loop
 * 2- Every behavior that must be done during window execution must be implemented as callback (and got no clue where to
 * do that)
 * 3- Closing GLUT window make program to shut down (and not only loop to stop). No tears down behavior can be
 * done (in callback maybe ?)
 * 4- Slow iteration rate (according to what I read, GLUT loop is ~20Hz) meaning GLUT is slow
 */

void display() {
    // Clear all pixels
    glClear(GL_COLOR_BUFFER_BIT);

    // draw white polygon (rectangle) with corners at
    // (0.25, 0.25, 0.0) and (0.75, 0.75, 0.0)
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_POLYGON);
    glVertex3f(0.25, 0.25, 0.0);
    glVertex3f(0.75, 0.25, 0.0);
    glVertex3f(0.75, 0.75, 0.0);
    glVertex3f(0.25, 0.75, 0.0);
    glEnd();

    // Don't wait start processing buffered OpenGL routines
    glFlush();
}

void init() {
    // select clearing (background) color
    glClearColor(0.0, 0.0, 0.0, 0.0);

    // initialize viewing values
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_RGB);

    glutInitWindowSize(255, 255);

    // when positions are negative, position is left to window manager to determined
    glutInitWindowPosition(-1, -1);

    glutCreateWindow("My first openGL window");

    init();

    // Call "display" function
    glutDisplayFunc(display);

    std::cout << "!!!!!" << std::endl;

    // Enter the GLUT event loop
    glutMainLoop();

    // Is never displayed
    std::cout << "Wesh" << std::endl;

    return 0;
}