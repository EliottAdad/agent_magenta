/*
 * Shape3D.h
 *
 *  Created on: 20 mai 2024
 *      Author: esn
 */

#ifndef SHAPE3D_H_

#define SHAPE3D_H_

#include <unordered_set>

#include "../core/Line3D.h"
#include "../core/Point3D.h"
#include "../display/Displayable.h"

/*
 * #################
 *  Shape3D<M, E> :)
 * #################
 */
template<typename M, typename E> class Shape3D : public Point3D<M, E>, public Displayable<M, E> {
public:
	Shape3D();
	virtual ~Shape3D();
	Shape3D(const Shape3D<M, E>& shape);

	virtual std::unordered_set<std::shared_ptr<Point3D<M, E>>> getPPoints() const;
	virtual std::unordered_set<std::shared_ptr<Line3D<M, E>>> getPLines() const;
	virtual std::unordered_set<std::shared_ptr<Triangle3D<M, E>>> getPTriangles() const;

	//virtual std::unordered_set<std::shared_ptr<Point3D<M, E>>> getPoints() const;//To render the shape
	//virtual std::unordered_set<std::shared_ptr<Line3D<M, E>>> getLines() const;//To render the shape
	//virtual std::unordered_set<std::shared_ptr<Line3D<M, E>>> getLines() const;//To render the shape

	virtual std::string to_string(const bool& spread=false, const bool& full_info=false, const unsigned char& indent=0) const;
	virtual void print(const bool& spread=false, const bool& full_info=false, const unsigned char& indent=0) const;
};

template<typename M, typename E> Shape3D<M, E>::Shape3D() {
	// TODO Auto-generated constructor stub

}

template<typename M, typename E> Shape3D<M, E>::~Shape3D() {
	// TODO Auto-generated destructor stub
}

template<typename M, typename E> Shape3D<M, E>::Shape3D(const Shape3D &other) {
	// TODO Auto-generated constructor stub

}


template<typename M, typename E> std::unordered_set<std::shared_ptr<Point3D<M, E>>> Shape3D<M, E>::getPPoints() const {
	std::unordered_set<std::shared_ptr<Point3D<M, E>>> ppoints;
	return ppoints;
}

template<typename M, typename E> std::unordered_set<std::shared_ptr<Line3D<M, E>>> Shape3D<M, E>::getPLines() const {
	std::unordered_set<std::shared_ptr<Line3D<M, E>>> plines;
	return plines;
}

template<typename M, typename E> std::unordered_set<std::shared_ptr<Triangle3D<M, E>>> Shape3D<M, E>::getPTriangles() const {
	std::unordered_set<std::shared_ptr<Triangle3D<M, E>>> ptriangles;
	return ptriangles;
}


template<typename M, typename E> std::string Shape3D<M, E>::to_string(const bool& spread, const bool& full_info, const unsigned char& indent) const {
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

template<typename M, typename E> void Shape3D<M, E>::print(const bool& spread, const bool& full_info, const unsigned char& indent) const {
	printTabs(indent);
	std::cout << this->to_string(spread, full_info, indent);
}


#endif /* SHAPE3D_H_ */
