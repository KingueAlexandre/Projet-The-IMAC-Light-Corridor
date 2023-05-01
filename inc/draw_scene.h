#pragma once

#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define PI 3.14159
#define NB_TEXTURE 17

#include "../src/game/Mur.h"
#include "../src/game/Balle.h"
#include "../src/game/Joueur.h"

#ifndef __DRAW__
#define __DRAW__

/*TYPE STRUCTURÉ REGROUPANT TOUTE LES INFOS UTILES POUR LOAD UNE TEXTURE*/
typedef struct Texture
{
    unsigned char *Niveau1;
    unsigned int texture;
    int largeur;
    int hauteur;
    int nbcanaux;
} Texture;

/*FONCTION CHARGEANT LES TEXTURE UTILES*/
void loadtextures();

/*FONCTION LIBÉRANT LES TEXTURES UTILES*/
void freetextures();

void drawFrame();

void drawBase();

void drawArm();

void drawPan();

void drawMurs(LstMurs lst, float cam_y);

void drawObstacles(LstObstacles lst, Joueur joueur);

void drawMur(float mur[4][3]);

void printfObstacles(LstObstacles lst);

void printfMur(float mur[4][3]);

void drawBalle(Balle balle);

void drawJoueur(Joueur joueur);

void drawBonus(Bonus bonus);

void drawMenu();

void draw_result(int i);

void draw_result_score(int score);

#endif