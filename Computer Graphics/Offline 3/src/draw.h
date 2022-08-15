#ifndef AD588FB1_ACBD_4692_A140_9D09DE3C670D
#define AD588FB1_ACBD_4692_A140_9D09DE3C670D

void drawAxes()
{
	if(drawaxes==1)
	{
		glColor3f(1.0, 1.0, 1.0);
		glBegin(GL_LINES);{
			glVertex3f( 100,0,0);
			glVertex3f(-100,0,0);

			glVertex3f(0,-100,0);
			glVertex3f(0, 100,0);

			glVertex3f(0,0, 100);
			glVertex3f(0,0,-100);
		}glEnd();
	}
}


void drawGrid()
{
	int i;
	if(drawgrid==1)
	{
		glColor3f(0.6, 0.6, 0.6);	//grey
		glBegin(GL_LINES);{
			for(i=-8;i<=8;i++){

				if(i==0)
					continue;	//SKIP the MAIN axes

				//lines parallel to Y-axis
				glVertex3f(i*10, -90, 0);
				glVertex3f(i*10,  90, 0);

				//lines parallel to X-axis
				glVertex3f(-90, i*10, 0);
				glVertex3f( 90, i*10, 0);
			}
		}glEnd();
	}
}

void drawSquare(double a)
{
    //glColor3f(1.0,0.0,0.0);
	glBegin(GL_QUADS);{
		glVertex3f( a, a,2);
		glVertex3f( a,-a,2);
		glVertex3f(-a,-a,2);
		glVertex3f(-a, a,2);
	}glEnd();
}


void drawSS()
{
    glColor3f(1,0,0);
    drawSquare(20);

    glRotatef(angle,0,0,1);
    glTranslatef(110,0,0);
    glRotatef(2*angle,0,0,1);
    glColor3f(0,1,0);
    drawSquare(15);

    glPushMatrix();
    {
        glRotatef(angle,0,0,1);
        glTranslatef(60,0,0);
        glRotatef(2*angle,0,0,1);
        glColor3f(0,0,1);
        drawSquare(10);
    }
    glPopMatrix();

    glRotatef(3*angle,0,0,1);
    glTranslatef(40,0,0);
    glRotatef(4*angle,0,0,1);
    glColor3f(1,1,0);
    drawSquare(5);
}

#endif /* AD588FB1_ACBD_4692_A140_9D09DE3C670D */
