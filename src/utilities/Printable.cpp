/*
 * Printable.cpp
 *
 *  Created on: 24 août 2024
 *      Author: esn
 */

#include "Printable.h"

Printable::Printable() {
	// TODO Auto-generated constructor stub

}

Printable::~Printable() {
	// TODO Auto-generated destructor stub
}

Printable::Printable(const Printable &other) {
	// TODO Auto-generated constructor stub

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

