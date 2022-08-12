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
	friend istream operator>>(istream &is, Object &o)
	{
		is>>o.c;
		is>>o.coefficiants[0]>>o.coefficiants[1]>>o.coefficiants[2]>>o.coefficiants[3];
		is>>o.shine;
		return is;
	}
};


#endif /* D2050A98_D2A4_42BD_9FE4_832315B4365E */
