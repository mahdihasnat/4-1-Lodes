#include<bits/stdc++.h>
using namespace std;
#define DBG(x) cerr << ""<<__FILE__<<":"<<__LINE__<< ": "<<(#x)<<" = "<<(x)<<endl;
#define NL cerr<<endl;

#include "vec4.h"
#include "vec3.h"
#include "mat4.h"
#include "gl.h"
typedef long double T;


int main(int argc,char *argv[])
{
	if(argc<3)
	{
		cerr<<"Usage: "<<argv[0]<<" <scene.txt> <config.txt> "<<"\n";
		return 1;
	}
	cerr<<setprecision(4)<<fixed;

	string scene_file_name(argv[1]);
	ifstream scene(scene_file_name);
	string config_file_name(argv[2]);
	ifstream config(config_file_name);

	ofstream stage1("stage1.txt");
	ofstream stage2("stage2.txt");
	ofstream stage3("stage3.txt");
	// ostream stage3(&nullBuffer);
	ofstream z_out("z_buffer.txt");
	stage1<<fixed<<setprecision(7);
	stage2<<fixed<<setprecision(7);
	stage3<<fixed<<setprecision(7);
	z_out<<fixed<<setprecision(6);

	Gl<T> gl;
	gl.setStage1(stage1);
	gl.setStage2(stage2);
	gl.setStage3(stage3);
	gl.setZOut(z_out);
	
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
	
	// DBG(fovY);
	// DBG(aspectRatio);
	// DBG(near);
	// DBG(far);
	// NL;
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

	int screen_width,screen_height;
	config>>screen_width>>screen_height;
	
	T x_min,x_max,y_min,y_max;
	config>>x_min;
	x_max = -x_min;

	config>>y_min;
	y_max = -y_min;

	T z_min,z_max;
	config>>z_min;
	config>>z_max;

	stage1.close();
	stage2.close();
	stage3.close();

	// ifstream stage3_in("stage3.txt");
	// gl.setTriangles(stage3_in);

	gl.draw(screen_width,screen_height,
		Vec3<T>(x_min,y_min,z_min),
		Vec3<T>(x_max,y_max,z_max),
		"out.bmp"
	);


}