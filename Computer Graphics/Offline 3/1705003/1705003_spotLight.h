#ifndef B7F60605_FA8A_4E1A_A2D0_F33525D3C519
#define B7F60605_FA8A_4E1A_A2D0_F33525D3C519

#include "1705003_constants.h"

template<typename T>
class SpotLight: public Light<T>
{
private:
	Vec3<T> direction;
	T cuttoffAngleDegree;
public:
	virtual bool isReachable(Vec3<T> const& point) override
	{
		T pointAngle = acos(direction.dot( (point - Light<T>::position).normalize() ));
		return pointAngle * 180 /PI <= cuttoffAngleDegree;
	}
	istream & read(istream & is)
	{
		Light<T>::read(is)>>direction>>cuttoffAngleDegree;
		direction.normalize();
		return is;
	}
	ostream & write(ostream & os) const
	{
		os<<"[sl: ";
		return Light<T>::write(os)<<" [d: "<<direction<<"] [a: "<<cuttoffAngleDegree<<"] ]";
	}
	void setDirection(Vec3<T> direction)
	{
		this->direction = direction;
		this->direction.normalize();
	}
	void setCuttoffAngleDegree(T cuttoffAngleDegree)
	{
		this->cuttoffAngleDegree = cuttoffAngleDegree;
	}
};

#endif /* B7F60605_FA8A_4E1A_A2D0_F33525D3C519 */
