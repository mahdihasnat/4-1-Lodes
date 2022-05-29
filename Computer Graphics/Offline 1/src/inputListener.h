#ifndef INPUTLISTENER_H

#define INPUTLISTENER_H
#include "GL/glut.h"

void keyboardListener(unsigned char key, int x,int y){
	switch(key){
		case '1':
			drawgrid=1-drawgrid;
			break;
		
		default:
			break;
	}
}


void specialKeyListener(int key, int x,int y){
	const double KEY_DISTANCE=3.0; 
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