#include <stdio.h>
#include <stdlib.h>

#ifndef __MUR__
#define __MUR__

typedef struct Murs
{
    int flag_mur;
    int num;
    float debut_x;
    float debut_y;
    float debut_z;
    float taille_x;
    float taille_y;
    float taille_z;
    float mur[4][3];
    float r;
    float g;
    float b;

    struct Murs *suivant;
} Murs, *LstMurs;

typedef struct Obstacles
{
    int type_obs;
    int sous_type;
    int num;
    float debut_x;
    float debut_y;
    float debut_z;
    float taille_x;
    float taille_y;
    float taille_z;
    float mur[4][3];
    float r;
    float g;
    float b;

    struct Obstacles *suivant;
} Obstacles, *LstObstacles;

Murs *AlloueMurs(float debut_x, float debut_y, float debut_z, float taille_x, float taille_y, float taille_z);

Obstacles *AlloueObstacles1(float debut_x, float debut_y, float debut_z, float taille_x, float taille_y, float taille_z);

Obstacles *AlloueObstacles2(float debut_x, float debut_y, float debut_z, float taille_x, float taille_y, float taille_z);

int insererM(LstMurs *lst, float debut_x, float debut_y, float debut_z, float taille_x, float taille_y, float taille_z);

int insererO(LstObstacles *lst, LstMurs murs);

void freePile(LstMurs *murs);

LstMurs section_murs(LstMurs murs, int num);

#endif