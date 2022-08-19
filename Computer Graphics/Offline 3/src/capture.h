#ifndef C6E292E4_7E6B_4D02_93A3_71317D11FCD6
#define C6E292E4_7E6B_4D02_93A3_71317D11FCD6

#include "ray.h"
#include "object.h"
#include "light.h"
#include "variables.h"
#include "bitmap_image.hpp"
#include "transObject.h"

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
	if(currentT<0)
	{
		// DBG(currentT);
		// DBG(*object);
		// DBG(incidentRay);
		// DBG(cameraPos);
		// DBG(cameraLookDir);
		// DBG(cameraUpDir);
	}
	if(currentT<0)
	{
		return true;
	}
	for(auto const& obj: objects)
	{
		if(obj.get() != object)
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

Color<Ftype> illuminateRecursive(Ray<Ftype> ray,int level)
{
	Color<Ftype> color;//0,0,0
	if(level == 0)
	{
		return color;
	}
	Object<Ftype> * closestObject = 0;
	Ftype minimumPositiveT = numeric_limits<Ftype>::max();
	for(auto const& object: objects)
	{
		Ftype t = object->getIntersectingT(ray);
		if(t>Ftype(0) and t < minimumPositiveT)
		{
			minimumPositiveT = t;
			closestObject = object.get();
		}
	}
	if(closestObject)
	{
		Vec3<Ftype > point = ray.getPoint(minimumPositiveT);
		const Color<Ftype> intersectionPointColor =closestObject->getColorAt(point);
		if(level == recursionLevel)
			color += intersectionPointColor*closestObject->getAmbientCoef();
		Ray<Ftype> viewRay(point,cameraPos-point);
		// assert(-ray.getDirection() == viewRay.getDirection());
		Vec3<Ftype> normal = closestObject->getNormalAt(point);
		if(normal.dot(viewRay.getDirection()) <0)
			normal = - normal;
		
		for(auto const & l: lights)
		{
			Ray<Ftype> incidentRay(l->getPosition(),point-l->getPosition());
			if(!l->isReachable(point)) continue;
			if(incidentRay.getDirection().dot(normal)>0) continue;
			if(isInShadow(closestObject,incidentRay)) continue;
			Ftype lambertValue = max(-incidentRay.getDirection().dot(normal),Ftype(0));
			color += l->getColor()* intersectionPointColor * (closestObject->getDiffuseCoef() * lambertValue);
			Vec3<Ftype> reflectedIncidentRayDirection = incidentRay.getDirection() - normal*(2*normal.dot(incidentRay.getDirection()));
			Ftype phongCosAngle = max(reflectedIncidentRayDirection.dot(viewRay.getDirection()),Ftype(0));
			Ftype phongValue = pow(phongCosAngle,closestObject->getShininess());
			color += l-> getColor() * (closestObject->getSpecularCoef() * phongValue);
		}
		Vec3<Ftype> reflectedRayDirection = ray.getDirection() - normal*(2*normal.dot(ray.getDirection()));
		Ray<Ftype> reflectedRay(point + reflectedRayDirection*1e-5,reflectedRayDirection);
		Color<Ftype> colorReflected = illuminateRecursive(reflectedRay,level-1);
		color += colorReflected * closestObject->getReflectionCoef();
		TransObject<Ftype> * transObject = dynamic_cast<TransObject<Ftype> *>(closestObject);
		if(transObject)
		{
			assert(transObject);
			Ray<Ftype> refractedRay;
			if(transObject->getRefractedRay(ray,color,refractedRay))
			{
				// DBG(refractedRay);
				refractedRay.setOrigin(point + refractedRay.getDirection()*1e-5);
				color+= illuminateRecursive(refractedRay,level-1);
			}
		}
	}
	
	// DBG(color);
	return color;
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
			Color<Ftype> color = illuminateRecursive(ray,recursionLevel);
			color.clip();
			image.set_pixel(i,j,round(color[0]*255),round(color[1]*255),round(color[2]*255));
		}
	}
	auto stop = high_resolution_clock::now();

	auto duration = duration_cast<microseconds>(stop - start);

	cerr<<"Time taken: "<<duration.count()/1e6<<" Second"<<endl<<endl;

	string fileName= getNewFileName();
	image.save_image(fileName);

}

#endif /* C6E292E4_7E6B_4D02_93A3_71317D11FCD6 */
