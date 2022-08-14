#ifndef DBE74540_73D9_4EBD_9F04_68CA243F283A
#define DBE74540_73D9_4EBD_9F04_68CA243F283A

#include "object.h"
#include "vec3.h"
#include "common.h"

template<typename T>
class Sphere: public Object<T>
{
protected:
	Vec3<T> center;
	T radius;
	void calculatePointsAtHeight(Vec3<T> * points,int i,int stacks, int slices)
	{
		T h = radius*sin(PI*i/2/stacks);
		T r = radius*cos(PI*i/2/stacks);
		for(int j=0;j<=slices;j++)
		{
			points[j][0]=r * cos(j*PI*2/slices);
			points[j][1]=r * sin(j*PI*2/slices);
			points[j][2]=h;
		}
	}
public:
	void drawAtOrigin()
	{
		const int SLICES = 100;
		const int STACKS = 100;
		Vec3<T> points[2][SLICES+1];
		calculatePointsAtHeight(points[0%2],0,STACKS,SLICES);
		for(int i=0;i<STACKS;i++)
		{
			calculatePointsAtHeight(points[(i+1)%2],i+1,STACKS,SLICES);
			for(int j=0;j<SLICES;j++)
			{
				glBegin(GL_QUADS);{
					// upper hemisphere
					points[0][j].draw();
					points[0][j+1].draw();
					points[1][j+1].draw();
					points[1][j].draw();

					// Lower hemisphere
					points[0][j][2] = -points[0][j][2];
					points[0][j+1][2] = -points[0][j+1][2];
					points[1][j+1][2] = -points[1][j+1][2];
					points[1][j][2] = -points[1][j][2];
					
					points[0][j].draw();
					points[0][j+1].draw();
					points[1][j+1].draw();
					points[1][j].draw();

					points[0][j][2] = -points[0][j][2];
					points[0][j+1][2] = -points[0][j+1][2];
					points[1][j+1][2] = -points[1][j+1][2];
					points[1][j][2] = -points[1][j][2];
					
				
				}glEnd();
			}
		}
	}
	void draw()
	{
		Object<T>::draw();
		glPushMatrix();
		{
			glTranslatef(center[0],center[1],center[2]);
			drawAtOrigin();
		}
		glPopMatrix();
	}
	virtual istream & read(istream & is)
	{
		is>>center>>radius;
		Object<T>::read(is);
		return is;
	}
	virtual ostream & write(ostream & os) const
	{
		os<<"[s: [c: "<<center<<"] [r: "<<radius<<"]";
		return Object<T>::write(os)<<" ]";
	}

};

#endif /* DBE74540_73D9_4EBD_9F04_68CA243F283A */
