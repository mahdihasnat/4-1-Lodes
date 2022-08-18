#ifndef A5B67414_B4F9_4255_A5C8_E3A99F99022B
#define A5B67414_B4F9_4255_A5C8_E3A99F99022B

#include "object.h"
#include "vec3.h"

template<typename T>
class GeneralQuadraticSurface: public Object<T>
{
	T v[10];
	Vec3<T> cubeReferencePoint;
	T dimension[3];
	bool isClipped(Vec3<T> const & point)
	{
		Vec3<T> tmp = point-cubeReferencePoint;
		for(int i=0;i<3;i++)
		{
			if(abs(dimension[i]) > EPS and (point[i]<0 or point[i]>dimension[i]))
			{
				return 1;
			}
		}
		return 0;
	}
	public:
	void draw()
	{

	}

	virtual T getIntersectingT(Ray<T> const& ray)
	{
		// Surface equation: Ax^2 + By^2 + Cz^2 + Dxy + Exz + Fyz + Gx + Hy + Iz = 0
		// A = v[0], B = v[1], C = v[2], D = v[3], E = v[4], F = v[5], G = v[6], H = v[7], I = v[8], J = v[9]

		// putting x = (ray.origin.x +  t * ray.direction.x)
		// putting y = (ray.origin.y +  t * ray.direction.y)
		// putting z = (ray.origin.z +  t * ray.direction.z)
		
		// A * (ray.o.x + t * ray.d.x)^2
		// +B * (ray.o.y + t * ray.d.y)^2
		// +C * (ray.o.z + t * ray.d.z)^2
		// +D * (ray.o.x + t * ray.d.x) * (ray.o.y + t * ray.d.y)
		// +E * (ray.o.x + t * ray.d.x) * (ray.o.z + t * ray.d.z)
		// +F * (ray.o.y + t * ray.d.y) * (ray.o.z + t * ray.d.z)
		// +G * (ray.o.x + t * ray.d.x)
		// +H * (ray.o.y + t * ray.d.y)
		// +I * (ray.o.z + t * ray.d.z)
		// +J = 0
		
		// this is quadratic equation with variable t: at^2 + bt + c = 0
		// where a = A *ray.d.x^2 + B * ray.d.y^2 + C * ray.d.z^2 +
		//          D * ray.d.x * ray.d.y + E * ray.d.x * ray.d.z + F * ray.d.y * ray.d.z +

		T a = v[0] *  ray.getDirection()[0] * ray.getDirection()[0] +
			  v[1] *  ray.getDirection()[1] * ray.getDirection()[1] +
			  v[2] *  ray.getDirection()[2] * ray.getDirection()[2] +
			  v[3] * (ray.getDirection()[0] * ray.getDirection()[1]) +
			  v[4] * (ray.getDirection()[0] * ray.getDirection()[2]) +
			  v[5] * (ray.getDirection()[1] * ray.getDirection()[2]);

		// b = 2 * A * ray.d.x * ray.o.x 
		// + 2 * B * ray.d.y * ray.o.y
		// + 2 * C * ray.d.z * ray.o.z
		// + D * (ray.o.x * ray.d.y + ray.o.y * ray.d.x)
		// + E * (ray.o.x * ray.d.z + ray.o.z * ray.d.x)
		// + F * (ray.o.y * ray.d.z + ray.o.z * ray.d.y)
		// + G * ray.d.x
		// + H * ray.d.y
		// + I * ray.d.z

		T b = 2 * v[0] * ray.getDirection()[0] * ray.getOrigin()[0] +
			  2 * v[1] * ray.getDirection()[1] * ray.getOrigin()[1] +
			  2 * v[2] * ray.getDirection()[2] * ray.getOrigin()[2] +
			  v[3] * (ray.getOrigin()[0] * ray.getDirection()[1] + ray.getOrigin()[1] * ray.getDirection()[0]) +
			  v[4] * (ray.getOrigin()[0] * ray.getDirection()[2] + ray.getOrigin()[2] * ray.getDirection()[0]) +
			  v[5] * (ray.getOrigin()[1] * ray.getDirection()[2] + ray.getOrigin()[2] * ray.getDirection()[1]) +
			  v[6] * ray.getDirection()[0] +
			  v[7] * ray.getDirection()[1] +
			  v[8] * ray.getDirection()[2];

		// c = A * ray.o.x^2 + B * ray.o.y^2 + C * ray.o.z^2
		// + D * ray.o.x * ray.o.y
		// + E * ray.o.x * ray.o.z
		// + F * ray.o.y * ray.o.z
		// + G * ray.o.x
		// + H * ray.o.y
		// + I * ray.o.z
		// + J 
		
		T c = v[0] * ray.getOrigin()[0] * ray.getOrigin()[0] +
			  v[1] * ray.getOrigin()[1] * ray.getOrigin()[1] +
			  v[2] * ray.getOrigin()[2] * ray.getOrigin()[2] +
			  v[3] * ray.getOrigin()[0] * ray.getOrigin()[1] +
			  v[4] * ray.getOrigin()[0] * ray.getOrigin()[2] +
			  v[5] * ray.getOrigin()[1] * ray.getOrigin()[2] +
			  v[6] * ray.getOrigin()[0] +
			  v[7] * ray.getOrigin()[1] +
			  v[8] * ray.getOrigin()[2] +
			  v[9];
		
		T tMin =T(-1);
		if(abs(a)<EPS) // a == 0
		{
			if(abs(b)<EPS) // b == 0
			{
				if(abs(c)<EPS) // c == 0
				{
					tMin = 0;
				}
				else
				{
					tMin = T(-1);
				}
			}
			else
			{
				tMin = -c/b;
				if( isClipped( ray.getPoint(tMin)) )
					tMin= T(-1);
			}
		}
		else 
		{
			T determinant = b * b - 4 * a * c;
			if(determinant<0) // imaginary solution
			{
				tMin=T(-1);
			}
			else
			{
				T t1 = (-b - sqrt(determinant)) / (2 * a);
				T t2 = (-b + sqrt(determinant)) / (2 * a);

				if(t1>t2)
					swap(t1,t2);
				if(t1>0 and !isClipped( ray.getPoint(t1) ))
				{
					tMin = t1;
				}
				else if(t2>0 and !isClipped( ray.getPoint(t2) ))
				{
					tMin = t2;
				}
			}
		}

		return tMin;
	}

