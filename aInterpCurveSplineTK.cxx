#include <dip/aInterpCurveSplineTK.h>
#include <cstdio>
#include <algorithm>


/**
* tk::spline interpolation of curve.
* \param f, const std::vector<aPoint<T> > & - input known (sorted by x-coordinate) curve points.
* \param g, std::vector<aPoint<T> > & - output (sorted by x-coordinate) interpolated curve points.
*/
template<class T> 
void aInterpCurveSplineTK<T>::make(const std::vector<aPoint<T> > &f, std::vector<aPoint<T> > &g) {

	std::cout << "Todo tk::spline make..." << std::endl;
	m_isOK = true;
	g.clear();

	initSpline(f);

	if (!m_isOK) {
		return;
	}

	T a, b;

	for ( T currentX=f[0].x; currentX<=f.back().x; currentX++ ) {
		a = (T)currentX;
		b = (T)m_spline_tk(currentX);
		aPoint<T> interpolatedPoint(a, b);
		g.push_back(interpolatedPoint);
	}
}

/**
* Initialize spline.
* \param f, const std::vector<aPoint<T> > & - input known (sorted by x-coordinate) curve points.
*/
template<class T>
void aInterpCurveSplineTK<T>::initSpline(const std::vector<aPoint<T> > &f) {
	int n = f.size();

	if (n <= 2) {
		m_isOK = false;
		m_lastError = "More than 2 points needed.";
		return;
	}

	std::vector<double> x(n);
	std::vector<double> y(n);

	x[0] = f[0].x;
	y[0] = f[0].y;

	for (int i = 1; i<n; i++) {
		if (f[i].x<f[i - 1].x) {
			m_isOK = false;
			m_lastError = "Curve points should be sorted by X-coordinate";
			//return;
		}
		x[i] = f[i].x;
		y[i] = f[i].y;
	} //end for

	m_spline_tk.set_points(x, y);
}


/**
* Compare accuracy between two methods of spline interpolation.
* \param f, const std::vector<aPoint<T> > & - input known (sorted by x-coordinate) curve points.
* \param loopCount, int - input number of loops
* \param l2, double & - output l2-norm difference.
* \param linf, double & - output max difference.
*/
template<class T>
void aInterpCurveSplineTK<T>::compare(const std::vector<aPoint<T> > &f, int loopCount, T& l2, T& linf)
{
	T a = f[0].x;
	T b = f.back().x;

	initSpline(f);

	if (!m_isOK) {
		return;
	}

	l2 = 0.0;
	linf = 0.0;
	for (int i = 0; i < loopCount; i++) {
		T x = a + (b - a) * std::rand() / (RAND_MAX + 1.0);
		T y1 = m_spline_tk(x);
		T y2 = 0; // TO DO: method from WP3.2 spline(x);
		T err = fabs(y1 - y2);
		l2 += err*err;
		linf = (T)std::max(linf, err);
	}
	l2 = (T)(sqrt(l2) / loopCount);
}

template class aInterpCurveSplineTK<float>;
template class aInterpCurveSplineTK<double>;

