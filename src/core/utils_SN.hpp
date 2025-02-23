/*
 * utils_SN.hpp
 *
 *  Created on: 22 decembre 2024
 *      Author: esn
 */

#ifndef UTILS_SN_HPP_

#define UTILS_SN_HPP_

#include <memory>

#include "SN.hpp"


template<typename M, typename E> std::string to_string(const SN<M, E>& nb) {
	std::string mes="";
	
	mes+="SN[";
	std::stringstream ss;
	ss << &nb;
	mes+=ss.str();
	mes+="]:";
	mes+=std::to_string(nb.m) + "x10^" + std::to_string(nb.e);

	return mes;
}

template<typename M, typename E> void print(const SN<M, E>& nb) {
	std::cout << to_string(nb);
}


#endif /* FUNCTIONS_SN_HPP_ */
