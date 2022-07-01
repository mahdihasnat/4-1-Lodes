#ifndef VEC3_H
#define VEC3_H


#include "vec4.h"
template<typename T>
class Vec3: public(Vec4<T>)
{
	Vec3(T x, T y, T z):Vec4(x, y, z, 1)
	{
	}
};

#endif /* VEC3_H */
