/*
 * functions_Vector3D.hpp
 *
 *  Created on: 22 decembre 2024
 *      Author: esn
 */

#ifndef FUNCTIONS_VECTOR3D_HPP_

#define FUNCTIONS_VECTOR3D_HPP_

#include <memory>

#include "Vector3D.hpp"


template<typename T> std::string to_string(const Vector3D<T>& v) const {
	std::string mes="";

	mes+="VECTOR3D[";
	std::stringstream ss;
	ss << this;
	mes+=ss.str();
	mes+="]:";
	
	mes+="(";
	mes+="P1";
	mes+= (this->pp1==NULL)?" NULL": to_string(*this->pp1);
	mes+=" ; ";
	
	mes+="P2";
	mes+=(this->pp2==NULL)?" NULL": to_string(*this->pp2);
	mes+=")";

	return mes;
}

template<typename T> void print(const Vector3D<T>& v) const {
	printTabs(indent);
	std::cout << this->to_string(spread, full_info, indent);
}



#endif /* FUNCTIONS_VECTOR3D_HPP_ */
