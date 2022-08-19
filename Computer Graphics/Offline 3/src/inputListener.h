#ifndef INPUTLISTENER_H

#define INPUTLISTENER_H
#include <GL/glut.h>
#include "capture.h"


void keyboardListener(unsigned char key, int x,int y){
	// drawgrid=1-drawgrid;
	// DBG(cameraPos);
	// DBG(cameraLookDir);
	// DBG(cameraUpDir);
	// DBG(cameraRightDir);
	// NL;
	const double ANGEL_DISTANCE = 3.0;
	switch(key){
		case '0':
			capture();
			break;
		case '1':
			rotateUnitPlane(
					cameraRightDir,
					cameraLookDir,
					cameraUpDir,
					ANGEL_DISTANCE
				);
			break;
		case '2':

			rotateUnitPlane(
					cameraRightDir,
					cameraLookDir,
					cameraUpDir,
					-ANGEL_DISTANCE
				);
			break;
		
		case '3':

			rotateUnitPlane(
					cameraLookDir,
					cameraUpDir,
					cameraRightDir,
					ANGEL_DISTANCE
				);
			break;
		case '4':

			rotateUnitPlane(
					cameraLookDir,
					cameraUpDir,
					cameraRightDir,
					-ANGEL_DISTANCE
				);
			break;
		
		case '5':
			rotateUnitPlane(
					cameraUpDir,
					cameraRightDir,
					cameraLookDir,
					ANGEL_DISTANCE
				);
			break;
		case '6':
			rotateUnitPlane(
					cameraUpDir,
					cameraRightDir,
					cameraLookDir,
					-ANGEL_DISTANCE
				);
			break;


		default:
			break;
	}
	
}

	const double KEY_DISTANCE=5.0; 

void specialKeyListener(int key, int x,int y){

	// DBG(cameraPos);
	// DBG(cameraLookDir);
	// DBG(cameraUpDir);
	// DBG(cameraRightDir);
	// NL;

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
			
			break;
		case GLUT_KEY_END:
			
			break;

		default:
			break;
	}
	DBG(cameraPos);
	DBG(cameraUpDir);
	DBG(cameraRightDir);
	DBG(cameraLookDir);
	NL;
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
		case 3:
			// zoom in
			cameraPos += cameraLookDir * KEY_DISTANCE;
			break;
		case 4:
			// zoom out
			cameraPos += cameraLookDir * -KEY_DISTANCE;
			break;
		default:
			break;
	}
	
}

void mouseWheelListener(int button, int dir, int x, int y)
{
    if (dir > 0)
    {
		// zoom in
        cameraPos += cameraLookDir * 0.1;
	}
	else
	{
		// zoom out
		cameraPos -= cameraLookDir * 0.1;
    }

    return;
}

#endif