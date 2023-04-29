#pragma once

#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define PI 3.14159

#include "../src/game/Mur.h"
#include "../src/game/Balle.h"
#include "../src/game/Joueur.h"

#ifndef __DRAW__
#define __DRAW__

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

#endif