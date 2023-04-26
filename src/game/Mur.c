#include "Mur.h"

#define FREQUENCE_OBS 40.

static int courrant_num_mur = 0;
static int courrant_num_obs = 0;

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

    murs->r = 100.;
    murs->g = 1.;
    murs->b = 1.;

    murs->suivant = NULL;

    return murs;
}

Obstacles *AlloueObstacles1(float debut_x, float debut_y, float debut_z, float taille_x, float taille_y, float taille_z)
{
    Obstacles *obstacles = (Obstacles *)malloc(sizeof(Obstacles));
    // Element *element = malloc(sizeof(*element));
    float tmp;
    if (obstacles == NULL)
    {
        printf("malloc(sizeof(LstMurs)) déconne.\n");
        return NULL;
    }
    obstacles->type_obs = 1;
    obstacles->num = courrant_num_obs++;

    tmp = ((float)rand() / (float)(RAND_MAX)) * (taille_x - DIST_RAYON_COTE_RAQUETTE * 2 + 2);
    printf("tmp=%f\n", tmp);
    if (rand() % 2 == 0)
    {
        obstacles->sous_type = 0;

        printf("1-0\n");
        obstacles->debut_x = -tmp;
        obstacles->debut_y = debut_y;
        obstacles->debut_z = debut_z;
        obstacles->taille_x = tmp;
        obstacles->taille_y = taille_y;
        obstacles->taille_z = taille_z;

        obstacles->mur[0][0] = -tmp;
        obstacles->mur[0][1] = debut_y;
        obstacles->mur[0][2] = debut_z;

        obstacles->mur[1][0] = -taille_x;
        obstacles->mur[1][1] = debut_y;
        obstacles->mur[1][2] = debut_z;

        obstacles->mur[2][0] = -taille_x;
        obstacles->mur[2][1] = debut_y;
        obstacles->mur[2][2] = debut_z + taille_z;

        obstacles->mur[3][0] = -tmp;
        obstacles->mur[3][1] = debut_y;
        obstacles->mur[3][2] = debut_z + taille_z;
    }
    else
    {
        obstacles->sous_type = 1;

        printf("1-1\n");
        obstacles->debut_x = debut_x;
        obstacles->debut_y = debut_y;
        obstacles->debut_z = debut_z;
        obstacles->taille_x = tmp;
        obstacles->taille_y = taille_y;
        obstacles->taille_z = taille_z;

        obstacles->mur[0][0] = debut_x;
        obstacles->mur[0][1] = debut_y;
        obstacles->mur[0][2] = debut_z;

        obstacles->mur[1][0] = debut_x - tmp;
        obstacles->mur[1][1] = debut_y;
        obstacles->mur[1][2] = debut_z;

        obstacles->mur[2][0] = debut_x - tmp;
        obstacles->mur[2][1] = debut_y;
        obstacles->mur[2][2] = debut_z + taille_z;

        obstacles->mur[3][0] = debut_x;
        obstacles->mur[3][1] = debut_y;
        obstacles->mur[3][2] = debut_z + taille_z;
    }

    obstacles->r = 148.;
    obstacles->g = 0.;
    obstacles->b = 211.;

    obstacles->suivant = NULL;
    return obstacles;
}

Obstacles *AlloueObstacles2(float debut_x, float debut_y, float debut_z, float taille_x, float taille_y, float taille_z)
{
    Obstacles *obstacles = (Obstacles *)malloc(sizeof(Obstacles));
    // Element *element = malloc(sizeof(*element));
    float tmp;
    if (obstacles == NULL)
    {
        printf("malloc(sizeof(LstMurs)) déconne.\n");
        return NULL;
    }
    obstacles->type_obs = 1;
    obstacles->num = courrant_num_obs++;

    tmp = ((float)rand() / (float)(RAND_MAX)) * (taille_z - DIST_RAYON_COTE_RAQUETTE * 2 + 2);
    printf("tmp=%f\n", tmp);
    if (rand() % 2 == 0)
    {
        obstacles->sous_type = 0;
        printf("2-0\n");
        obstacles->debut_x = debut_x;
        obstacles->debut_y = debut_y;
        obstacles->debut_z = debut_z;
        obstacles->taille_x = taille_x;
        obstacles->taille_y = taille_y;
        obstacles->taille_z = tmp;

        obstacles->mur[0][0] = debut_x;
        obstacles->mur[0][1] = debut_y;
        obstacles->mur[0][2] = debut_z;

        obstacles->mur[1][0] = -taille_x;
        obstacles->mur[1][1] = debut_y;
        obstacles->mur[1][2] = debut_z;

        obstacles->mur[2][0] = -taille_x;
        obstacles->mur[2][1] = debut_y;
        obstacles->mur[2][2] = debut_z + tmp;

        obstacles->mur[3][0] = debut_x;
        obstacles->mur[3][1] = debut_y;
        obstacles->mur[3][2] = debut_z + tmp;
    }
    else
    {
        obstacles->sous_type = 1;
        printf("2-1\n");
        obstacles->debut_x = debut_x;
        obstacles->debut_y = debut_y;
        obstacles->debut_z = tmp;
        obstacles->taille_x = taille_x;
        obstacles->taille_y = taille_y;
        obstacles->taille_z = tmp;

        obstacles->mur[0][0] = debut_x;
        obstacles->mur[0][1] = debut_y;
        obstacles->mur[0][2] = tmp;

        obstacles->mur[1][0] = -taille_x;
        obstacles->mur[1][1] = debut_y;
        obstacles->mur[1][2] = tmp;

        obstacles->mur[2][0] = -taille_x;
        obstacles->mur[2][1] = debut_y;
        obstacles->mur[2][2] = taille_z;

        obstacles->mur[3][0] = debut_x;
        obstacles->mur[3][1] = debut_y;
        obstacles->mur[3][2] = taille_z;
    }

    obstacles->r = 100.;
    obstacles->g = 0.;
    obstacles->b = 100.;

    obstacles->suivant = NULL;
    return obstacles;
}

