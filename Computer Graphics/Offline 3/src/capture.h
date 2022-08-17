#ifndef C6E292E4_7E6B_4D02_93A3_71317D11FCD6
#define C6E292E4_7E6B_4D02_93A3_71317D11FCD6

#include "ray.h"
#include "object.h"
#include "light.h"
#include "variables.h"
#include "bitmap_image.hpp"


#include <chrono>
using namespace std::chrono;


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


bool isInShadow(Object<Ftype> * object, Ray<Ftype> &incidentRay)
{
	Ftype currentT = object->getIntersectingT(incidentRay);
	assert(currentT >= 0);
	for(Object<Ftype> * obj: objects)
	{
		if(obj!= object)
		{
			Ftype t = obj->getIntersectingT(incidentRay);
			if(t >= 0 && t < currentT)
			{
				return true;
			}
		}
	}
	return false;
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

	auto start = high_resolution_clock::now();

	
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
	currentTopLeft = currentTopLeft+cameraRightDir*(du/2.0)-cameraUpDir*(dv/2.0);

	assert(currentTopLeft == topLeft);

	Ray<Ftype> ray;
	ray.setOrigin(cameraPos);
	for(int i=0;i<imageWidth;i++,currentTopLeft+=cameraRightDir*du)
	{
		Vec3<Ftype> currentPixel=currentTopLeft;
		for(int j=0;j<imageHeight;j++,currentPixel-=cameraUpDir*dv)
		{
			// currentPixel= topLeft + cameraRightDir*(i*du) - cameraUpDir*(j*dv);
			
			ray.setDirection(currentPixel - cameraPos);
			
			Object<Ftype> * closestObject = 0;
			Ftype minimumPositiveT = numeric_limits<Ftype>::max();
			for(Object<Ftype> * object: objects)
			{
				Ftype t = object->getIntersectingT(ray);
				if(t>Ftype(0) and t < minimumPositiveT)
				{
					minimumPositiveT = t;
					closestObject = object;
				}
			}
			if(closestObject)
			{
				Color<Ftype> color;
				Vec3<Ftype > point = ray.getPoint(minimumPositiveT);
				const Color<Ftype> intersectionPointColor =closestObject->getColorAt(point);
				color=intersectionPointColor*closestObject->getAmbientCoef();
				
				for(Light<Ftype> * l: lights)
				{
					Ray<Ftype> incidentRay(l->getPosition(),point-l->getPosition());
					if(!l->isReachable(point)) continue;
					if(isInShadow(closestObject,incidentRay)) continue;
					Vec3<Ftype> normal = closestObject->getNormalAt(point,incidentRay);
					Ftype lambertValue = max(-incidentRay.getDirection().dot(normal),Ftype(0));
					color += l->getColor()* intersectionPointColor * (closestObject->getDiffuseCoef() * lambertValue);
					Vec3<Ftype> reflectedRayDirection = incidentRay.getDirection() - normal*(2*normal.dot(incidentRay.getDirection()));
					Ftype phongValue = pow(max(-reflectedRayDirection.dot(ray.getDirection()),Ftype(0)),closestObject->getShininess());
					color += l-> getColor() * (closestObject->getSpecularCoef() * phongValue);
				}

				color.clip();
				image.set_pixel(i,j,round(color[0]*255),round(color[1]*255),round(color[2]*255));
			}
		}
	}
	auto stop = high_resolution_clock::now();

	auto duration = duration_cast<microseconds>(stop - start);

	cerr<<"Time taken: "<<duration.count()/1e6<<" Second"<<endl<<endl;

	string fileName= getNewFileName();
	image.save_image(fileName);

}

#endif /* C6E292E4_7E6B_4D02_93A3_71317D11FCD6 */
