#ifndef D46B3C26_2DFF_4FE7_8F21_2ECB686E278C
#define D46B3C26_2DFF_4FE7_8F21_2ECB686E278C

#include "vec3.h"

template<typename T>
class Ray
{
	Vec3<T> origin;
	Vec3<T> direction;
public:
	Ray(){}
	Ray(Vec3<T> origin, Vec3<T> direction):origin(origin),direction(direction)
	{
		this->direction.normalize();
	}
	void setOrigin(Vec3<T> const & o)
	{
		origin = o;
	}
	void setDirection(Vec3<T> const & d)
	{
		direction = d;
		direction.normalize();
	}
	Vec3<T> getOrigin() const
	{
		return origin;
	}
	Vec3<T> getDirection() const
	{
		return direction;
	}
	Vec3<T> getPoint(T t) const
	{
		return origin + direction * t;
	}
};

#endif /* D46B3C26_2DFF_4FE7_8F21_2ECB686E278C */