Obstacles *AlloueObstacles3(float debut_x, float debut_y, float debut_z, float taille_x, float taille_y, float taille_z)
{
    Obstacles *obstacles = (Obstacles *)malloc(sizeof(Obstacles));
    // Element *element = malloc(sizeof(*element));
    float tmp;
    if (obstacles == NULL)
    {
        printf("malloc(sizeof(LstMurs)) déconne.\n");
        return NULL;
    }
    obstacles->type_obs = 1;
    obstacles->num = courrant_num_obs++;

    tmp = ((float)rand() / (float)(RAND_MAX)) * (taille_z - DIST_RAYON_COTE_RAQUETTE * 2 + 2);
    printf("tmp=%f\n", tmp);
    if (rand() % 2 == 0)
    {
        obstacles->sous_type = 0;
        printf("2-0\n");
        obstacles->debut_x = debut_x;
        obstacles->debut_y = debut_y;
        obstacles->debut_z = debut_z;
        obstacles->taille_x = taille_x;
        obstacles->taille_y = taille_y;
        obstacles->taille_z = tmp;

        obstacles->mur[0][0] = debut_x;
        obstacles->mur[0][1] = debut_y;
        obstacles->mur[0][2] = debut_z;

        obstacles->mur[1][0] = -taille_x;
        obstacles->mur[1][1] = debut_y;
        obstacles->mur[1][2] = debut_z;

        obstacles->mur[2][0] = -taille_x;
        obstacles->mur[2][1] = debut_y;
        obstacles->mur[2][2] = debut_z + tmp;

        obstacles->mur[3][0] = debut_x;
        obstacles->mur[3][1] = debut_y;
        obstacles->mur[3][2] = debut_z + tmp;
    }
    else
    {
        obstacles->sous_type = 1;
        printf("2-1\n");
        obstacles->debut_x = debut_x;
        obstacles->debut_y = debut_y;
        obstacles->debut_z = tmp;
        obstacles->taille_x = taille_x;
        obstacles->taille_y = taille_y;
        obstacles->taille_z = tmp;

        obstacles->mur[0][0] = debut_x;
        obstacles->mur[0][1] = debut_y;
        obstacles->mur[0][2] = tmp;

        obstacles->mur[1][0] = -taille_x;
        obstacles->mur[1][1] = debut_y;
        obstacles->mur[1][2] = tmp;

        obstacles->mur[2][0] = -taille_x;
        obstacles->mur[2][1] = debut_y;
        obstacles->mur[2][2] = taille_z;

        obstacles->mur[3][0] = debut_x;
        obstacles->mur[3][1] = debut_y;
        obstacles->mur[3][2] = taille_z;
    }

    obstacles->r = 100.;
    obstacles->g = 0.;
    obstacles->b = 100.;

    obstacles->suivant = NULL;
    return obstacles;
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

int insererO(LstObstacles *lst, LstMurs murs)
{
    int niveau = murs->num / 3;
    float max_y = murs->debut_y + murs->taille_y;
    float pas = FREQUENCE_OBS - niveau * 5.;
    float tmp_y;
    if (*lst != NULL)
    {
        tmp_y = (*lst)->debut_y + pas;
    }
    else
    {
        tmp_y = pas;
    }
    while (tmp_y <= max_y)
    {
        printf("%f/%f  pas : %f\n", tmp_y, max_y, pas);
        /*
        int tmp_z, tmp_x;
        */
        int type_obs = (rand() % 2) + 1;
        Obstacles *cel = NULL;

        if (type_obs == 1)
        {
            cel = AlloueObstacles1(0, tmp_y, 0, murs->taille_x, 0, murs->taille_z);
        }
        else if (type_obs == 2)
        {
            cel = AlloueObstacles2(0, tmp_y, 0, murs->taille_x, 0, murs->taille_z);
        }

        if (cel == NULL)
        {
            printf("Erreur mémoire.\n");
            return -1;
        }
        if (*lst == NULL)
        {
            *lst = cel;
        }
        else
        {
            cel->suivant = *lst;
            *lst = cel;
        }

        tmp_y += pas;
    }

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
