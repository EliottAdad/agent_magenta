/*
 * VectorField.cpp
 *
 *  Created on: 9 mai 2024
 *      Author: esn
 */

#include "VectorField.h"

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



std::unordered_set<Moveable*> VectorField::getPMoveables() const {
	return m_pmoveables;
}

bool VectorField::addPMoveable(Moveable* pmoveable) {
	bool success=false;
	if (pmoveable!=NULL){
		success=(m_pmoveables.insert(pmoveable)).second;
		//std::cout << "Success? " << (m_pmoveables.insert(pmoveable)).second;
		//m_pmoveables.insert(pmoveable);
	}
	return success;
}

unsigned int VectorField::getMode() const {
	return m_mode;
}

void VectorField::setMode(const unsigned int& mode) {
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

void VectorField::setT(const long double& dt){
	;
}


std::string VectorField::to_string(const bool& spread, const bool& full_info, const unsigned int& indent) const{// :)
	std::string mes=(spread)?"\n":"";

	mes+="VECTOR_FIELD";

	if (full_info){
		mes+="():";//Pointer
		mes+=((spread)?"\n" : "");
	}
	mes+="mode= " + std::to_string(m_mode) + ";k= "+std::to_string(m_k)+";sets: " + std::to_string(m_pmoveables.size()) +"\n";

	mes+="Moveables list:\n";
	int i=0;
	for (Moveable* pmoveable : m_pmoveables){
		i++;
		mes+=std::to_string(i);
		mes+=pmoveable->to_string(true, true);
	}
	return mes;
}

void VectorField::print(const bool& spread, const bool& full_info, const unsigned int& indent) const{// :)
	printTabs(indent);
	printf((this->to_string(spread, indent, full_info)).c_str());
}


