#ifndef VEC4_H
#define VEC4_H

const double EPS = 1e13; 

template<typename T>
class Vec4
{
	T v[4];
public:
	Vec4(T x, T y, T z, T w)
	{
		v[0] = x;
		v[1] = y;
		v[2] = z;
		v[3] = w;
	}
};

#endif // VEC4_H