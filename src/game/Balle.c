#include "Balle.h"

Balle initBalle(float x, float y, float z)
{
    Balle balle;
    balle.x = x;
    balle.y = y;
    balle.z = z;
    balle.vec_x = 0.5;
    balle.vec_y = 0.5;
    balle.vec_z = -0.5;
    balle.force_vec_x = 0.2;
    balle.force_vec_y = 0.2;
    balle.force_vec_z = 0.2;
    return balle;
}

void mouv_balle(Balle *balle)
{

    balle->x += balle->vec_x * balle->force_vec_x;
    balle->y += balle->vec_y * balle->force_vec_y;
    balle->z += balle->vec_z * balle->force_vec_z;
}

void colision_balle_mur(Balle *balle, int max_x, int max_z)
{
    if (balle->x - 1 <= -max_x)
    {

        balle->vec_x *= -1;
        balle->x = 1 - max_x;
    }
    else if (0 <= balle->x + 1)
    {

        balle->vec_x *= -1;
        balle->x = -1.;
    }
    if (balle->z - 1 <= 0)
    {

        balle->vec_z *= -1;
        balle->z = 1.;
    }
    else if (max_z <= balle->z + 1)
    {

        balle->vec_z *= -1;
        balle->z = max_z - 1.;
    }
}

int colision_balle_obs_type(Balle *balle, Obstacles *ret)
{

    return (ret->debut_x >= balle->x && ret->mur[2][0] <= balle->x) && (ret->debut_z <= balle->z && ret->mur[2][2] >= balle->z);
}

int colision_balle_obs_type_rebord(Balle *balle, Obstacles *ret)
{
    /*BORD HORIZONTAL*/
    float ajout_x, ajout_y, ajout_z;

    float dist_hb = sqrt((balle->y - ret->mur[0][1]) * (balle->y - ret->mur[0][1]) + (balle->z - ret->mur[0][2]) * (balle->z - ret->mur[0][2]));
    float dist_hh = sqrt((balle->y - ret->mur[0][1]) * (balle->y - ret->mur[0][1]) + (balle->z - ret->mur[2][2]) * (balle->z - ret->mur[2][2]));

    float dist_vb = sqrt((balle->y - ret->mur[0][1]) * (balle->y - ret->mur[0][1]) + (balle->x - ret->mur[0][0]) * (balle->x - ret->mur[0][0]));
    float dist_vh = sqrt((balle->y - ret->mur[0][1]) * (balle->y - ret->mur[0][1]) + (balle->x - ret->mur[1][0]) * (balle->x - ret->mur[1][0]));
    if (dist_hb <= 1.)
    {
        ajout_y = balle->y - ret->mur[0][1];
        ajout_z = balle->z - ret->mur[0][2];
        balle->vec_y += ajout_y;
        balle->vec_z += ajout_z;
    }
    else if (dist_hh <= 1.)
    {
        ajout_y = balle->y - ret->mur[0][1];
        ajout_z = balle->z - ret->mur[2][2];
        balle->vec_y += ajout_y;
        balle->vec_z += ajout_z;
    }
    if (dist_vb <= 1.)
    {
        ajout_y = balle->y - ret->mur[0][1];
        ajout_x = balle->x - ret->mur[0][0];
        balle->vec_y += ajout_y;
        balle->vec_x += ajout_x;
    }
    else if (dist_vh <= 1.)
    {
        ajout_y = balle->y - ret->mur[0][1];
        ajout_x = balle->x - ret->mur[1][0];
        balle->vec_y += ajout_y;
        balle->vec_x += ajout_x;
    }

    return 1;
}

