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
	friend ostream & operator <<(ostream & os, const Sphere & s)
	{
		os<<"[s: [c: "<<s.center<<"] [r: "<<s.radius<<"]";
		os<<(Object<T> const&)s;
		os<<']';
		return os;
	}
	friend istream & operator >>(istream & is, Sphere & s)
	{
		is>>s.center>>s.radius;
		is>>(Object<T>&)s;
		return is;
	}
	
};

#endif /* DBE74540_73D9_4EBD_9F04_68CA243F283A */
