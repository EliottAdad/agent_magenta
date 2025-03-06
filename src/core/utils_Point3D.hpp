/*
 * utils_Point3D.hpp
 *
 *  Created on: 22 decembre 2024
 *      Author: esn
 */

#ifndef UTILS_POINT3D_HPP_

#define UTILS_POINT3D_HPP_

#include <memory>
#include <eigen3/Eigen/Dense>
#include "string.h"

#include "Point3D.hpp"

/*
 * Functions
 */

/**
 * g
 */
template<typename T> inline Eigen::Matrix<T, 3, 1> toEigen(const Point3D<T>& p) {
	return Eigen::Matrix<T, 3, 1> {{p.x}, {p.y}, {p.z}};
}

/**
 * g
 */
template<typename T> inline Point3D<T> toPoint(const Eigen::Matrix<T, 3, 1>& m) {
	return Point3D<T>{m[0], m[1], m[2]};
}




/* 
 * Console
 */

template<typename T> std::string to_string(const Point3D<T>& p) {
	std::string mes="";
	
	mes+="POINT3D[";
	std::stringstream ss;
	ss << &p;
	mes+=ss.str();
	mes+="]:";
	
	mes+="(x:" + std::to_string(p.x) + " ; y:" + std::to_string(p.y) + " ; z:" + std::to_string(p.z) + ")";

	return mes;
}

//SN pecific
template<typename M, typename E> std::string to_string(const Point3D<SN<M, E>>& p) {
	std::string mes="";

	mes+="POINT3D[";
	std::stringstream ss;
	ss << &p;
	mes+=ss.str();
	mes+="]:";

	mes+="(x:" + to_string(p.x) + " ; y:" + to_string(p.y) + " ; z:" + to_string(p.z) + ")";

	return mes;
}

template<typename T> void print(const Point3D<T>& p) {
	std::cout << to_string(p);
}

#endif /* FUNCTIONS_POINT3D_HPP_ */
