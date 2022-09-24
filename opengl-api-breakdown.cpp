/**
 * Labelling everything in the OpenGL API
 * So that you know what is going on in the program
 */

// Including glut.h automatically includes glu and gl.
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

/**
 * A kind of Display Callback.
 * Executed when the display is refreshed
 *   eg. when the window is opened
 * Draws things on the screen.
 * Can have input and window functions.
 */
void mydisplay()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // Clears the frame when a new frame is drawn.
    // COLOR clears the colour buffer
    // DEPTH clears the depth buffer
    glBegin(GL_POLYGON);
        glVertex3f(-0.5, -0.5, 0.0); // gl from gl library
        glVertex3f(-0.5, 0.5, 0.0);  // function name is Vertex
        glVertex3f(0.5, 0.5, 0.0);   // 3 dimensions
        glVertex3f(0.5, -0.5, 0.0);  // f == floats, d == doubles, v is pointer to an array
    glEnd();
    glFlush();
}

/**
 * A kind of Timer Callback function
 * you get to choose how much time before this function executes
 */
void myTimer( void )
{
    // hi
}

/**
 * Sets viewing state variables
 * Sets attributes
 */
void init()
{
    glClearColor(0.0, 0.0, 0.0, 1.0); // window colour = black, opaque
    glEnable(GL_DEPTH_TEST); // enable 3D and z-buffer algo 
                             // for hidden surface removal

    glColor3f(1.0, 1.0, 1.0);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
}

/**
 * Defines the callback functions
 * Opens windows with their respective properties
 * Enters event loop
 */
int main(int argc, char** argv)
{
    glutInit(&argc, argv); // get CLI args, init system
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    // GLUT_SINGLE: single buffer, must use glFlush();
    // GLUT_DOUBLE: double colour buffer, use gl??SwapBuffers();
    // GLUT_RGB: use RGB colour
    // GLUT_DEPTH: z-buffer for 3D

    // Define window properties
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(0, 0); // from top left of screen, array of px

    glutCreateWindow("OpenGL Reference Program"); // name the window
    glutDisplayFunc(mydisplay); // set display callback

    init(); // I set my OpenGL state in here

    glutMainLoop(); // Enter the event loop. Nothing else runs after this statement.
    return 0;
}
