#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#include <unistd.h>
#include <GL/glut.h>
#include <bits/stdc++.h>
using namespace std;

#define DBG(x) cout<<"Line "<<__LINE__<<": "<<#x" = "<<x<<endl;
#define NL cout<<endl;
#define pi (2*acos(0.0))

#include "point.h"

double cameraHeight;
double cameraAngle;

int drawgrid;
int drawaxes;
double angle;
double wheelUpRotation; // with x axis
double wheelAxleRotation; // 
point wheelPosition;
const double wheelRadius = 20;
double inclinationAngel = 30;


void wheelWalkTheta(double theta)
{
	double distance = wheelRadius * theta / 360 * pi;
	wheelPosition+=point({cos(wheelUpRotation*pi/180),sin(wheelUpRotation*pi/180),0})*distance;
	wheelAxleRotation+=theta;
}

#include "draw2.h"

#include "inputListener2.h"



void display(){
	
	//clear the display
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0,0,0,0);	//color black
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	/********************
	/ set-up camera here
	********************/
	//load the correct matrix -- MODEL-VIEW matrix
	glMatrixMode(GL_MODELVIEW);

	//initialize the matrix
	glLoadIdentity();

	//now give three info
	//1. where is the camera (viewer)?
	//2. where is the camera looking?
	//3. Which direction is the camera's UP direction?

	//gluLookAt(100,100,100,	0,0,0,	0,0,1);
	gluLookAt(200*cos(cameraAngle), 200*sin(cameraAngle), cameraHeight,		0,0,0,		0,0,1);
	


	//again select MODEL-VIEW
	glMatrixMode(GL_MODELVIEW);


	/****************************
	/ Add your objects from here
	****************************/
	//add objects

	drawAxes();
	drawGrid();

    //glColor3f(1,0,0);
    //drawSquare(10);

    // drawSS();
	drawMain();

    // drawCircle(30,24);

    //drawCone(20,50,24);

	// drawSphere(30,24,20);




	//ADD this line in the end --- if you use double buffer (i.e. GL_DOUBLE)
	glutSwapBuffers();
}


void animate(){
	angle+=0.05;
	//codes for any changes in Models, Camera
	glutPostRedisplay();
}

void initCamera(){
	cameraHeight=150.0;
	cameraAngle=1.0;
	angle=0;
}

void initObject()
{
	wheelUpRotation = 0;
	wheelAxleRotation = 0;
	wheelPosition = {0,0,0};
}

void init(){
	//codes for initialization
	drawgrid=1;
	drawaxes=1;
	
	initCamera();
	initObject();

	//clear the screen
	glClearColor(0,0,0,0);

	/************************
	/ set-up projection here
	************************/
	//load the PROJECTION matrix
	glMatrixMode(GL_PROJECTION);

	//initialize the matrix
	glLoadIdentity();

	//give PERSPECTIVE parameters
	gluPerspective(80,	1,	1,	1000.0);
	//field of view in the Y (vertically)
	//aspect ratio that determines the field of view in the X direction (horizontally)
	//near distance
	//far distance
}

int main(int argc, char **argv){
	glutInit(&argc,argv);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);	//Depth, Double buffer, RGB color

	glutCreateWindow("My OpenGL Program");

	init();

	glEnable(GL_DEPTH_TEST);	//enable Depth Testing

	glutDisplayFunc(display);	//display callback function
	glutIdleFunc(animate);		//what you want to do in the idle time (when no drawing is occuring)

	glutKeyboardFunc(keyboardListener);
	glutSpecialFunc(specialKeyListener);
	glutMouseFunc(mouseListener);

	glutMainLoop();		//The main loop of OpenGL

	return 0;
}
