#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include "3D_tools.h"
#include "draw_scene.h"
#include "Event.h"

int main(int argc, char **argv)
{
	srand(time(NULL));
	The_Light_Corridor(); /*FONCTION JEU*/
	return 0;
}
