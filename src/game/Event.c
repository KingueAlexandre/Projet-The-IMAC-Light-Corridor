#include "Event.h"

/* Window properties */
static const unsigned int WINDOW_WIDTH = 750;
static const unsigned int WINDOW_HEIGHT = 750;
static const char WINDOW_TITLE[] = "The Light Corridor";
static float aspectRatio = 1.0;

static float avance_cam_y = 2.; /*L'AVANCEMENT DE LA CAMÉRA SUR L'AXE Y*/

/* Minimal time wanted between two images */
static const double FRAMERATE_IN_SECONDS = 1. / 30.;

/* IHM flag */
static int flag_mode_cam = 1; /*MODE DE CAMÉRA*/

static int flag_animate_balle = 1; /*FLAG ANIMATION DE LA BALLE*/

static int flag_balle_collante = 1;         /*FLAG BALLE COLLÉ À LA RAQUETTE*/
static int flag_attente_balle_collante = 0; /*FLAG INDIQUANT QUE LA RAQUETTE EST COLLANTE*/

static int flag_menu = 1;       /*FLAG INDIQUANT SI LE JOUEUR A FAIT UN CHOIX DE NIVEAU (-1 = PAS ENCORE CHOISIS)*/
static int niveau_choisis = -1; /*FLAG INDIQUANT LE NIVEAU CHOISIS DEPUIS LE MENU*/
static int flag_result = -1;    /*FLAG INDIQUANT LE RÉSULTAT DE LA PARTIE (-1 = PAS ENCORE FINIS/CHOISIS)*/
static int flag_insert = 1;     /*FLAG INDIQUANT LA FIN DU NIVEAU (PLUS D'INSERTION DE MURS)*/

static LstMurs lst;            /*LISTES MURS*/
static LstObstacles obstacles; /*LISTES OBSTACLES*/
static Joueur joueur;          /*JOUEUR SYMBOLISÉ PAR UNE RAQUETTE EN FORME DE CADRE BLANC*/
static Balle balle;            /*BALLE*/
static Bonus bonus1;           /*1ER BONUS*/
static Bonus bonus2;           /*2EME BONUS*/
static Bonus bonus3;           /*3EME BONUS*/

/* Error handling function */
void onError(int error, const char *description)
{
    fprintf(stderr, "GLFW Error: %s\n", description);
}

void onWindowResized(GLFWwindow *window, int width, int height)
{
    aspectRatio = width / (float)height;

    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, aspectRatio, Z_NEAR, Z_FAR);
    glMatrixMode(GL_MODELVIEW);
}

void onKey(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    if (action == GLFW_PRESS)
    {
        switch (key)
        {
        case GLFW_KEY_A:
        case GLFW_KEY_ESCAPE:
            glfwSetWindowShouldClose(window, GLFW_TRUE); /*ON QUITTE LE JEU*/
            break;
        case GLFW_KEY_L:
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); /*MODE TANSPARENT*/
            break;
        case GLFW_KEY_P:
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); /*MODE NORMAL*/
            break;
        case GLFW_KEY_C: /*CHANGEMENT DE CAMÉRA*/
            flag_mode_cam = 1 - flag_mode_cam;
            break;
        case GLFW_KEY_B: /*PAUSE*/
            flag_animate_balle = 1 - flag_animate_balle;
            break;
        case GLFW_KEY_KP_9: /*APRÈS CE SONT LES PARAMÈTRES DE LA CAMÉRA*/
            if (dist_zoom < 100.0f)
                dist_zoom *= 1.1;
            printf("Zoom is %f\n", dist_zoom);
            break;
        case GLFW_KEY_KP_3:
            if (dist_zoom > 1.0f)
                dist_zoom *= 0.9;
            printf("Zoom is %f\n", dist_zoom);
            break;
        case GLFW_KEY_UP:
            if (phy > 2)
                phy -= 2;
            printf("Phy %f\n", phy);
            break;
        case GLFW_KEY_DOWN:
            if (phy <= 188.)
                phy += 2;
            printf("Phy %f\n", phy);
            break;
        case GLFW_KEY_LEFT:
            theta -= 5;
            break;
        case GLFW_KEY_RIGHT:
            theta += 5;
            break;
        default:
            fprintf(stdout, "Touche non gérée (%d)\n", key);
        }
    }
}

