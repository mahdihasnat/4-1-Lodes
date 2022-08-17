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
	virtual Color<T> getColorAt(Vec3<T> point) const
	{
		int i = abs(point[0])/tile_size;
		int j = abs(point[1])/tile_size;
		if((i+j+(point[0]>0)+(point[1]>0))%2)
			return Color<T>(0,0,0);
		else if(typeid(T) == typeid(double))
			return Color<T>(1,1,1);
		else assert(0);
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

	virtual Vec3<T> getNormalAt(Vec3<T> const& point, Ray<T> const & viewRay) override
	{
		if(viewRay.getDirection()[2] <0)
			return Vec3<T>(0,0,T(-1));
		else
			return Vec3<T>(0,0,T(+1));
	}
	
	Floor()
	{
		// TODO : set color,coefficients,etc in base class
		Object<T>::coefficiants[0] = T(0.25);
		Object<T>::coefficiants[1] = T(0.25);
		Object<T>::coefficiants[2] = T(0.25);
		Object<T>::coefficiants[3] = T(0.25);
		Object<T>:: shine = 1;
	}

};

#endif /* FB5DDE1F_8D91_4F02_A735_C37A7016D910 */
