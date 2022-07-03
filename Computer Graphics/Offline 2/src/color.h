#ifndef COLOR_H
#define COLOR_H

#include<bits/stdc++.h>
using namespace std;

class Color
{
	private:
		int c[3];
	public:
		Color(int r=0,int g=0,int b=0):c{r,g,b}{
			
		}
		static Color red(){
			return Color(255,0,0);
		}
		static Color green(){
			return Color(0,255,0);
		}
		static Color blue(){
			return Color(0,0,255);
		}
		static Color black(){
			return Color(0,0,0);
		}
		static Color white(){
			return Color(255,255,255);
		}
		static Color random(){
			return Color(rand()%255,rand()%255,rand()%255);
		}
};

#endif /* COLOR_H */
