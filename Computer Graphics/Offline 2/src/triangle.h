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
		Triangle(Vec3<T> v[3],Color c):c(c){
			for(int i=0;i<3;i++){
				this->v[i] = v[i];
			}
		}
};

#endif /* TRIANGLE_H */
