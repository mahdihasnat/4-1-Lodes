#ifndef D2050A98_D2A4_42BD_9FE4_832315B4365E
#define D2050A98_D2A4_42BD_9FE4_832315B4365E

#include "color.h"

template<typename T>
class Object
{
protected:
	Color<T> c;
	T coefficiants[4];
	int shine;
public:
	virtual void draw() = 0;
	virtual istream & read(istream & is)
	{
		cerr<<"here im in object"<<endl;
		is>>c;
		is>>coefficiants[0]>>coefficiants[1]>>coefficiants[2]>>coefficiants[3];
		is>>shine;
		return is;
	}
	friend istream &operator>>(istream &is, Object &o)
	{
		cerr<<"here im in object"<<endl;
		is>>o.c;
		is>>o.coefficiants[0]>>o.coefficiants[1]>>o.coefficiants[2]>>o.coefficiants[3];
		is>>o.shine;
		return is;
	}
	friend ostream &operator<<(ostream &os, Object const &o)
	{
		os<<"[o: [color:"<<o.c<<"] [coeff:"<<o.coefficiants[0]<<" "<<o.coefficiants[1]
		<<" "<<o.coefficiants[2]<<" "<<o.coefficiants[3]<<"] [shine:"<<o.shine<<"] ]";
		return os;
	}
};


#endif /* D2050A98_D2A4_42BD_9FE4_832315B4365E */
