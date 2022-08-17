#ifndef DBE74540_73D9_4EBD_9F04_68CA243F283A
#define DBE74540_73D9_4EBD_9F04_68CA243F283A

#include "object.h"
#include "vec3.h"

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
public:
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
	virtual T getIntersectingT(Ray<T> const& ray)
	{

		// (ray.o + t * ray.d  - center) dot  (ray.o + t * ray.d  - center) 
		//  - radius* radius = 0

		// t^2 ( ray.d dot ray.d) + t * 2 * (ray.o - center) dot (ray.o - center)  
		// + (ray.o dot ray.o  - radius * radius) = 0;

		//  SOLVING a * t^2 + b * t + c = 0

		T a = ray.getDirection().dot(ray.getDirection());
		T b = 2 * (ray.getOrigin() - center).dot(ray.getDirection());
		T c = ((ray.getOrigin() - center).dot((ray.getOrigin() - center)) - radius * radius);

		T tMin = -1;
		T determinant = b * b - 4 * a * c;

		

		if(determinant < T(0)) // imaginary roots
			tMin = -1;
		else
		{
			
			T t1 = (-b + sqrt(determinant)) / (2 * a);
			T t2 = (-b - sqrt(determinant)) / (2 * a);
			if(t1 > t2)
				swap(t1,t2);
			
			if(T(0) < t1)
				tMin = t1;
			else if(T(0) < t2)
				tMin = t2;
		}
		return tMin;
	}

	Vec3<T> getNormalAt(Vec3<T> const& point) override
	{
		return (point - center).normalize();
	}

	virtual T intersect(Ray<T> const& ray, Color<T> &color, int level)
	{
		return T(-1); // TODO: remove this later
		T tMin = getIntersectingT(ray);
		if(level==0)
			return tMin;

		assert(0);

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
