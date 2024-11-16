/*
 * VectorFieldUnidirectional.cpp
 *
 *  Created on: 18 mai 2024
 *      Author: esn
 */

#include "VectorFieldUnidirectional.h"

VectorFieldUnidirectional::VectorFieldUnidirectional() {
	m_k=1;
	m_pv=new Vector3D(Point3D{LSN{0, 0}, LSN{0, 0}, LSN{0, 0}}, Point3D{LSN{1, 0}, LSN{1, 0}, LSN{1, 0}});//:?
	m_delv=true;
}

VectorFieldUnidirectional::~VectorFieldUnidirectional() {
	if (m_delv){
		delete m_pv;
	}
}

/*
 * Methods
 */

Vector3D VectorFieldUnidirectional::getVector() const{
	return *m_pv;
}

Vector3D* VectorFieldUnidirectional::getPVector(){
	return (m_delv)?NULL : m_pv;
}


/*void VectorFieldUnidirectional::addAsForce(const long double& dt){
	for (ParticleSet* ppart_set : m_ppart_sets){
		ppart_set->addAsForce(*m_pv, dt);
	}
}

void VectorFieldUnidirectional::addAsAcc(const long double& dt){
	for (ParticleSet* ppart_set : m_ppart_sets){
		ppart_set->addAsAcc(*m_pv, dt);
	}
}

void VectorFieldUnidirectional::addAsSpeed(){
	for (ParticleSet* ppart_set : m_ppart_sets){
		ppart_set->addAsSpeed(*m_pv);
	}
}

void VectorFieldUnidirectional::addAsPos(){
	for (ParticleSet* ppart_set : m_ppart_sets){
		ppart_set->addAsPos(*m_pv);
	}
}

void VectorFieldUnidirectional::applyAsForce(const long double& dt){
	for (ParticleSet* ppart_set : m_ppart_sets){
		ppart_set->applyAsForce(*m_pv, dt);
	}
}

void VectorFieldUnidirectional::applyAsAcc(const long double& dt){
	for (ParticleSet* ppart_set : m_ppart_sets){
		ppart_set->applyAsAcc(*m_pv, dt);
	}
}

void VectorFieldUnidirectional::applyAsSpeed(){
	for (ParticleSet* ppart_set : m_ppart_sets){
		ppart_set->applyAsSpeed(*m_pv);
	}
}

void VectorFieldUnidirectional::applyAsPos(){
	for (ParticleSet* ppart_set : m_ppart_sets){
		ppart_set->applyAsPos(*m_pv);
	}
}*/

/*
 * Redefines setT() from TimeSensitive
 */
void VectorFieldUnidirectional::setT(const long double& dt){
	for (Moveable* pmov : m_pmoveables){
		//Vector3D v(*m_pv);
		//v*=pow(dt, m_mode);
		//v/=factorial(m_mode);
		pmov->apply();
	}
}


std::string VectorFieldUnidirectional::to_string(const bool& spread, const bool& full_info, const unsigned int& indent) const {// :)
	std::string mes=(spread)?"\n":"";

	mes+="VECTOR_FIELD_UNIDIRECTIONAL";

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
		mes+="-";
		mes+=pmoveable->to_string(spread, full_info);
	}
	return mes;
}

void VectorFieldUnidirectional::print(const bool& spread, const bool& full_info, const unsigned int& indent) const {// :)
	printTabs(indent);
	std::cout << this->to_string(spread, full_info, indent);
}

