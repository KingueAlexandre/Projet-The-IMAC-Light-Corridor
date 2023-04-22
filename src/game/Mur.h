#include <stdio.h>
#include <stdlib.h>

static int courrant_num_mur = 0;

typedef struct Murs
{
    int num;
    float debut_x;
    float debut_y;
    float debut_z;
    float taille_x;
    float taille_y;
    float taille_z;
    float mur[4][3];

    struct Murs *suivant;
} Murs, *LstMurs;

Murs *AlloueMurs(float debut_x, float debut_y, float debut_z, float taille_x, float taille_y, float taille_z);

int insererM(LstMurs *lst, float debut_x, float debut_y, float debut_z, float taille_x, float taille_y, float taille_z);

void freePile(LstMurs *murs);

LstMurs section_murs(LstMurs murs, int num);
