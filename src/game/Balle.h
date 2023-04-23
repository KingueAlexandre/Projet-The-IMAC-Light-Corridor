#include <stdio.h>
#include <stdlib.h>

#include "Mur.h"

#ifndef __BALLE__
#define __BALLE__

typedef struct Balle
{
    float x;
    float y;
    float z;

    float vec_x;
    float vec_y;
    float vec_z;

    float force_vec_x;
    float force_vec_y;
    float force_vec_z;
} Balle;

Balle initBalle(float x, float y, float z);

void mouv_balle(Balle *balle);

void colision_balle_mur(Balle *balle, int max_x, int max_z);

void colision_balle_obs(Balle *balle, LstObstacles obstacles);

#endif