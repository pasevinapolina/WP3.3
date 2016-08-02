#include "aInterpCurveSplineTK.h"
#include <cstdio>


/**
* Cubic TK::spline interpolation of curve.
* \param f, const std::vector<aPoint<T> > & - input known (sorted by x-coordinate) curve points.
* \param g, std::vector<aPoint<T> > & - output (sorted by x-coordinate) interpolated curve points.
*/
template<class T>
void aInterpCurveSplineTK<T>::make(const std::vector<aPoint<T> > &f, std::vector<aPoint<T> > &g) {
	std::cout << "Todo TK::spline curve make..." << std::endl;
	m_isOK = true;
	g.clear();
	// simply copy vector for this example
	for (int i = 0; i < f.size(); i++) {
		g.push_back(f[i]);
	}
}

template class aInterpCurveSplineTK<float>;
template class aInterpCurveSplineTK<double>;