#include "aInterpCurveSplineTK.h"
#include <cstdio>


/**
* Cubic TK::spline interpolation of curve.
* \param f, const std::vector<aPoint<T> > & - input known (sorted by x-coordinate) curve points.
* \param g, std::vector<aPoint<T> > & - output (sorted by x-coordinate) interpolated curve points.
*/
template<class T>
void aInterpCurveSplineTK<T>::make(const std::vector<aPoint<T> > &f, std::vector<aPoint<T> > &g) {
	
	std::cout << "Todo tk::spline make..." << std::endl;
	m_isOK = true;
	g.clear();

	int n = f.size();

	if ( n<=2 ) {
		m_isOK = false;
		m_lastError = "More than 2 points needed.";
		return;
	}

	std::vector<double> x(n);
	std::vector<double> y(n);

	x[0] = f[0].x;
	y[0] = f[0].y;

	for ( int i=1; i<n; i++ ) {
		if ( f[i]<f[i - 1] ) {
			m_isOK = false;
			m_lastError = "Curve points should be sorted by X-coordinate";
			return;
		}
		x[i] = f[i].x;
		y[i] = f[i].y;
	} //end for

	tk::spline s;
	s.set_points(x, y);

	T a, b;

	for ( T currentX=x[0]; currentX<=x.back(); currentX++ ) {
		a = (T)currentX;
		b = (T)s(currentX);
		aPoint<T> interpolatedPoint(a, b);
		g.push_back(interpolatedPoint);
	}
}

template<class T>
T aInterpCurveSplineTK<T>::getValue(method method, T x)
{
	T result;
	if (method == aInterpCurveLinear<T>::TK) {
		//result = m_spline_tk(x);
	}
	else if(method == aInterpCurveLinear<T>::CUSTOM) {
		// TODO: method from WP3.2
		//result = spline(x);
	}
	return result;
}

/**
* Compare accuracy between two methods of spline interpolation.
* \param l2, double & - output l2-norm difference.
* \param linf, double & - output max difference.
* \param firstMethod, method - input type of first spline interpolation method.
* \param secondMethod, method - input type of second spline interpolation method.
* \param num_ops, int - input number of loops
*/
template<class T>
void aInterpCurveSplineTK<T>::compare(const std::vector<aPoint<T> > &f, method firstMethod, method secondMethod,
	int loopCount, T& l2, T& linf)
{
	T a = f[0].x;
	T b = f.back().x;

	l2 = 0.0;
	linf = 0.0;
	for (int i = 0; i < loopCount; i++) {
		T x = a + (b - a) * std::rand() / (RAND_MAX + 1.0);
		T y1 = getValue(firstMethod, x);
		T y2 = getValue(secondMethod, x);
		T err = fabs(y1 - y2);
		l2 += err*err;
		linf = (T)std::max(linf, err);
	}
	l2 = (T)(sqrt(l2) / loopCount);
}

template class aInterpCurveSplineTK<float>;
template class aInterpCurveSplineTK<double>;
