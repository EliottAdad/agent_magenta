/*
 * utils_PropertySet.hpp
 *
 *  Created on: 22 decembre 2024
 *      Author: esn
 */

#ifndef UTILS_PROPERTYSET_HPP_

#define UTILS_PROPERTYSET_HPP_

#include <memory>

#include "PropertySet.hpp"


template<typename U, typename T> std::string to_string(const PropertySet<U, T>& property_set) {
	std::string mes="";
	
	mes+="PROPERTYSET[";
	std::stringstream ss;
	ss << &property_set;
	mes+=ss.str();
	mes+="]:";
	//mes+=std::to_string(m) + "x10^" + std::to_string(e);

	return mes;
}

template<typename U, typename T> void print(const PropertySet<U, T>& property_set) {
	std::cout << to_string(property_set);
}


#endif /* UTILS_PROPERTYSET_HPP_ */
