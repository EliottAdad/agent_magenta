/*
 * utils_Physics.hpp
 *
 *  Created on: 22 decembre 2024
 *      Author: esn
 */

#ifndef UTILS_PHYSICS_HPP_

#define UTILS_PHYSICS_HPP_

#include <memory>

#include "Physics.hpp"


std::string to_string(const Physics& physics) {
	std::string mes="";
	
	mes+="PHYSICS[";
	std::stringstream ss;
	ss << &physics;
	mes+=ss.str();
	mes+="]:";
	//mes+=std::to_string(m) + "x10^" + std::to_string(e);

	return mes;
}

void print(const Physics& physics) {
	std::cout << to_string(physics);
}


#endif /* UTILS_PHYSICS_HPP_ */
