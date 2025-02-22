/*
 * functions_Line3D.hpp
 *
 *  Created on: 22 decembre 2024
 *      Author: esn
 */

#ifndef FUNCTIONS_LINE3D_HPP_

#define FUNCTIONS_LINE3D_HPP_

#include <memory>

#include "Line3D.hpp"


template<typename T> std::string to_string(const Line3D<T>& l) const {
	std::string mes="";

	mes+="LINE3D[";
	std::stringstream ss;
	ss << this;
	mes+=ss.str();
	mes+="]:";
	
	mes+="(";
	mes+="P1" + (this->pp1==NULL)?:" NULL", to_string(*this->pp1);
	mes+=" ; ";
	mes+="P2" + (this->pp2==NULL)?:" NULL", to_string(*this->pp2);
	mes+=")";

	return mes;
}

template<typename T> void print(const Line3D<T>& l) const {
	printTabs(indent);
	std::cout << this->to_string(spread, full_info, indent);
}


#endif /* FUNCTIONS_LINE3D_HPP_ */
