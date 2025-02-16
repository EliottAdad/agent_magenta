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

#include "../core/Point3D.hpp"

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


#endif /* FUNCTIONS_POINT3D_HPP_ */
