/*
 * utils_System3D.hpp
 *
 *  Created on: 22 decembre 2024
 *      Author: esn
 */

#ifndef UTILS_SYSTEM3D_HPP_

#define UTILS_SYSTEM3D_HPP_

#include <memory>

#include "System3D.hpp"


template<typename U, typename T> std::string to_string(const System3D<U, T> system) {
	std::string mes="";

	mes+="SYSTEM3D[";
	std::stringstream ss;
	ss << &system;
	mes+=ss.str();
	mes+="]:\n";
	mes+="a=" + to_string(system.a);
	
	mes+="\n";

	mes+=to_string(*system.poctree, 0);

	return mes;
}

template<typename U, typename T> void print(const System3D<U, T>& system) {
	std::cout << to_string(system);
}


#endif /* FUNCTIONS_SYSTEM3D_HPP_ */
