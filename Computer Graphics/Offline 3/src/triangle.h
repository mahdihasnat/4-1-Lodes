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
	virtual istream & read(istream & is)
	{
		cerr<<"here im in triangle"<<endl;
		is>>v[0]>>v[1]>>v[2];
		Object<T>::read(is);
		return is;
	}
	virtual ostream & write(ostream & os) const
	{
		os<<"[t: [v: "<<v[0]<<" "<<v[1]<<" "<<v[2]<<"]";
		return Object<T>::write(os)<<" ]";
	}
};
#endif /* D19651B0_6552_4A20_8663_D0DEA6FB1CA3 */
