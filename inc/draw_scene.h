#pragma once

#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "../src/game/Mur.h"
#include "../src/game/Balle.h"

void drawFrame();

void drawBase();

void drawArm();

void drawPan();

void drawMurs(LstMurs lst);

void drawMur(float mur[4][3]);

void drawBalle(Balle balle);
