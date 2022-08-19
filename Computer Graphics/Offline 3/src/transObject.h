#ifndef E2BF7435_307B_456A_92D5_6DA42F519279
#define E2BF7435_307B_456A_92D5_6DA42F519279

template<typename T>
class TransObject
{
public:
	virtual Vec3<T> getNormalAt(Vec3<T> const& point, Ray<T> const & viewRay) = 0;
	virtual bool getRefractedRay(
		Ray<T> const &transmittedRay,
		Color<T> const&color,
		Ray<T> &incidentRay)
	{
		//  N is opposite direction of T

		// I = N (sqrt(1-(itaTOverItaI*itaTOverItaI) * (1 - (-N dot T )))) 
		// 	+ ItaTOverItaI * ( - T - N ( - N dot T ));
		// T normal = getNormalAt()
		// T itaTOverItaI = getItaTOverItaI(transmittedRay);
		// T cosThetaT = 
		return false;
	}
	virtual T getItaTOverItaI(Vec3<T> const& transmittedRay) = 0;
};

#endif /* E2BF7435_307B_456A_92D5_6DA42F519279 */
