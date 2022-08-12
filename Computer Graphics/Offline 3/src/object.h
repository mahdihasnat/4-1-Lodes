#ifndef D2050A98_D2A4_42BD_9FE4_832315B4365E
#define D2050A98_D2A4_42BD_9FE4_832315B4365E

#include "color.h"

template<typename T>
class Object
{
	protected:
	Color<int> c;
	T coefficiants[4];
	
	public:
	virtual void draw() = 0;

};


#endif /* D2050A98_D2A4_42BD_9FE4_832315B4365E */
