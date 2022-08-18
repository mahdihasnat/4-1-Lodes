#ifndef E2BF7435_307B_456A_92D5_6DA42F519279
#define E2BF7435_307B_456A_92D5_6DA42F519279

template<typename T>
class TransObject
{
public:
	virtual bool getRefractedRay(Ray<T> const &incidentRay, Color<T> const&color, Ray<T> &refractedRay) = 0;
};

#endif /* E2BF7435_307B_456A_92D5_6DA42F519279 */
