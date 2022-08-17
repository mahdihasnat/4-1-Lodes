#ifndef D19651B0_6552_4A20_8663_D0DEA6FB1CA3
#define D19651B0_6552_4A20_8663_D0DEA6FB1CA3

#include "object.h"
#include "vec3.h"

template <class T>
T getTriangleArea(Vec3<T> const &a, Vec3<T> const &b, Vec3<T> const &c)
{
	return (b-a).cross(c-a).length() / T(2);
}

template <class T>
class Triangle: public Object<T>
{
	Vec3<T> v[3];
public:
	void draw()
	{
		glBegin(GL_TRIANGLES);
		Object<T>::draw();
		for(int i=0;i<3;i++)
		{
			v[i].draw();
		}
		glEnd();
	}
	virtual T getIntersectingT(Ray<T> const& ray)
	{

		Vec3<T> normal = (v[1]-v[0]).cross(v[2]-v[0]);
		normal.normalize();
		// T tMin = (v[0]-ray.getOrigin()).dot(normal)/ray.getDirection().dot(normal);
		T niche = ray.getDirection().dot(normal);
		if(abs(niche)<EPS)
		{
			return T(-1);
		}
		T tMin = (v[0]-ray.getOrigin()).dot(normal)/niche;
		
		Vec3<T> point = ray.getOrigin()+ray.getDirection()*tMin;
		// check if point is within triangle
		
		if( abs(
			getTriangleArea(v[0],v[1],v[2])
			-getTriangleArea(v[0],v[1],point) 
			-getTriangleArea(v[1],v[2],point) 
			-getTriangleArea(v[2],v[0],point)
			) > EPS)
			tMin = T(-1);
		return tMin;
	}
	virtual Vec3<T> getNormalAt(Vec3<T> const& point, Ray<T> const & viewRay) override
	{
		Vec3<T> normal = (v[1]-v[0]).cross(v[2]-v[0]);
		normal.normalize();
		if(viewRay.getDirection().dot(normal)<0)
			normal = -normal;
		return normal;
	}

	virtual T intersect(Ray<T> const& ray, Color<T> &color, int level)
	{
		return T(-1); // TODO: remove later
		T tMin = getIntersectingT(ray);

		if(level == 0)
			return tMin;
		
		DBG("Not implemented");
		assert(0);
		return T(-1);
	}

	virtual istream & read(istream & is)
	{
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
