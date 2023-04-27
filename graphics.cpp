#include "circle.h"
#include "graphics.h"
#include <ctime>
#include <iostream>
#include <vector>
using namespace std;

GLdouble width, height;
int wd, clickX, clickY;

Circle sun;

vector<Circle> snow;

void init() {
    srand(time(0));
    width = 1000;
    height = 625;

    clickX = clickY = 0;

    sun.setCenter(width, 0);
    sun.setColor(1, 1, 0, 1);
    sun.setRadius(100);


    for (int i = 0; i < 150; ++i) {
        snow.push_back(Circle(1, 1, 1, 1, rand() % int(width), -(rand() % int(height)), rand() % 5 + 1));
    }
}

/* Initialize OpenGL Graphics */
void initGL() {
    // Set "clearing" or background color
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Black and opaque
}

/* Handler for window-repaint event. Call back when the window first appears and
 whenever the window needs to be re-painted. */
void display() {
    // Tell OpenGL to use the whole window for drawing
    glViewport(0, 0, width, height); // DO NOT CHANGE THIS LINE

    // Do an orthographic parallel projection with the coordinate
    // system set to first quadrant, limited by screen/window size
    glMatrixMode(GL_PROJECTION); // DO NOT CHANGE THIS LINE
    glLoadIdentity(); // DO NOT CHANGE THIS LINE
    glOrtho(0.0, width, height, 0.0, -1.f, 1.f); // DO NOT CHANGE THIS LINE

    // Clear the color buffer with current clearing color
    glClear(GL_COLOR_BUFFER_BIT); // DO NOT CHANGE THIS LINE

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // DO NOT CHANGE THIS LINE

    glEnable(GL_BLEND);
    // Thanks https://stackoverflow.com/questions/1617370/how-to-use-alpha-transparency-in-opengl
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


    /*
     * Draw here
     */
    sun.draw();


    for (Circle &flake : snow) {
        flake.draw();
    }

    // D2: What is being drawn? Where? What color?



    // D3: What does this code do? What will it look like? Where will it be?
    string message = "You clicked the mouse at coordinate (" + to_string(clickX) + ", " + to_string(clickY) + ")";
    glColor3f(1, 1, 1);
    glRasterPos2i(0, height);
    for (char letter : message) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, letter);
    }


    // D1: What is being drawn? Where? What color?
    /*glColor3f(0, 0.5, 0);
    glBegin(GL_TRIANGLES);
    glVertex2i(0, 0);
    glVertex2i(0, 100);
    glVertex2i(100, 0);
    glVertex2i(width, height);
    glVertex2i(width, height - 100);
    glVertex2i(width - 100, height);
    glEnd();*/

    glDisable(GL_BLEND);

    glFlush();  // Render now
}

// http://www.theasciicode.com.ar/ascii-control-characters/escape-ascii-code-27.html
void kbd(unsigned char key, int x, int y) {
    switch(key) {
        case 27: {
            // escape
            glutDestroyWindow(wd);
            exit(0);
        }
        case 'b': {
            // K1: What does this line of code do? When?
            //bubble.setColor(0, 0, 0, 0);
            break;
        }
        case 'o': {
            // K2: What happens when the bubble gets big
            // enough to overlap with other shapes?
            //bubble.setRadius(bubble.getRadius() + 5);
            break;
        }
    }
    glutPostRedisplay();
}

void kbdUp(unsigned char key, int x, int y) {
    // K3: What will happen here? When?
    switch(key) {
        case 'b': {
            //bubble.setColor(0.7, 0.8, 0.8, 1);
            break;
        }
    }
    glutPostRedisplay();
}

void kbdS(int key, int x, int y) {
    switch(key) {
        case GLUT_KEY_DOWN:

            break;
        case GLUT_KEY_LEFT:

            break;
        case GLUT_KEY_RIGHT:

            break;
        case GLUT_KEY_UP:

            break;
    }

    glutPostRedisplay();
}

void cursor(int x, int y) {

    // M2: What does this line do? What will it look like?
    //eye[1].setColor(0, x/double(width), y/double(height), 1);

    // M3: What do these lines do? What will it look like?
    //if (x >= 0 && x <= width && y >= 0 && y <= height) {
    //    eye[1].setCenter(eye[0].getCenterX() + ((x - eye[0].getCenterX()) / (double) width * 20),
    //                     eye[0].getCenterY() + ((y - eye[0].getCenterY()) / (double) height * 20));
    //    eye[2].setCenter(eye[1].getCenterX() + ((x - eye[1].getCenterX()) / (double) width * 14),
    //                     eye[1].getCenterY() + ((y - eye[1].getCenterY()) / (double) height * 14));
    //}
    glutPostRedisplay();
}

// button will be GLUT_LEFT_BUTTON or GLUT_RIGHT_BUTTON
// state will be GLUT_UP or GLUT_DOWN
void mouse(int button, int state, int x, int y) {

    clickX = x;
    clickY = y;

    // M1: What does this code do?
    //if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
    //    for (Circle &e : eye) {
    //        e.setCenter(x, y);
    //    }
    //}
    glutPostRedisplay();
}

void timer(int dummy) {

    // T1: In what direction will the sun move?
    sun.move(-1, 1);

    // T2: What does this line do? What will it look like?
    sun.setColor(1.0, sun.getGreen() - 1.0/1000, 0, 1);

    // T3: What does this loop do? What will it look like?
    // Why are these arguments given to the methods?
    for (Circle &flake : snow) {
        flake.moveY(flake.getRadius());
        if (flake.getTopY() > height) {
            flake.setCenter(rand() % int(width), -flake.getRadius());
        }
    }

    glutPostRedisplay();
    glutTimerFunc(30, timer, dummy);
}

/* Main function: GLUT runs as a console application starting at main()  */
int main(int argc, char** argv) {

    init();

    glutInit(&argc, argv);          // Initialize GLUT

    glutInitDisplayMode(GLUT_RGBA);

    glutInitWindowSize((int)width, (int)height);
    glutInitWindowPosition(0, 0); // Position the window's initial top-left corner
    /* create the window and store the handle to it */
    wd = glutCreateWindow("Ski Mountain!" /* title */ );

    // Register callback handler for window re-paint event
    glutDisplayFunc(display);

    // Our own OpenGL initialization
    initGL();

    // register keyboard press event processing function
    // works for numbers, letters, spacebar, etc.
    glutKeyboardFunc(kbd);
    glutKeyboardUpFunc(kbdUp);

    // register special event: function keys, arrows, etc.
    glutSpecialFunc(kbdS);

    // handles mouse movement
    glutPassiveMotionFunc(cursor);

    // handles mouse click
    glutMouseFunc(mouse);

    // handles timer
    glutTimerFunc(0, timer, 0);

    // Enter the event-processing loop
    glutMainLoop();
    return 0;
}