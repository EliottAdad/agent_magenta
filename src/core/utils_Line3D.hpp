/*
 * utils_Line3D.hpp
 *
 *  Created on: 22 decembre 2024
 *      Author: esn
 */

#ifndef UTILS_LINE3D_HPP_

#define UTILS_LINE3D_HPP_

#include <memory>

#include "Line3D.hpp"


template<typename T> std::string to_string(const Line3D<T>& l) {
	std::string mes="";

	mes+="LINE3D[";
	std::stringstream ss;
	ss << &l;
	mes+=ss.str();
	mes+="]:";
	
	mes+="(";
	mes+="P1" + (l.pp1==NULL)?:" NULL", to_string(*l.pp1);
	mes+=" ; ";
	mes+="P2" + (l.pp2==NULL)?:" NULL", to_string(*l.pp2);
	mes+=")";

	return mes;
}

template<typename T> void print(const Line3D<T>& l) {
	std::cout << to_string(l);
}


#endif /* FUNCTIONS_LINE3D_HPP_ */
