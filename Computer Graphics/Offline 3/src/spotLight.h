#ifndef B7F60605_FA8A_4E1A_A2D0_F33525D3C519
#define B7F60605_FA8A_4E1A_A2D0_F33525D3C519

template<typename T>
class SpotLight: public Light<T>
{
private:
	Vec3<T> direction;
	T cuttoffAngleDegree;
public:
	istream & read(istream & is)
	{
		return Light<T>::read(is)>>direction>>cuttoffAngleDegree;
	}
	ostream & write(ostream & os) const
	{
		os<<"[sl: ";
		return Light<T>::write(os)<<" [d: "<<direction<<"] [a: "<<cuttoffAngleDegree<<"] ]";
	}
};

#endif /* B7F60605_FA8A_4E1A_A2D0_F33525D3C519 */
