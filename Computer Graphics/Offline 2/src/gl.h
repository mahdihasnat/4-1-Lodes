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
	public:
	Gl():stage1( new ostream(&nullBuffer))
	{
		m_stack.push(Mat4<T>::identity());
	}
	void setStage1(ostream &s)
	{
		stage1 = &s;
	}
	void lookAt(
							Vec3<T> eye,
							Vec3<T> look,
							Vec3<T> up
						)
	{
		
	}

	void perspective(T fovY, T aspectRatio, T near, T far)
	{
		
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

	Vec3<T> transformPoint(Vec3<T> p)
	{
		return m_stack.top()*p;
	}

	
};

#endif // GL_H
