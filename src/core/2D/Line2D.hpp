/*
 * Line2D.hpp
 *
 *  Created on: 20 août 2024
 *      Author: esn
 */

#ifndef LINE2D_HPP_

#define LINE2D_HPP_

#include <memory>

#include "../utilities/functions.hpp"
#include "Point2D.hpp"
//#include "../utilities/Printable.hpp"

/*
 * #############
 *  Line2D<T> :)
 * #############
 * A line is represented by two points.
 * This class present a few useful methods
 * to compute the geometry of the objects.
 */
template<typename T> class Line2D {
public:
	std::shared_ptr<Point2D<T>> pp1;
	std::shared_ptr<Point2D<T>> pp2;

	Line2D();
	Line2D(const Point2D<T>& p1, const Point2D<T>& p2);
	Line2D(std::shared_ptr<Point2D<T>> pp1, std::shared_ptr<Point2D<T>> pp2);
	virtual ~Line2D();												//:)
	Line2D(const Line2D<T>& line);
};



template<typename T> inline Line2D<T>::Line2D(){
	this->pp1=std::make_shared<Point2D<T>>();				// Point created at the origin
	this->pp2=std::make_shared<Point2D<T>>((T)1,(T)1;	// {1, 1}
}

template<typename T> inline Line2D<T>::Line2D(const Point2D<T>& p1, const Point2D<T>& p2){//:)
	this->pp1=std::make_shared<Point2D<T>>(p1);// Copy the point
	this->pp2=std::make_shared<Point2D<T>>(p2);// Copy the point
}

template<typename T> inline Line2D<T>::Line2D(std::shared_ptr<Point2D<T>> pp1, std::shared_ptr<Point2D<T>> pp2){//:)
	this->pp1=pp1;
	this->pp2=pp2;
}

template<typename T> inline Line2D<T>::~Line2D() {
	;
}

/*
 * Copy constructor
 */
template<typename T> inline Line2D<T>::Line2D(const Line2D<T>& line){
	this->pp1=line.pp1;
	this->pp2=line.pp2;
}


#endif /* LINE2D_HPP_ */
