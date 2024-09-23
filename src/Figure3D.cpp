/*
 * Figure3D.cpp
 *
 *  Created on: 20 mai 2024
 *      Author: esn
 */

#include "Figure3D.h"

Figure3D::Figure3D() {
	// TODO Auto-generated constructor stub

}

Figure3D::~Figure3D() {
	// TODO Auto-generated destructor stub
}

Figure3D::Figure3D(const Figure3D &other) {
	// TODO Auto-generated constructor stub

}



std::string Figure3D::to_string(const bool& spread, const bool& full_info, const unsigned int& indent) const {
	std::string mes=((spread)?"\n" : "");

	if (full_info){
		mes+="FIGURE3D ():";
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

void Figure3D::print(const bool& spread, const bool& full_info, const unsigned int& indent) const {
	printTabs(indent);
	std::cout << this->to_string(spread, full_info, indent);
}

