const double EPS = 1e13;
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

// pair<double, double > linear2(
// 	double a1, double b1,double c1
// 	,double a2, double b2,double c2)
// {
// 	cout<<"linear 2 "<<a1<<" "<<b1<<" "<<c1<<" "<<a2<<" "<<b2<<" "<<c2<<endl;
	
// 	double x,y;
// 	double d=a1*b2-a2*b1;
// 	assert( abs(d)> EPS);
// 	x=(c1*b2-c2*b1)/d;
// 	y=(a1*c2-a2*c1)/d;
// 	return make_pair(x,y);
// }

point rotateUnitVector(point const & x,
						point const & axis,
						double angel){
	// given x and axis perpendicular
	// rotate x by angel
	assert(x.dot(axis)  < EPS);
	point temp;
	double cos_a=cos(angel);
	double sin_a=sin(angel);	
	temp = x * cos_a + axis.cross(x) * sin_a ; //+ x.cross(axis) * (1-cos_a);
	assert( abs(abs(temp)-1) < EPS);
	// temp = temp/abs(temp);
	return temp;
}

void rotateUnitPlane(point &x,point &y,point const & z,double angel)
{
	// x * y = z
	// rotate x and y by angel
	assert(x.cross(y) ==  z);
	x = rotateUnitVector(x,z,angel);
	y = rotateUnitVector(y,z,angel);
}