int colision_balle_obs_type_rebord_3(Balle *balle, Obstacles *ret)
{
    /*BORD HORIZONTAL*/
    float ajout_x, ajout_y, ajout_z;

    float dist_hb = sqrt((balle->y - ret->mur[0][1]) * (balle->y - ret->mur[0][1]) + (balle->z - ret->mur[0][2]) * (balle->z - ret->mur[0][2]));
    float dist_hh = sqrt((balle->y - ret->mur[0][1]) * (balle->y - ret->mur[0][1]) + (balle->z - ret->mur[2][2]) * (balle->z - ret->mur[2][2]));

    float dist_vb = sqrt((balle->y - ret->mur[0][1]) * (balle->y - ret->mur[0][1]) + (balle->x - ret->mur[0][0]) * (balle->x - ret->mur[0][0]));
    float dist_vh = sqrt((balle->y - ret->mur[0][1]) * (balle->y - ret->mur[0][1]) + (balle->x - ret->mur[1][0]) * (balle->x - ret->mur[1][0]));
    if (dist_hb <= 1. && (ret->debut_x >= balle->x - 1 && ret->mur[2][0] <= balle->x + 1))
    {
        ajout_y = balle->y - ret->mur[0][1];
        ajout_z = balle->z - ret->mur[0][2];
        balle->vec_y += ajout_y;
        balle->vec_z += ajout_z;
    }
    else if (dist_hh <= 1. && (ret->debut_x >= balle->x - 1 && ret->mur[2][0] <= balle->x + 1))
    {
        ajout_y = balle->y - ret->mur[0][1];
        ajout_z = balle->z - ret->mur[2][2];
        balle->vec_y += ajout_y;
        balle->vec_z += ajout_z;
    }
    if (dist_vb <= 1. && (ret->debut_z <= balle->z - 1 && ret->mur[2][2] >= balle->z + 1))
    {
        ajout_y = balle->y - ret->mur[0][1];
        ajout_x = balle->x - ret->mur[0][0];
        balle->vec_y += ajout_y;
        balle->vec_x += ajout_x;
    }
    else if (dist_vh <= 1. && (ret->debut_z <= balle->z - 1 && ret->mur[2][2] >= balle->z + 1))
    {
        ajout_y = balle->y - ret->mur[0][1];
        ajout_x = balle->x - ret->mur[1][0];
        balle->vec_y += ajout_y;
        balle->vec_x += ajout_x;
    }

    return 1;
}

void colision_balle_obs(Balle *balle, LstObstacles obstacles, Joueur joueur)
{
    Obstacles *ret = obstacles;
    while (ret != NULL)
    {
        if (ret->mur[0][1] > joueur.y)
        {
            if (((balle->y <= ret->debut_y && balle->y + 1. >= ret->debut_y) || (balle->y >= ret->debut_y && balle->y - 1. <= ret->debut_y)))
            {
                /*
                (balle->z < ret->debut_z && balle->z + 1. >= ret->debut_z)*/
                if (colision_balle_obs_type(balle, ret))
                {
                    balle->vec_y *= -1.;
                    ret->vie -= 1;
                    if (ret->type_obs == 4)
                    {
                        ret->r -= 9.;
                        ret->g -= 9.;
                        ret->b -= 9.;
                        if (balle->vec_x < 0)
                        {
                            balle->vec_x -= (0.1 * (rand() % 4));
                        }
                        else
                        {
                            balle->vec_x += (0.1 * (rand() % 4));
                        }
                        if (balle->vec_z < 0)
                        {
                            balle->vec_z -= (0.1 * (rand() % 4));
                        }
                        else
                        {
                            balle->vec_z += (0.1 * (rand() % 4));
                        }
                        if (balle->force_vec_x < 0.6)
                        {
                            balle->force_vec_x += (0.1 * (rand() % 2));
                        }
                        if (balle->force_vec_z < 0.6)
                        {
                            balle->force_vec_z += (0.1 * (rand() % 2));
                        }
                    }
                }
                if (ret->type_obs != 3)
                {
                    colision_balle_obs_type_rebord(balle, ret);
                }
                else
                {
                    colision_balle_obs_type_rebord_3(balle, ret);
                }
            }
        }
        ret = ret->suivant;
    }
}

int colision_balle_joueur(Balle *balle, Joueur joueur, int flag_attente_balle_collante)
{

    if ((balle->y >= joueur.y && balle->y - 1. <= joueur.y) &&
        (joueur.max_cote_x >= balle->x && joueur.min_cote_x <= balle->x) &&
        (joueur.max_cote_z >= balle->z && joueur.min_cote_z <= balle->z))
    {
        /*BALLE COLLANTE*/
        if (flag_attente_balle_collante)
        {
            balle->x = joueur.x;
            balle->y = joueur.y;
            balle->z = joueur.z;
            return 2;
        }

        balle->vec_y *= -1.;
        balle->y += 0.5;

        float centre_z = (joueur.max_cote_z + joueur.min_cote_z) / 2;
        float ajout_vec_z = ((balle->z - joueur.min_cote_z) / (joueur.max_cote_z - joueur.min_cote_z)) - ((centre_z - joueur.min_cote_z) / (joueur.max_cote_z - joueur.min_cote_z));
        float centre_x = (joueur.min_cote_x + joueur.max_cote_x) / 2;
        float ajout_vec_x = ((balle->x - joueur.min_cote_x) / (joueur.max_cote_x - joueur.min_cote_x)) - ((centre_x - joueur.min_cote_x) / (joueur.max_cote_x - joueur.min_cote_x));

        balle->vec_x += ajout_vec_x / (joueur.dist_cote);
        balle->vec_z += ajout_vec_z / (joueur.dist_cote);

        return 1;
    }
    return 0;
}

