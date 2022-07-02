#ifndef MAT4_H
#define MAT4_H

#include "vec3.h"

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
				m[i][j] = T(0);
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
	
	static Mat4 translate(Vec3<T> const& v)
	{
		Mat4<T> ret = identity();
		ret[0][3] = v[0];
		ret[1][3] = v[1];
		ret[2][3] = v[2];
		return ret;
	}

	static Mat4 scale(Vec3<T> &v)
	{
		Mat4<T> ret ; // zero
		ret[0][0] = v[0];
		ret[1][1] = v[1];
		ret[2][2] = v[2];
		ret[3][3] = T(1);
		return ret;
	}

	static Mat4 rotate(T const & angel, Vec3<T> const & axis)
	{
		Mat4<T> ret; // zero
		Vec3<T> a = axis;
		a.normalize();

		ret[3][3] = T(1);
		for(int i=0;i<3;i++)
		{
			Vec3<T> unit; // (0,0,0,1)
			unit[i]=T(1);
			Vec3<T> rotated = unit.rotate(angel,a);
			for(int j=0;j<3;j++)
				ret[j][i] = rotated[j];
		}
		return ret;
	}


	
	T * operator [](int const & x) const
	{
		return const_cast<T*>(m[x]);
	}

	Mat4 operator*(Mat4 const& rhs) const
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
	
	Vec3<T> operator *(Vec3<T> const& vec3) const
	{
		Vec3<T> ret; // (0,0,0,1)
		ret[3]=0;
		for(int i=0;i<4;i++)
		{
			for(int j=0;j<4;j++)
			{
				ret[i] += m[i][j]*(vec3[j]);
			}
		}
		for(int i=0;i<3;i++)
			ret[i]/=ret[3];
		ret[3]=T(1);
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
		os<<"\n";
		for(int i=0;i<4;i++){
			for(int j=0;j<4;j++)
				os<<m4.m[i][j]<<" ";
			os<<"\n";
		}
		return os;
	}


};

#endif /* MAT4_H */
