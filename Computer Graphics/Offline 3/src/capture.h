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
	bitmap_image bmp(pixelDimension, pixelDimension);
	// set the background color to black
	bmp.set_all_channels(0, 0, 0);
	string fileName= getNewFileName();
	DBG(fileName);
	bmp.save_image(fileName);
}

#endif /* C6E292E4_7E6B_4D02_93A3_71317D11FCD6 */
