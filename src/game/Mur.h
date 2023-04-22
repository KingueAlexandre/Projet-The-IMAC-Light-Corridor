#include <stdio.h>
#include <stdlib.h>

static int courrant_num_mur = 0;

typedef struct Murs
{
    int num;
    int debut_x;
    int debut_y;
    int debut_z;
    int taille_x;
    int taille_y;
    int taille_z;
    int mur1[4][3];
    int mur2[4][3];
    int mur3[4][3];
    int mur4[4][3];

    struct Murs *suivant;
}Murs, *LstMurs;

Murs *AlloueMurs(int debut_x, int debut_y, int debut_z, int taille_x, int taille_y, int taille_z);

int insererM(LstMurs *lst, int debut_x, int debut_y, int debut_z, int taille_x, int taille_y, int taille_z);

void freePile(LstMurs *murs);

LstMurs section_murs(LstMurs murs, int num);
