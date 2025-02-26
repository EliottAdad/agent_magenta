//:)
/*
 * BezierCurve3D.hpp
 *
 *  Created on: 22 oct. 2024
 *      Author: esn
 */

#ifndef BEZIERCURVE3D_H

#define BEZIERCURVE3D_H


#include <string>
#include <vector>
#include <unordered_set>

#include "../core/Point3D.hpp"
#include "../display/Displayable3D.hpp"
#include "../utilities/functions.hpp"


/*
 * ####################
 *  BezierCurve3D<T> :)
 * ####################
 * @brief
 * A bezier curve defined by 2 or more control points.
 */
template<typename T> class BezierCurve3D : public Displayable3D {
public:
	float t;
	std::unordered_set<std::shared_ptr<Point3D<T>>> pctr_points;// Pointeurs to the control points of the curve.

	BezierCurve3D();//:)
	BezierCurve3D(const BezierCurve3D<T>& bezier_curve);//:)
	~BezierCurve3D();//:)
	
	std::shared_ptr<Point3D<T>> getImage(const float& t);//:) t is between 0 and 1.

	bool testOnLine(const Point3D<T>& point);//:)
	//Line2D* getPerpendicularLine(Point2D* ppoint);//:) Get a perpendicular line passing throug the point in parameter.
	
	// Displayable3D
	virtual std::unordered_set<Point3D<T>*> getPPoints() const {Displayable3D<T>::getPPoints();}
};



template<typename T> inline BezierCurve3D<T>::BezierCurve3D() {
	this->t=0;
}

template<typename T> inline BezierCurve3D<T>::BezierCurve3D(const BezierCurve3D<T>& bezier_curve) {
	this->t=bezier_curve.t;
}

template<typename T> inline BezierCurve3D<T>::~BezierCurve3D() {
	;
}

/**
 * Get the image on the line given the factor t.
 * \t is between 0 and 1.
 */
template<typename T> std::shared_ptr<Point3D<T>> BezierCurve3D<T>::getImage(const float& t) {
	T x=(T)0, y=(T)0, z=(T)0;

	unsigned int i(0);
	for (std::shared_ptr<Point3D<T>> ppoint: this->pctr_points){
		x+=binomialCoef(this->pctr_points.size(), i)*pow(1-t, this->pctr_points.size()-i)*pow(t, i)*ppoint->x;
		y+=binomialCoef(this->pctr_points.size(), i)*pow(1-t, this->pctr_points.size()-i)*pow(t, i)*ppoint->y;
		z+=binomialCoef(this->pctr_points.size(), i)*pow(1-t, this->pctr_points.size()-i)*pow(t, i)*ppoint->z;
		i++;
	}

	return std::make_shared<Point3D<T>>(x, y, z);
}


#endif
