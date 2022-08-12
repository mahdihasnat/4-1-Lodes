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
		static Color<T> random(){
			return Color<T>(rand()%255,rand()%255,rand()%255);
		}
		// << operator overloading
		friend ostream &operator <<(ostream &os , Color &c)
		{
			os<<"("<<c.c[0]<<" "<<c.c[1]<<" "<<c.c[2]<<")";
			return os;
		}

		// [] operator overloading
		T & operator[](int i) const
		{
			return const_cast< T &>(c[i]);
		}

};

#endif /* COLOR_H */