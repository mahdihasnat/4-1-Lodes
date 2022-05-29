
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

};
ostream & operator<<(ostream &os,const point &p)
{
	os<<"("<<p.x<<","<<p.y<<","<<p.z<<")";
	return os;
}