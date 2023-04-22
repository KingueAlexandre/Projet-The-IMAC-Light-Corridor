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

static float pas_base = 0.;
static float pas_balancier = 0.;

static int avance_cam_y = 0;
static float index_balancier = 1.;

/* Minimal time wanted between two images */
static const double FRAMERATE_IN_SECONDS = 1. / 30.;

/* IHM flag */
static int flag_animate_rot_scale = 0;
static int flag_animate_rot_arm = 0;
static int flag_mode_cam = 1;
static int flag_animate_balle = 0;

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

	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
	{
		avance_cam_y += 5;
	}
	else if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
	{
		avance_cam_y -= 5;
	}
}

int main(int argc, char **argv)
{
	/* GLFW initialisation */
	GLFWwindow *window;
	LstMurs lst;
	Balle balle;
	float debut_x = 0;
	float debut_y = 0;
	float debut_z = 0;
	float taille_x = 15;
	float taille_y = 100;
	float taille_z = 15;
	int nb_section = 1;

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
	/*
	printf("Fenetre créé.\nInit Murs:\n");
	*/
	if (insererM(&lst, debut_x, debut_y, debut_z, taille_x, taille_y, taille_z) == -1)
	{
		exit(0);
	}
	printf("Init Balle\n");

	balle = initBalle(-taille_x / 2., taille_y / 3., taille_z / 2);

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	glfwSetWindowSizeCallback(window, onWindowResized);
	glfwSetKeyCallback(window, onKey);
	glfwSetMouseButtonCallback(window, mouse_button_callback);

	onWindowResized(window, WINDOW_WIDTH, WINDOW_HEIGHT);

	glPointSize(5.0);
	glEnable(GL_DEPTH_TEST);
	/*
	printf("Animation commnce\n");
*/
	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
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
			gluLookAt(-taille_x / 2., -25. + avance_cam_y, taille_z / 2.,
					  -taille_x / 2., 5. + dist_zoom + avance_cam_y, taille_z / 2.,
					  0.0, 0.0, 1.0);
		}
		else
		{
			setCamera();
		}

		/*
	printf("Etape animation:\n");*/
		glPushMatrix();
		/*
		printf("Murs\n");
	*/
		drawMurs(lst);
		drawFrame();
		/*
		printf("Balle\n");
	*/
		drawBalle(balle);

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

		/* Animate scenery */
		if (flag_animate_rot_scale == 1)
		{
			pas_base += .1;
		}
		if (flag_animate_rot_arm == 1)
		{
			if (pas_balancier >= 10.)
			{
				index_balancier = -1.;
			}
			else if (pas_balancier <= -10.)
			{
				index_balancier = 1.;
			}
			pas_balancier += index_balancier;
		}
		if (flag_animate_balle == 1)
		{
			colision_balle_mur(&balle, taille_x, taille_z);
			mouv_balle(&balle);
		}
		if (avance_cam_y >= nb_section * taille_y - taille_y / 2)
		{
			printf("Affichage maj.\n");
			nb_section += 1;
			printf("debut_x, debut_y , debut_z, taille_x, taille_y, taille_z : %f, %f, %f, %f, %f, %f", debut_x, debut_y + taille_y, debut_z, taille_x, taille_y, taille_z);
			if (insererM(&lst, debut_x, debut_y + taille_y, debut_z, taille_x, taille_y, taille_z) == -1)
			{
				printf("Erreur.\n");
				exit(0);
			}
			debut_y += taille_y;
		}
		/*
		printf("Collion maj:\n");
		*/
	}

	glfwTerminate();
	return 0;
}
