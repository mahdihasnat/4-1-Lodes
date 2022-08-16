#ifndef FB5DDE1F_8D91_4F02_A735_C37A7016D910
#define FB5DDE1F_8D91_4F02_A735_C37A7016D910

#include "object.h"

template<typename T>
class Floor: public Object<T>
{
public:
	const int tile_size = 20;
	const int tile_count = 25;
	void draw()
	{
		for(int rot=0;rot<4;rot++)
		{
			glPushMatrix();
			glRotatef(90*rot,0,0,1);
			for(int i=0,x=0;i<tile_count;i++,x+=tile_size)
			{
				for(int j=0,y=0;j<tile_count;j++,y+=tile_size)
				{
					glBegin(GL_QUADS);{
						if((i+j+rot)%2)
							glColor3d(0,0,0);
						else
							glColor3d(1,1,1);
						glVertex3i(x,y,0);
						glVertex3i(x,y+tile_size,0);
						glVertex3i(x+tile_size,y+tile_size,0);
						glVertex3i(x+tile_size,y,0);
					}
					glEnd();
				}
			}
			glPopMatrix();
		}
	}
	virtual T getIntersectingT(Ray<T> const& ray)
	{
		// (ray.o + t * ray.d ) dot (0,0,1) =0
		// t = -ray.o.z / ray.d.z
		T tMin = T(-1);
		if(abs(ray.getDirection()[2]) < EPS) // ray parallel to xy-plane
		{
			if(abs(ray.getOrigin()[2]) < EPS) // ray origin on xy-plane
				tMin = T(0);
			else
				tMin=T(-1);
		}
		else
		{
			tMin = -ray.getOrigin()[2] / ray.getDirection()[2];
		}

		Vec3<T> point = ray.getOrigin()+ray.getDirection()*tMin;
		const int MAXPOINT = tile_count * tile_size;
		bool inside = 1;
		for(int i=0;i<2;i++)
			inside = inside and abs(point[i])<=MAXPOINT;
		
		if(!inside)
			tMin = T(-1);
		
		return tMin;
	}
	virtual T intersect(Ray<T> const& ray, Color<T> &color, int level)
	{
		return T(-1); // TODO: remove later
		T tMin = getIntersectingT(ray);
		if(level == 0)
			return tMin;
		assert(0);
	}
	
	Floor()
	{
		// TODO : set color,coefficients,etc in base class
	}

};

#endif /* FB5DDE1F_8D91_4F02_A735_C37A7016D910 */
