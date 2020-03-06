//All of the OpenGL code is sitting in here


#include "stdafx.h"
#include "pic.h"
#include <windows.h>
#include <stdlib.h>
#include <GL/glu.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <iostream>
#include <cmath>
#include <fstream>
#include "sim.h"

#include "opencv2/core/core.hpp"
#include "opencv2/core/utility.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/imgcodecs/imgcodecs.hpp"

//#include "sim.h"//my very own simulator uwu

#define PI 3.14159265
#define WIDTH 100
#define HEIGHT 100

// start using this instead of your homemade vectors: cv::Vec3f testvector;
cv::Mat3b text;
cv::Mat3b background;

unsigned int textTex;
unsigned int backTex;

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

int readImage(char *filename, cv::Mat3b &image, bool displayOn);

void myinit()
{
	glMatrixMode(GL_PROJECTION);
	glOrtho(-WIDTH / 2, WIDTH / 2, -HEIGHT / 2, HEIGHT / 2, 0, 200);
	glMatrixMode(GL_MODELVIEW);
	glClearColor(0.0, 0.0, 0.0, 0.0);
}
sim mysim;
GLint axis = 2;
float theta[3] = { 0.0, 0.0, 0.0 };
float heightcoefficient = 0.25;
GLenum modes[3] = { GL_POINT, GL_LINE, GL_FILL };
int rastaMode = 1;

void setupCamera() {
	gluLookAt(0, 0, 100, 0, 0, 0, 1, 0, 0);
}
double angle = 0.0;
float radius = 30.0;
int steps = 0;
int maxsteps = 10000;

void displaybodies()
{
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	setupCamera();
	//draw here
	//draw background
	/*glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, backTex);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0); 
	glVertex3f(-256.0, -256.0, -50);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(-256.0,  256.0, -50);
	glTexCoord2f(1.0, 1.0);
	glVertex3f( 256.0,  256.0, -50);
	glTexCoord2f(1.0, 0.0);
	glVertex3f( 256.0, -256.0, -50);
	glEnd();
	glDisable(GL_TEXTURE_2D);*/
	glColor3f(0.5, 1.0, 0.5);
	glBegin(GL_QUADS);
	glVertex3f(-256.0, -256.0, -50);
	glVertex3f(-256.0,  256.0, -50);
	glVertex3f( 256.0,  256.0, -50);
	glVertex3f( 256.0, -256.0, -50);
	glEnd();





	//glColor3f(1, 1, 1);//rgb color
	//glTranslatef(0, 0, 0);//xyz coordinates
	//gluSphere(gluNewQuadric(), 5, 100, 20);//radius here is 5
	//glColor3f(0, 0, 1);
	//glTranslatef(radius*cos(angle), radius*sin(angle), 0);
	//angle += 0.001;
	//gluSphere(gluNewQuadric(), 2, 100, 20);

	angle += 0.001;
	std::vector<std::pair<float, float>> testpos;
	testpos.push_back(std::pair<float, float>(0.0, 0.0));
	testpos.push_back(std::pair<float, float>(radius*cos(angle), radius*sin(angle)));

	/*for (int i = 0; i < testpos.size(); i++) {
		glTranslatef(testpos[i].first, testpos[i].second, 0);
		if (i == 0) {
			glColor3f(1, 01, 1);
		}
		else {
			glColor3f(0, 0, 1);
		}
		gluSphere(gluNewQuadric(), 5, 100, 20);
	}*/

	if (steps++/* < maxsteps*/) {
		mysim.advance(0.001);
	}
	std::vector<std::pair<float, float>> positions = mysim.positions();
	std::vector<int> bodysizes = { 4, 2, 2, 2, 1, 1, 1 };
	for (unsigned int i = 0; i < positions.size(); i++) {
		//std::cout << "i = " << i << std::endl;
		glColor3f(1, 0, 1);
		//std::cout << "coordinates " << positions[i].second << " " << -positions[i].first << std::endl;
		glTranslatef(positions[i].second, -positions[i].first, 0);
		gluSphere(gluNewQuadric(), bodysizes[i], 100, 20);
	}

	//glPolygonMode(GL_FRONT_AND_BACK, modes[rastaMode]);
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

	//read in the images
	readImage("HololensFont.bmp", text, false);//displayOn = true
	glGenTextures(1, &textTex);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textTex);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 256, 256, 0, GL_RGBA, GL_UNSIGNED_BYTE, text.data);
	readImage("nier background.png", background, false);
	glGenTextures(1, &backTex);
	glBindTexture(GL_TEXTURE_2D, backTex);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 1024, 1024, 0, GL_RGBA, GL_UNSIGNED_BYTE, background.data);
	glDisable(GL_TEXTURE_2D);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGBA);
	glEnable(GL_DEPTH_TEST);
	glutInitWindowSize(512, 512);
	glutInitWindowPosition(128, 128);
	glutCreateWindow("Jeffrey's N-body Simulator");

	/* tells glut to use a particular display function to redraw */
	glutDisplayFunc(displaybodies);
	/* allow the user to quit using the right mouse button menu */
	g_iMenuId = glutCreateMenu(menufunc);
	glutSetMenu(g_iMenuId);
	glutAddMenuEntry("Quit", 0);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutReshapeFunc(myReshape);
	/* replace with any animate code */
	glutIdleFunc(doIdle);

	glutMotionFunc(mousedrag);
	glutPassiveMotionFunc(mouseidle);
	glutMouseFunc(mousebutton);
	glutKeyboardFunc(keystroke);



	myinit();
	glutMainLoop();
	return 0;
}


int readImage(char *filename, cv::Mat3b &image, bool displayOn) {
	std::cout << "reading image : " << filename << std::endl;
	image = cv::imread(filename);
	if (!image.data) {
		std::cout << "Could not open or find the image." << std::endl;
		return 1;
	}
	if (displayOn) {
		cv::imshow("TestWindow", image);
		cv::waitKey(0); //press any key to exit
	}
}