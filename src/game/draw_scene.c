#include "draw_scene.h"
#include "3D_tools.h"

void drawBase()
{
    glColor3f(235 / 255., 207 / 255., 52 / 255.);

    glPushMatrix();

    glScalef(1., 1., 10.);
    drawCone();

    glPopMatrix();

    glPopMatrix();

    glPushMatrix();
    glScalef(3., 3., 1.);
    drawCircle();
    glPopMatrix();
}

void drawFrame()
{
    glPushMatrix();

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

    glColor3f(245 / 255., 164 / 255., 66 / 255.);

    glPushMatrix();

    glPushMatrix();
    // glScalef(3., 3., 3.);
    // glScalef(3.2, 3.2, 3.2);
    glScalef(1.6, 1.6, 1.6);

    drawSphere();
    glPopMatrix();

    glPushMatrix();
    glRotatef(-90., 0., 1., 0.);
    glPushMatrix();

    glScalef(1., 1., 10.);
    drawCone();

    glPopMatrix();
    glPopMatrix();

    glRotatef(90., 0., 1., 0.);
    glPushMatrix();

    glScalef(1., 1., 10.);
    drawCone();

    glPopMatrix();
    glPopMatrix();
}

void drawPan()
{
    glColor3f(89 / 255., 115 / 255., 0 / 255.);

    glPushMatrix();
    glScalef(3., 3., 1.);
    drawCircle();
    glPopMatrix();
    float step_rad = 2 * M_PI / (float)3;
    glColor3f(1., 0., 0.);

    glScalef(3., 3., 1.);

    glBegin(GL_LINE_LOOP);

    glVertex3f(0., 0., 5.);
    glVertex3f(cos(0), sin(0), 0.0f);

    glEnd();
    glBegin(GL_LINE_LOOP);
    glVertex3f(0., 0., 5.);
    glVertex3f(cos(step_rad), sin(step_rad), 0.0f);

    glEnd();
    glBegin(GL_LINE_LOOP);
    glVertex3f(0., 0., 5.);
    glVertex3f(cos(2 * step_rad), sin(2 * step_rad), 0.0f);

    glEnd();
}

void drawMurs(LstMurs lst){
    Murs *ret = lst;
    while(ret!=NULL){
        glColor3f(89 / 255., 0, 0 / 255.);

        glPushMatrix();
        drawMur(ret->mur1);
        glPopMatrix();

        glPushMatrix();
        glRotatef(90., 0., 1., 0.);
        drawMur(ret->mur1);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(0., 0., ret->taille_z);
        drawMur(ret->mur1);
        glPopMatrix();

        glPushMatrix();
        glRotatef(90., 0., 1., 0.);
        glTranslatef(0., 0., -ret->taille_z);
        drawMur(ret->mur1);
        glPopMatrix();

        /*
        glScalef(.50, .50, .50);
        drawArm();
        */
        ret = ret->suivant;
    }
}

void drawMur(int mur[4][3]){

    glBegin(GL_TRIANGLE_FAN);
    for(int i = 0; i < 4; i++){
        glVertex3f(mur[i][0], mur[i][1], mur[i][2]);
    }
    glEnd();
}