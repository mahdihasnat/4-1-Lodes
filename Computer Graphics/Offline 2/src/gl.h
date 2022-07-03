#ifndef GL_H
#define GL_H

#include "vec3.h"
#include "mat4.h"
#include "triangle.h"

#include "bitmap_image.hpp"

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
	ostream * z_out;
	Mat4<T> m_view,m_proj;
	vector<Triangle<T>> m_triangles;

	public:
	Gl():stage1( new ostream(&nullBuffer)),
			 stage2( new ostream(&nullBuffer)),
			 stage3( new ostream(&nullBuffer)),
			 z_out( new ostream(&nullBuffer))
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

	void setZOut(ostream &s)
	{
		z_out = &s;
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
			v[i] = transformPoint(v[i]);
			(*stage1)<<v[i]<<"\n";
			v[i] = m_view * v[i];
			(*stage2)<<v[i]<<"\n";
			v[i] = m_proj * v[i];
			(*stage3)<<v[i]<<"\n";
		}
		(*stage1)<<"\n";
		(*stage2)<<"\n";
		(*stage3)<<"\n";
		m_triangles.push_back(Triangle<T>(v,Color::random()));
	}

	Vec3<T> transformPoint(Vec3<T> p)
	{
		return m_stack.top()*p;
	}
	
	void draw(int screen_width, 
				int screen_height,
				Vec3<T> mn,
				Vec3<T> mx,
				string output_file_name
				)
	{
		
		T dx = (mx[0]-mn[0])/T(screen_width);
		T dy = (mx[1]-mn[1])/T(screen_height);
		
		T top_y = mx[1] - dy/2;
		T left_x = mn[0] + dx/2;

		// init z-buffer
		vector< vector<T> > z_values(screen_width,vector<T>(screen_height,mx[2]));
		bitmap_image image(screen_width,screen_height);

		for(int i=0;i<screen_width;i++)
		{
			for(int j=0;j<screen_height;j++)
			{
				// init color as black
				image.set_pixel(i,j,0,0,0);
			}
		}


		for(Triangle<T> const&t:m_triangles)
		{
			// bool baire = 0;
			// for(int i=0;i<3;i++)
			// 	baire = baire or (t.min(i)>mx[i] or t.max(i)<mn[i]);
			// if(baire) continue;

			// calculating normal of triangle
			Vec3<T> n = (t[1]-t[0]).cross(t[2]-t[0]);
			Vec3<T> p = t[0];

			// calculating coefficient of equation ax+by+cz+d=0;
			T a = n[0], b = n[1], c = n[2], d = -n.dot(p);

			// t.min(1) <=  top_y - i*dy <= t.max(1)
			int top_scanline = ceil((top_y - t.max(1))/dy);
			int bottom_scanline = floor(top_y - t.min(1)/dy);
			top_scanline = max(0,top_scanline);
			bottom_scanline = min(screen_height-1,bottom_scanline);

			
			T y_val = top_y - top_scanline*dy;
			for(
				int row = top_scanline;
				row<=bottom_scanline;
				row++,y_val -=dy
				)
			{
				// if there is a 3d point inside triangle with y = y_val and minimize/maximize value of x
				// then that point should lie on border of triangles

				vector<T> x_values;
				Vec3<T> point = t[0];
				Vec3<T> vec = t[1]-t[0];
				{
					vec.normalize();
					// point + a * vec  lies inside segment
					// now point.y + a * vec.y == y_val
					T a = (y_val - point[1])/vec[1];
					if(a>=T(0) and a<=T(1))
						x_values.push_back(point[0]+a*vec[0]);
				}

				vec = t[2]-t[0];
				{
					vec.normalize();
					T a = (y_val - point[1])/vec[1];
					if(a>=T(0) and a<=T(1))
						x_values.push_back(point[0]+a*vec[0]);
				}
				
				point = t[1];
				vec = t[2]-t[1];
				{
					vec.normalize();
					// if(abs(vec[1]) < EPS) continue; 
					T a = (y_val - point[1])/vec[1];
					if(a>=T(0) and a<=T(1))
						x_values.push_back(point[0]+a*vec[0]);
				}
				assert(x_values.size());
				if(x_values.empty()) continue;
				sort(x_values.begin(),x_values.end());



				// x_min <= left_x + i * dx <= x_max
				int left_intersecting_col = ceil((*x_values.begin() - left_x)/dx);
				int right_intersecting_col = floor(*x_values.end() - left_x/dx);
				left_intersecting_col = max(0,left_intersecting_col);
				right_intersecting_col = min(screen_width-1,right_intersecting_col);
				
				T x_val = left_x + left_intersecting_col*dx;
				T z_value = - (a*x_val + d)/c;
				T z_incr = -a*dx/c;
				for(
					int col=left_intersecting_col;
					col<=right_intersecting_col ; 
					col++,z_value += z_incr
					// ,x_val += dx
					)
				{
					// Calculate z value from triangle t
					if(z_values[col][row] < z_value) continue;
					if(z_value<mn[2] ) continue;
					image.set_pixel(col,row,t.c[0],t.c[1],t.c[2]);
				}

				
			}


		}
		for(int i=0;i<screen_height;i++)
		{
			for(int j=0;j<screen_width;j++)
			{
				(*z_out)<<z_values[j][i]<<" ";
			}
			(*z_out)<<"\n";
		}

		image.save_image(output_file_name);
	}
	
};

#endif // GL_H
