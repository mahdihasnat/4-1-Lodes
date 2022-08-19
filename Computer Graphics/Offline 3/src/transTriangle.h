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
	virtual Vec3<T> getNormalAt(Vec3<T> const& point, Ray<T> const & viewRay) override
	{
		return Triangle<T>::getNormalAt(point, viewRay);
	}
	virtual T getItaTOverItaI(Vec3<T> const& transmittedRay) override
	{
		// TODO : implement carefully
		return refractionCoefficient;
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
