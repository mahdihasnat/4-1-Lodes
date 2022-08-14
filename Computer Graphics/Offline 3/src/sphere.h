#ifndef DBE74540_73D9_4EBD_9F04_68CA243F283A
#define DBE74540_73D9_4EBD_9F04_68CA243F283A

#include "object.h"
#include "vec3.h"

template<typename T>
class Sphere: public Object<T>
{
protected:
	Vec3<T> center;
	T radius;
public:
	void draw()
	{

	}
	virtual istream & read(istream & is)
	{
		is>>center>>radius;
		Object<T>::read(is);
		return is;
	}
	virtual ostream & write(ostream & os) const
	{
		os<<"[s: [c: "<<center<<"] [r: "<<radius<<"]";
		return Object<T>::write(os)<<" ]";
	}

};

#endif /* DBE74540_73D9_4EBD_9F04_68CA243F283A */
