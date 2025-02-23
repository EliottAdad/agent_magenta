/*
 * utils_CoordinateSystem3D.hpp
 *
 *  Created on: 22 decembre 2024
 *      Author: esn
 */

#ifndef UTILS_COORDINATESYSTEM3D_HPP_

#define UTILS_COORDINATESYSTEM3D_HPP_

#include <memory>

#include "CoordinateSystem3D.hpp"

template<typename U, typename T> std::string to_string(const CoordinateSystem3D<T>& csystem, const unsigned char& indent) {
	std::string mes="";
	
	mes+=to_stringTabs(indent);
	mes+="COORDINATESYSTEM3D[";
	std::stringstream ss;
	ss << &csystem;
	mes+=ss.str();
	mes+="]:";
	
	mes+="[";
	mes+="E1:";
	mes+=((csystem.pe1==NULL)?"NULL":to_string(*csystem.pe1);
	mes+="|";
	mes+="E2:";
	mes+=((csystem.pe1==NULL)?"NULL":to_string(*csystem.pe2);
	mes+="|";
	mes+="E3:";
	mes+=((csystem.pe1==NULL)?"NULL":to_string(*csystem.pe3);
	mes+="]";

	return mes;
}

template<typename U, typename T> void print(const CoordinateSystem3D<T>& csystem) {
	std::cout << to_string(csystem);
}





#endif /* UTILS_COORDINATESYSTEM3D_HPP_ */
