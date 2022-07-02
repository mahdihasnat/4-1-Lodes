#ifndef VEC4_H
#define VEC4_H
#include<bits/stdc++.h>
using namespace std;

const double EPS = 1e13; 

template<typename T>
class Vec4
{
	T v[4];
public:

	// Vec4(T x=T(0), T y=T(0), T z=T(0), T w=T(1))
	Vec4(T x, T y, T z, T w)
	{
		v[0] = x;
		v[1] = y;
		v[2] = z;
		v[3] = w;
	}
	T& operator[](int const &x) const
	{
		return const_cast<T&>(v[x]);
	}
	friend ostream &operator<<(ostream &os, Vec4<T> const &v4)
	{
		os << v4.v[0] << " " << v4.v[1] << " " << v4.v[2] << " " << v4.v[3];
		return os;
	}
	
};

#endif // VEC4_H