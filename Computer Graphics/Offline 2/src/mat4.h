#ifndef MAT4_H
#define MAT4_H

#include<bits/stdc++.h>
using namespace std;
template<typename T>
class Mat4
{
	T m[4][4];
	public:
	Mat4()
	{
		for(int i=0;i<4;i++)
		{
			for(int j=0;j<4;j++)
			{
				m[i][j] = 0;
			}
			m[i][i]=T(1);
		}
	}

	friend ostream & operator <<(ostream & os,Mat4 const & m4)
	{
		for(int i=0;i<4;i++){
			for(int j=0;j<4;j++)
				os<<m4.m[i][j]<<" ";
			os<<"\n";
		}
		return os;
	}

};

#endif /* MAT4_H */
