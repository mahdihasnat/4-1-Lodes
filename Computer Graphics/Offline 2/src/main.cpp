#include<bits/stdc++.h>
using namespace std;
#define DBG(x) cerr << ""<<__FILE__<<":"<<__LINE__<< ": "<<(#x)<<" = "<<(x)<<endl;
#define NL cerr<<endl;

#include "vec4.h"
#include "vec3.h"
#include "mat4.h"
#include "gl.h"
typedef double T;


int main(int argc,char *argv[])
{
	cerr<<setprecision(3)<<fixed;
	
	ifstream scene("scene.txt");
	ofstream stage1("stage1.txt");
	Gl<T> gl;
	gl.setStage1(stage1);
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
		DBG(cmd);
		NL;
		if(cmd == "triangle")
		{
			Vec3<T> v[3];
			for(int i=0;i<3;i++)
			{
				scene>>v[i];
				// DBG(v[i]);
				DBG(gl.transformPoint(v[i]));
			}
		}
		else if(cmd =="scale")
		{
			Vec3<T> v;
			scene>>v;
			gl.scale(v);
		}
		else if(cmd =="translate")
		{
			Vec3<T> v;
			scene>>v;
			gl.translate(v);
		}
		else if(cmd == "rotate")
		{
			T angle;
			Vec3<T> v;
			scene>>angle>>v;
			gl.rotate(angle,v);
		}
		else if(cmd == "push")
		{
			gl.push();
		}
		else if(cmd == "pop")
		{
			gl.pop();
		}
		else if(cmd == "end")
		{
			break;
		}
		else
		{
			cerr<<"unknown command: "<<cmd<<endl;
			assert(0);
			return 1;
		}
	}


}