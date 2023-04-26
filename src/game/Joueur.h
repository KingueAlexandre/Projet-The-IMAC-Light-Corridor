#include <stdio.h>
#include <stdlib.h>

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

Joueur initJoueur(float x, float y, float z, float max_x, float max_z, float dist_cote);

#endif