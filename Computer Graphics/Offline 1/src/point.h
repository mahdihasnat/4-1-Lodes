const double EPS = 1e13;
class point
{
	public:
	double x,y,z;
	
	point operator + (const point &p)
	{
		point temp;
		temp.x=x+p.x;
		temp.y=y+p.y;
		temp.z=z+p.z;
		return temp;
	}
	point &operator+= (const point &p)
	{
		x+=p.x;
		y+=p.y;
		z+=p.z;
		return *this;
	}
	point operator * (const double &p)
	{
		point temp;
		temp.x=x*p;
		temp.y=y*p;
		temp.z=z*p;
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
};


ostream & operator<<(ostream &os,const point &p)
{
	os<<"("<<p.x<<","<<p.y<<","<<p.z<<")";
	return os;
}
double abs(point const &p)
{
	return sqrt(p.x*p.x+p.y*p.y+p.z*p.z);
}

pair<double, double > linear2(
	double a1, double b1,double c1
	,double a2, double b2,double c2)
{
	cout<<"linear 2 "<<a1<<" "<<b1<<" "<<c1<<" "<<a2<<" "<<b2<<" "<<c2<<endl;
	
	double x,y;
	double d=a1*b2-a2*b1;
	assert( abs(d)> EPS);
	x=(c1*b2-c2*b1)/d;
	y=(a1*c2-a2*c1)/d;
	return make_pair(x,y);
}

point rotateUnitVector(point const & x,
						point const & axis,
						double angel){
	// given x and axis perpendicular
	// rotate x by angel
	DBG(x);
	DBG(axis);
	NL;
	point temp;
	double cos_a=cos(angel);
	double sin_a=sin(angel);
	auto tmp2 = linear2(
		x.y + x.z * axis.z/axis.y , x.z *axis.x / axis.y , axis.x * sin_a
		,-x.x , x.z , axis.y * sin_a
	  );
	temp.z = tmp2.first;
	temp.x = tmp2.second;
	temp.y = - (temp.x*axis.x +temp.z * axis.z)/axis.y;
	assert( abs(abs(temp)-1) < EPS);
	return temp;
}

void rotateUnitPlane(point &x,point &y,point const & z,double angel)
{
	// x * y = z
	// rotate x and y by angel
	DBG(x);
	DBG(y);
	DBG(z);
	DBG(angel);
	NL;
	x = rotateUnitVector(x,z,angel);
	y = rotateUnitVector(y,z,angel);
}