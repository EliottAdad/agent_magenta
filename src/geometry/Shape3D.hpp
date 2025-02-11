/*
 * Shape3D.hpp
 *
 *  Created on: 20 mai 2024
 *      Author: esn
 */

#ifndef SHAPE3D_HPP_

#define SHAPE3D_HPP_

#include <unordered_set>

#include "../core/Line3D.hpp"
#include "../core/Point3D.hpp"
#include "../display/Displayable.hpp"

/*
 * #################
 *  Shape3D<T> :)
 * #################
 */
template<typename T> class Shape3D : public Point3D<T>, public Displayable<T> {
public:
	Shape3D();
	virtual ~Shape3D();
	Shape3D(const Shape3D<T>& shape);

	virtual std::unordered_set<std::shared_ptr<Point3D<T>>> getPPoints() const;
	virtual std::unordered_set<std::shared_ptr<Line3D<T>>> getPLines() const;
	virtual std::unordered_set<std::shared_ptr<Triangle3D<T>>> getPTriangles() const;

	//virtual std::unordered_set<std::shared_ptr<Point3D<T>>> getPoints() const;//To render the shape
	//virtual std::unordered_set<std::shared_ptr<Line3D<T>>> getLines() const;//To render the shape
	//virtual std::unordered_set<std::shared_ptr<Line3D<T>>> getLines() const;//To render the shape

	virtual std::string to_string(const bool& spread=false, const bool& full_info=false, const unsigned char& indent=0) const;
	virtual void print(const bool& spread=false, const bool& full_info=false, const unsigned char& indent=0) const;
};

template<typename T> Shape3D<T>::Shape3D() {
	// TODO Auto-generated constructor stub

}

template<typename T> Shape3D<T>::~Shape3D() {
	// TODO Auto-generated destructor stub
}

template<typename T> Shape3D<T>::Shape3D(const Shape3D &other) {
	// TODO Auto-generated constructor stub

}


template<typename T> std::unordered_set<std::shared_ptr<Point3D<T>>> Shape3D<T>::getPPoints() const {
	std::unordered_set<std::shared_ptr<Point3D<T>>> ppoints;
	return ppoints;
}

template<typename T> std::unordered_set<std::shared_ptr<Line3D<T>>> Shape3D<T>::getPLines() const {
	std::unordered_set<std::shared_ptr<Line3D<T>>> plines;
	return plines;
}

template<typename T> std::unordered_set<std::shared_ptr<Triangle3D<T>>> Shape3D<T>::getPTriangles() const {
	std::unordered_set<std::shared_ptr<Triangle3D<T>>> ptriangles;
	return ptriangles;
}


template<typename T> std::string Shape3D<T>::to_string(const bool& spread, const bool& full_info, const unsigned char& indent) const {
	std::string mes=((spread)?"\n" : "");

	if (full_info){
		mes+="SHAPE3D[";
		std::stringstream ss;
		ss << this;
		mes+=ss.str();
		mes+="]:";
		mes+=((spread)?"\n" : "");
	}
	return mes;
}

template<typename T> void Shape3D<T>::print(const bool& spread, const bool& full_info, const unsigned char& indent) const {
	printTabs(indent);
	std::cout << this->to_string(spread, full_info, indent);
}


#endif /* SHAPE3D_HPP_ */
