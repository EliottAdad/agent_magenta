/*
 * Polyhedron.cpp
 *
 *  Created on: 20 mai 2024
 *      Author: esn
 */

#include "Polyhedron.h"

Polyhedron::Polyhedron() {
	// TODO Auto-generated constructor stub

}

Polyhedron::~Polyhedron() {
	// TODO Auto-generated destructor stub
}

Polyhedron::Polyhedron(const Polyhedron &other) {
	// TODO Auto-generated constructor stub

}


std::string Polyhedron::to_string(const bool& spread, const bool& full_info, const unsigned int& indent) const {
	std::string mes=((spread)?"\n" : "");

	if (full_info){
		mes+="POLYHEDRON ():";
		mes+=((spread)?"\n" : "");
	}
	/*for (Particle3D* ppart : m_poctree->getPElements()){
		mes+="	- ( ";
		mes+=ppart->to_string(false, false);
		mes+=" )";
		mes+="\n";
	}*/
	return mes;
}

void Polyhedron::print(const bool& spread, const bool& full_info, const unsigned int& indent) const {
	printTabs(indent);
	printf((this->to_string(spread, indent, full_info)).c_str());
}


