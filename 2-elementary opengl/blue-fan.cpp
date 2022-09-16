#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <stdlib.h>

// is there a way to save the colour to a variable??

void mydisplay()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_TRIANGLE_FAN);
        glColor3f(0.3, 0.5, 0.8);
        glVertex2f(0, -0.5);
        glColor3f(0.1, 0.2, 0.5);
        glVertex2f(-0.6, 0);
        glColor3f(0.3, 0.5, 0.8);
        glVertex2f(-0.5, 0.4);
        glColor3f(0.1, 0.2, 0.5);
        glVertex2f(-0.2, 0.3);
        glColor3f(0.3, 0.5, 0.8);
        glVertex2f(0, 0.6);
        glColor3f(0.1, 0.2, 0.5);
        glVertex2f(0.2, 0.3);
        glColor3f(0.3, 0.5, 0.8);
        glVertex2f(0.5, 0.4);
        glColor3f(0.1, 0.2, 0.5);
        glVertex2f(0.6, 0);
    glEnd();
    glFlush();
}

// spawn square when click
void spawnSquare(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        // spawn square, centered where the mouse is
        glBegin(GL_TRIANGLES);
            glColor3f(0.1, 0.9, 0.7);
            glVertex2f(x - 0.1, y - 0.1);
            glVertex2f(x - 0.1, y + 0.1);
            glVertex2f(x + 0.1, y - 0.1);

            glColor3f(0.1, 0.8, 0.6);
            glVertex2f(x + 0.1, y - 0.1);
            glVertex2f(x + 0.1, y + 0.1);
            glVertex2f(x - 0.1, y + 0.1);
        glEnd();
        glFlush();
    }
}

// quit on right click
void quitRightClick(int button, int state, int x, int y)
{
    if (button == GLUT_RIGHT_BUTTON 
        && state == GLUT_DOWN)
    {
        exit(0);
    }
}

// quit on Q or q
void quitQ(unsigned char key, int x, int y)
{
    if (key == 'Q' | key == 'q')
    {
        exit(0);
    }
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutCreateWindow("Blue Fan");
    glutDisplayFunc(mydisplay);
    glutMouseFunc(spawnSquare);
    glutMouseFunc(quitRightClick);
    glutKeyboardFunc(quitQ);
    glutMainLoop();
}
