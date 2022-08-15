#ifndef AC7C476B_76ED_4768_9979_014D5E7C094E
#define AC7C476B_76ED_4768_9979_014D5E7C094E
#include "common.h"

class point
{
	public:
	double x,y,z;
	
	point operator + (const point &p) const
	{
		point temp;
		temp.x=x+p.x;
		temp.y=y+p.y;
		temp.z=z+p.z;
		return temp;
	}
	point operator - (const point &p) const
	{
		point temp;
		temp.x=x-p.x;
		temp.y=y-p.y;
		temp.z=z-p.z;
		return temp;
	}
	point &operator+= (const point &p)
	{
		x+=p.x;
		y+=p.y;
		z+=p.z;
		return *this;
	}
	point operator * (const double &p) const
	{
		point temp;
		temp.x=x*p;
		temp.y=y*p;
		temp.z=z*p;
		return temp;
	}
	point operator / (const double &p) const
	{
		point temp;
		temp.x=x/p;
		temp.y=y/p;
		temp.z=z/p;
		return temp;
	}
	point cross (const point &p) const
	{
		point temp;
		temp.x=y*p.z-z*p.y;
		temp.y=z*p.x-x*p.z;
		temp.z=x*p.y-y*p.x;
		return temp;
	}
	bool operator ==( point const & p) const
	{
		return abs(x-p.x)<EPS 
				&& abs(y-p.y)<EPS
				 && abs(z-p.z)<EPS;
	}
	double dot(const point &p) const
	{
		return x*p.x+y*p.y+z*p.z;
	}
};


ostream & operator<<(ostream &os,const point &p)
{
	os<<"("<<fixed<<setprecision(3)<<p.x<<","<<p.y<<","<<p.z<<")";
	return os;
}
double abs(point const &p)
{
	return sqrt(p.x*p.x+p.y*p.y+p.z*p.z);
}

#endif /* AC7C476B_76ED_4768_9979_014D5E7C094E */
