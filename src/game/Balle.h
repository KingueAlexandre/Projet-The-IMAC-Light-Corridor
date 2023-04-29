#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "Mur.h"
#include "Joueur.h"

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

int colision_balle_obs_type(Balle *balle, Obstacles *ret);

void colision_balle_obs(Balle *balle, LstObstacles obstacles, Joueur joueur);

int colision_balle_joueur(Balle *balle, Joueur joueur, int flag_attente_balle_collante);

int collision_joueur_murs(LstObstacles obstacles, Joueur joueur);

int colision_bonus_balle(Bonus *bonus1, Bonus *bonus2, Balle balle, Joueur *joueur, int nb_section);

#endif