#include "Mur.h"

#define FREQUENCE_OBS 30.

static int courrant_num_mur = 0;
static int courrant_num_obs = 0;

Murs *AlloueMurs(float debut_x, float debut_y, float debut_z, float taille_x, float taille_y, float taille_z, int niveau)
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

    if (niveau == 1)
    {
        murs->r = 50.;
        murs->g = 82.5;
        murs->b = 1.;
    }
    else if (niveau == 2)
    {
        murs->r = 1.;
        murs->g = 40.;
        murs->b = 1.;
    }
    else if (niveau == 3)
    {
        murs->r = 100.;
        murs->g = 1.;
        murs->b = 1.;
    }

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

    tmp = DIST_RAYON_COTE_RAQUETTE * 2 + 1 + ((float)rand() / (float)(RAND_MAX)) * (taille_x - DIST_RAYON_COTE_RAQUETTE * 4 - 1);

    printf("V tmp=%f\n", tmp);

    if (rand() % 2 == 0)
    {
        obstacles->sous_type = 0;
        /*
        printf("1-0\n");
        */
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
        /*
        printf("1-1\n");
        */
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

    obstacles->vie = 0;

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

    tmp = DIST_RAYON_COTE_RAQUETTE * 2 + 1 + ((float)rand() / (float)(RAND_MAX)) * (taille_z - DIST_RAYON_COTE_RAQUETTE * 4 - 1);

    printf("H tmp=%f\n", tmp);

    if (rand() % 2 == 0)
    {
        obstacles->sous_type = 0;
        /*
        printf("2-0\n");
        */
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
        /*
        printf("2-1\n");
        */
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

    obstacles->vie = 0;

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
    float tmp_x, tmp_z;
    if (obstacles == NULL)
    {
        printf("malloc(sizeof(LstMurs)) déconne.\n");
        return NULL;
    }
    obstacles->type_obs = 3;
    obstacles->num = courrant_num_obs++;
    tmp_x = DIST_RAYON_COTE_RAQUETTE * 2 + 1 + ((float)rand() / (float)(RAND_MAX)) * (taille_x - DIST_RAYON_COTE_RAQUETTE * 4 - 1);
    tmp_z = DIST_RAYON_COTE_RAQUETTE * 2 + ((float)rand() / (float)(RAND_MAX)) * (taille_z - DIST_RAYON_COTE_RAQUETTE * 4 + 2);
    /*
    printf("tmp=%f\n", tmp);
    */
    if (rand() % 2 == 0)
    {
        obstacles->sous_type = 0;
        if (rand() % 2 == 0)
        {
            obstacles->debut_x = -tmp_x;
            obstacles->debut_y = debut_y;
            obstacles->debut_z = debut_z;
            obstacles->taille_x = tmp_x;
            obstacles->taille_y = taille_y;
            obstacles->taille_z = tmp_z;

            obstacles->mur[0][0] = -tmp_x;
            obstacles->mur[0][1] = debut_y;
            obstacles->mur[0][2] = debut_z;

            obstacles->mur[1][0] = -taille_x;
            obstacles->mur[1][1] = debut_y;
            obstacles->mur[1][2] = debut_z;

            obstacles->mur[2][0] = -taille_x;
            obstacles->mur[2][1] = debut_y;
            obstacles->mur[2][2] = debut_z + tmp_z;

            obstacles->mur[3][0] = -tmp_x;
            obstacles->mur[3][1] = debut_y;
            obstacles->mur[3][2] = debut_z + tmp_z;
        }
        else
        {
            obstacles->debut_x = debut_x;
            obstacles->debut_y = debut_y;
            obstacles->debut_z = debut_z;
            obstacles->taille_x = tmp_x;
            obstacles->taille_y = taille_y;
            obstacles->taille_z = tmp_z;

            obstacles->mur[0][0] = debut_x;
            obstacles->mur[0][1] = debut_y;
            obstacles->mur[0][2] = debut_z;

            obstacles->mur[1][0] = debut_x - tmp_x;
            obstacles->mur[1][1] = debut_y;
            obstacles->mur[1][2] = debut_z;

            obstacles->mur[2][0] = debut_x - tmp_x;
            obstacles->mur[2][1] = debut_y;
            obstacles->mur[2][2] = debut_z + tmp_z;

            obstacles->mur[3][0] = debut_x;
            obstacles->mur[3][1] = debut_y;
            obstacles->mur[3][2] = debut_z + tmp_z;
        }
    }
    else
    {
        obstacles->sous_type = 1;
        /*
        printf("2-1\n");
        */
        if (rand() % 2 == 0)
        {
            obstacles->debut_x = -tmp_x;
            obstacles->debut_y = debut_y;
            obstacles->debut_z = tmp_z;
            obstacles->taille_x = tmp_x;
            obstacles->taille_y = taille_y;
            obstacles->taille_z = tmp_z;

            obstacles->mur[0][0] = -tmp_x;
            obstacles->mur[0][1] = debut_y;
            obstacles->mur[0][2] = tmp_z;

            obstacles->mur[1][0] = -taille_x;
            obstacles->mur[1][1] = debut_y;
            obstacles->mur[1][2] = tmp_z;

            obstacles->mur[2][0] = -taille_x;
            obstacles->mur[2][1] = debut_y;
            obstacles->mur[2][2] = taille_z;

            obstacles->mur[3][0] = -tmp_x;
            obstacles->mur[3][1] = debut_y;
            obstacles->mur[3][2] = taille_z;
        }
        else
        {
            obstacles->debut_x = debut_x;
            obstacles->debut_y = debut_y;
            obstacles->debut_z = tmp_z;
            obstacles->taille_x = tmp_x;
            obstacles->taille_y = taille_y;
            obstacles->taille_z = tmp_z;

            obstacles->mur[0][0] = debut_x;
            obstacles->mur[0][1] = debut_y;
            obstacles->mur[0][2] = tmp_z;

            obstacles->mur[1][0] = debut_x - tmp_x;
            obstacles->mur[1][1] = debut_y;
            obstacles->mur[1][2] = tmp_z;

            obstacles->mur[2][0] = debut_x - tmp_x;
            obstacles->mur[2][1] = debut_y;
            obstacles->mur[2][2] = taille_z;

            obstacles->mur[3][0] = debut_x;
            obstacles->mur[3][1] = debut_y;
            obstacles->mur[3][2] = taille_z;
        }
    }

    obstacles->vie = 0;

    obstacles->r = 100.;
    obstacles->g = 1.;
    obstacles->b = 200.;

    obstacles->suivant = NULL;
    return obstacles;
}

Obstacles *AlloueObstaclesF(float debut_x, float debut_y, float debut_z, float taille_x, float taille_y, float taille_z)
{
    Obstacles *obstacles = (Obstacles *)malloc(sizeof(Obstacles));
    if (obstacles == NULL)
    {
        printf("malloc(sizeof(LstMurs)) déconne.\n");
        return NULL;
    }
    obstacles->type_obs = 4;
    obstacles->num = courrant_num_obs++;
    obstacles->debut_x = 0;
    obstacles->debut_y = debut_y;
    obstacles->debut_z = 0;
    obstacles->taille_x = TAILLE_X;
    obstacles->taille_y = TAILLE_Z;
    obstacles->taille_z = 0;

    obstacles->mur[0][0] = 0;
    obstacles->mur[0][1] = debut_y;
    obstacles->mur[0][2] = 0;

    obstacles->mur[1][0] = -TAILLE_X;
    obstacles->mur[1][1] = debut_y;
    obstacles->mur[1][2] = 0;

    obstacles->mur[2][0] = -TAILLE_X;
    obstacles->mur[2][1] = debut_y;
    obstacles->mur[2][2] = TAILLE_Z;

    obstacles->mur[3][0] = 0;
    obstacles->mur[3][1] = debut_y;
    obstacles->mur[3][2] = TAILLE_Z;

    obstacles->vie = 10;

    obstacles->r = 100.;
    obstacles->g = 100.;
    obstacles->b = 100.;

    obstacles->suivant = NULL;
    return obstacles;
}

int insererM(LstMurs *lst, float debut_x, float debut_y, float debut_z, float taille_x, float taille_y, float taille_z, int niveau)
{
    Murs *cel;
    cel = AlloueMurs(debut_x, debut_y, debut_z, taille_x, taille_y, taille_z, niveau);
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

int insererO(LstObstacles *lst, LstMurs murs, int niveau)
{
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

        int type_obs = (rand() % 3) + 1;

        Obstacles *cel = NULL;
        if (tmp_y + 30 >= niveau * 5 * murs->taille_y)
        {
            printf("PAs normal\n");
            cel = AlloueObstaclesF(0, niveau * 5 * murs->taille_y, 0, murs->taille_x, 0, murs->taille_z);
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
            return 0;
        }
        if (type_obs == 3)
        {
            type_obs = (rand() % 3) + 1;
        }

        if (type_obs == 1)
        {
            cel = AlloueObstacles1(0, tmp_y, 0, murs->taille_x, 0, murs->taille_z);
        }
        else if (type_obs == 2)
        {
            cel = AlloueObstacles2(0, tmp_y, 0, murs->taille_x, 0, murs->taille_z);
        }
        else if (type_obs == 3)
        {
            cel = AlloueObstacles3(0, tmp_y, 0, murs->taille_x, 0, murs->taille_z);
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

void freePileObs(LstObstacles *obs)
{
    Obstacles *iter = *obs;
    Obstacles *temp = iter;
    while (iter != NULL)
    {
        temp = iter->suivant;
        free(iter);
        iter = temp;
    }
    *obs = NULL;
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

int victoire(LstObstacles obs)
{
    Obstacles *ret = obs;
    while (ret != NULL)
    {
        if (ret->type_obs == 4 && ret->vie <= 0)
        {
            return 1;
        }
        ret = ret->suivant;
    }
    return 0;
}
