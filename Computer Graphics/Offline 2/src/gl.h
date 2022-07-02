#ifndef GL_H
#define GL_H

#include "vec3.h"
#include "mat4.h"
#include<bits/stdc++.h>
using namespace std;

class NullBuffer : public std::streambuf
{
public:
  int overflow(int c) { return c; }
} nullBuffer;

template<typename T>
class Gl
{
	std::stack<Mat4<T>> m_stack;
	ostream * stage1;
	ostream * stage2;
	ostream * stage3;
	Mat4<T> m_view,m_proj;
	
	public:
	Gl():stage1( new ostream(&nullBuffer)),
			 stage2( new ostream(&nullBuffer)),
			 stage3( new ostream(&nullBuffer))
	{
		m_stack.push(Mat4<T>::identity());
	}
	void setStage1(ostream &s)
	{
		stage1 = &s;
	}
	
	void setStage2(ostream &s)
	{
		stage2 = &s;
	}
	
	void setStage3(ostream &s)
	{
		stage3 = &s;
	}

	void lookAt(
							Vec3<T> eye,
							Vec3<T> look,
							Vec3<T> up
						)
	{
		Vec3<T> l = look-eye;
		l.normalize();
		Vec3<T> r = l.cross(up);
		r.normalize();
		Vec3<T> u = r.cross(l);
		Mat4<T> tran = Mat4<T>::translate(-eye);
		
		Mat4<T> rot = Mat4<T>(); // zero
		for(int i=0;i<3;i++)	rot[0][i] = r[i];
		for(int i=0;i<3;i++)	rot[1][i] = u[i];
		for(int i=0;i<3;i++)	rot[2][i] = -l[i];
		rot[3][3] = T(1);

		m_view = rot * tran;
		
	}

	void perspective(T fovY, T aspectRatio, T near, T far)
	{
		T fovX = fovY * aspectRatio;
		T t = near * tan(fovY*PI/T(360));
		T r = near * tan(fovX*PI/T(360));

		m_proj = Mat4<T>(); // zero matrix
		m_proj[0][0] = near/r;
		m_proj[1][1] = near/t;
		m_proj[2][2] = -(far+near)/(far-near);
		m_proj[2][3] = -T(2)*far*near/(far-near);
		m_proj[3][2] = -T(1);
	}

	void scale(Vec3<T>  &v)
	{
		m_stack.top() = m_stack.top() * Mat4<T>::scale(v);
	}
	void translate(Vec3<T> const &v)
	{
		m_stack.top() = m_stack.top() * Mat4<T>::translate(v);
	}
	void rotate(T const &angel, Vec3<T> const &axis)
	{
		m_stack.top() = m_stack.top() * Mat4<T>::rotate(angel,axis);
	}

	void push()
	{
		m_stack.push(m_stack.top());
	}
	void pop()
	{
		assert(m_stack.size()>1);
		m_stack.pop();
	}

	void triangle(Vec3<T> v[3])
	{
		for(int i=0;i<3;i++)
		{
			Vec3<T> vv = transformPoint(v[i]);
			(*stage1)<<vv<<"\n";
			vv = m_view * vv;
			(*stage2)<<vv<<"\n";
			vv = m_proj * vv;
			(*stage3)<<vv<<"\n";
			
		}
		(*stage1)<<"\n";
		(*stage2)<<"\n";
		(*stage3)<<"\n";
		
	}

	Vec3<T> transformPoint(Vec3<T> p)
	{
		return m_stack.top()*p;
	}

	
};

#endif // GL_H
