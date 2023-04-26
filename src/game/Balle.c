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
    /*    printf("%f += %f * %f\n", balle->x, balle->vec_x, balle->force_vec_x);
     */
    balle->x += balle->vec_x * balle->force_vec_x;
    balle->y += balle->vec_y * balle->force_vec_y;
    balle->z += balle->vec_z * balle->force_vec_z;
}

void colision_balle_mur(Balle *balle, int max_x, int max_z)
{
    if (balle->x - 1 <= -max_x)
    {
        /*
        printf("Colision mur gauche: (%f,%f,%f)\n", balle->x, balle->y, balle->z);
        */
        balle->vec_x *= -1;
        balle->x = 1 - max_x;
    }
    else if (0 <= balle->x + 1)
    {
        /*
        printf("Colision mur droite: (%f,%f,%f)\n", balle->x, balle->y, balle->z);
        */
        balle->vec_x *= -1;
        balle->x = -1.;
    }
    if (balle->z - 1 <= 0)
    {
        /*
        printf("Colision mur bas: (%f,%f,%f)\n", balle->x, balle->y, balle->z);
        */
        balle->vec_z *= -1;
        balle->z = 1.;
    }
    else if (max_z <= balle->z + 1)
    {
        /*
        printf("Colision mur haut: (%f,%f,%f)\n", balle->x, balle->y, balle->z);
        */
        balle->vec_z *= -1;
        balle->z = max_z - 1.;
    }
}

int colision_balle_obs_type(Balle *balle, Obstacles *ret)
{
    /*
    printf("(%f >= %f && %f <= %f) && (%f <= %f && %f >= %f)\n", ret->debut_x, balle->x, ret->mur[2][0], balle->x, ret->debut_z, balle->z, ret->mur[2][2], balle->z);
    */
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
    else if (dist_vb <= 1.)
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
    else
    {
        return 0;
    }
    /*BORD VERTICAL*/

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
                    /*
                    printf("Colision Obstacle: (%f,%f,%f)\n", balle->x, balle->y, balle->z);

                    for (int i = 0; i < 4; i++)
                    {
                        printf("(%f,%f,%f) ", ret->mur[i][0], ret->mur[i][1], ret->mur[i][2]);
                    }
                    printf("\n");
                    */
                    balle->vec_y *= -1.;
                }
                else if (colision_balle_obs_type_rebord(balle, ret))
                {
                }
            }
        }
        ret = ret->suivant;
    }
}

int colision_balle_joueur(Balle *balle, Joueur joueur)
{
    if ((balle->y >= joueur.y && balle->y - 1. <= joueur.y) &&
        (joueur.max_cote_x >= balle->x && joueur.min_cote_x <= balle->x) &&
        (joueur.max_cote_z >= balle->z && joueur.min_cote_z <= balle->z))
    {
        /*
        printf("Colision Raquette\n");
        printf("Balle: (%f,%f,%f)\n", balle->x, balle->y, balle->z);
        printf("Raquette: (%f,%f,%f)\n", joueur.x, joueur.y, joueur.z);

        printf("Colision Raquette: (%f,%f,%f)\n", balle->vec_x, balle->vec_y, balle->vec_z);
        */
        balle->vec_y *= -1.;
        balle->y += 0.5;

        float centre_z = (joueur.max_cote_z + joueur.min_cote_z) / 2;
        float ajout_vec_z = ((balle->z - joueur.min_cote_z) / (joueur.max_cote_z - joueur.min_cote_z)) - ((centre_z - joueur.min_cote_z) / (joueur.max_cote_z - joueur.min_cote_z));
        float centre_x = (joueur.min_cote_x + joueur.max_cote_x) / 2;
        float ajout_vec_x = ((balle->x - joueur.min_cote_x) / (joueur.max_cote_x - joueur.min_cote_x)) - ((centre_x - joueur.min_cote_x) / (joueur.max_cote_x - joueur.min_cote_x));
        /*
        balle->vec_x *= -1.;
        balle->vec_z *= -1.;

        printf("centre_x = %f = (%f + %f) / 2\n", (joueur.min_cote_x + joueur.max_cote_x) / 2, joueur.min_cote_x, joueur.max_cote_x);
        printf("ajout_vec_x  = %f = ((%f - %f) / (%f - %f)) - ((centre_x - %f) / (%f - %f));", ((balle->x - joueur.min_cote_x) / (joueur.max_cote_x - joueur.min_cote_x)) - ((centre_x - joueur.min_cote_x) / (joueur.max_cote_x - joueur.min_cote_x)), balle->x, joueur.min_cote_x, joueur.max_cote_x, joueur.min_cote_x, joueur.min_cote_x, joueur.max_cote_x, joueur.min_cote_x);
        printf("%f += %f / %f\n", balle->vec_x, ajout_vec_x, (joueur.dist_cote * 10));

        printf("centre_z = %f = (%f + %f) / 2\n", (joueur.min_cote_z + joueur.max_cote_z) / 2, joueur.min_cote_z, joueur.max_cote_z);
        printf("ajout_vec_z  = %f = ((%f - %f) / (%f - %f)) - ((centre_z - %f) / (%f - %f));", ((balle->z - joueur.min_cote_z) / (joueur.max_cote_z - joueur.min_cote_z)) - ((centre_z - joueur.min_cote_z) / (joueur.max_cote_z - joueur.min_cote_z)), balle->z, joueur.min_cote_z, joueur.max_cote_z, joueur.min_cote_z, joueur.min_cote_z, joueur.max_cote_z, joueur.min_cote_z);

        printf("%f += %f / %f\n", balle->vec_z, ajout_vec_z, (joueur.dist_cote));
        */
        balle->vec_x += ajout_vec_x / (joueur.dist_cote);
        balle->vec_z += ajout_vec_z / (joueur.dist_cote);
        /*
        printf("Colision Raquette: (%f,%f,%f)\n", balle->vec_x, balle->vec_y, balle->vec_z);
        */
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