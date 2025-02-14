//:)
#ifndef BEZIERCURVE3D_H

#define BEZIERCURVE3D_H


#include <string>
#include <vector>
#include <unordered_set>

#include "../core/Point3D.hpp"
#include "../utilities/functions.hpp"


/*
 * ####################
 *  BezierCurve3D<T> :)
 * ####################
 * A bezier curve defined by 2 or more control points.
 */
template<typename T> class BezierCurve3D {
	public:
	std::unordered_set<std::shared_ptr<Point3D<T>>> m_pctr_points;// Pointeurs to the control points of the curve.

	BezierCurve3D();//:)
	BezierCurve3D(const BezierCurve3D<T>& bezier_curve);//:)
	~BezierCurve3D();//:)
	
	//std::shared_ptr<Point3D<T>> getImage(const float& t);//:) t is between 0 and 1.

	bool testOnLine(const Point3D<T>& point);//:)
	//Line2D* getPerpendicularLine(Point2D* ppoint);//:) Get a perpendicular line passing throug the point in parameter.
};



template<typename T> inline BezierCurve3D<T>::BezierCurve3D() {
	;
}

template<typename T> inline BezierCurve3D<T>::BezierCurve3D(const BezierCurve3D<T>& bezier_curve) {
	;
}

template<typename T> inline BezierCurve3D<T>::~BezierCurve3D() {
	/*int szppoints=m_ppoints.size();
	for (int i(0) ; i<szppoints ; i++)
	{
		m_ppoints.erase(m_ppoints.begin());
	}*/
}

/**
 * Get the image on the line given the factor t.
 */
/*template<typename T> std::shared_ptr<Point3D<T>> BezierCurve3D<T>::getImage(const float& t) {
	SN<T> x{0, 0}, y{0, 0};

	for (int i(0) ; i<(int)m_ppoints.size() ; i++)
	{
		x+=binomialCoef(m_ppoints.size(), i)*pow(1-t, (int)m_ppoints.size()-i)*pow(t, i)*m_ppoints[i]->x;
		y+=binomialCoef(m_ppoints.size(), i)*pow(1-t, (int)m_ppoints.size()-i)*pow(t, i)*m_ppoints[i]->y;
	}

	return new Point3D{x, y};
}*/


#endif
