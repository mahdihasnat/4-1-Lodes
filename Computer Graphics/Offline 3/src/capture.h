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

	bitmap_image bmp(imageWidth,imageHeight);
	// set the background color to black
	bmp.set_all_channels(0, 0, 0);

	Ftype planeDistance = windowHeight / 2.0 / tan(fieldOfView * PI /2 / 180.0);

	Vec3<Ftype> topLeft = cameraPos + cameraLookDir*planeDistance 
							-cameraRightDir*(windowWidth/2)
							+cameraUpDir *(windowHeight/2);
	Ftype du = windowWidth/imageWidth;
	Ftype dv = windowHeight/imageHeight;

	Vec3<Ftype> currentLeft = cameraPos + cameraLookDir * planeDistance
								-cameraRightDir*(windowWidth/2)
								+cameraUpDir *(windowHeight/2);

	for(int i=0;i<imageWidth;i++)
	{
		for(int j=0;j<imageHeight;j++)
		{

		}
	}
	string fileName= getNewFileName();
	DBG(fileName);
	bmp.save_image(fileName);
}

#endif /* C6E292E4_7E6B_4D02_93A3_71317D11FCD6 */
