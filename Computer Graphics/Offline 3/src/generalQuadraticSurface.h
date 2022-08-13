#ifndef A5B67414_B4F9_4255_A5C8_E3A99F99022B
#define A5B67414_B4F9_4255_A5C8_E3A99F99022B

#include "object.h"
#include "vec3.h"

template<typename T>
class GeneralQuadraticSurface: public Object<T>
{
	T v[10];
	Vec3<T> cubeReferencePoint;
	T length,width,height;
	public:
	void draw()
	{

	}
	friend istream & operator >> (istream & is, GeneralQuadraticSurface & s)
	{
		for(int i=0;i<10;i++)
			is>>s.v[i];
		is>>s.cubeReferencePoint>>s.length>>s.width>>s.height;
		is>>(Object<T>&)s;
		return is;
	}
	friend ostream & operator << (ostream & os, const GeneralQuadraticSurface & s)
	{
		os<<"[gqs: [v: ";
		for(int i=0;i<10;i++)
			os<<s.v[i]<<" ";
		os<<"] [crp: "<<s.cubeReferencePoint<<"] [l: "<<s.length<<"] [w: "<<s.width<<"] [h: "<<s.height<<"]";
		os<<(Object<T> const&)s;
		os<<" ]";
		return os;
	}

};

#endif /* A5B67414_B4F9_4255_A5C8_E3A99F99022B */
