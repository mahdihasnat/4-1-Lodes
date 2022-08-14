#ifndef CA216431_319D_4CC3_8B03_D9197686F9BD
#define CA216431_319D_4CC3_8B03_D9197686F9BD

#include "light.h"

template<typename T>
class PointLight: public Light<T>
{
	public:
	ostream & write(ostream & os) const
	{
		os<<"[pl: ";
		return Light<T>::write(os)<<"]";
	}
};

#endif /* CA216431_319D_4CC3_8B03_D9197686F9BD */
