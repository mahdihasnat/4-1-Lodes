#include <GL/glut.h>
#include <bits/stdc++.h>
using namespace std;

#define DBG(x) cout<<__FILE__<<":"<<__LINE__<<" "<<#x" = "<<x<<endl;
#define NL cout<<endl;

#include "1705003_uniquePtr.h"


// ordered 
#include "1705003_constants.h"

#include "1705003_color.h"

#include "1705003_vec4.h"
#include "1705003_vec3.h"
#include "1705003_ray.h"
#include "1705003_object.h"
#include "1705003_triangle.h"
#include "1705003_generalQuadraticSurface.h"
#include "1705003_floor.h"
#include "1705003_sphere.h"
#include "1705003_light.h"
#include "1705003_pointLight.h"
#include "1705003_spotLight.h"

#include "1705003_mat4.h"

#include "1705003_common.h"
#include "1705003_variables.h"

#include "1705003_draw.h"

#include "bitmap_image.hpp"

#include "1705003_capture.h"
#include "1705003_inputListener.h"



#include "1705003_transTriangle.h"

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
	
	for(auto const & obj : objects)
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

	cameraPos=Vec3<Ftype>(-100 ,-100, 50);
	// maintain r cross l = u
	cameraUpDir= Vec3<Ftype>(0,0,1);
	cameraLookDir= Vec3<Ftype>(1,1,0);
	cameraLookDir.normalize();
	cameraUpDir.normalize();
	cameraRightDir= cameraLookDir.cross(cameraUpDir);
	cameraRightDir.normalize();
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


