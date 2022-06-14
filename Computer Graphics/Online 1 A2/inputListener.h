#ifndef INPUTLISTENER_H

#define INPUTLISTENER_H
#include "GL/glut.h"

const double ANGEL_DISTANCE = 3.0;
void UpRotate(double angel)
{
	rotateUnitPlane(
					cameraLookDir,
					cameraUpDir,
					cameraRightDir,
					angel
				);
}
void LeftRotate(double angel)
{
	rotateUnitPlane(
					cameraRightDir,
					cameraLookDir,
					cameraUpDir,
					angel
				);
}

void TiltRotate(double angel)
{
	rotateUnitPlane(
					cameraUpDir,
					cameraRightDir,
					cameraLookDir,
					angel
				);
}

void keyboardListener(unsigned char key, int x,int y){
	// drawgrid=1-drawgrid;
	// DBG(cameraPos);
	// DBG(cameraLookDir);
	// DBG(cameraUpDir);
	// DBG(cameraRightDir);
	// NL;
	switch(key){
		case '1':
			LeftRotate(ANGEL_DISTANCE);
			break;
		case '2':
			LeftRotate(-ANGEL_DISTANCE);
			break;
		
		case '3':

			UpRotate(ANGEL_DISTANCE);
			break;
		case '4':

			UpRotate(-ANGEL_DISTANCE);
			break;
		
		case '5':
			TiltRotate(ANGEL_DISTANCE);
			break;
		case '6':
			TiltRotate(-ANGEL_DISTANCE);
			break;
		case '7':
			UpRotate(ANGEL_DISTANCE);
			LeftRotate(ANGEL_DISTANCE);
			break;
		case '8':
			UpRotate(ANGEL_DISTANCE);
			LeftRotate(-ANGEL_DISTANCE);
			break;
		case '9':
			UpRotate(-ANGEL_DISTANCE);
			LeftRotate(ANGEL_DISTANCE);
			break;
		case '0':
			UpRotate(-ANGEL_DISTANCE);
			LeftRotate(-ANGEL_DISTANCE);
			break;
		default:
			break;
	}
}


void specialKeyListener(int key, int x,int y){

	// DBG(cameraPos);
	// DBG(cameraLookDir);
	// DBG(cameraUpDir);
	// DBG(cameraRightDir);
	// NL;

	const double KEY_DISTANCE=5.0; 
	switch(key){
		case GLUT_KEY_DOWN:		//down arrow key
			cameraPos += cameraLookDir * -KEY_DISTANCE;
			break;
		case GLUT_KEY_UP:		// up arrow key
			
			cameraPos += cameraLookDir * KEY_DISTANCE;
			break;

		case GLUT_KEY_RIGHT:
			cameraPos += cameraRightDir * KEY_DISTANCE;
			break;
		case GLUT_KEY_LEFT:
			cameraPos += cameraRightDir * -KEY_DISTANCE;
			break;

		case GLUT_KEY_PAGE_UP:
			cameraPos += cameraUpDir * KEY_DISTANCE;
			break;
		case GLUT_KEY_PAGE_DOWN:
			cameraPos += cameraUpDir * -KEY_DISTANCE;
			break;

		case GLUT_KEY_INSERT:
			break;

		case GLUT_KEY_HOME:
			squareHalf = min(radius , squareHalf + 1);
			break;
		case GLUT_KEY_END:
			squareHalf = max(squareHalf-1 , 0.0);
			break;

		default:
			break;
	}
}


void mouseListener(int button, int state, int x, int y){	//x, y is the x-y of the screen (2D)
	
	switch(button){
		case GLUT_LEFT_BUTTON:
			if(state == GLUT_DOWN){		// 2 times?? in ONE click? -- solution is checking DOWN or UP
				drawaxes=1-drawaxes;
			}
			break;

		case GLUT_RIGHT_BUTTON:
			//........
			break;

		case GLUT_MIDDLE_BUTTON:
			//........
			break;

		default:
			break;
	}
}

#endif