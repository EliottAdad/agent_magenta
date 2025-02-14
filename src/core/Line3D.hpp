/*
 * Line3D.hpp
 *
 *  Created on: 20 août 2024
 *      Author: esn
 */

#ifndef LINE3D_HPP_

#define LINE3D_HPP_

#include <memory>

#include "../utilities/functions.hpp"
#include "Point3D.hpp"
//#include "../utilities/Printable.hpp"

/*
 * #############
 *  Line3D<T> :)
 * #############
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



template<typename T> inline Line3D<T>::Line3D(){
	this->pp1=std::make_shared<Point3D<T>>();				// Point created at the origin
	this->pp2=std::make_shared<Point3D<T>>((T)1,(T)1,(T)1);	// {1, 1, 1}
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


#endif /* LINE3D_HPP_ */
