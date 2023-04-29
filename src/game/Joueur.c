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
    ret.vie = 10;
    ret.score = 0;
    return ret;
}

Bonus generateBonus(int type_bonus, float y, float dist_came_joueur, float taille_x, float taille_y, float taille_z, int nb_section)
{
    Bonus ret;
    ret.type_bonus = type_bonus;
    ret.indic_taille = 0.5;
    ret.x = -(ret.indic_taille + (rand() % (int)(taille_x - 2 * ret.indic_taille)));
    ret.y = (nb_section - 1) * taille_y + ret.indic_taille + dist_came_joueur + (rand() % (int)(taille_y * 3 - 2 * ret.indic_taille));
    ret.z = 2 * ret.indic_taille + (rand() % (int)(taille_z - 4 * ret.indic_taille));

    ret.angle_x = 0.;
    ret.angle_y = 0.;
    ret.angle_z = 0.;

    return ret;
}