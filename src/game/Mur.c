#include "Mur.h"

Murs *AlloueMurs(float debut_x, float debut_y, float debut_z, float taille_x, float taille_y, float taille_z)
{
    Murs *murs = (Murs *)malloc(sizeof(Murs));
    // Element *element = malloc(sizeof(*element));

    if (murs == NULL)
    {
        printf("malloc(sizeof(LstMurs)) déconne.\n");
        return NULL;
    }
    murs->num = courrant_num_mur++;
    murs->debut_x = debut_x;
    murs->debut_y = debut_y;
    murs->debut_z = debut_z;
    murs->taille_x = taille_x;
    murs->taille_y = taille_y;
    murs->taille_z = taille_z;
    /*
        liste->mur1[0] = {debut_x,debut_y,debut_z};
        liste->mur1[1] = [debut_x-taille_x,debut_y,debut_z];
        liste->mur1[2] = [debut_x-taille_x,debut_y+taille_y,debut_z];
        liste->mur1[3] = [debut_x,debut_y+taille_y,debut_z];
    */
    murs->mur[0][0] = debut_x;
    murs->mur[0][1] = debut_y;
    murs->mur[0][2] = debut_z;

    murs->mur[1][0] = debut_x - taille_x;
    murs->mur[1][1] = debut_y;
    murs->mur[1][2] = debut_z;

    murs->mur[2][0] = debut_x - taille_x;
    murs->mur[2][1] = debut_y + taille_y;
    murs->mur[2][2] = debut_z;

    murs->mur[3][0] = debut_x;
    murs->mur[3][1] = debut_y + taille_y;
    murs->mur[3][2] = debut_z;

    murs->suivant = NULL;

    return murs;
}
int insererM(LstMurs *lst, float debut_x, float debut_y, float debut_z, float taille_x, float taille_y, float taille_z)
{
    Murs *cel;
    cel = AlloueMurs(debut_x, debut_y, debut_z, taille_x, taille_y, taille_z);
    if (cel == NULL)
    {
        printf("Erreur mémoire.\n");
        return -1;
    }
    if (*lst == NULL)
    {
        *lst = cel;
        return 1;
    }
    cel->suivant = *lst;
    *lst = cel;
    return 1;
}

void freePile(LstMurs *murs)
{
    Murs *iter = *murs;
    Murs *temp = iter;
    while (iter != NULL)
    {
        temp = iter->suivant;
        free(iter);
        iter = temp;
    }
    *murs = NULL;
}

LstMurs section_murs(LstMurs murs, int num)
{
    Murs *ret = murs;
    while (ret != NULL)
    {
        if (ret->num == num)
        {
            return ret;
        }
        ret = ret->suivant;
    }
    return NULL;
}
