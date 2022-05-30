
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


void drawCircle(double radius,int segments)
{
    int i;
    struct point points[100];
    glColor3f(0.7,0.7,0.7);
    //generate points
    for(i=0;i<=segments;i++)
    {
        points[i].x=radius*cos(((double)i/(double)segments)*2*pi);
        points[i].y=radius*sin(((double)i/(double)segments)*2*pi);
    }
    //draw segments using generated points
    for(i=0;i<segments;i++)
    {
        glBegin(GL_LINES);
        {
			glVertex3f(points[i].x,points[i].y,0);
			glVertex3f(points[i+1].x,points[i+1].y,0);
        }
        glEnd();
    }
}

void drawCone(double radius,double height,int segments)
{
    int i;
    double shade;
    struct point points[100];
    //generate points
    for(i=0;i<=segments;i++)
    {
        points[i].x=radius*cos(((double)i/(double)segments)*2*pi);
        points[i].y=radius*sin(((double)i/(double)segments)*2*pi);
    }
    //draw triangles using generated points
    for(i=0;i<segments;i++)
    {
        //create shading effect
        if(i<segments/2)shade=2*(double)i/(double)segments;
        else shade=2*(1.0-(double)i/(double)segments);
        glColor3f(shade,shade,shade);

        glBegin(GL_TRIANGLES);
        {
            glVertex3f(0,0,height);
			glVertex3f(points[i].x,points[i].y,0);
			glVertex3f(points[i+1].x,points[i+1].y,0);
        }
        glEnd();
    }
}


void drawSphere(double radius,int slices,int stacks)
{
	struct point points[100][100];
	int i,j;
	double h,r;
	//generate points
	for(i=0;i<=stacks;i++)
	{
		h=radius*sin(((double)i/(double)stacks)*(pi/2));
		r=radius*cos(((double)i/(double)stacks)*(pi/2));
		for(j=0;j<=slices;j++)
		{
			points[i][j].x=r*cos(((double)j/(double)slices)*2*pi);
			points[i][j].y=r*sin(((double)j/(double)slices)*2*pi);
			points[i][j].z=h;
		}
	}
	//draw quads using generated points
	for(i=0;i<stacks;i++)
	{
        glColor3f((double)i/(double)stacks,(double)i/(double)stacks,(double)i/(double)stacks);
		for(j=0;j<slices;j++)
		{
			glBegin(GL_QUADS);{
			    //upper hemisphere
				glVertex3f(points[i][j].x,points[i][j].y,points[i][j].z);
				glVertex3f(points[i][j+1].x,points[i][j+1].y,points[i][j+1].z);
				glVertex3f(points[i+1][j+1].x,points[i+1][j+1].y,points[i+1][j+1].z);
				glVertex3f(points[i+1][j].x,points[i+1][j].y,points[i+1][j].z);
                //lower hemisphere
                glVertex3f(points[i][j].x,points[i][j].y,-points[i][j].z);
				glVertex3f(points[i][j+1].x,points[i][j+1].y,-points[i][j+1].z);
				glVertex3f(points[i+1][j+1].x,points[i+1][j+1].y,-points[i+1][j+1].z);
				glVertex3f(points[i+1][j].x,points[i+1][j].y,-points[i+1][j].z);
			}glEnd();
		}
	}
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

void drawQuarterRing(double radius,double widthHalf,int stacks)
{
	// ring is placed in xz plane, axle is along y axis
	// 
	point points[stacks+1][2];
	for(int i=0;i<=stacks;i++)
	{
		double theta = (double)i * pi / 2.0 /(double)stacks;
		points[i][1].x = points[i][0].x = radius * cos(theta);
		points[i][1].z = points[i][0].z = radius * sin(theta);
		points[i][0].y=-widthHalf;
		points[i][1].y=widthHalf;
	}
	for(int i=0;i<stacks;i++)
	{
		glBegin(GL_QUADS);
		{
			glVertex3f(points[i][0].x,points[i][0].y,points[i][0].z);
			glVertex3f(points[i][1].x,points[i][1].y,points[i][1].z);
			glVertex3f(points[i+1][1].x,points[i+1][1].y,points[i+1][1].z);
			glVertex3f(points[i+1][0].x,points[i+1][0].y,points[i+1][0].z);
		}
		glEnd();
	}
}
void drawRing(double radius,double widthHalf)
{
	// ring in xz plane
	// axle in y axis
	for(int rot=0;rot<360;rot+=90)
	{
		glPushMatrix();
		{
			glRotatef(rot,0,1,0);
			drawQuarterRing(radius,widthHalf,10);
		}
		glPopMatrix();
	}
}
void drawRectangle(double zdirHalf,double ydirHalf)
{
	glBegin(GL_QUADS);
	{
		glVertex3d(0,-ydirHalf,zdirHalf);
		glVertex3d(0,-ydirHalf,-zdirHalf);
		glVertex3d(0,ydirHalf,-zdirHalf);
		glVertex3d(0,ydirHalf,zdirHalf);
	}
	glEnd();
}
void drawWheelCenter(double radius,double widthHalf)
{
	// axle in y axis

	glColor3d(1.0,0,0);
	drawRing(radius,widthHalf);
	glColor3d(0,1.0,0);
	drawRectangle(radius,widthHalf/3.0);
	glColor3d(0,0,1.0);
	glPushMatrix();
	{
		glRotated(90,0,1,0);
		drawRectangle(radius,widthHalf/3.0);
	}
	glPopMatrix();
	
}
void drawWheel()
{
	const double widthHalf=5;
	glPushMatrix();
	{
		glTranslated(wheelPosition.x,wheelPosition.y,wheelPosition.z);
		glTranslated(0,0,wheelRadius);
		glRotated(wheelUpRotation,0,0,1);
		glRotated(wheelAxleRotation,0,1,0);
		drawWheelCenter(wheelRadius,widthHalf);
	}
	glPopMatrix();
}

void drawMain()
{
	drawWheel();
}