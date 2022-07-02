#include<bits/stdc++.h>
using namespace std;

#include "vec4.h"
#include "vec3.h"
#include "mat4.h"
#include "gl.h"
#define DBG(x) cerr << "line "<<__LINE__<< ": "<<(#x)<<" = "<<(x)<<endl;
#define NL cerr<<endl;
typedef double T;

int main(int argc,char *argv[])
{
	ifstream scene("scene.txt");
	Gl<T> gl;
	
	T ex,ey,ez;
	T lx,ly,lz;
	T ux,uy,uz;
	Vec3<T> eye,look,up;
	scene>>eye;
	scene>>look;
	scene>>up;

	DBG(eye);
	DBG(look);
	DBG(up);
	NL;

	gl.lookAt(
		eye,
		look,
		up
	);

	T fovY,aspectRatio,near,far;
	scene>>fovY>>aspectRatio>>near>>far;
	
	DBG(fovY);
	DBG(aspectRatio);
	DBG(near);
	DBG(far);
	NL;
	gl.perspective(fovY,aspectRatio,near,far);

	while(1)
	{
		string cmd;
		scene>>cmd;
		if(cmd == "triangle")
		{
			Vec3<T> v[3];
			for(int i=0;i<3;i++)
			{
				scene>>v[i];
				DBG(v[i]);
				DBG(gl.transformPoint(v[i]));
			}
		}
		else if(cmd == "push")
		{
			
		}
		else 
			break;
	}


}