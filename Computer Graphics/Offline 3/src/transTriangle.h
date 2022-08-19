#ifndef F15EE736_194C_4395_8E03_2F9FE05682D8
#define F15EE736_194C_4395_8E03_2F9FE05682D8

#include "triangle.h"
#include "transObject.h"

template<typename T>
class TransTriangle : public Triangle<T>, public TransObject<T>
{
	T refractionCoefficient = 1;
public:
	virtual bool isTransparent() override
	{
		return true;
	}
	virtual bool getRefractedRay(Ray<T> const &incidentRay, Color<T> const&color, Ray<T> &refractedRay) override
	{
		
		refractedRay = incidentRay;
		return true;
	}
	void setRefrectionCoefficient(T refractionCoefficient)
	{
		this->refractionCoefficient = refractionCoefficient;
	}
	virtual ostream & write(ostream & os) const override
	{
		os<<"[tt: [rc:"<<refractionCoefficient<<"] ";
		Triangle<T>::write(os);
		os<<"]";
		return os;
	}
};

#endif /* F15EE736_194C_4395_8E03_2F9FE05682D8 */
