/*
 * utils_Vector3D.hpp
 *
 *  Created on: 22 decembre 2024
 *      Author: esn
 */

#ifndef UTILS_VECTOR3D_HPP_

#define UTILS_VECTOR3D_HPP_

#include <memory>

#include "Vector3D.hpp"


template<typename T> std::string to_string(const Vector3D<T>& v) {
	std::string mes="";

	mes+="VECTOR3D[";
	std::stringstream ss;
	ss << &v;
	mes+=ss.str();
	mes+="]:";
	
	mes+="(";
	mes+="P1";
	mes+= to_string(v.getP1());
	mes+=" ; ";
	
	mes+="P2";
	mes+= to_string(v.getP2());
	mes+=")";

	return mes;
}

template<typename T> void print(const Vector3D<T>& v) {
	std::cout << to_string(v);
}



#endif /* FUNCTIONS_VECTOR3D_HPP_ */
