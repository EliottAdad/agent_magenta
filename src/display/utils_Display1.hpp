/*
 * utils_Display1.hpp
 *
 *  Created on: 28 janv. 2025
 *      Author: esn
 */
 
#ifndef UTILS_DISPLAY1_HPP_

#define UTILS_DISPLAY1_HPP_

#include "Display1.hpp"


template<typename T> std::string to_string(const Display1<T>& display) {// :)
	std::string mes="";

	mes+="DISPLAY1\n";

	return mes;
}

template<typename T> void print(const Display1<T>& display) {// :)
	std::cout << to_string(display);
}


 #endif /* UTILS_DISPLAY1_HPP_ */
