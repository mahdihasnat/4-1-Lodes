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

	virtual istream & read(istream & is)
	{
		for(int i=0;i<10;i++)
			is>>v[i];
		is>>cubeReferencePoint>>length>>width>>height;
		Object<T>::read(is);
		return is;
	}
	virtual ostream & write(ostream & os) const
	{
		os<<"[gqs: [v: ";
		for(int i=0;i<10;i++)
			os<<v[i]<<" ";
		os<<"] [crp: "<<cubeReferencePoint<<"] [l: "<<length<<"] [w: "<<width<<"] [h: "<<height<<"]";
		return Object<T>::write(os)<<" ]";
	}

};

#endif /* A5B67414_B4F9_4255_A5C8_E3A99F99022B */
