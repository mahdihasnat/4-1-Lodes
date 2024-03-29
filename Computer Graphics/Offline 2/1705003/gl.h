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

ostream nullStream(&nullBuffer);

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
	Gl():stage1( & nullStream),
			 stage2( & nullStream),
			 stage3( &nullStream),
			 z_out( &nullStream)
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

	void setTriangles(ifstream & is)
	{
		m_triangles.clear();
		Vec3<T> v[3];
		while(is>>v[0])
		{
			for(int i=1;i<3;i++)
				is>>v[i];
			m_triangles.push_back(Triangle<T>(v,Color::random()));
		}
	}

	void draw_method1(
		int screen_width, 
		int screen_height,
		Vec3<T> mn,
		Vec3<T> mx,
		T dx,
		T dy,
		T top_y,
		T left_x,
		vector<vector<T> > &z_values,
		bitmap_image & image,
		Triangle<T> const& t
		)
	{
		// calculating normal of triangle
		Vec3<T> p = t[0];
		Vec3<T> n = (t[1]-t[0]).cross(t[2]-t[0]);

		// calculating coefficient of equation ax+by+cz+d=0;
		T a = n[0], b = n[1], c = n[2], d = -n.dot(p);

		// t.min(1) <=  top_y - i*dy <= t.max(1)
		int top_scanline = ceil((top_y - t.max(1))/dy);
		int bottom_scanline = floor((top_y - t.min(1))/dy);
		
		top_scanline = max(0,top_scanline);
		bottom_scanline = min(screen_height-1,bottom_scanline);

		// DBG(t.max(1));
		// DBG(t.min(1));
		// DBG(top_scanline);
		// DBG(bottom_scanline);
		
		T y_val = top_y - top_scanline*dy;
		for(
			int row = top_scanline;
			row<=bottom_scanline;
			row++,y_val -=dy
			)
		{
			
			assert(y_val<=t.max(1));
			assert(t.min(1)<=y_val);
			// if there is a 3d point inside triangle with y = y_val and minimize/maximize value of x
			// then that point should lie on border of triangles

			vector<T> x_values;
			Vec3<T> point = t[0];
			Vec3<T> vec = t[1]-t[0];
			{
				// vec.normalize();
				// point + a * vec  lies inside segment
				// now point.y + a * vec.y == y_val
				T a = (y_val - point[1])/vec[1];
				if(a>=T(0) and a<=T(1))
					x_values.push_back(point[0]+a*vec[0]);
			}

			vec = t[2]-t[0];
			{
				// vec.normalize();
				T a = (y_val - point[1])/vec[1];
				if(a>=T(0) and a<=T(1))
					x_values.push_back(point[0]+a*vec[0]);
			}
			
			point = t[1];
			vec = t[2]-t[1];
			{
				// vec.normalize();
				T a = (y_val - point[1])/vec[1];
				if(a>=T(0) and a<=T(1))
					x_values.push_back(point[0]+a*vec[0]);
			}
			assert(x_values.size());
			if(x_values.empty()) continue;

			// DBG(x_values.size());
			// for(auto i: x_values)
			// {
			// 	cerr<<i<<" ";
			// }
			// NL;
			
			sort(x_values.begin(),x_values.end());
			// DBG(dx);
			// DBG(dy);

			// x_min <= left_x + i * dx <= x_max
			int left_intersecting_col = ceil((*x_values.begin() - left_x)/dx);
			int right_intersecting_col = floor((*x_values.rbegin() - left_x)/dx); // dont use end() for last value
			left_intersecting_col = max(0,left_intersecting_col);
			right_intersecting_col = min(screen_width-1,right_intersecting_col);
			
			// DBG(left_intersecting_col);
			// DBG(right_intersecting_col);

			T x_val = left_x + left_intersecting_col*dx;
			T z_value = - (a*x_val + d+b*y_val)/c;
			T z_incr = -a*dx/c;
			for(
				int col=left_intersecting_col;
				col<=right_intersecting_col ; 
				col++,z_value += z_incr
				,x_val += dx
				)
			{
				//checking if x_value are in range
				assert(x_val<=*x_values.rbegin());
				assert(*x_values.begin()<=x_val);

				// Calculate z value from triangle t
				if(z_values[col][row] <= z_value) continue;
				if(z_value<mn[2] ) continue;
				image.set_pixel(col,row,t.c[0],t.c[1],t.c[2]);
				z_values[col][row] = z_value;
			}
		}
	}
	


	void draw_method2(
		int screen_width, 
		int screen_height,
		Vec3<T> mn,
		Vec3<T> mx,
		T dx,
		T dy,
		T top_y,
		T left_x,
		vector<vector<T> > &z_values,
		bitmap_image & image,
		Triangle<T> const& t
		)
	{
		// y = top_y - i*dy , 0<=i < screen_height
		// x = left_x + i*dx , 0<=i < screen_width
		int top_scanline = max(0,(int)(ceil((top_y-t.max(1))/dy)) );
		int bottom_scanline = min(screen_height-1, (int)(floor((top_y-t.min(1))/dy)));
		T ys = top_y - top_scanline*dy;
		for(
			int row = top_scanline;
			row<=bottom_scanline;
			row++, ys-=dy
			)
		{
			//      t[0]
			//      / \
			//     /   \
			//    /     \
			// t[1]      \
			//    .       \
			//      .      \
			//         .    \
			//           . t[2]
			// 

			bool in[3] ;
			int tot=0;
			for(int i=0;i<3;i++)
			{
				T y1 = t[i][1];
				T y2 = t[(i+1)%3][1];
				in[i] = min(y1,y2)<=ys and ys<=max(y1,y2);
				tot+=in[i];
			}
			assert(tot==2);
			
			// line1           line2        intersection  other two
			// line[0 -> 1] & line[1 -> 2] -> p1 = 1 , (p2,p3) = (0,2)
			// line[0 -> 1] & line[2 -> 0] -> p1 = 0 , (p2,p3) = (1,2)
			// line[1 -> 2] & line[2 -> 0] -> p1 = 2 , (p2,p3) = (0,1)
			int intersec = -1;
			for(int i=0;i<3;i++)
			{
				if(in[i] and in[(i-1+3)%3])
				{
					intersec = i;
				}
			}
			int other_1 = (intersec+1)%3;
			int other_2 = (intersec+2)%3;

			T x_a = t[intersec][0] + (ys-t[intersec][1])*
								(t[other_1][0]-t[intersec][0])/
								(t[other_1][1]-t[intersec][1]);
			T x_b = t[intersec][0] + (ys-t[intersec][1])*
								(t[other_2][0]-t[intersec][0])/
								(t[other_2][1]-t[intersec][1]);
			T z_a = t[intersec][2] + (ys-t[intersec][1])*
								(t[other_1][2]-t[intersec][2])/
								(t[other_1][1]-t[intersec][1]);
			T z_b = t[intersec][2] + (ys-t[intersec][1])*
								(t[other_2][2]-t[intersec][2])/
								(t[other_2][1]-t[intersec][1]);
			if(x_a > x_b)
			{
				swap(x_a,x_b);
				swap(z_a,z_b);
				swap(other_1,other_2);
			}

			assert(x_a <= x_b);

			// left_x + i * dy = x
			int left_intersecting_column = max(
					0,
					(int) ceil( (x_a - left_x)/dx )
				);
			int right_intersecting_column = min(
					screen_width-1,
					(int) floor( (x_b - left_x)/dx )
				);
			
			T x_p = left_x + left_intersecting_column*dx;
			T z_p = z_a + (x_p - x_a)*(z_b-z_a)/(x_b-x_a);
			T dz = dx*(z_b-z_a)/(x_b-x_a);
			for(
				int column = left_intersecting_column;
				column<=right_intersecting_column;
				column++,
				x_p+=dx,
				z_p+=dz
				)
			{
				assert(x_p >= x_a);
				assert(x_p <= x_b);
				if(z_values[column][row] <= z_p) continue;
				if(z_p < mn[2]) continue;
				z_values[column][row] = z_p;
				image.set_pixel(column,row,t.c[0],t.c[1],t.c[2]);
			}
		}

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

		// DBG(top_y);
		// DBG(left_x);
		// DBG(dy);

		for(Triangle<T> const&t:m_triangles)
		{
			draw_method2(
				screen_width,
				screen_height,
				mn,
				mx,
				dx,
				dy,
				top_y,
				left_x,
				z_values,
				image,
				t
				);
		}
		
		for(int i=0;i<screen_height;i++)
		{
			for(int j=0;j<screen_width;j++)
			{
				if(z_values[j][i] < mx[2])
					(*z_out)<<z_values[j][i]<<"\t";
				// else 
				// 	(*z_out)<<string(z_out->precision(),' ')<<" ";
			}
			(*z_out)<<"\n";
		}

		image.save_image(output_file_name);
	}
	
};

#endif // GL_H
