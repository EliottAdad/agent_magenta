/*
 * Triangle3D.cpp
 *
 *  Created on: 20 mai 2024
 *      Author: esn
 */

#include "Triangle3D.h"

template<typename M, typename E> Triangle3D<M, E>::Triangle3D() {
	pp1=new Point3D<M, E>({{1,0},{0,0},{0,0}});
	pp2=new Point3D<M, E>({{0,0},{1,0},{0,0}});
	pp3=new Point3D<M, E>({{0,0},{0,0},{1,0}});
}

template<typename M, typename E> Triangle3D<M, E>::Triangle3D(const Point3D<M, E>& p1, const Point3D<M, E>& p2, const Point3D<M, E>& p3) {
	pp1=new Point3D<M, E>(p1);
	pp2=new Point3D<M, E>(p2);
	pp3=new Point3D<M, E>(p3);
}

template<typename M, typename E> Triangle3D<M, E>::Triangle3D(Point3D<M, E>* pp1, Point3D<M, E>* pp2, Point3D<M, E>* pp3) {
	this->pp1=pp1;
	this->pp2=pp2;
	this->pp3=pp3;
}

template<typename M, typename E> Triangle3D<M, E>::~Triangle3D() {
	;
}

/*template<typename M, typename E> Triangle3D::Triangle3D(const Triangle3D &other) {
	// TODO Auto-generated constructor stub

}*/



/*template<typename M, typename E> Point3D<M, E> Triangle3D<M, E>::getP1() const {
	return *pp1;
}

template<typename M, typename E> Point3D<M, E>* Triangle3D<M, E>::getPP1() {
	return pp1;
}

template<typename M, typename E> void Triangle3D<M, E>::setP1(const Point3D<M, E>& p1) {
	*pp1=p1;
}

template<typename M, typename E> Point3D<M, E> Triangle3D<M, E>::getP2() const {
	return *pp2;
}

template<typename M, typename E> Point3D<M, E>* Triangle3D<M, E>::getPP2() {
	return pp2;
}

template<typename M, typename E> void Triangle3D<M, E>::setP2(const Point3D<M, E>& p2) {
	*pp2=p2;
}

template<typename M, typename E> Point3D<M, E> Triangle3D<M, E>::getP3() const {
	return *pp3;
}

template<typename M, typename E> Point3D<M, E>* Triangle3D<M, E>::getPP3() {
	return pp3;
}

template<typename M, typename E> void Triangle3D<M, E>::setP3(const Point3D<M, E>& p3) {
	*pp3=p3;
}*/


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

