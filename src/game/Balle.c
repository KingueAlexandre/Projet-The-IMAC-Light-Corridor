#include "Balle.h"

Balle initBalle(float x, float y, float z)
{
    Balle balle;
    balle.x = x;
    balle.y = y;
    balle.z = z;
    balle.vec_x = 0.5;
    balle.vec_y = 0.5;
    balle.vec_z = 0.5;
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
        printf("Colision mur gauche: (%f,%f,%f)\n", balle->x, balle->y, balle->z);
        balle->vec_x *= -1;
    }
    else if (0 <= balle->x + 1)
    {
        printf("Colision mur droite: (%f,%f,%f)\n", balle->x, balle->y, balle->z);
        balle->vec_x *= -1;
    }
    if (balle->z - 1 <= 0)
    {
        printf("Colision mur bas: (%f,%f,%f)\n", balle->x, balle->y, balle->z);
        balle->vec_z *= -1;
    }
    else if (max_z <= balle->z + 1)
    {
        printf("Colision mur haut: (%f,%f,%f)\n", balle->x, balle->y, balle->z);
        balle->vec_z *= -1;
    }
}