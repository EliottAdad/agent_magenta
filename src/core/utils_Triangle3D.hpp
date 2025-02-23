/*
 * utils_SN.hpp
 *
 *  Created on: 22 decembre 2024
 *      Author: esn
 */

#ifndef UTILS_SN_HPP_

#define UTILS_SN_HPP_

#include <memory>

#include "Triangle3D.hpp"


template<typename T> std::string to_string(const Triangle3D<T>& triangle) {
	std::string mes="";
	
	mes+="TRIANGLE[";
	std::stringstream ss;
	ss << &triangle;
	mes+=ss.str();
	mes+="]:";
	//mes+=std::to_string(m) + "x10^" + std::to_string(e);

	return mes;
}

template<typename T> void print(const Triangle3D<T>& triangle) {
	std::cout << to_string(triangle);
}


#endif /* FUNCTIONS_SN_HPP_ */
