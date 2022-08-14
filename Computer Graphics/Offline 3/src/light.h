#ifndef CF462996_4F29_4A1C_BF80_551D39096B13
#define CF462996_4F29_4A1C_BF80_551D39096B13
#include "object.h"
#include "vec3.h"
#include "color.h"


template<typename T>
class Light
{
private:
	Vec3<T> pos;
	Color<T> color;
public:
	virtual istream & read(istream & is)
	{
		return is>>pos>>color;
	}
	virtual ostream & write(ostream & os) const
	{
		return os<<"[p: "<<pos<<"] [c: "<<color<<"]";
	}

	friend istream & operator >> (istream & is, Light<T> & l)
	{
		return l.read(is);
	}
	friend ostream & operator << (ostream & os, const Light<T> & l)
	{
		return l.write(os);
	}
};

#endif /* CF462996_4F29_4A1C_BF80_551D39096B13 */
