/*
 * Printable.hpp
 *
 *  Created on: 24 août 2024
 *      Author: esn
 */

#ifndef PRINTABLE_HPP_
#define PRINTABLE_HPP_

#include <iostream>
#include <string>
#include <sstream>

#include "functions.hpp"

class Printable {
public:
	Printable();
	virtual ~Printable();

	virtual std::string to_string(const bool& spread=false, const bool& full_info=false, const unsigned char& indent=0) const = 0;// :)
	virtual void print(const bool& spread=false, const bool& full_info=false, const unsigned char& indent=0) const = 0;// :)
};




Printable::Printable() {
	// TODO Auto-generated constructor stub

}

Printable::~Printable() {
	// TODO Auto-generated destructor stub
}



std::string Printable::to_string(const bool& spread, const bool& full_info, const unsigned char& indent) const {
	std::string mes=((spread)?"\n" : "");
	printTabs(indent);

	if (full_info){
		mes+="PRINTABLE[";
		std::stringstream ss;
		ss << this;
		mes+=ss.str();
		mes+="]:";
		mes+=((spread)?"\n" : "");
	}

	return mes;
}

void Printable::print(const bool& spread, const bool& full_info, const unsigned char& indent) const {
	printTabs(indent);
	std::cout << this->to_string(spread, full_info, indent);
}



#endif /* PRINTABLE_HPP_ */
