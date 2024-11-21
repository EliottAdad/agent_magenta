/*
 * Displayable.cpp
 *
 *  Created on: 8 nov. 2024
 *      Author: esn
 */

#include "Displayable.h"

Displayable::Displayable() {
	pcolor=NULL;		// Will be interprated as white by the cameras and displays
	pmesh=NULL;			//
}

Displayable::~Displayable() {
	pcolor=NULL;		// Will be interprated as white by the cameras
	pmesh=NULL;			//
}

Displayable::Displayable(const Displayable &other) {
	pcolor=other.pcolor;		// Will be interprated as white by the cameras
	pmesh=other.pmesh;			//
}


/*SDL_Color* Displayable::getPColor(){
	return m_pcolor;
}*/

/*void Displayable::setColor(int r, int b, int g, int a){
	m_pcolor->r=r;
	m_pcolor->g=g;
	m_pcolor->b=b;
	m_pcolor->a=a;
}*/


LSN Displayable::getX() const{
	return {0, 0};
}

LSN Displayable::getY() const{
	return {0, 0};
}

LSN Displayable::getZ() const{
	return {0, 0};
}


std::string Displayable::to_string(const bool& spread, const bool& full_info, const unsigned char& indent) const {// :)
	std::string mes=(spread)?"\n":"";

	mes+="DISPLAYABLE";

	return mes;
}

void Displayable::print(const bool& spread, const bool& full_info, const unsigned char& indent) const {// :)
	printTabs(indent);
	std::cout << this->to_string(spread, full_info, indent);
}


