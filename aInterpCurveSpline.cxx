#include "aInterpCurveSplineTK.h"
#include <cstdio>


/**
* Cubic TK::spline interpolation of curve.
* \param f, const std::vector<aPoint<T> > & - input known (sorted by x-coordinate) curve points.
* \param g, std::vector<aPoint<T> > & - output (sorted by x-coordinate) interpolated curve points.
*/
template<class T>
void aInterpCurveSplineTK<T>::make(const std::vector<aPoint<T> > &f, std::vector<aPoint<T> > &g) {
	
	std::cout<<"Todo tk::spline make..."<<std::endl;
	m_isOK = true;
	g.clear();

	int n = f.size();

	tk::spline s;
	std::vector<double> x(n);
	std::vector<double> y(n);

	for (int i = 0; i < n; i++) {
		x[i] = f[i].x;
		y[i] = f[i].y;
	}

	s.set_points(x, y);

	T a, b;
	T currentX = x[0];

	for (int i = 0; i < n; i++, currentX++) {
		a = (T)currentX;
		b = (T)s(currentX);
		aPoint<T> interp(a, b);
		g.push_back(interp);
	}
}

template class aInterpCurveSplineTK<float>;
template class aInterpCurveSplineTK<double>;
