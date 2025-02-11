/*
 * VectorField.cpp
 *
 *  Created on: 9 mai 2024
 *      Author: esn
 */

#include "VectorField.hpp"

VectorField::VectorField() {
	m_mode=2;
	m_k=1;
}

/*VectorField::VectorField(std::unordered_set<Particle3D*>* pparts) {
	m_k=1;
	m_pparticles.insert(pparts);
}*/

VectorField::~VectorField() {
	/*for (Moveable* pmov : m_pmoveables){//Maybe not necessary.
		pmov=NULL;
	}*/
	//m_pmoveables.clear();
}

/*VectorField::VectorField(const VectorField &other) {
	;
}*/



std::unordered_set<TimeSensitive*> VectorField::getPMoveables() const {
	return m_pmoveables;
}

bool VectorField::addPMoveable(TimeSensitive* pmoveable) {
	bool success=false;
	if (pmoveable!=NULL){
		success=(m_pmoveables.insert(pmoveable)).second;
		//std::cout << "Success? " << (m_pmoveables.insert(pmoveable)).second;
		//m_pmoveables.insert(pmoveable);
	}
	return success;
}

unsigned char VectorField::getMode() const {
	return m_mode;
}

void VectorField::setMode(const unsigned char& mode) {
	if (mode>=2){
		m_mode=mode;
	}
}



/*void VectorField::applyAsAcc(const double& dt){
	;
}

void VectorField::applyAsSpeed(){
	;
}

void VectorField::applyAsPos(){

}*/

void VectorField::setT(const float& dt){
	;
}


std::string VectorField::to_string(const bool& spread, const bool& full_info, const unsigned char& indent) const{// :)
	std::string mes=(spread)?"\n":"";

	if (full_info){
		mes+="VECTOR_FIELD[";
		std::stringstream ss;
		ss << this;
		mes+=ss.str();
		mes+="]:";
		mes+=((spread)?"\n" : "");
	}
	mes+="mode= " + std::to_string(m_mode) + ";k= "+std::to_string(m_k)+";sets: " + std::to_string(m_pmoveables.size()) +"\n";

	mes+="Moveables list:\n";
	int i=0;
	for (TimeSensitive* pmoveable : m_pmoveables){
		i++;
		mes+=std::to_string(i);
		mes+=pmoveable->to_string(true, true);
	}
	return mes;
}

void VectorField::print(const bool& spread, const bool& full_info, const unsigned char& indent) const{// :)
	printTabs(indent);
	std::cout << this->to_string(spread, full_info, indent);
}


