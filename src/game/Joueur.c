#include "Joueur.h"

Joueur initJoueur(float x, float y, float z, float max_x, float max_z, float dist_cote)
{
    Joueur ret;
    ret.x = x;
    ret.y = y;
    ret.z = z;
    ret.max_x = max_x;
    ret.max_z = max_z;
    ret.dist_cote = dist_cote;
    ret.max_cote_x = 0;
    ret.max_cote_z = 0;
    ret.min_cote_x = 0;
    ret.min_cote_z = 0;
    ret.vie = 5;
    ret.score = 0;
    return ret;
}