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

#include "common.h"
#include "point.h"
#include "vec4.h"
#include "vec3.h"
#include "mat4.h"

#include "object.h"
#include "triangle.h"
#include "sphere.h"
#include "generalQuadraticSurface.h"

typedef double T;

Object<T> ** objects;

point cameraPos;
point cameraUpDir;
point cameraRightDir;
point cameraLookDir;

int drawgrid;
int drawaxes;
double angle;
const double radius = 50;
double squareHalf;

#include "draw.h"

#include "inputListener.h"



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
	//gluLookAt(200*cos(cameraAngle), 200*sin(cameraAngle), cameraHeight,		0,0,0,		0,0,1);
	gluLookAt(cameraPos.x,cameraPos.y,cameraPos.z
				,cameraPos.x + cameraLookDir.x,cameraPos.y + cameraLookDir.y,cameraPos.z + cameraLookDir.z
				,cameraUpDir.x,cameraUpDir.y,cameraUpDir.z);


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

	cameraPos={0,0,200};
	// maintain r cross l = u
	cameraUpDir={0,1,0};
	cameraRightDir={1,0,0};
	cameraLookDir={0,0,-1};
	angle=0;
}

void init(){
	//codes for initialization
	drawgrid=0;
	drawaxes=1;
	
	initCamera();
	squareHalf = radius * 0.7;
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

void loadData(){
	ifstream in("inputs.txt");
	int recursionLevel;
	int pixelDimension;

	in >> recursionLevel;
	in >> pixelDimension;

	cerr<<"Recursion Level: "<<recursionLevel<<endl;
	cerr<<"Pixel Dimension: "<<pixelDimension<<endl;

	int nObjects;
	in >> nObjects;
	cerr<<"Number of Objects: "<<nObjects<<endl;
	objects = new Object<T> *[nObjects];

	for(int i=0;i<nObjects;i++)
	{
		string type;
		in >> type;
		if(type=="triangle")
		{
			objects[i] = new Triangle<T>();
		}
		else if(type=="sphere")
		{
			objects[i] = new Sphere<T>();
		}
		else if(type=="general")
		{
			objects[i] = new GeneralQuadraticSurface<T>();
		}
		else assert(0);
		in>>*objects[i];
		cerr<<*objects[i]<<endl;
	}


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

	loadData();

	glutMainLoop();		//The main loop of OpenGL

	return 0;
}
