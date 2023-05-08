#include "circle.h"
#include "graphics.h"
#include "rect.h"
#include <ctime>
#include <iostream>
#include <vector>
using namespace std;

GLdouble width, height;
int wd, clickX, clickY;

Circle sun;
vector<Circle> snow;
Rect liftie1;
Rect liftie2;
Rect skiier;

vector<Rect> leftLift;
vector<Rect> rightLift;

bool click, leftTrail, rightTrail = false;

// enum for different screens
enum screens {start, mountain};
screens screen;


void init() {
    srand(time(0));
    width = 1000;
    height = 625;

    clickX = clickY = 0;

    sun.setCenter(width, 0);
    sun.setColor(1, 1, 0, 1);
    sun.setRadius(100);

    liftie1.setCenter(735, 170);
    liftie1.setSize(15, 20);
    liftie1.setColor(0.75, 0.4, 0, 1);
    liftie2.setCenter(325, 170);
    liftie2.setSize(15, 20);
    liftie2.setColor(0.75, 0.4, 0, 1);

    skiier.setColor(1, 0, 0, 1);
    skiier.setSize(10, 10);

    for (int i = 0; i < 150; ++i) {
        snow.push_back(Circle(1, 1, 1, 1, rand() % int(width), -(rand() % int(height)), rand() % 5 + 1));
    }


}

/* Initialize OpenGL Graphics */
void initGL() {
    // Set "clearing" or background color
    glClearColor(0.0f, 0.6f, 1.0f, 1.0f); // Black and opaque
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

    if (screen == start) {
        string startMessage = "Press s key to simulate ski mountain";
        glColor3f(1, 1, 1);
        glRasterPos2i(500 - (4 * startMessage.length()), 319.5);
        for (const char &letter : startMessage) {
            glutBitmapCharacter(GLUT_BITMAP_8_BY_13, letter);
        }
    }

    if (screen == mountain) {
        //draw mountains
        glBegin(GL_TRIANGLE_FAN);
        glVertex2i(0, 625);
        glColor3f(1.0, 1.0, 1.0);
        glVertex2i(312.5, 150);
        glColor3f(1.0, 1.0, 1.0);
        glVertex2i(625, 625);
        glColor3f(1.0, 1.0, 1.0);
        glEnd();

        glBegin(GL_TRIANGLE_FAN);
        glVertex2i(450, 625);
        glColor3f(1.0, 1.0, 1.0);
        glVertex2i(725, 150);
        glColor3f(1.0, 1.0, 1.0);
        glVertex2i(1000, 625);
        glColor3f(1.0, 1.0, 1.0);
        glEnd();

        glBegin(GL_LINES);
        glColor3f(0,0,0);
        glVertex2f(735, 170);
        glVertex2f(800, 625);
        glEnd();

        glBegin(GL_LINES);
        glColor3f(0,0,0);
        glVertex2f(735, 170);
        glVertex2f(670, 625);
        glEnd();

        glBegin(GL_LINES);
        glColor3f(0,0,0);
        glVertex2f(325, 170);
        glVertex2f(390, 625);
        glEnd();

        glBegin(GL_LINES);
        glColor3f(0,0,0);
        glVertex2f(325, 170);
        glVertex2f(260, 625);
        glEnd();

        liftie1.draw();
        liftie2.draw();

        if (click) {
            skiier.draw();
        }

        for (Circle &flake : snow) {
            flake.draw();
        }



        // D3: What does this code do? What will it look like? Where will it be?
        string message = "You clicked the mouse at coordinate (" + to_string(clickX) + ", " + to_string(clickY) + ")";
        glColor3f(1, 1, 1);
        glRasterPos2i(0, 50);
        for (char letter : message) {
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, letter);
        }
    }

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
        case 's': {
            screen = mountain;
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
    glutPostRedisplay();
}

// button will be GLUT_LEFT_BUTTON or GLUT_RIGHT_BUTTON
// state will be GLUT_UP or GLUT_DOWN
void mouse(int button, int state, int x, int y) {

    clickX = x;
    clickY = y;

    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        click = true;
    }

    if (x < 312.5 && y > 150) {
        // Go down left of left ski mountain
        skiier.setCenter(312.5, 150);
        leftTrail = true;
        rightTrail = false;
    } else if (x > 312.5 && x < 530 && y > 150) {
        // Go down right side of left ski mountain
        skiier.setCenter(312.5, 150);
        leftTrail = false;
        rightTrail = true;
    } else if (x > 530 && x < 725 && y > 150) {
        // Go down left side of right ski mountain
        skiier.setCenter(725, 150);
        leftTrail = true;
        rightTrail = false;
    } else if (x > 725 && y > 150) {
        // Go down right side of right ski mountain
        skiier.setCenter(725, 150);
        leftTrail = false;
        rightTrail = true;
    }

    glutPostRedisplay();
}

void timer(int dummy) {

    if (leftTrail && !rightTrail) {
        skiier.move(-1, 2);
    } else if (!leftTrail && rightTrail) {
        skiier.move(1, 2);
    }

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