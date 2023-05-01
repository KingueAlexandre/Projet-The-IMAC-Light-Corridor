#include "draw_scene.h"
#include "3D_tools.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define NB_BIT_COLOR 256

/*LES NOMS DES DIFFÉRENTES TEXTURES*/
static char *textures_name[NB_TEXTURE] = {"./input/Niveau1.jpg",
                                          "./input/Niveau2.jpg",
                                          "./input/Niveau3.jpg",
                                          "./input/Quitter.jpg",
                                          "./input/Victoire.jpg",
                                          "./input/GameOver.jpg",
                                          "./input/int0.jpg",
                                          "./input/int1.jpg",
                                          "./input/int2.jpg",
                                          "./input/int3.jpg",
                                          "./input/int4.jpg",
                                          "./input/int4.jpg",
                                          "./input/int5.jpg",
                                          "./input/int6.jpg",
                                          "./input/int7.jpg",
                                          "./input/int8.jpg",
                                          "./input/int9.jpg"};
static Texture textures[NB_TEXTURE];

Texture generateTexture_i(int i)
{
    Texture texture;
    texture.Niveau1 = stbi_load(textures_name[i], &(texture.largeur), &(texture.hauteur), &(texture.nbcanaux), 0);

    if (texture.Niveau1 != NULL)
    {
        printf("Image bien chargé.\n");
    }
    else
    {
        printf("problème : %s\n", textures_name[i]);
    }

    glGenTextures(1, &(texture.texture));
    glBindTexture(GL_TEXTURE_2D, texture.texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    glTexImage2D(
        GL_TEXTURE_2D, 0, GL_RGB,
        texture.largeur, texture.hauteur, 0,
        GL_RGB, GL_UNSIGNED_BYTE, texture.Niveau1);

    return texture;
}

void loadtextures()
{
    for (int i = 0; i < NB_TEXTURE; i++)
    {
        textures[i] = generateTexture_i(i);
    }
}

void freetextures()
{
    for (int i = 0; i < NB_TEXTURE; i++)
    {

        glDeleteTextures(1, &(textures[i].texture));
        stbi_image_free(textures[i].Niveau1);
    }
}

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

void drawMurs(LstMurs lst, float cam_y)
{
    Murs *ret = lst;
    while (ret != NULL)
    {
        if (ret->debut_y + TAILLE_Y < cam_y)
        {
            ret = ret->suivant;
            continue;
        }
        /*ON A UN MURS QU'ON AFFCIHE 4 FOIS POUR FAIRE LE CORRIDOR*/
        glColor3f(ret->r / NB_BIT_COLOR, ret->g / NB_BIT_COLOR, ret->b / NB_BIT_COLOR);

        glPushMatrix();
        drawMur(ret->mur);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(0., 0., ret->taille_z);
        drawMur(ret->mur);
        glPopMatrix();

        glColor3f(ret->g / NB_BIT_COLOR, ret->b / NB_BIT_COLOR, ret->r / NB_BIT_COLOR);

        glPushMatrix();
        glRotatef(90., 0., 1., 0.);
        drawMur(ret->mur);
        glPopMatrix();

        glPushMatrix();
        glRotatef(90., 0., 1., 0.);
        glTranslatef(0., 0., -ret->taille_z);
        drawMur(ret->mur);
        glPopMatrix();

        /*COINS DES MURS POUR FAIRE DE MEILLEURES REPÉRES*/
        glPushMatrix();
        glRotatef(90., 0., 0., 1.);
        glScalef(4., .50, .50);
        glTranslatef((ret->taille_y / 4) * (1 + ret->num), 0., 0);
        glColor3f(0., 0., 0.);

        drawArm();
        glColor3f(0., 0., 0.);
        glPushMatrix();

        glTranslatef(0., 0., 2 * ret->taille_z);
        glColor3f(0., 0., 0.);

        drawArm();

        glPopMatrix();
        glPopMatrix();

        glPushMatrix();
        glTranslatef(-ret->taille_x, 0., 0.);
        glPushMatrix();
        glRotatef(90., 0., 0., 1.);
        glScalef(4., .50, .50);
        glTranslatef((ret->taille_y / 4) * (1 + ret->num), 0., 0);
        glColor3f(0., 0., 0.);

        drawArm();

        glColor3f(0., 0., 0.);
        glPushMatrix();
        glTranslatef(0., 0., 2 * ret->taille_z);
        glColor3f(0., 0., 0.);

        drawArm();
        glPopMatrix();
        glPopMatrix();

        glPopMatrix();

        ret = ret->suivant;
    }
}

void drawObstacles(LstObstacles lst, Joueur joueur)
{
    Obstacles *ret = lst;
    glPushMatrix();

    while (ret != NULL)
    {
        if (ret->mur[0][1] > joueur.y)
        {
            glColor3f(ret->r / NB_BIT_COLOR, ret->g / NB_BIT_COLOR, ret->b / NB_BIT_COLOR);

            glPushMatrix();
            drawMur(ret->mur);
            glPopMatrix();

            glColor3f(0., 0., 0.);

            glPushMatrix();
            glBegin(GL_LINE_LOOP);
            glVertex3f(-TAILLE_X, ret->mur[0][1] - 5., 0.);

            glVertex3f(0., ret->mur[0][1] - 5., 0.);

            glVertex3f(0., ret->mur[0][1] - 5., TAILLE_Z);

            glVertex3f(-TAILLE_X, ret->mur[0][1] - 5., TAILLE_Z);
            glEnd();
            glPopMatrix();
        }

        glPushMatrix();
        glBegin(GL_LINE_LOOP);
        glVertex3f(-TAILLE_X, ret->mur[0][1] + 5., 0.);

        glVertex3f(0., ret->mur[0][1] + 5., 0.);

        glVertex3f(0., ret->mur[0][1] + 5., TAILLE_Z);

        glVertex3f(-TAILLE_X, ret->mur[0][1] + 5., TAILLE_Z);
        glEnd();
        glPopMatrix();

        ret = ret->suivant;
    }
    glPopMatrix();
}
void drawMur(float mur[4][3])
{
    glBegin(GL_TRIANGLE_FAN);
    for (int i = 0; i < 4; i++)
    {
        /*
        printf("(%f,%f,%f) ", mur[i][0], mur[i][1], mur[i][2]);
        */
        glVertex3f(mur[i][0], mur[i][1], mur[i][2]);
    }
    glEnd();
}

void printfObstacles(LstObstacles lst)
{
    printf("\ndrawObstacles\n");
    Obstacles *ret = lst;
    while (ret != NULL)
    {
        /*
        printf("Section n⁰%d\n", ret->num);
        */

        printfMur(ret->mur);
        ret = ret->suivant;
    }
    printf("Fin\n");
}
void printfMur(float mur[4][3])
{
    for (int i = 0; i < 4; i++)
    {
        printf("(%f,%f,%f) ", mur[i][0], mur[i][1], mur[i][2]);
    }
    printf("\n");
}

void drawBalle(Balle balle)
{
    glPushMatrix();
    glTranslatef(balle.x, balle.y, balle.z);
    drawSphere();
    glPopMatrix();
}

void drawJoueur(Joueur joueur)
{
    glColor3f(0., 1., 1.);
    for (int i = 0; i < joueur.vie; i++)
    {
        glBegin(GL_TRIANGLE_FAN);
        float step_rad = 2 * M_PI / (float)100;
        for (int i2 = 0; i2 <= 100; i2++)
        {
            glVertex3f(-TAILLE_X + 1 + 0.35 * i + 0.25 * cos(i2 * step_rad), joueur.y, TAILLE_Z - 1 + 0.25 * sin(i2 * step_rad));
        }
        glEnd();
    }

    glColor3f(1., 1., 1.);

    glBegin(GL_LINE_LOOP);

    glVertex3f(joueur.max_cote_x, joueur.y, joueur.min_cote_z);
    glVertex3f(joueur.min_cote_x, joueur.y, joueur.min_cote_z);
    glVertex3f(joueur.min_cote_x, joueur.y, joueur.max_cote_z);
    glVertex3f(joueur.max_cote_x, joueur.y, joueur.max_cote_z);

    glEnd();
}

void drawBonus(Bonus bonus)
{
    glPushMatrix();
    glBegin(GL_LINE_LOOP);
    if (bonus.type_bonus == 1)
    {
        glColor3f(.5, 0.5, 0.);
    }
    else if (bonus.type_bonus == 0)
    {
        glColor3f(1., 1., 1.);
    }
    else if (bonus.type_bonus == 2)
    {
        /*
        printf("(%f,%f,%f)\n", bonus.x, bonus.y, bonus.z);
        */
        glColor3f(1., 0., 0.);
    }
    glVertex3f(bonus.x, bonus.y, bonus.z - 2 * bonus.indic_taille);
    glVertex3f(bonus.x + bonus.indic_taille * cos(bonus.angle), bonus.y - bonus.indic_taille * sin(bonus.angle), bonus.z);
    glVertex3f(bonus.x, bonus.y, bonus.z + 2 * bonus.indic_taille);

    glVertex3f(bonus.x + bonus.indic_taille * cos(bonus.angle + PI / 2), bonus.y - bonus.indic_taille * sin(bonus.angle + PI / 2), bonus.z);
    glVertex3f(bonus.x, bonus.y, bonus.z - 2 * bonus.indic_taille);

    glVertex3f(bonus.x + bonus.indic_taille * cos(bonus.angle - PI / 2), bonus.y - bonus.indic_taille * sin(bonus.angle - PI / 2), bonus.z);
    glVertex3f(bonus.x, bonus.y, bonus.z + 2 * bonus.indic_taille);

    glVertex3f(bonus.x + bonus.indic_taille * cos(bonus.angle + PI), bonus.y - bonus.indic_taille * sin(bonus.angle + PI), bonus.z);
    glVertex3f(bonus.x, bonus.y, bonus.z - 2 * bonus.indic_taille);

    glVertex3f(bonus.x + bonus.indic_taille * cos(bonus.angle), bonus.y - bonus.indic_taille * sin(bonus.angle), bonus.z);
    glVertex3f(bonus.x + bonus.indic_taille * cos(bonus.angle + PI / 2), bonus.y - bonus.indic_taille * sin(bonus.angle + PI / 2), bonus.z);
    glVertex3f(bonus.x + bonus.indic_taille * cos(bonus.angle + PI), bonus.y - bonus.indic_taille * sin(bonus.angle + PI), bonus.z);
    glVertex3f(bonus.x + bonus.indic_taille * cos(bonus.angle - PI / 2), bonus.y - bonus.indic_taille * sin(bonus.angle - PI / 2), bonus.z);
    glVertex3f(bonus.x + bonus.indic_taille * cos(bonus.angle), bonus.y - bonus.indic_taille * sin(bonus.angle), bonus.z);

    glEnd();
    glPopMatrix();
}

void drawMenu()
{
    for (int i = 0; i < 4; i++)
    {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, textures[i].texture);

        glPushMatrix();
        glBegin(GL_QUADS);
        glTexCoord2f(0., 1.);
        glVertex3f(-TAILLE_X, 0, TAILLE_Z - (TAILLE_Z / 4.) * (i + 1));

        glTexCoord2f(1., 1.);
        glVertex3f(0, 0, TAILLE_Z - (TAILLE_Z / 4.) * (i + 1));

        glTexCoord2f(1., 0.);
        glVertex3f(0, 0, TAILLE_Z - (TAILLE_Z / 4.) * i);

        glTexCoord2f(0., 0.);
        glVertex3f(-TAILLE_X, 0, TAILLE_Z - (TAILLE_Z / 4.) * i);
        glEnd();
        glPopMatrix();

        glBindTexture(GL_TEXTURE_2D, 0);
        glDisable(GL_TEXTURE_2D);
    }
}

void draw_result(int i)
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textures[i].texture);
    glPushMatrix();
    glBegin(GL_QUADS);
    glTexCoord2f(0., 1.);
    glVertex3f(-TAILLE_X, 0., 0.);

    glTexCoord2f(1., 1.);
    glVertex3f(0., 0., 0.);

    glTexCoord2f(1., 0.);
    glVertex3f(0., 0., TAILLE_Z);

    glTexCoord2f(0., 0.);
    glVertex3f(-TAILLE_X, 0., TAILLE_Z);
    glEnd();
    glPopMatrix();
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);
}

void draw_result_score(int score)
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textures[1].texture);
    glPushMatrix();
    glBegin(GL_QUADS);
    glTexCoord2f(0., 1.);
    glVertex3f(-5, 0., 4.5);

    glTexCoord2f(1., 1.);
    glVertex3f(-4.5, 0., 4.5);

    glTexCoord2f(1., 0.);
    glVertex3f(-4.5, 0., 5.);

    glTexCoord2f(0., 0.);
    glVertex3f(-5, 0., 5.);
    glEnd();
    glPopMatrix();
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);
}