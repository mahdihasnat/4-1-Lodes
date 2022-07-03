#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "vec3.h"
#include "color.h"

template<class T>
class Triangle
{
	Vec3<T> v[3];
	Color c;
	public:
		Triangle(Vec3<T> v0,Vec3<T> v1,Vec3<T> v2,Color c):c(c){
			v[0]=v0;
			v[1]=v1;
			v[2]=v2;
		}
};

#endif /* TRIANGLE_H */
