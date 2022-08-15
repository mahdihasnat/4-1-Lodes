#ifndef D2050A98_D2A4_42BD_9FE4_832315B4365E
#define D2050A98_D2A4_42BD_9FE4_832315B4365E

#include "color.h"
#include "ray.h"

template<typename T>
class Object
{
protected:
	Color<T> c;
	T coefficiants[4];
	int shine;
public:
	virtual void draw()
	{
		c.draw();
	}
	virtual T intersect(Ray<T> const& ray, Color<T> &color, int level)
	{
		return T(-1);
	}
	virtual istream & read(istream & is)
	{
		// cerr<<"here im in object"<<endl;
		is>>c;
		is>>coefficiants[0]>>coefficiants[1]>>coefficiants[2]>>coefficiants[3];
		is>>shine;
		return is;
	}
	virtual ostream & write(ostream & os) const
	{
		os<<"[color:"<<c<<"] [coeff:"<<coefficiants[0]<<" "<<coefficiants[1]
		<<" "<<coefficiants[2]<<" "<<coefficiants[3]<<"] [shine:"<<shine<<"]";
		return os;
	}
	friend istream &operator>>(istream &is, Object &o)
	{
		return o.read(is);
	}
	friend ostream &operator<<(ostream &os, Object const &o)
	{
		return o.write(os);
	}
};


#endif /* D2050A98_D2A4_42BD_9FE4_832315B4365E */
