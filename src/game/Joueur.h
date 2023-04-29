#include <stdio.h>
#include <stdlib.h>

#define DIST_CAM_RAQ 13

#ifndef __JOUEUR__
#define __JOUEUR__

typedef struct Joueur
{
    float x;
    float y;
    float z;
    float max_x;
    float max_z;
    float min_cote_x;
    float min_cote_z;
    float max_cote_x;
    float max_cote_z;
    float dist_cote;
    int score;
    int vie;
} Joueur;

typedef struct Bonus
{
    int type_bonus;
    float x;
    float y;
    float z;
    float angle;

    float indic_taille;
} Bonus;

Joueur initJoueur(float x, float y, float z, float max_x, float max_z, float dist_cote);

Bonus generateBonus(int type_bonus, float y, float dist_came_joueur, float taille_x, float taille_y, float taille_z);

#endif