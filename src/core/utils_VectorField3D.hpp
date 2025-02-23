/*
 * utils_SN.hpp
 *
 *  Created on: 22 decembre 2024
 *      Author: esn
 */

#ifndef UTILS_VECTORFIELD3D_HPP_

#define UTILS_VECTORFIELD3D_HPP_

#include <memory>

#include "VectorField3D.hpp"


template<typename T> std::string to_string(const VectorField3D<T>& vfield) {
	std::string mes="";
	
	mes+="VECTORFIELD3D[";
	std::stringstream ss;
	ss << &vfield;
	mes+=ss.str();
	mes+="]:";
	//mes+=std::to_string(m) + "x10^" + std::to_string(e);

	return mes;
}

template<typename T> void print(const VectorField3D<T>& vfield) {
	std::cout << to_string(vfield);
}


#endif /* UTILS_VECTORFIELD3D_HPP_ */
