/*
 * Shape3D.cpp
 *
 *  Created on: 20 mai 2024
 *      Author: esn
 */

#include "Shape3D.h"

Shape3D::Shape3D() {
	// TODO Auto-generated constructor stub

}

Shape3D::~Shape3D() {
	// TODO Auto-generated destructor stub
}

Shape3D::Shape3D(const Shape3D &other) {
	// TODO Auto-generated constructor stub

}



std::string Shape3D::to_string(const bool& spread, const bool& full_info, const unsigned char& indent) const {
	std::string mes=((spread)?"\n" : "");

	if (full_info){
		mes+="SHAPE3D [";
		std::stringstream ss;
		ss << this;
		mes+=ss.str();
		mes+="]:";
		mes+=((spread)?"\n" : "");
	}
	return mes;
}

void Shape3D::print(const bool& spread, const bool& full_info, const unsigned char& indent) const {
	printTabs(indent);
	std::cout << this->to_string(spread, full_info, indent);
}

