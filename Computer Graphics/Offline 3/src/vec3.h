#ifndef VEC3_H
#define VEC3_H
#include "vec4.h"
#include "constants.h"

#include<bits/stdc++.h>
using namespace std;

template<typename T>
class Vec3: public Vec4<T> 
{
	public:
	Vec3(T x=T(0), T y=T(0), T z=T(0)):Vec4<T>(x, y, z, T(1))
	{
		
	}
	// for ray tracing offline
	void draw()
	{
		assert(typeid(T) == typeid(double));
		glVertex3f(this->operator[](0), this->operator[](1), this->operator[](2));
	}
	T length() const
	{
		T len = T(0);
		for(int i=0;i<3;i++)
		{
			len += this->operator[](i) * this->operator[](i);
		}
		len = sqrt(len);
		return len;
	}
	void normalize()
	{
		T len = length();
		for(int i=0;i<3;i++)
		{
			this->operator[](i) /= len;
		}
	}
	T dot(Vec3<T> const & v) const
	{
		T ret = T(0);
		for(int i=0;i<3;i++)
		{
			ret += this->operator[](i) * v[i];
		}
		return ret;
	}
	Vec3<T> cross(Vec3<T> const & v) const
	{
		
		Vec3<T> ret; // (0,0,0,1)
		#ifdef X
			#error "X is defined"
		#endif

		#define X 0
		#define Y 1
		#define Z 2

		ret[X] = this->operator[](Y)*v[Z] - this->operator[](Z)*v[Y];
		ret[Y] = this->operator[](Z)*v[X] - this->operator[](X)*v[Z];
		ret[Z] = this->operator[](X)*v[Y] - this->operator[](Y)*v[X];

		#undef X
		#undef Y
		#undef Z
		return ret;
	}
	Vec3<T> rotate(T const& angel,Vec3<T> const & axis)
	{
		Vec3<T> ret; // (0,0,0,1)
		T cos_theta = cos(angel* PI / 180.0);
		ret += (*this * cos_theta);
		ret += axis * (axis.dot(*this)*(1-cos_theta));
		ret += axis.cross(*this) * sin(angel* PI / 180.0);
		
		return ret;	
	}

	Vec3<T> operator - (Vec3<T> const & v) const
	{
		Vec3<T> ret; // (0,0,0,1)
		for(int i=0;i<3;i++)
		{
			ret[i] = this->operator[](i) - v[i];
		}
		return ret;
	}
	Vec3<T> operator-()const
	{
		Vec3<T> ret; // (0,0,0,1)
		for(int i=0;i<3;i++)
		{
			ret[i] = -this->operator[](i);
		}
		return ret;
	}

	Vec3<T> operator + (Vec3<T> const & v) const
	{
		Vec3<T> ret; // (0,0,0,1)
		for(int i=0;i<3;i++)
		{
			ret[i] = this->operator[](i) + v[i];
		}
		return ret;
	}

	Vec3<T> operator *(T const & m) const
	{
		Vec3<T> ret; // (0,0,0,1)
		for(int i=0;i<3;i++)
		{
			ret[i] = this->operator[](i) * m;
		}
		return ret;
	}
	Vec3<T> &operator+=(Vec3<T> const & v)
	{
		for(int i=0;i<3;i++)
		{
			this->operator[](i) += v[i];
		}
		return *this;
	}

	Vec3<T> &operator-=(Vec3<T> const & v)
	{
		for(int i=0;i<3;i++)
		{
			this->operator[](i) -= v[i];
		}
		return *this;
	}
	
	T& operator[](int const & x) const
	{
		return Vec4<T>::operator[](x);
	}

	bool operator == (const Vec3<T> & v) const
	{
		for(int i=0;i<3;i++)
		{
			if(abs(this->operator[](i) - v[i]) > EPS)
			{
				return false;
			}
		}
		return true;
	}

	friend istream & operator >>(istream & is,Vec3<T> & v3)
	{
		is>>v3[0]>>v3[1]>>v3[2];
		v3[3]=T(1);
		return is;
	}

	friend ostream & operator <<(ostream & os,Vec3<T> const & v3)
	{
		return os<<v3[0]<<" "<<v3[1]<<" "<<v3[2];
	}
};



template<class T>
Vec3<T> rotateUnitVector(Vec3<T> const & x,
						Vec3<T> const & axis,
						double angel){
	// given x and axis perpendicular
	// rotate x by angel
	assert(x.dot(axis)  < EPS);
	Vec3<T> temp;
	double cos_a=cos(angel/180.0*PI);
	double sin_a=sin(angel/180.0*PI);	
	temp = x * cos_a + axis.cross(x) * sin_a ; //+ x.cross(axis) * (1-cos_a);
	assert( abs((temp).length()-1) < EPS);
	// temp = temp/abs(temp);
	return temp;
}

template<typename T>
void rotateUnitPlane(Vec3<T> &x,Vec3<T> &y,Vec3<T> const & z,double angel)
{
	// x * y = z
	// rotate x and y by angel
	assert(x.cross(y) ==  z);
	x = rotateUnitVector(x,z,angel);
	y = rotateUnitVector(y,z,angel);
}


#endif /* VEC3_H */