void addPrism()
{
	TransTriangle<Ftype> *tt = new TransTriangle<Ftype>();
	tt->setRefrectionCoefficient(1/1.5);
	
	// 0->1->2 ghurle vector ta jate prism er vitore thake
	// direction of right hand rule from going along 
	// v0 -> v1 -> v2 align inside prism
	// see resource/prism_coordinates.jpeg for more details
	const Ftype dx = 20;
	const Ftype dy = 5;
	const Ftype dz = 40;
	const Vec3<Ftype> origin(0,0,5);
	tt->setVertex(0,origin+Vec3<Ftype>(dx,dy,0));
	tt->setVertex(1,origin+Vec3<Ftype>(-dx,dy,0));
	tt->setVertex(2,Vec3<Ftype>(-dx,0,dz));

	tt->setColor(Color<Ftype> (0.1,0.1,0.1));
	tt->setAmbient(0);
	tt->setDiffuse(0.001);
	tt->setSpecular(0.01);
	tt->setReflection(0.001);
	tt->setShine(1);

	objects.emplace_back(tt);

	{
		TransTriangle<Ftype> *ntt = new TransTriangle<Ftype>(*tt);
		ntt->setVertex(0,origin+Vec3<Ftype>(dx,dy,0));
		ntt->setVertex(2,origin+Vec3<Ftype>(-dx,0,dz));
		ntt->setVertex(1,origin+Vec3<Ftype>(dx,0,dz));
		objects.push_back(ntt);
	}
	
	{
		TransTriangle<Ftype> *ntt = new TransTriangle<Ftype>(*tt);
		ntt->setVertex(0,origin+Vec3<Ftype>(-dx,0,dz));
		ntt->setVertex(1,origin+Vec3<Ftype>(dx,-dy,0));
		ntt->setVertex(2,origin+Vec3<Ftype>(dx,0,dz));
		objects.push_back(ntt);
	}
	
	{
		TransTriangle<Ftype> *ntt = new TransTriangle<Ftype>(*tt);
		ntt->setVertex(0,origin+Vec3<Ftype>(-dx,0,dz));
		ntt->setVertex(1,origin+Vec3<Ftype>(-dx,-dy,0));
		ntt->setVertex(2,origin+Vec3<Ftype>(dx,-dy,0));
		objects.push_back(ntt);
	}

	{
		TransTriangle<Ftype> *ntt = new TransTriangle<Ftype>(*tt);
		ntt->setVertex(0,origin+Vec3<Ftype>(dx,dy,0));
		ntt->setVertex(1,origin+Vec3<Ftype>(dx,-dy,0));
		ntt->setVertex(2,origin+Vec3<Ftype>(dx,0,dz));
		objects.push_back(ntt);
	}

	{
		TransTriangle<Ftype> *ntt = new TransTriangle<Ftype>(*tt);
		ntt->setVertex(0,origin+Vec3<Ftype>(-dx,0,dz));
		ntt->setVertex(1,origin+Vec3<Ftype>(-dx,dy,0));
		ntt->setVertex(2,origin+Vec3<Ftype>(-dx,-dy,0));
		objects.push_back(ntt);
	}
	
	{
		TransTriangle<Ftype> *ntt = new TransTriangle<Ftype>(*tt);
		ntt->setVertex(0,origin+Vec3<Ftype>(dx,-dy,0));
		ntt->setVertex(1,origin+Vec3<Ftype>(-dx,-dy,0));
		ntt->setVertex(2,origin+Vec3<Ftype>(-dx,dy,0));
		objects.push_back(ntt);
	}
	
	{
		TransTriangle<Ftype> *ntt = new TransTriangle<Ftype>(*tt);
		ntt->setVertex(0,origin+Vec3<Ftype>(dx,-dy,0));
		ntt->setVertex(1,origin+Vec3<Ftype>(-dx,dy,0));
		ntt->setVertex(2,origin+Vec3<Ftype>(dx,dy,0));
		objects.push_back(ntt);
	}


	for(auto const & obj: objects)
	{
		// obj->setColor(Color<Ftype> (0,0,0));
	}

	SpotLight<Ftype> * sp = new SpotLight<Ftype>();
	sp->setPosition(origin + Vec3<Ftype>(0,dy*5,dz*0.75));
	sp->setColor(Color<Ftype> (1,1,1));
	sp->setDirection(Vec3<Ftype>(0,-1,0));
	sp->setCuttoffAngleDegree(10);
	lights.push_back(sp);

	{
		// for prism
		SpotLight<Ftype> * sl = new SpotLight<Ftype>();
		sl->setDirection(Vec3<Ftype>(0,0,-1));
		sl->setCuttoffAngleDegree(0.001);

		sl->setPosition(Vec3<Ftype>(0,-15,200));	
		sl->setColor(Color<Ftype> (1,1,1));

		lights.push_back(sl);
	}
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
		objects.emplace_back(UniquePtr<Object<Ftype> >(pObject));
	}
	
	nObjects++;
	objects.push_back(new Floor<Ftype>());
	int nPointLights;
	in>>nPointLights;
	for(int i=0;i<nPointLights;i++)
	{
		Light<Ftype> * light = new PointLight<Ftype>();
		in>>*light;
		lights.emplace_back(UniquePtr<Light<Ftype> >(light));
	}
	int nSpotLights;
	in>>nSpotLights;
	for(int i=0;i<nSpotLights;i++)
	{
		Light<Ftype> * light = new SpotLight<Ftype>();
		in>>*light;
		lights.push_back(UniquePtr<Light<Ftype> >(light));
	}
	
	for(auto const& l: lights)
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

	// TransTriangle<Ftype> * tt = new TransTriangle<Ftype>();
	// tt->setRefrectionCoefficient(1.2);
	
	// tt->setVertex(0,Vec3<Ftype>(-10,-10,20));
	// tt->setVertex(1,Vec3<Ftype>(10,-10,20));
	// tt->setVertex(2,Vec3<Ftype>(0,10,20));

	// tt->setColor(Color<Ftype> (0.5,0.5,0.5));
	// tt->setAmbient(0.5);
	// tt->setDiffuse(0.2);
	// tt->setSpecular(0.2);
	// tt->setReflection(0.2);
	// tt->setShine(1);
	// objects.push_back(tt);

	// addPrism();



	


	DBG(objects.size());
	for(auto const& o: objects)
	{
		cerr<<*o<<endl;
	}
	DBG(lights.size());
	for(auto const& l: lights)
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
