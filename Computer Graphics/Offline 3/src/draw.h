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

void drawMySquare(double radius,double d)
{
	// draw plane along yz plane
	// distance from origin is radius
	// square side is 2 * d
	glBegin(GL_QUADS);
	{
		glVertex3d(radius,d,d);
		glVertex3d(radius,d,-d);
		glVertex3d(radius,-d,-d);
		glVertex3d(radius,-d,d);
	}
	glEnd();
}

void drawMyCube()
{
	glColor3d(1,1,1);
	drawMySquare(radius,squareHalf);
	for(int i=1;i<4;i++){
		glPushMatrix();
		{
			glRotated(90*i,0,0,1);
			drawMySquare(radius,squareHalf);
		}
		glPopMatrix();
	}
	glPushMatrix();
	{
		glRotated(90,0,1,0);
		drawMySquare(radius,squareHalf);
	}
	glPopMatrix();
	glPushMatrix();
	{
		glRotated(-90,0,1,0);
		drawMySquare(radius,squareHalf);
	}
	glPopMatrix();
}

void drawMyCylinderSingle(double radius,double squareHalf,int stacks,int slices)
{
// y
// ^
// | -- squareHalf-- 
// 	___________.
// 				|   .
// 				|    ..
// 				|     ..
// 				________.
// 						|
// 						|
// 						|
// 						|
// (0,0)   --radius--		| -> x

	double r = radius - squareHalf;// radius in each stack
	point points[stacks+1][slices+1];
	for(int i=0;i<=stacks;i++)
	{
		double z = - squareHalf + i * 2 * squareHalf / stacks;
		for(int j=0;j<=slices;j++)
		{
			points[i][j].x = r * cos(j*pi/2/slices) + squareHalf;
			points[i][j].y = r * sin(j*pi/2/slices) + squareHalf;
			points[i][j].z = z;
		}
	}
	for(int i=0;i<stacks;i++)
	{
		for(int j=0;j<slices;j++)
		{
			glBegin(GL_QUADS);
			{
				glVertex3d(points[i][j].x,points[i][j].y,points[i][j].z);
				glVertex3d(points[i][j+1].x,points[i][j+1].y,points[i][j+1].z);
				glVertex3d(points[i+1][j+1].x,points[i+1][j+1].y,points[i+1][j+1].z);
				glVertex3d(points[i+1][j].x,points[i+1][j].y,points[i+1][j].z);
			}
			glEnd();
		}
	}
}
void drawMyCylinder()
{

	glColor3f(0,1,0);
	const int stacks = 1;
	const int slices = 100;
	drawMyCylinderSingle(radius,squareHalf,stacks,slices);
	for(int i=1;i<4;i++)
	{
		glPushMatrix();
		{
			glRotated(90*i,0,0,1);
			drawMyCylinderSingle(radius,squareHalf,stacks,slices);
		}
		glPopMatrix();
	}
	
	for(int i=0;i<4;i++)
	{
		glPushMatrix();
		{
			glRotated(90*i,0,1,0);
			glRotated(90,1,0,0);
			drawMyCylinderSingle(radius,squareHalf,stacks,slices);
		}
		glPopMatrix();
	}
	
	for(int i=0;i<4;i++)
	{
		glPushMatrix();
		{
			glRotated(90*i,1,0,0);
			glRotated(90,0,1,0);
			drawMyCylinderSingle(radius,squareHalf,stacks,slices);
		}
		glPopMatrix();
	}
}

void drawMySphereSingle(double radius,double squareHalf,int stacks,int slices)
{
// 					y
// 					^
// 					|

// 					|
// 					|
// 					|
// 					|
// 					|
//  (0,0)				-------------  -> x
// 					/
// 				   /
// 				  /
// 				 /
// 				\/	
// 				z
	point points[stacks+1][slices+1];
	for(int i=0;i<=stacks;i++)
	{
		double theta = i * pi/2.0/stacks;
		double y = (radius-squareHalf)*sin(theta) + squareHalf;

		for(int j=0;j<=slices;j++)
		{
			double phi = j * pi/2.0/slices;

			points[i][j].x = (radius-squareHalf) * cos(theta) * cos(phi) + squareHalf;
			points[i][j].y = y;
			points[i][j].z = (radius-squareHalf) * cos(theta) * sin(phi) + squareHalf;
		}
	}
	for(int i=0;i<stacks;i++)
	{
		for(int j=0;j<slices;j++)
		{
			glBegin(GL_QUADS);
			{
				glVertex3d(points[i][j].x,points[i][j].y,points[i][j].z);
				glVertex3d(points[i][j+1].x,points[i][j+1].y,points[i][j+1].z);
				glVertex3d(points[i+1][j+1].x,points[i+1][j+1].y,points[i+1][j+1].z);
				glVertex3d(points[i+1][j].x,points[i+1][j].y,points[i+1][j].z);
			}
			glEnd();
		}
	}
}
void drawMySphere()
{
	const int stacks = 100;
	const int slices = 100;
	glColor3d(1.0,0,0);
	for(int i=0;i<4;i++)
	{
		glPushMatrix();
		{
			glRotated(90*i,0,1,0);
			drawMySphereSingle(radius,squareHalf,stacks,slices);
		}
		glPopMatrix();
	}
	for(int i=0;i<4;i++)
	{
		glPushMatrix();
		{
			glRotated(90*i,0,1,0);
			glRotated(90,1,0,0);
			drawMySphereSingle(radius,squareHalf,stacks,slices);
		}
		glPopMatrix();
	}
}

void drawMain()
{
	drawMyCube();
	drawMyCylinder();
	drawMySphere();
}


#endif /* AD588FB1_ACBD_4692_A140_9D09DE3C670D */
