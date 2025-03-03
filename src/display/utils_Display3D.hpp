/*
 * utils_Display3D.hpp
 *
 *  Created on: 28 janv. 2025
 *      Author: esn
 */
 
#ifndef UTILS_DISPLAY3D_HPP_

#define UTILS_DISPLAY3D_HPP_

#include "Display3D.hpp"


template<typename T> std::string to_string(const Display3D<T>& display) {// :)
	std::string mes="";

	mes+="DISPLAY3D\n";

	return mes;
}

template<typename T> void print(const Display3D<T>& display) {// :)
	std::cout << to_string(display);
}


 #endif /* UTILS_DISPLAY3D_HPP_ */
