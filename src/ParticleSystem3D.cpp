/*
 * ParticleSystem3D.cpp
 *
 *  Created on: 7 juin 2024
 *      Author: esn
 */

#include "ParticleSystem3D.h"

ParticleSystem3D::ParticleSystem3D() {
	m_a={1,1};				//10m sided box
	m_poctree=new Oct<Particle3D>(m_a);
}

/*ParticleSystem3D::ParticleSystem3D(const ParticleSystem3D &other) {
	// TODO Auto-generated constructor stub

}*/

ParticleSystem3D::~ParticleSystem3D() {
	delete m_poctree;
}



LSN ParticleSystem3D::getA() const {
	return m_poctree->getA();
}

/*void ParticleSystem3D::setA(const LSN& a) {
	m_poctree->m_a=a;
}*/

Oct<Particle3D>* ParticleSystem3D::getPOctree() {
	return m_poctree;
}

float ParticleSystem3D::getAlpha() const {
	return m_poctree->m_ALPHA;
}

void ParticleSystem3D::setAlpha(const float& alpha) {
	m_poctree->m_ALPHA=alpha;
}

std::unordered_set<Particle3D*> ParticleSystem3D::getPParticles() const {
	return m_poctree->getPElements();
}

bool ParticleSystem3D::addPParticle(Particle3D* ppart) {
	bool success=false;
	if (ppart!=NULL) {
		success=m_poctree->insert(ppart);
	}
	return success;
}



void ParticleSystem3D::move(const Vector3D& dp){
	for (Particle3D* ppart : m_poctree->getPElements()){
		//ppart->wp+= dp.getP2();
		//ppart->addAsPos(dp);
	}
}



std::string ParticleSystem3D::to_string(const bool& spread, const bool& full_info, const unsigned int& indent) const {
	std::string mes=((spread)?"\n" : "");

	if (full_info){
		mes+="PARTICLE SET ():";
		mes+=((spread)?"\n" : "");
	}
	for (Particle3D* ppart : m_poctree->getPElements()){
		mes+="	- ( ";
		mes+=ppart->to_string(false, false);
		mes+=" )";
		mes+="\n";
	}
	return mes;
}

void ParticleSystem3D::print(const bool& spread, const bool& full_info, const unsigned int& indent) const {
	printTabs(indent);
	std::cout << this->to_string(spread, full_info, indent);
}

