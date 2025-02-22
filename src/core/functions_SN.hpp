/*
 * functions_Particle3D.hpp
 *
 *  Created on: 22 decembre 2024
 *      Author: esn
 */

#ifndef FUNCTIONS_SN_HPP_

#define FUNCTIONS_SN_HPP_

#include <memory>

#include "SN.hpp"


template<typename M, typename E> std::string to_string(const SN<M, E>& nb, const bool& spread, const bool& full_info, const unsigned char& indent) const {
	std::string mes="";
		mes+="SN[";
		std::stringstream ss;
		ss << this;
		mes+=ss.str();
		mes+="]:";
		mes+=std::to_string(m) + "x10^" + std::to_string(e);

	return mes;
}

template<typename M, typename E> void print(const SN<M, E>& nb, const bool& spread, const bool& full_info, const unsigned char& indent) const {
	printTabs(indent);
	std::cout << this->to_string(spread, full_info, indent);
}


#endif /* FUNCTIONS_SN_HPP_ */
