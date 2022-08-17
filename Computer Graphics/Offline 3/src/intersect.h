#ifndef C62F5D1D_3B49_4E8F_ACFF_38FD566EB936
#define C62F5D1D_3B49_4E8F_ACFF_38FD566EB936

template<typename T>
T Object<T>::intersect(Ray<T> const& ray, Color<T> &color, int level)
{
	T tMin = getIntersectingT(ray);
	if(level == 0)
		return tMin;
	
	assert(0);
}
	

#endif /* C62F5D1D_3B49_4E8F_ACFF_38FD566EB936 */
