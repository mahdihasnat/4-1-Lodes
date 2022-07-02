#ifndef VEC3_H
#define VEC3_H
#include "vec4.h"

#include<bits/stdc++.h>
using namespace std;

template<typename T>
class Vec3: public Vec4<T> 
{
	public:
	Vec3(T x=T(0), T y=T(0), T z=T(0)):Vec4<T>(x, y, z, T(1))
	{
		
	}
	
	T& operator[](int const & x)
	{
		return Vec4<T>::operator[](x);
	}

	friend istream & operator >>(istream & is,Vec3<T> & v3)
	{
		is>>v3[0]>>v3[1]>>v3[2];
		v3[3]=T(1);
		return is;
	}
};

#endif /* VEC3_H */
