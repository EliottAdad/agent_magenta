/*
 * Triangle3D.hpp
 *
 *  Created on: 20 mai 2024
 *      Author: esn
 */

#ifndef TRIANGLE3D_HPP_

#define TRIANGLE3D_HPP_

#include <memory>

#include "../core/Point3D.hpp"

/*
 * #################
 *  Triangle3D<T> :)
 * #################
 * @brief
 * A set of 3 points.
 */
template<typename T> class Triangle3D {
public:
	std::shared_ptr<Point3D<T>> pp1;
	std::shared_ptr<Point3D<T>> pp2;
	std::shared_ptr<Point3D<T>> pp3;

	Triangle3D();
	Triangle3D(const Point3D<T>& p1, const Point3D<T>& p2, const Point3D<T>& p3);
	Triangle3D(std::shared_ptr<Point3D<T>> pp1, std::shared_ptr<Point3D<T>> pp2, std::shared_ptr<Point3D<T>> pp3);
	virtual ~Triangle3D();
	Triangle3D(const Triangle3D& triangle);

	//virtual std::unordered_set<std::shared_ptr<Point3D<T>>> getPoints() const;//To render the shape
	//virtual std::unordered_set<std::shared_ptr<Line3D<T>>> getLines() const;//To render the shape
};


template<typename T> inline Triangle3D<T>::Triangle3D() {
	pp1=std::make_shared<Point3D<T>>(Point3D<T>{(T)1,(T)1,(T)1});
	pp2=std::make_shared<Point3D<T>>(Point3D<T>{(T)1,(T)1,(T)1});
	pp3=std::make_shared<Point3D<T>>(Point3D<T>{(T)1,(T)1,(T)1});
}

template<typename T> inline Triangle3D<T>::Triangle3D(const Point3D<T>& p1, const Point3D<T>& p2, const Point3D<T>& p3) {
	pp1=std::make_shared<Point3D<T>>(p1);
	pp2=std::make_shared<Point3D<T>>(p2);
	pp3=std::make_shared<Point3D<T>>(p3);
}

template<typename T> inline Triangle3D<T>::Triangle3D(std::shared_ptr<Point3D<T>> pp1, std::shared_ptr<Point3D<T>> pp2, std::shared_ptr<Point3D<T>> pp3) {
	this->pp1=pp1;
	this->pp2=pp2;
	this->pp3=pp3;
}

template<typename T> inline Triangle3D<T>::~Triangle3D() {
	;
}

template<typename T> inline Triangle3D<T>::Triangle3D(const Triangle3D& triangle) {
	this->pp1=triangle.pp1;
	this->pp2=triangle.pp2;
	this->pp3=triangle.pp3;
}






#endif /* TRIANGLE3D_HPP_ */