static void mouse_button_callback(GLFWwindow *window, int button, int action, int mods)
{

    if (flag_menu == 0 && button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS && flag_balle_collante == 0 && collision_joueur_murs(obstacles, joueur) == 0)
    {
        /*JEU*/
        /*LE JOUEUR CLIC POUR AVANCER EN FAISANT ATTENTION AU COLLISION*/
        avance_cam_y += 5;
        joueur.y += 5;
    }
    else if (flag_menu == 0 && button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS && -DIST_CAM_RAQ <= -20. + avance_cam_y && flag_balle_collante == 0)
    {
        /*JEU*/
        /*LE JOUEUR CLIC POUR RECULER*/
        avance_cam_y -= 5;
        joueur.y -= 5;
    }
    else if (flag_result != -1 && flag_menu && button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
    {
        /*RÉSULTAT DE LA PARTIE PRÉCÉDENTE*/
        /*LE JOUEUR CLIC POUR REVENIR AU MENU*/
        flag_result = -1;
    }
    else if (flag_menu && button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
    {
        /*MENU*/
        /*LE JOUEUR CLIC POUR CHOISIR UN OPTION*/
        double xpos, zpos;
        glfwGetCursorPos(window, &xpos, &zpos);
        niveau_choisis = (zpos / WINDOW_HEIGHT) * 4.;
        niveau_choisis = (niveau_choisis + 1) % 4;
        flag_menu = 0;
    }
    else if (flag_menu == 0 && button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS && flag_balle_collante)
    {
        /*JEU*/
        /*LE JOUEUR CLIC POUR RENVOYER LA BALLE APRÈS UNE BALLE COLLANTE*/
        flag_balle_collante = 0;
        balle.vec_y = 1.;
        balle.vec_x = 0.;
        balle.vec_z = 0.;
        balle.y += 1.1;
    }
}

void m_a_j_Bonus(Joueur joueur, Bonus *bonus1, Bonus *bonus2, Bonus *bonus3)
{
    /*SI LE JOUEUR DÉPASSE UN BONUS, IL EST ALORS GÉNÉRÉ AILLEURS DEVANT LUI*/
    if (joueur.y >= bonus1->y)
    {
        *bonus1 = generateBonus(rand() % 3, joueur.y, DIST_CAM_RAQ, TAILLE_X, TAILLE_Y, TAILLE_Z);
    }
    if (joueur.y >= bonus2->y)
    {
        *bonus2 = generateBonus(rand() % 3, joueur.y, DIST_CAM_RAQ, TAILLE_X, TAILLE_Y, TAILLE_Z);
    }
    if (joueur.y >= bonus3->y)
    {
        *bonus3 = generateBonus(rand() % 3, joueur.y, DIST_CAM_RAQ, TAILLE_X, TAILLE_Y, TAILLE_Z);
    }
}

void m_a_j_Cadre_Joueur(Joueur *joueur)
{
    /*Mis à jour Raquette du Joueur*/
    if (joueur->x + joueur->dist_cote >= 0)
    {
        joueur->min_cote_x = -2 * joueur->dist_cote;
        joueur->max_cote_x = 0;
    }
    else if (joueur->x - joueur->dist_cote <= -joueur->max_x)
    {
        joueur->min_cote_x = -joueur->max_x;
        joueur->max_cote_x = -joueur->max_x + joueur->dist_cote * 2;
    }
    else
    {
        joueur->min_cote_x = joueur->x - joueur->dist_cote;
        joueur->max_cote_x = joueur->x + joueur->dist_cote;
    }

    if (joueur->z + joueur->dist_cote >= joueur->max_z)
    {
        joueur->min_cote_z = joueur->max_z - 2 * joueur->dist_cote;
        joueur->max_cote_z = joueur->max_z;
    }
    else if (joueur->z - joueur->dist_cote <= 0.)
    {
        joueur->min_cote_z = 0;
        joueur->max_cote_z = joueur->dist_cote * 2;
    }
    else
    {
        joueur->min_cote_z = joueur->z - joueur->dist_cote;
        joueur->max_cote_z = joueur->z + joueur->dist_cote;
    }
}

int jeu(int niveau, GLFWwindow *window)
{

    double xpos, zpos;
    float debut_x = 0, debut_y = 0, debut_z = 0;
    float taille_x = TAILLE_X, taille_y = TAILLE_Y, taille_z = TAILLE_Z;
    int nb_section = 1;

    joueur = initJoueur(taille_x / 2, 0., taille_z / 2, TAILLE_X, TAILLE_Z, DIST_RAYON_COTE_RAQUETTE);

    /*ON INSÉRE LES 1ER MURS ET OBSTACLES DANS LE COORIDOR*/
    if (insererM(&lst, debut_x, debut_y, debut_z, taille_x, taille_y, taille_z, niveau) == -1)
    {
        printf("Erreur. insererM\n");
        exit(0);
    }
    balle = initBalle(-taille_x / 2., 0., taille_z / 2);
    if (insererO(&obstacles, lst, niveau) == -1)
    {
        printf("Erreur. insererO\n");
        exit(0);
    }

    bonus1 = generateBonus(rand() % 3, joueur.y, DIST_CAM_RAQ, TAILLE_X, TAILLE_Y, TAILLE_Z);
    bonus2 = generateBonus(rand() % 3, joueur.y, DIST_CAM_RAQ, TAILLE_X, TAILLE_Y, TAILLE_Z);
    bonus3 = generateBonus(rand() % 3, joueur.y, DIST_CAM_RAQ, TAILLE_X, TAILLE_Y, TAILLE_Z);

    while (!glfwWindowShouldClose(window) && joueur.vie > 0 && victoire(obstacles) == 0) /*ON CONTINUE TANT QUE LE JOUEUR À DES VIE ET QUON ATTEINT PAS LA FIN*/
    {
        /* Get time (in second) at loop beginning */
        double startTime = glfwGetTime();

        /* Cleaning buffers and setting Matrix Mode */
        glClearColor(0.0, 0.0, 0.0, 0.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        if (flag_mode_cam) /*LES DIFFÉRENTS MODES DE CAMÉRA*/
        {
            gluLookAt(-taille_x / 2., -15. + avance_cam_y, taille_z / 2.,
                      -taille_x / 2., 5. + dist_zoom + avance_cam_y, taille_z / 2.,
                      0.0, 0.0, 1.0);
        }
        else
        {
            setCamera();
        }

        /*AFFICHAGE DU CORRDIDOR*/

        glPushMatrix();

        drawMurs(lst, -15. + avance_cam_y);
        drawFrame();
        drawBalle(balle);
        drawObstacles(obstacles, joueur);
        drawJoueur(joueur);
        drawBonus(bonus1);
        drawBonus(bonus2);
        drawBonus(bonus3);

        glPopMatrix();

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();

        /* Elapsed time computation from loop begining */
        double elapsedTime = glfwGetTime() - startTime;
        /* If to few time is spend vs our wanted FPS, we wait */
        if (elapsedTime < FRAMERATE_IN_SECONDS)
        {
            glfwWaitEventsTimeout(FRAMERATE_IN_SECONDS - elapsedTime);
        }

        if (flag_animate_balle == 1 && flag_balle_collante == 0) /*ON GÈRE LES COLLISIONS SEULEMENT SI LA BALLE EST EN MOUVEMENT ET PAS COLLÉ À LA RAQUTTE*/
        {
            colision_balle_obs(&balle, obstacles, joueur);
            colision_balle_mur(&balle, taille_x, taille_z);
            if (colision_balle_joueur(&balle, joueur, flag_attente_balle_collante) == 2) /*LA BALLE EST COLLÉ À LA RAQUETTE*/
            {
                flag_attente_balle_collante = 0;
                flag_balle_collante = 1;
            }
            if (colision_bonus_balle(&bonus1, &bonus2, &bonus3, &balle, &joueur, nb_section)) /*LA RAQUTTE EST COLLANTE*/
            {
                flag_attente_balle_collante = 1;
            }
            /*ON FAIT BOUGÉ LES ÉLÉMENTS*/
            mouv_balle(&balle);
            bonus1.angle += 0.1;
            bonus2.angle += 0.1;
            bonus3.angle += 0.1;
        }
        else if (flag_animate_balle == 0) /*ON EST EN PAUSE DONC ON NE FAIT RIEN*/
        {
            continue;
        }
        if (flag_insert && nb_section < niveau * 5 && (avance_cam_y >= nb_section * taille_y - taille_y / 2 || balle.y >= nb_section * taille_y - 15))
        {
            /*ON RAJOUTE DES SECTIONS QUAND LE JOUEUR ET LA BALLE AVANCENET DANS LE CORRIDOR*/
            nb_section += 1;

            if (insererM(&lst, debut_x, debut_y + taille_y, debut_z, taille_x, taille_y, taille_z, niveau) == -1)
            {
                printf("Erreur. insererM\n");
                exit(0);
            }
            int insert = insererO(&obstacles, lst, niveau);
            if (insert == -1)
            {
                printf("Erreur. insererO\n");
                exit(0);
            }
            else if (insert == 2)
            {
                flag_insert = 0;
            }
            debut_y += taille_y;
        }
        /*MIS A JOUR DU JOUEUR ET SON CADRE*/
        glfwGetCursorPos(window, &xpos, &zpos);
        joueur.x = -(TAILLE_X - (xpos / WINDOW_WIDTH) * TAILLE_X);
        joueur.z = TAILLE_Z - (zpos / WINDOW_HEIGHT) * TAILLE_Z;
        if (flag_balle_collante)
        {
            balle.x = joueur.x;
            balle.y = joueur.y;
            balle.z = joueur.z;
        }
        m_a_j_Cadre_Joueur(&joueur);

        /*ON REGARDE SI LE BALLE A PASSÉ LA RAQUETTE ET SI OUI ON ENELÈVE UN VIE*/
        if (balle.y <= joueur.y && colision_balle_joueur(&balle, joueur, flag_attente_balle_collante) == 0 && flag_balle_collante == 0)
        {
            joueur.vie -= 1;
            flag_balle_collante = 1;
            printf("Vie perdu : ");
            if (joueur.vie > 0)
            {
                printf(" plus que %d et score actuel de %d\n", joueur.vie, joueur.score);
            }
            else
            {
                printf(" DOMMAGE GAME OVER!!\nScore final : %d\n", joueur.score);
            }
        }
        else if (balle.y > joueur.score)
        {
            joueur.score = balle.y;
        }
        /*ON MET À JOUR LES BONUS SI BESOIN*/
        m_a_j_Bonus(joueur, &bonus1, &bonus2, &bonus3);
    }
    /*lA PARTIE EST FINIS, ON REMET EN POSISTION LES FLAGS COMME AU DÉBUT*/
    avance_cam_y = 2.;
    flag_menu = 1;
    flag_mode_cam = 1;
    flag_animate_balle = 1;
    flag_balle_collante = 1;
    flag_attente_balle_collante = 0;
    niveau_choisis = -1;
    flag_insert = 1;

    freePile(&lst);
    freePileObs(&obstacles);
    lst = NULL;
    obstacles = NULL;
    return joueur.vie > 0;
}

int The_Light_Corridor()
{
    /* GLFW initialisation */
    GLFWwindow *window;

    float taille_x = TAILLE_X, taille_z = TAILLE_Z;

    if (!glfwInit())
        return -1;

    /* Callback to a function if an error is rised by GLFW */
    glfwSetErrorCallback(onError);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, NULL, NULL);
    if (!window)
    {
        // If no context created : exit !
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    glfwSetWindowSizeCallback(window, onWindowResized);
    glfwSetKeyCallback(window, onKey);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    onWindowResized(window, WINDOW_WIDTH, WINDOW_HEIGHT);

    glPointSize(5.0);
    glEnable(GL_DEPTH_TEST);

    /*ON CHARGE LES TEXTURE QUI VONT ÊTRE UTILISÉ DANS LE JEU*/
    loadtextures();

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Get time (in second) at loop beginning */
        double startTime = glfwGetTime();

        /* Cleaning buffers and setting Matrix Mode */
        glClearColor(0.0, 0.0, 0.0, 0.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        if (flag_mode_cam) /*LES DIFFÉRENTS MODE DE CAMÉRA*/
        {
            gluLookAt(-taille_x / 2., -15. + avance_cam_y, taille_z / 2.,
                      -taille_x / 2., 5. + dist_zoom + avance_cam_y, taille_z / 2.,
                      0.0, 0.0, 1.0);
        }
        else
        {
            setCamera();
        }

        if (flag_result == -1) /*LE MENU*/
        {
            drawMenu();
        }
        else if (flag_result == 1) /*LA VICTOIRE*/
        {
            draw_result(4);
        }
        else if (flag_result == 0) /*LA DÉFAITE*/
        {
            draw_result_score(0);
            draw_result(5);
        }

        if (niveau_choisis > 0) /*Un niveau a était choisis*/
        {
            flag_result = jeu(niveau_choisis, window);
        }
        else if (niveau_choisis == 0) /*On quitte le jeu*/
        {
            glfwSetWindowShouldClose(window, GLFW_TRUE);
        }

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();

        /* Elapsed time computation from loop begining */
        double elapsedTime = glfwGetTime() - startTime;
        /* If to few time is spend vs our wanted FPS, we wait */
        if (elapsedTime < FRAMERATE_IN_SECONDS)
        {
            glfwWaitEventsTimeout(FRAMERATE_IN_SECONDS - elapsedTime);
        }
    }
    /*ON FREE LES TEXTURE QUI ON ÉTÉ UTILISÉ DANS LE JEU ET ON FERME LE JEU*/

    freetextures();
    glfwTerminate();
    freePile(&lst);
    freePileObs(&obstacles);
    return 0;
}