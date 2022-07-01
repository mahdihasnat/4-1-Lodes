#ifndef GL_H
#define GL_H

#include "vec3.h"
#include "mat4.h"
#include<stack>

template<typename T>
class Gl
{
	std::stack<Mat4<T>> m_stack;
	public:
	Gl()
	{

	}
	void lookAt(
							Vec3<T> eye,
							Vec3<T> look,
							Vec3<T> up
						)
	{
		
	}
	
};

#endif // GL_H
