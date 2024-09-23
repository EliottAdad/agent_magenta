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



std::string Printable::to_string(const bool& spread, const bool& full_info, const unsigned int& indent) const{
	std::string mes=((spread)?"\n" : "");
	//mes+=((spread)?to_stringTabs(indent) : "");
	//mes+=((spread)?to_stringTabs(0) : "");
	//mes+="QUAD";

	if (full_info){
		mes+="PRINTABLE[";
		mes+="p";									//Pointer
		mes+="]";
		mes+=((spread)?"\n" : "");
	}

	return mes;
}

void Printable::print(const bool& spread, const bool& full_info, const unsigned int& indent) const{
	printTabs(indent);
	//printf((to_string(spread, indent, full_info)).c_str());
	std::cout << this->to_string(spread, full_info, indent);
}

