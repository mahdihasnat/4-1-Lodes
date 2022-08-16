#ifndef C6E292E4_7E6B_4D02_93A3_71317D11FCD6
#define C6E292E4_7E6B_4D02_93A3_71317D11FCD6

#include "ray.h"
#include "object.h"
#include "variables.h"
#include "bitmap_image.hpp"

string getNewFileName()
{
	int fileNumber = 1;
	while(true)
	{
		string fileName = "Output_1"+to_string(fileNumber)+".bmp";
		return fileName; // TODO: remove on submit
		ifstream ifs(fileName.c_str());
		if(!ifs.good())
		{
			return fileName;
		}
		else
		{
			fileNumber++;
		}
	}
}

void capture()
{
	DBG("capture");

	// (0,0) ....................(imageWidth-1,0)
	// ..
	// ..
	// ..
	// (0,imageHeight-1).........(imageWidth-1,imageHeight-1)

	bitmap_image image(imageWidth,imageHeight);

	// set the background color to black
	image.set_all_channels(0,0,0);

	DBG(imageWidth);
	DBG(imageHeight);

	Ftype planeDistance = windowHeight / 2.0 / tan(fieldOfView * PI /2 / 180.0);

	Vec3<Ftype> topLeft = cameraPos + cameraLookDir*planeDistance 
							-cameraRightDir*(windowWidth/2)
							+cameraUpDir *(windowHeight/2);

	Ftype du = Ftype(windowWidth)/Ftype(imageWidth);
	Ftype dv = Ftype(windowHeight)/Ftype(imageHeight);

	topLeft = topLeft+cameraRightDir*(du/2.0)-cameraUpDir*(dv/2.0);

	Vec3<Ftype> currentTopLeft = cameraPos + cameraLookDir * planeDistance
								-cameraRightDir*(windowWidth/2)
								+cameraUpDir *(windowHeight/2);

	Ray<Ftype> ray;
	ray.setOrigin(cameraPos);
	for(int i=0;i<imageWidth;i++)
	{
		currentTopLeft;
		for(int j=0;j<imageHeight;j++)
		{
			Vec3<Ftype> currentPixel = topLeft + cameraRightDir*(i*du) - cameraUpDir*(j*dv);
			
			ray.setDirection(currentPixel - cameraPos);
			
			Color<Ftype> color;
			Object<Ftype> * closestObject = 0;
			Ftype minimumPositiveT = numeric_limits<Ftype>::max();
			for(Object<Ftype> * object: objects)
			{
				Ftype t = object->intersect(ray,color,0);
				if(t>Ftype(0) and t < minimumPositiveT)
				{
					minimumPositiveT = t;
					closestObject = object;
				}
			}
			if(closestObject)
			{
				// assert(0);
				image.set_pixel(i,j,255,255,255);
			}
		}
		currentTopLeft += cameraRightDir*du;
	}
	string fileName= getNewFileName();
	DBG(fileName);
	image.save_image(fileName);
}

#endif /* C6E292E4_7E6B_4D02_93A3_71317D11FCD6 */
