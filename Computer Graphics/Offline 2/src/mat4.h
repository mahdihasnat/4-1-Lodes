#ifndef MAT4_H
#define MAT4_H

#include<bits/stdc++.h>
using namespace std;
template<typename T>
class Mat4
{
	T m[4][4];
	public:
	/*
		Zero matrix
	*/
	Mat4()
	{
		for(int i=0;i<4;i++)
		{
			for(int j=0;j<4;j++)
			{
				m[i][j] = 0;
			}
		}
	}
	/*
		Identity matrix
	*/
	static Mat4 identity()
	{
		Mat4<T> ret; // zero matrix
		for(int i=0;i<4;i++)
		{
			ret[i][i]=1;
		}
		return ret;
	}
	
	T * operator [](int const & x)
	{
		return m[x];
	}

	Mat4 operator*(const Mat4& rhs) const
	{
		Mat4 ret; // zero matrix
		for(int i=0;i<4;i++)
		{
			for(int j=0;j<4;j++)
			{
				for(int k=0;k<4;k++)
				{
					ret[i][j] += m[i][k]*rhs[k][j];
				}
			}
		}
		return ret;
	}
	Vec3<T> operator *(Vec3<T> & vec3)
	{
		Vec3<T> ret;
		for(int i=0;i<3;i++)
		{
			for(int j=0;j<3;j++)
			{
				ret[i] += m[i][j]*(vec3[j]);
			}
		}
		return ret;
	}



	void to_3x3(ostream &os)
	{
		for(int i=0;i<3;i++)
		{
			for(int j=0;j<3;j++)
			{
				os<<m[i][j]<<" ";
			}
			os<<"\n";
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
