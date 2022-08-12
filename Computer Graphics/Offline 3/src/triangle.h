#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "vec3.h"
#include "color.h"

template<class T>
class Triangle
{
	Vec3<T> v[3];
public:
	Color<int> c;
	Triangle(Vec3<T> v[3],Color<int> c):c(c){
		for(int i=0;i<3;i++){
			this->v[i] = v[i];
		}
	}
	T min(int i) const
	{
		T ret = v[0][i];
		if(v[1][i]<ret)
			ret = v[1][i];
		if(v[2][i]<ret)
			ret = v[2][i];
		return ret;
	}

	T max(int i) const
	{
		T ret = v[0][i];
		if(v[1][i]>ret)
			ret = v[1][i];
		if(v[2][i]>ret)
			ret = v[2][i];
		return ret;
	}

	Vec3<T> & operator[](int i) const
	{
		return const_cast< Vec3<T> &>(v[i]);
	}
	
	friend ostream &operator <<(ostream &os , Triangle<T> &t)
	{
		os<<"Triangle: "<<"\n";
		for(int i=0;i<3;i++)
			os<<t.v[i]<<"\n";
		os<<"Color: "<<t.c<<"\n";
		return os;
	}

};

#endif /* TRIANGLE_H */
