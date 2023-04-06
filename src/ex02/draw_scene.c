#include "draw_scene.h"
#include "3D_tools.h"

void drawBase()
{

    glBegin(GL_LINE_LOOP);

    glColor3f(1., 0., 0.);
    glVertex2f(0., 0.);
    glVertex2f(1., 0.);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glColor3f(0., 1., 0.);
    glVertex2f(0., 0.);
    glVertex2f(0., 1.);

    glBegin(GL_LINE_LOOP);
    glColor3f(0., 0., 1.);
    glVertex3f(0., 0., 0.);
    glVertex3f(0., 0., 1.);

    glEnd();
}

void drawArm()
{
}

void drawPan()
{
}
