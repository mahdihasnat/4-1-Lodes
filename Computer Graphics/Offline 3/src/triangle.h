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
	virtual T getIntersectingT(Ray<T> const& ray) override
	{
		// Möller–Trumbore_intersection_algorithm
		// pseudo code from wikipedia
		// https://en.wikipedia.org/wiki/M%C3%B6ller%E2%80%93Trumbore_intersection_algorithm
		T a,f,u,vv;
		Vec3<T> edge1 = v[1] - v[0];
		Vec3<T> edge2 = v[2] - v[0];
		
		Vec3<T> h = ray.getDirection().cross(edge2);
		a = edge1.dot(h);
		if (abs(a) < EPS)
			return T(-1);    // This ray is parallel to this triangle.
		f = 1.0/a;
		Vec3<T> s = ray.getOrigin() - v[0];
		u = f * s.dot(h);
		if (u < 0.0 || u > 1.0)
			return T(-1);

		Vec3<T> q = s.cross(edge1);
		vv = f * ray.getDirection().dot(q);
		if (vv < 0.0 || u + vv > 1.0)
			return T(-1);

		// At this stage we can compute t to find out where the intersection point is on the line.
		T tMin = f * edge2.dot(q);
		if(tMin<EPS)
			return T(-1);

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
