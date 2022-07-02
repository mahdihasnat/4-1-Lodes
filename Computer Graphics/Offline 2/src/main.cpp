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
	if(argc<2)
	{
		cerr<<"Usage: "<<argv[0]<<" <scene.txt> <config.txt> "<<"\n";
		return 1;
	}
	cerr<<setprecision(3)<<fixed;

	string scene_file_name(argv[1]);
	ifstream scene(scene_file_name);
	ofstream stage1("stage1.txt");
	ofstream stage2("stage2.txt");
	ofstream stage3("stage3.txt");
	stage1<<fixed<<setprecision(7);
	stage2<<fixed<<setprecision(7);
	stage3<<fixed<<setprecision(7);

	Gl<T> gl;
	gl.setStage1(stage1);
	gl.setStage2(stage2);
	gl.setStage3(stage3);
	
	
	Vec3<T> eye,look,up;
	scene>>eye;
	scene>>look;
	scene>>up;

	// DBG(eye);
	// DBG(look);
	// DBG(up);
	// NL;

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
		// DBG(cmd);
		// NL;
		if(cmd == "triangle")
		{
			Vec3<T> v[3];
			for(int i=0;i<3;i++)
			{
				scene>>v[i];
			}
			gl.triangle(v);
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