int collision_joueur_murs(LstObstacles obstacles, Joueur joueur)
{
    Obstacles *ret = obstacles;
    while (ret != NULL)
    {
        if (ret->mur[0][1] - 5. >= joueur.y && ret->mur[0][1] - 6. <= joueur.y)
        {
            if (((joueur.max_cote_x <= ret->mur[0][0] && joueur.max_cote_x >= ret->mur[1][0]) ||
                 (joueur.min_cote_x <= ret->mur[0][0] && joueur.min_cote_x >= ret->mur[1][0])) &&
                ((joueur.max_cote_z <= ret->mur[2][2] && joueur.max_cote_z >= ret->mur[0][2]) ||
                 (joueur.min_cote_z <= ret->mur[2][2] && joueur.min_cote_z > ret->mur[0][2])))
            {
                return 1;
            }
            return 0;
        }
        ret = ret->suivant;
    }
    return 0;
}

int colision_bonus_balle(Bonus *bonus1, Bonus *bonus2, Bonus *bonus3, Balle *balle, Joueur *joueur, int nb_section)
{
    int ret = 0;
    if ((bonus1->x - bonus1->indic_taille <= balle->x + 1 && balle->x - 1 <= bonus1->x + bonus1->indic_taille) &&
        (bonus1->y - bonus1->indic_taille <= balle->y + 1 && balle->y - 1 <= bonus1->y + bonus1->indic_taille) &&
        (bonus1->z - 2 * bonus1->indic_taille <= balle->z + 1 && balle->z - 1 <= bonus1->z + 2 * bonus1->indic_taille))
    {
        if (bonus1->type_bonus == 0)
        {
            joueur->vie += 1;
        }
        else if (bonus1->type_bonus == 1)
        {
            ret = 1;
        }
        else if (bonus1->type_bonus == 2)
        {
            if (balle->force_vec_y < 0.6)
            {
                balle->force_vec_y += 0.4;
            }
        }

        *bonus1 = generateBonus(rand() % 3, joueur->y, DIST_CAM_RAQ, TAILLE_X, TAILLE_Y, TAILLE_Z);
    }
    if ((bonus2->x - bonus2->indic_taille <= balle->x + 1 && balle->x - 1 <= bonus2->x + bonus2->indic_taille) &&
        (bonus2->y - bonus2->indic_taille <= balle->y + 1 && balle->y - 1 <= bonus2->y + bonus2->indic_taille) &&
        (bonus2->z - 2 * bonus2->indic_taille <= balle->z + 1 && balle->z - 1 <= bonus2->z + 2 * bonus2->indic_taille))
    {
        if (bonus2->type_bonus == 0)
        {
            joueur->vie += 1;
        }
        else if (bonus2->type_bonus == 1)
        {
            ret = 1;
        }
        else if (bonus1->type_bonus == 2)
        {
            if (balle->force_vec_y < 0.6)
            {
                balle->force_vec_y += 0.4;
            }
        }

        *bonus2 = generateBonus(rand() % 3, joueur->y, DIST_CAM_RAQ, TAILLE_X, TAILLE_Y, TAILLE_Z);
    }

    if ((bonus3->x - bonus3->indic_taille <= balle->x + 1 && balle->x - 1 <= bonus3->x + bonus3->indic_taille) &&
        (bonus3->y - bonus3->indic_taille <= balle->y + 1 && balle->y - 1 <= bonus3->y + bonus3->indic_taille) &&
        (bonus3->z - 2 * bonus3->indic_taille <= balle->z + 1 && balle->z - 1 <= bonus3->z + 2 * bonus3->indic_taille))
    {
        if (bonus3->type_bonus == 0)
        {
            joueur->vie += 1;
        }
        else if (bonus3->type_bonus == 1)
        {
            ret = 1;
        }
        else if (bonus1->type_bonus == 2)
        {
            if (balle->force_vec_y < 0.6)
            {
                balle->force_vec_y += 0.4;
            }
        }

        *bonus3 = generateBonus(rand() % 3, joueur->y, DIST_CAM_RAQ, TAILLE_X, TAILLE_Y, TAILLE_Z);
    }
    return ret;
}