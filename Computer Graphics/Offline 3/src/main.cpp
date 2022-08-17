#include <GL/glut.h>
#include <bits/stdc++.h>
using namespace std;

#define DBG(x) cout<<__FILE__<<":"<<__LINE__<<" "<<#x" = "<<x<<endl;
#define NL cout<<endl;

// ordered 
#include "constants.h"

#include "color.h"

#include "vec4.h"
#include "vec3.h"
#include "ray.h"
#include "object.h"
#include "triangle.h"
#include "generalQuadraticSurface.h"
#include "floor.h"
#include "sphere.h"
#include "light.h"
#include "pointLight.h"
#include "spotLight.h"

#include "mat4.h"

#include "common.h"
#include "variables.h"

#include "draw.h"

#include "bitmap_image.hpp"

#include "capture.h"
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
	gluLookAt(cameraPos[0],cameraPos[1],cameraPos[2]
				,cameraPos[0] + cameraLookDir[0],cameraPos[1] + cameraLookDir[1],cameraPos[2] + cameraLookDir[2]
				,cameraUpDir[0],cameraUpDir[1],cameraUpDir[2]);


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
	
	for(Object<Ftype> * obj : objects)
		obj->draw();

    // drawCircle(30,24);

    //drawCone(20,50,24);




	//ADD this line in the end --- if you use double buffer (i.e. GL_DOUBLE)
	glutSwapBuffers();
}


void animate(){
	angle+=0.05;
	//codes for any changes in Models, Camera
	glutPostRedisplay();
}

void initCamera(){

	cameraPos=Vec3<Ftype>(27.253 ,-102.934, 47.588);
	// maintain r cross l = u
	cameraUpDir= Vec3<Ftype>(0.0312734 ,0.099422 ,0.994554);
	cameraRightDir= Vec3<Ftype>(0.969694, 0.238213, -0.0543049);
	cameraUpDir.normalize();
	cameraRightDir.normalize();
	cameraLookDir= cameraUpDir.cross(cameraRightDir);
	angle=0;
}

void init(){
	//codes for initialization
	drawgrid=0;
	drawaxes=1;
	
	initCamera();
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
	gluPerspective(fieldOfView,	aspectRatio, nearPlane, farPlane);
	//field of view in the Y (vertically)
	//aspect ratio that determines the field of view in the X direction (horizontally)
	//near distance
	//far distance
}

void loadData(){
	ifstream in("inputs.txt");

	in >> recursionLevel;
	in >> imageWidth;
	imageHeight =  imageWidth;

	cerr<<"Recursion Level: "<<recursionLevel<<endl;
	cerr<<"Pixel Dimension: "<<imageHeight<<endl;

	in >> nObjects;
	cerr<<"Number of Objects: "<<nObjects<<endl;
	for(int i=0;i<nObjects;i++)
	{
		string type;
		in >> type;
		Object<Ftype> * pObject;
		if(type=="triangle")
		{
			pObject = new Triangle<Ftype>();
		}
		else if(type=="sphere")
		{
			pObject = new Sphere<Ftype>();
		}
		else if(type=="general")
		{
			pObject = new GeneralQuadraticSurface<Ftype>();
		}
		else assert(0);
		in>>*pObject;
		objects.push_back(pObject);
	}
	
	nObjects++;
	objects.push_back(new Floor<Ftype>());
	int nPointLights;
	in>>nPointLights;
	for(int i=0;i<nPointLights;i++)
	{
		Light<Ftype> * light = new PointLight<Ftype>();
		in>>*light;
		lights.push_back(light);
	}
	int nSpotLights;
	in>>nSpotLights;
	for(int i=0;i<nSpotLights;i++)
	{
		Light<Ftype> * light = new SpotLight<Ftype>();
		in>>*light;
		lights.push_back(light);
	}
	
	for(Light<Ftype> * l: lights)
	{
		Sphere<Ftype> * o = new Sphere<Ftype>();
		Ftype r = 1;
		o->setCenter(l->getPosition()+Vec3<Ftype>(0,0,1+r));
		o->setRadius(r);
		o->setColor(l->getColor());
		o->setAmbient(1);
		o->setDiffuse(1);
		o->setSpecular(1);
		o->setShine(1);
		// objects.push_back(o);
	}

	DBG(objects.size());
	for(Object<Ftype> * o: objects)
	{
		cerr<<*o<<endl;
	}
	DBG(lights.size());
	for(Light<Ftype> * l: lights)
	{
		cerr<<*l<<endl;
	}
}	

int main(int argc, char **argv){
	
	loadData();
	
	glutInit(&argc,argv);
	glutInitWindowSize(windowWidth, windowHeight);
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
