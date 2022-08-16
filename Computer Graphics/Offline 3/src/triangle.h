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
		glBegin(GL_TRIANGLES);
		Object<T>::draw();
		for(int i=0;i<3;i++)
		{
			v[i].draw();
		}
		glEnd();
	}

	virtual T intersect(Ray<T> const& ray, Color<T> &color, int level)
	{
		Vec3<T> normal = (v[1]-v[0]).cross(v[2]-v[0]);
		T tMin = (v[0]-ray.getOrigin()).dot(normal)/ray.getDirection().dot(normal);

		Vec3<T> point = ray.getOrigin()+ray.getDirection()*tMin;
		// check if point is withing triangle
		Vec3<T> mn = v[0];
		Vec3<T> mx = v[0];
		for(int i=1;i<3;i++)
		{
			for(int j=0;j<3;j++)
				mn[j]=min(mn[j],v[i][j]),
				mx[j]=max(mx[j],v[i][j]);
		}
		bool withinTriangle = true;
		for(int i=0;i<3;i++)
		{
			withinTriangle = withinTriangle and ((mn[i]<=point[i]) and (point[i]<=mx[i]));
		}
		if(withinTriangle)
		{
			// assert(0);
		}
		if(!withinTriangle)
			tMin = T(-1);
		

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
