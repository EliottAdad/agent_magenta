/*
 * functions_Point3D.hpp
 *
 *  Created on: 22 decembre 2024
 *      Author: esn
 */

#ifndef FUNCTIONS_POINT3D_HPP_

#define FUNCTIONS_POINT3D_HPP_

#include <memory>
#include <eigen3/Eigen/Dense>

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

template<typename T> std::string to_string(const Point3D<T>& p) const {
	//std::cout<<"Help1\n";
	std::string mes=((spread)?"\n" : "");
	mes+=to_stringTabs(indent);
	//printf("Help2\n");
	if (full_info){
		mes+="POINT3D[";
		std::stringstream ss;
		ss << this;
		mes+=ss.str();
		mes+="]:";
		mes+=((spread)?"\n" + to_stringTabs(1) : "");
	}
	//printf("Help3\n");
	mes+=to_stringTabs(indent);
	mes+="(x:" + to_string(x) + " ; y:" + to_string(y) + " ; z:" + to_string(z) + ")";

	return mes;
}

template<typename T> void print(const Point3D<T>& p) const {
	printTabs(indent);
	std::cout << this->to_string(spread, full_info, indent);
}

#endif /* FUNCTIONS_POINT3D_HPP_ */
