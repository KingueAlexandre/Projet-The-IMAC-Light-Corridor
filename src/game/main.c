#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "3D_tools.h"
#include "draw_scene.h"

/* Window properties */
static const unsigned int WINDOW_WIDTH = 750;
static const unsigned int WINDOW_HEIGHT = 750;
static const char WINDOW_TITLE[] = "Main";
static float aspectRatio = 1.0;

/*
static float pas_base = 0.;
static float pas_balancier = 0.;
*/
static float avance_cam_y = 2.;
/*
static float index_balancier = 1.;
*/
/* Minimal time wanted between two images */
static const double FRAMERATE_IN_SECONDS = 1. / 30.;

/* IHM flag */
static int flag_animate_rot_scale = 0;
static int flag_animate_rot_arm = 0;
static int flag_mode_cam = 1;
static int flag_animate_balle = 1;
static int flag_balle_collante = 1;
static int flag_attente_balle_collante = 0;

static LstMurs lst;
static LstObstacles obstacles;
static Joueur joueur;
static Balle balle;
static Bonus bonus1;
static Bonus bonus2;

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
			glfwSetWindowShouldClose(window, GLFW_TRUE);
			break;
		case GLFW_KEY_L:
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			break;
		case GLFW_KEY_P:
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			break;
		case GLFW_KEY_R:
			flag_animate_rot_arm = 1 - flag_animate_rot_arm;
			break;
		case GLFW_KEY_T:
			flag_animate_rot_scale = 1 - flag_animate_rot_scale;
			break;
		case GLFW_KEY_C:
			flag_mode_cam = 1 - flag_mode_cam;
			break;
		case GLFW_KEY_B:
			flag_animate_balle = 1 - flag_animate_balle;
			break;
		case GLFW_KEY_KP_9:
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
			if (phy <= 88.)
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
	// printf("mouse\n");

	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS && flag_balle_collante == 0 && collision_joueur_murs(obstacles, joueur) == 0)
	{
		avance_cam_y += 5;
		joueur.y += 5;
		/*
		printf("avance_cam_y : %f\n", avance_cam_y);
		*/
	}
	else if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS && -DIST_CAM_RAQ <= -20. + avance_cam_y && flag_balle_collante == 0)
	{
		avance_cam_y -= 5;
		joueur.y -= 5;
		/*
		printf("avance_cam_y : %f\n", avance_cam_y);
		*/
	}
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS && flag_balle_collante)
	{
		flag_balle_collante = 0;
		balle.vec_y = 1.;
		balle.vec_x = 0.;
		balle.vec_z = 0.;
		balle.y += 1.1;
	}
}

