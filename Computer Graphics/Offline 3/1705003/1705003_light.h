#ifndef CF462996_4F29_4A1C_BF80_551D39096B13
#define CF462996_4F29_4A1C_BF80_551D39096B13
#include "1705003_object.h"
#include "1705003_vec3.h"
#include "1705003_color.h"


template<typename T>
class Light
{
protected:
	Vec3<T> position;
	Color<T> color;
public:
	virtual bool isReachable(Vec3<T> const& point) = 0;
	Vec3<T> getPosition()
	{
		return position;
	}
	Color<T> getColor()
	{
		return color;
	}
	void setPosition(Vec3<T> position)
	{
		this->position = position;
	}
	void setColor(Color<T> color)
	{
		this->color = color;
	}
	virtual istream & read(istream & is)
	{
		return is>>position>>color;
	}
	virtual ostream & write(ostream & os) const
	{
		return os<<"[p: "<<position<<"] [c: "<<color<<"]";
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
