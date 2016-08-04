#ifndef _A_INTERPCURVE_SPLINE_TK_H
#define _A_INTERPCURVE_SPLINE_TK_H

#include <dip/aInterpCurve.h>
#include <utils/spline.h>

/** \class aInterpCurveSplineTK
* \brief A TK::spline interpolation of 2D curve.
*
* Input coordinates of know curve points coordinates, the first derivatives are not applied.
* Output coordinates of interpolated curve points.
* \author ooo
* \date 2016
*/
template<class T> class aInterpCurveSplineTK : public aInterpCurve<T> {
public:

	//! Default constructor. 
	aInterpCurveSplineTK() {
		Init();
	};

	//! Virtual destructor.
	virtual ~aInterpCurveSplineTK() {
	};

	//! Calculate the convolution of imgI and imgG. oImg = imgT*imgG
	virtual void make(const std::vector<aPoint<T> > &f, std::vector<aPoint<T> > &g);

	//! Compare accuracy of two spline interpolation methods.
    virtual void compare(const std::vector<aPoint<T> > &f, method firstMethod, method secondMethod,
	  int loopCount, T& l2, T& linf);

    virtual T getValue(method method, T x);
  
	//!
	virtual bool isOK() {
		return m_isOK;
	};

	//!
	virtual std::string getLastError() {
		return m_lastError;
	};

	//! Set first derivative for the first point. 
	virtual void setDrvFirstPoint(T val) {
		m_drvP1 = val; // not applied for this class
	};

	//! Set first derivative for the last point. Not used in this class.
	virtual void setDrvLastPoint(T val) {
		m_drvP2 = val; // not applied for this class
	};

    //! First and second derivatives.
    T m_drvP1, m_drvP2;
	
protected:
	//! State.
	int m_isOK;

	//! Last message.
	std::string m_lastError;

	void Init() { // Init method
		m_drvP1     = (T)0.0;
		m_drvP2     = (T)0.0;
		m_isOK = true;
		m_lastError = "";
	};

}; // end of aInterpCurveSplineTK class description

#endif  // _A_INTERPCURVE_SPLINE_TK_H