void draw()
{
	/* Switch to 2D Mode */
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0, 8, 0, 6);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glEnable(GL_BLEND);
	glDisable(GL_LIGHTING);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	/* Draw the gray transparent zone over the game */
	glColor4f(0.8, 0.8, 0.8, 0.5);
	glBegin(GL_QUADS);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 6, 0);
	glVertex3f(8, 6, 0);
	glVertex3f(8, 0, 0);
	glEnd();

	/* Switch back to 3D Mode */
	glEnable(GL_LIGHTING);
	glDisable(GL_BLEND);
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char **argv)
{
	/* GLFW initialisation */
	GLFWwindow *window;

	double xpos, zpos;
	float debut_x = 0, debut_y = 0, debut_z = 0;
	float taille_x = TAILLE_X, taille_y = TAILLE_Y, taille_z = TAILLE_Z;
	int nb_section = 1;

	joueur = initJoueur(taille_x / 2, 0., taille_z / 2, TAILLE_X, TAILLE_Z, DIST_RAYON_COTE_RAQUETTE);

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

	if (insererM(&lst, debut_x, debut_y, debut_z, taille_x, taille_y, taille_z) == -1)
	{
		printf("Erreur. insererM\n");
		exit(0);
	}
	balle = initBalle(-taille_x / 2., taille_y / 3., taille_z / 2);
	if (insererO(&obstacles, lst) == -1)
	{
		printf("Erreur. insererO\n");
		exit(0);
	}

	bonus1 = generateBonus(rand() % 2, joueur.y, DIST_CAM_RAQ, TAILLE_X, TAILLE_Y, TAILLE_Z);
	bonus2 = generateBonus(rand() % 2, joueur.y, DIST_CAM_RAQ, TAILLE_X, TAILLE_Y, TAILLE_Z);
	printf("(%f,%f,%f) size = %f\n", bonus1.x, bonus1.y, bonus1.z, bonus1.indic_taille * 2);
	printf("(%f,%f,%f) size = %f\n", bonus2.x, bonus2.y, bonus2.z, bonus2.indic_taille * 2);

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	glfwSetWindowSizeCallback(window, onWindowResized);
	glfwSetKeyCallback(window, onKey);
	glfwSetMouseButtonCallback(window, mouse_button_callback);

	onWindowResized(window, WINDOW_WIDTH, WINDOW_HEIGHT);

	glPointSize(5.0);
	glEnable(GL_DEPTH_TEST);

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window) && joueur.vie > 0)
	{
		/* Get time (in second) at loop beginning */
		double startTime = glfwGetTime();

		/* Cleaning buffers and setting Matrix Mode */
		glClearColor(0.2, 0.0, 0.0, 0.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		if (flag_mode_cam)
		{
			gluLookAt(-taille_x / 2., -15. + avance_cam_y, taille_z / 2.,
					  -taille_x / 2., 5. + dist_zoom + avance_cam_y, taille_z / 2.,
					  0.0, 0.0, 1.0);
		}
		else
		{
			setCamera();
		}

		glPushMatrix();

		drawMurs(lst, -15. + avance_cam_y);
		drawFrame();
		drawBalle(balle);
		drawObstacles(obstacles, joueur);
		drawJoueur(joueur);
		drawBonus(bonus1);
		drawBonus(bonus2);

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

		if (flag_animate_balle == 1 && flag_balle_collante == 0)
		{
			colision_balle_obs(&balle, obstacles, joueur);
			colision_balle_mur(&balle, taille_x, taille_z);
			if (colision_balle_joueur(&balle, joueur, flag_attente_balle_collante) == 2)
			{
				flag_attente_balle_collante = 0;
				flag_balle_collante = 1;
			}
			if (colision_bonus_balle(&bonus1, &bonus2, balle, &joueur, nb_section))
			{
				flag_attente_balle_collante = 1;
			}

			mouv_balle(&balle);
			bonus1.angle += 0.1;
			bonus2.angle += 0.1;
		}
		else if (flag_animate_balle == 0)
		{
			continue;
		}
		if (avance_cam_y >= nb_section * taille_y - taille_y / 2 || balle.y >= nb_section * taille_y - 15)
		{
			/*Ajout Remparts/Murs*/
			/*
			printf("Ajout Remparts/Murs\n");
			*/
			nb_section += 1;

			if (insererM(&lst, debut_x, debut_y + taille_y, debut_z, taille_x, taille_y, taille_z) == -1)
			{
				printf("Erreur. insererM\n");
				exit(0);
			}
			if (insererO(&obstacles, lst) == -1)
			{
				printf("Erreur. insererO\n");
				exit(0);
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
		/*Mis à jour Raquette du Joueur*/
		if (joueur.x + joueur.dist_cote >= 0)
		{
			joueur.min_cote_x = -2 * joueur.dist_cote;
			joueur.max_cote_x = 0;
		}
		else if (joueur.x - joueur.dist_cote <= -joueur.max_x)
		{
			joueur.min_cote_x = -joueur.max_x;
			joueur.max_cote_x = -joueur.max_x + joueur.dist_cote * 2;
		}
		else
		{
			joueur.min_cote_x = joueur.x - joueur.dist_cote;
			joueur.max_cote_x = joueur.x + joueur.dist_cote;
		}

		if (joueur.z + joueur.dist_cote >= joueur.max_z)
		{
			joueur.min_cote_z = joueur.max_z - 2 * joueur.dist_cote;
			joueur.max_cote_z = joueur.max_z;
		}
		else if (joueur.z - joueur.dist_cote <= 0.)
		{
			joueur.min_cote_z = 0;
			joueur.max_cote_z = joueur.dist_cote * 2;
		}
		else
		{
			joueur.min_cote_z = joueur.z - joueur.dist_cote;
			joueur.max_cote_z = joueur.z + joueur.dist_cote;
		}
		/*
		glRasterPos2f(15, 15);
		*/

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
		if (joueur.y >= bonus1.y)
		{
			bonus1 = generateBonus(rand() % 2, joueur.y, DIST_CAM_RAQ, TAILLE_X, TAILLE_Y, TAILLE_Z);
		}
		if (joueur.y >= bonus2.y)
		{
			bonus2 = generateBonus(rand() % 2, joueur.y, DIST_CAM_RAQ, TAILLE_X, TAILLE_Y, TAILLE_Z);
		}
	}

	glfwTerminate();
	freePile(&lst);
	freePileObs(&obstacles);
	return 0;
}
