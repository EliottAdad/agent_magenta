/*
 * utils_TimeManager.hpp
 *
 *  Created on: 22 decembre 2024
 *      Author: esn
 */

#ifndef UTILS_TIME_MANAGER_HPP_

#define UTILS_TIME_MANAGER_HPP_

#include <memory>

#include "TimeManager.hpp"


std::string to_string(const TimeManager& time_manager) {
	std::string mes="";
	
	mes+="TIME_MANAGER[";
	std::stringstream ss;
	ss << &time_manager;
	mes+=ss.str();
	mes+="]:";
	//mes+=std::to_string(m) + "x10^" + std::to_string(e);

	return mes;
}

void print(const TimeManager& time_manager) {
	std::cout << to_string(time_manager);
}


#endif /* UTILS_TIME_MANAGER_HPP_ */
