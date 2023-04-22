#pragma once

#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "../src/game/Mur.h"

void drawFrame();

void drawBase();

void drawArm();

void drawPan();

void drawMurs(LstMurs lst);

void drawMur(int mur[4][3]);

