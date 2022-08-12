#ifndef D19651B0_6552_4A20_8663_D0DEA6FB1CA3
#define D19651B0_6552_4A20_8663_D0DEA6FB1CA3

#include "object.h"
#include "vec3.h"
template <class T>
class Triangle: public Object<T>
{
	Vec3<T> v[3];
public:
	void draw()
	{

	}

	friend istream &operator >>(istream & is, Triangle & t)
	{
		is>>t.v[0]>>t.v[1]>>t.v[2];
		cerr<<" here im in triangle"<<endl;
		// call the base class's operator >>
		is >> (Object<T>&)t;
		return is;
	}
	friend ostream &operator<<(ostream &os, Triangle const &t)
	{
		os<<"[t: "<<t.v[0]<<" "<<t.v[1]<<" "<<t.v[2]<<"]";
		os<<(Object<T> const &)t;
		return os;
	}
};
#endif /* D19651B0_6552_4A20_8663_D0DEA6FB1CA3 */
