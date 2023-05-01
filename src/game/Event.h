#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdio.h>
#include <stdlib.h>

#include "3D_tools.h"
#include "draw_scene.h"
#include "Mur.h"
#include "Joueur.h"

#ifndef __EVENT__
#define __EVENT__

void onError(int error, const char *description);

void onWindowResized(GLFWwindow *window, int width, int height);

void onKey(GLFWwindow *window, int key, int scancode, int action, int mods);

/*LANCE LA PARTIE JEU*/
int jeu(int niveau, GLFWwindow *window);

/*LE SQUELETTE DU JEU QUI FAIT APPEL À LA FONCTION DU JEU ET AFFICHE LE MENU*/
int The_Light_Corridor();

#endif