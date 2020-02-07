//All of the OpenGL code is sitting in here


#include "stdafx.h"
#include "pic.h"
#include <windows.h>
#include <stdlib.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <iostream>
#include <cmath>

#include "opencv2/core/core.hpp"
#include "opencv2/core/utility.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/imgcodecs/imgcodecs.hpp"

#define PI 3.14159265
#define WIDTH 100
#define HEIGHT 100

int g_iMenuId;

int g_vMousePos[2] = { 0, 0 };
int g_iLeftMouseButton = 0;    /* 1 if pressed, 0 if not */
int g_iMiddleMouseButton = 0;
int g_iRightMouseButton = 0;

typedef enum { ROTATE, TRANSLATE, SCALE } CONTROLSTATE;

CONTROLSTATE g_ControlState = ROTATE;

/* state of the world */
float g_vLandRotate[3] = { 0.0, 0.0, 0.0 };
float g_vLandTranslate[3] = { 0.0, 0.0, 0.0 };
float g_vLandScale = 1.0;

void myinit()
{
	glMatrixMode(GL_PROJECTION);
	glOrtho(-WIDTH / 2, WIDTH / 2, -HEIGHT / 2, HEIGHT / 2, 0, 200);
	glMatrixMode(GL_MODELVIEW);
	glClearColor(0.0, 0.0, 0.0, 0.0);
}

GLint axis = 2;
float theta[3] = { 0.0, 0.0, 0.0 };
float heightcoefficient = 0.25;
GLenum modes[3] = { GL_POINT, GL_LINE, GL_FILL };
int rastaMode = 1;

void setupCamera() {
	gluLookAt(0, 0, 100, 0, 0, 0, 1, 0, 0);
}
void displaybodies()
{
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	setupCamera();
	//draw here

	glColor3f(1, 1, 1);//rgb color
	glTranslatef(0, 0, 0);//xyz coordinates
	gluSphere(gluNewQuadric(), 5, 100, 20);//radius here is 5

	glColor3f(0, 0, 1);
	glTranslatef(0, 30, 0);
	gluSphere(gluNewQuadric(), 2, 100, 20);

	glPolygonMode(GL_FRONT_AND_BACK, modes[rastaMode]);
	glutSwapBuffers();
}

void menufunc(int value)
{
	switch (value)
	{
	case 0:
		exit(0);
		break;
	}
}

void doIdle()
{
	
	glutPostRedisplay();
}

void mousedrag(int x, int y)
{
	int vMouseDelta[2] = { x - g_vMousePos[0], y - g_vMousePos[1] };

	switch (g_ControlState)
	{
	case TRANSLATE:
		if (g_iLeftMouseButton)
		{
			g_vLandTranslate[1] += vMouseDelta[0] * 0.1;
			g_vLandTranslate[0] -= vMouseDelta[1] * 0.1;
		}
		if (g_iMiddleMouseButton)
		{
			g_vLandTranslate[2] -= vMouseDelta[1] * 0.1;
		}
		break;
	case ROTATE:
		if (g_iLeftMouseButton)
		{
			g_vLandRotate[0] += vMouseDelta[1];
			g_vLandRotate[2] += vMouseDelta[0];
		}
		if (g_iMiddleMouseButton)
		{
			g_vLandRotate[1] += vMouseDelta[1];
		}
		break;
	case SCALE:
		if (g_iLeftMouseButton)
		{
			g_vLandScale *= 1.0 + vMouseDelta[0] * 0.01;
			g_vLandScale *= 1.0 - vMouseDelta[1] * 0.01;
		}
		if (g_iMiddleMouseButton)
		{
			g_vLandScale *= 1.0 - vMouseDelta[1] * 0.01;
		}
		break;
	}
	g_vMousePos[0] = x;
	g_vMousePos[1] = y;
}

void mouseidle(int x, int y)
{
	g_vMousePos[0] = x;
	g_vMousePos[1] = y;
}

void myReshape(int w, int h) {
	GLfloat aspect = (GLfloat)w / (GLfloat)h;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, 1.0*h / w, 0.01, 2000.0);

	glMatrixMode(GL_MODELVIEW);
}

void mousebutton(int button, int state, int x, int y)
{

	switch (button)
	{
	case GLUT_LEFT_BUTTON:
		g_iLeftMouseButton = (state == GLUT_DOWN);
		break;
	case GLUT_MIDDLE_BUTTON:
		g_iMiddleMouseButton = (state == GLUT_DOWN);
		break;
	case GLUT_RIGHT_BUTTON:
		g_iRightMouseButton = (state == GLUT_DOWN);
		break;
	}

	switch (glutGetModifiers())
	{
	case GLUT_ACTIVE_CTRL:
		g_ControlState = TRANSLATE;
		break;
	case GLUT_ACTIVE_SHIFT:
		g_ControlState = SCALE;
		break;
	default:
		g_ControlState = ROTATE;
		break;
	}

	g_vMousePos[0] = x;
	g_vMousePos[1] = y;
}

void keystroke(unsigned char key, int x, int y) {
	switch (key)
	{
	case '1':
		rastaMode = 0;
		break;
	case '2':
		rastaMode = 1;
		break;
	case '3':
		rastaMode = 2;
		break;
	}
}
int main(int argc, char* argv[])
{
	//opening that window
	glutInit(&argc, (char**)argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGBA);
	glEnable(GL_DEPTH_TEST);
	glutInitWindowSize(1000, 1000);
	glutInitWindowPosition(500, 250);
	glutCreateWindow("Jeffrey's N-body Simulator");

	/* tells glut to use a particular display function to redraw */
	glutDisplayFunc(displaybodies);//displaybodies for the bodies
	/* allow the user to quit using the right mouse button menu */
	g_iMenuId = glutCreateMenu(menufunc);
	glutSetMenu(g_iMenuId);
	glutAddMenuEntry("Quit", 0);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutReshapeFunc(myReshape);
	/* replace with any animate code */
	glutIdleFunc(doIdle);

	/* callback for mouse drags */
	glutMotionFunc(mousedrag);
	/* callback for idle mouse movement */
	glutPassiveMotionFunc(mouseidle);
	/* callback for mouse button changes */
	glutMouseFunc(mousebutton);
	glutKeyboardFunc(keystroke);
	/* do initialization */
	myinit();

	glutMainLoop();
	return 0;
}