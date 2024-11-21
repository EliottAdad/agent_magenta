/*
 * Moveable.cpp
 *
 *  Created on: 24 août 2024
 *      Author: esn
 */

#include "Moveable.h"

Moveable::Moveable() {
	// TODO Auto-generated constructor stub

}

Moveable::~Moveable() {
	// TODO Auto-generated destructor stub
}

Moveable::Moveable(const Moveable &other) {
	// TODO Auto-generated constructor stub

}


void Moveable::apply() {//Useless
	;
}

/*void Moveable::apply(const Vector3D& v) {//Useless
	;
}*/

/*void Moveable::applyAsAcc(const Vector3D& v, const double& dt) {//Useless
	;
}

void Moveable::applyAsSpeed(const Vector3D& v) {
	;
}

void Moveable::applyAsPos(const Vector3D& v) {
	;
}*/



std::string Moveable::to_string(const bool& spread, const bool& full_info, const unsigned char& indent) const {// :)
	std::string mes=(spread)?"\n":"";

	mes+="MOVEABLE";

	/*if (full_info){
		mes+="():";//Pointer
		mes+=((spread)?"\n" : "");
	}
	mes+="mode= " + std::to_string(m_mode) + ";k= "+std::to_string(m_k)+";sets: " + std::to_string(m_pmoveables.size()) +"\n";

	mes+="Particles list:\n";
	int i=0;
	for (Moveable* pmoveable : m_pmoveables){
		i++;
		mes+=std::to_string(i);
		mes+=pmoveable->to_string(true, true);
	}*/
	return mes;
}

void Moveable::print(const bool& spread, const bool& full_info, const unsigned char& indent) const {// :)
	printTabs(indent);
	std::cout << this->to_string(spread, full_info, indent);
}



