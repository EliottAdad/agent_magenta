/*
 * Line3D.hpp
 *
 *  Created on: 20 août 2024
 *      Author: esn
 */

#ifndef LINE3D_HPP_

#define LINE3D_HPP_

#include <memory>
#include <eigen3/Eigen/Dense>

#include "../utilities/functions.hpp"
#include "utils_Point3D.hpp"

/**
 * #############
 *  Line3D<T> :)
 * #############
 * @brief
 * A line is represented by two points.
 * This class present a few useful methods
 * to compute the geometry of the objects.
 */
template<typename T> class Line3D {
public:
	std::shared_ptr<Point3D<T>> pp1;
	std::shared_ptr<Point3D<T>> pp2;

	Line3D();
	Line3D(const Point3D<T>& p1, const Point3D<T>& p2);
	Line3D(std::shared_ptr<Point3D<T>> pp1, std::shared_ptr<Point3D<T>> pp2);
	virtual ~Line3D();												//:)
	Line3D(const Line3D<T>& line);
};

template<typename T> Point3D<T> getIntersection(const Line3D<T>& l1, const Line3D<T>& l2);
template<typename T> Point3D<T> getIntersectionSegments(const Line3D<T>& l1, const Line3D<T>& l2);


template<typename T> inline Line3D<T>::Line3D(){
	this->pp1=std::make_shared<Point3D<T>>();				// First point created at origin
	this->pp2=std::make_shared<Point3D<T>>((T)1,(T)1,(T)1);	// Second point at {1, 1, 1}
}

template<typename T> inline Line3D<T>::Line3D(const Point3D<T>& p1, const Point3D<T>& p2){//:)
	this->pp1=std::make_shared<Point3D<T>>(p1);// Copy the point
	this->pp2=std::make_shared<Point3D<T>>(p2);// Copy the point
}

template<typename T> inline Line3D<T>::Line3D(std::shared_ptr<Point3D<T>> pp1, std::shared_ptr<Point3D<T>> pp2){//:)
	this->pp1=pp1;
	this->pp2=pp2;
}

template<typename T> inline Line3D<T>::~Line3D() {
	;
}

/*
 * Copy constructor
 */
template<typename T> inline Line3D<T>::Line3D(const Line3D<T>& line){
	this->pp1=line.pp1;
	this->pp2=line.pp2;
}

/**
 * Returns NULL if no intersection or 
 * computes the point where they intersect.
 */
template<typename T> Point3D<T> getIntersection(const Line3D<T>& l1, const Line3D<T>& l2) {
	if (*(l1.pp2) - *(l1.pp1) == *(l2.pp2) - *(l2.pp1)){//if p2-p1 == p2'-p1' not intersction
		return NULL;
	}else{
		//Point3D<T> p;
		//t=(p1'-p1)(p2-p1-(p2'-p1'))
		Eigen::Matrix<T, 3, 1> t= toEigen(*(l1.pp2)-*(l1.pp1) - (*(l2.pp2)-*(l2.pp1))).inverse() * toEigen(*(l2.pp1)-*(l1.pp1));
		Eigen::Matrix<T, 3, 1> p= toEigen(*(l1.pp2)-*(l1.pp1)) * t + toEigen(*l1.pp1);
		return toPoint(p);
	}
}

/**
 * Returns NULL if no intersection or 
 * computes the point where they intersect.
 */
template<typename T> Point3D<T> getIntersectionSegments(const Line3D<T>& l1, const Line3D<T>& l2) {
	if (*(l1.pp2) - *(l1.pp1) == *(l2.pp2) - *(l2.pp1)){//if p2-p1 == p2'-p1' not intersction
			return NULL;
		}else{
			//Point3D<T> p;
			//t=(p1'-p1)(p2-p1-(p2'-p1'))
			Eigen::Matrix<T, 3, 1> t= toEigen(*(l1.pp2)-*(l1.pp1) - (*(l2.pp2)-*(l2.pp1))).inverse() * toEigen(*(l2.pp1)-*(l1.pp1));
			//Eigen::Matrix<T, 3, 1> p= toEigen(*(l1.pp2)-*(l1.pp1)) * t + toEigen(*l1.pp1);
			if (Point3D<SN<float, char>>{{0,0},{0,0},{0,0}}<=toPoint(t) && toPoint(t)<=Point3D<SN<float, char>>{{1,0},{1,0},{1,0}}){
				Eigen::Matrix<T, 3, 1> p= toEigen(*(l1.pp2)-*(l1.pp1)) * t + toEigen(*l1.pp1);
				return toPoint(p);
			}else{
				return NULL;
			}
		}
}


#endif /* LINE3D_HPP_ */
