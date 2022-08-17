#ifndef COLOR_H
#define COLOR_H

#include<bits/stdc++.h>
using namespace std;


template<typename T>
class Color
{
	private:
		T c[3];
	public:
		Color(T r=0,T g=0,T b=0):c{r,g,b}{
			
		}
		void draw()
		{
			assert(typeid(T) == typeid(double));
			glColor3f(c[0],c[1],c[2]);
		}
		static Color<T> random(){
			if(typeid(T) == typeid(int))
				return Color<T>(rand()%255,rand()%255,rand()%255);
			else assert(0);
		}
		void clip()
		{
			assert(typeid(T) == typeid(double));
			for(int i=0;i<3;i++)
				c[i] = max(min(c[i],T(1)),T(0));
		}
		// << operator overloading
		friend ostream &operator <<(ostream &os , Color &c)
		{
			os<<"("<<c.c[0]<<" "<<c.c[1]<<" "<<c.c[2]<<")";
			return os;
		}

		friend istream &operator >>(istream &is , Color &c)
		{
			is>>c.c[0]>>c.c[1]>>c.c[2];
			return is;
		}

		friend ostream &operator <<(ostream &os , Color const &c)
		{
			os<<"("<<c.c[0]<<" "<<c.c[1]<<" "<<c.c[2]<<")";
			return os;
		}

		// [] operator overloading
		T & operator[](int i) const
		{
			return const_cast< T &>(c[i]);
		}

		Color operator*(T const &t) const
		{
			return Color(c[0]*t,c[1]*t,c[2]*t);
		}

};

#endif /* COLOR_H */