	virtual Vec3<T> getNormalAt(Vec3<T> const& point, Ray<T> const & viewRay) override
	{
		// Equation:  Ax^2   +  By^2   + Cz^2    + Dxy    + Exz    + Fyz    + Gx    +  Hy   + Iz    + J    = 0
		// Equation: v[0]x^2 + v[1]y^2 + v[2]z^2 + v[3]xy + v[4]xz + v[5]yz + v[6]x + v[7]y + v[8]z + v[9] = 0
		// normal.x = (2*A, D , E) dot (point) + G
		// normal.y = (D, 2*B, F) dot (point) + H
		// normal.z = (E, F, 2*C) dot (point) + I
		Vec3<T> normal(
			Vec3<T> (2*v[0], v[3], v[4]).dot(point) + v[6],
			Vec3<T> (v[3], 2*v[1], v[5]).dot(point) + v[7],
			Vec3<T> (v[4], v[5], 2*v[2]).dot(point) + v[8]
		);
		normal.normalize();
		
		if(normal.dot(viewRay.getDirection())<0)
			normal = -normal;
		return normal;
	}
	
	virtual istream & read(istream & is)
	{
		for(int i=0;i<10;i++)
			is>>v[i];
		is>>cubeReferencePoint>>dimension[0]>>dimension[1]>>dimension[2];
		Object<T>::read(is);
		return is;
	}
	virtual ostream & write(ostream & os) const
	{
		os<<"[gqs: [v: ";
		for(int i=0;i<10;i++)
			os<<v[i]<<" ";
		os<<"] [crp: "<<cubeReferencePoint<<"] ";
		os<<"[d:";
		for(int i=0;i<3;i++)
			os<<" "<<dimension[i];
		os<<"] ";
		return Object<T>::write(os)<<" ]";
	}

};

#endif /* A5B67414_B4F9_4255_A5C8_E3A99F99022B */
