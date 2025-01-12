/*
 * Triangle3D.h
 *
 *  Created on: 20 mai 2024
 *      Author: esn
 */

#ifndef TRIANGLE3D_H_

#define TRIANGLE3D_H_

#include <memory>

#include "../core/Point3D.h"

/*
 * ####################
 *  Triangle3D<M, E> :)
 * ####################
 * A set of 3 points.
 */
template<typename M, typename E> class Triangle3D {
public:
	std::shared_ptr<Point3D<M, E>> pp1;
	std::shared_ptr<Point3D<M, E>> pp2;
	std::shared_ptr<Point3D<M, E>> pp3;

	Triangle3D();
	Triangle3D(const Point3D<M, E>& p1, const Point3D<M, E>& p2, const Point3D<M, E>& p3);
	Triangle3D(std::shared_ptr<Point3D<M, E>> pp1, std::shared_ptr<Point3D<M, E>> pp2, std::shared_ptr<Point3D<M, E>> pp3);
	virtual ~Triangle3D();
	Triangle3D(const Triangle3D& triangle);

	//virtual std::unordered_set<std::shared_ptr<Point3D<M, E>>> getPoints() const;//To render the shape
	//virtual std::unordered_set<std::shared_ptr<Line3D<M, E>>> getLines() const;//To render the shape

	virtual std::string to_string(const bool& spread=false, const bool& full_info=false, const unsigned char& indent=0) const;
	virtual void print(const bool& spread=false, const bool& full_info=false, const unsigned char& indent=0) const;
};


template<typename M, typename E> Triangle3D<M, E>::Triangle3D() {
	pp1=std::make_shared<Point3D<M, E>>(Point3D<M, E>{{1,0},{0,0},{0,0}});
	pp2=std::make_shared<Point3D<M, E>>(Point3D<M, E>{{0,0},{1,0},{0,0}});
	pp3=std::make_shared<Point3D<M, E>>(Point3D<M, E>{{0,0},{0,0},{1,0}});
}

template<typename M, typename E> Triangle3D<M, E>::Triangle3D(const Point3D<M, E>& p1, const Point3D<M, E>& p2, const Point3D<M, E>& p3) {
	pp1=std::make_shared<Point3D<M, E>>(p1);
	pp2=std::make_shared<Point3D<M, E>>(p2);
	pp3=std::make_shared<Point3D<M, E>>(p3);
}

template<typename M, typename E> Triangle3D<M, E>::Triangle3D(std::shared_ptr<Point3D<M, E>> pp1, std::shared_ptr<Point3D<M, E>> pp2, std::shared_ptr<Point3D<M, E>> pp3) {
	this->pp1=pp1;
	this->pp2=pp2;
	this->pp3=pp3;
}

template<typename M, typename E> Triangle3D<M, E>::~Triangle3D() {
	;
}

template<typename M, typename E> Triangle3D<M, E>::Triangle3D(const Triangle3D& triangle) {
	this->pp1=triangle.pp1;
	this->pp2=triangle.pp2;
	this->pp3=triangle.pp3;
}




template<typename M, typename E> std::string Triangle3D<M, E>::to_string(const bool& spread, const bool& full_info, const unsigned char& indent) const {
	std::string mes=((spread)?"\n" : "");

	if (full_info){
		mes+="TRIANGLE [";
		std::stringstream ss;
		ss << this;
		mes+=ss.str();
		mes+="]:";
		mes+=((spread)?"\n" : "");
	}

	return mes;
}

template<typename M, typename E> void Triangle3D<M, E>::print(const bool& spread, const bool& full_info, const unsigned char& indent) const {
	printTabs(indent);
	std::cout << this->to_string(spread, full_info, indent);
}



#endif /* TRIANGLE3D_H_ */
