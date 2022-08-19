#ifndef D2050A98_D2A4_42BD_9FE4_832315B4365E
#define D2050A98_D2A4_42BD_9FE4_832315B4365E

#include "color.h"
#include "ray.h"

template<typename T>
class Object
{
protected:
	Color<T> c;
	T coefficiants[4]; //ambient, diffuse, specular, recursive reflection coefficient
	T shine;
public:
	virtual void draw()
	{
		c.draw();
	}
	virtual T getIntersectingT(Ray<T> const& ray)
	{
		return T(-1);
	}
	virtual Vec3<T> getNormalAt(Vec3<T> const& point) = 0;
	
	void setColor(Color<T> c)
	{
		this->c = c;
	}

	void setAmbient(T ambient)
	{
		coefficiants[0] = ambient;
	}

	void setDiffuse(T diffuse)
	{
		coefficiants[1] = diffuse;
	}

	void setSpecular(T specular)
	{
		coefficiants[2] = specular;
	}
	void setReflection(T reflection)
	{
		coefficiants[3] = reflection;
	}
	void setShine(T shine)
	{
		this->shine = shine;
	}

	T getAmbientCoef()
	{
		return coefficiants[0];
	}
	T getDiffuseCoef()
	{
		return coefficiants[1];
	}
	T getSpecularCoef()
	{
		return coefficiants[2];
	}
	T getReflectionCoef()
	{
		return coefficiants[3];
	}
	T getShininess()
	{
		return shine;
	}
	virtual Color<T> getColorAt(Vec3<T> point) const
	{
		return c;
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
