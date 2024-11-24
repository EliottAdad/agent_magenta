/*
 * VectorFieldVortex.cpp
 *
 *  Created on: 18 mai 2024
 *      Author: esn
 */

#include "VectorFieldVortex.h"

VectorFieldVortex::VectorFieldVortex() {
	m_k=1;
	m_m=1;
	this->m_ppoint=new Point3D<float, char>();
}

VectorFieldVortex::~VectorFieldVortex() {
	delete this->m_ppoint;
}


void VectorFieldVortex::applyAsForce(const float& dt){
	/*for (Particle3D* ppart : m_pparticles){
		*(ppart->getPSpeed())+=getDistance(*m_ppoint, ppart->wp)*m_m*dt;//Il faut trouver le vecteur tangent au cercle.
	}*/
}

void VectorFieldVortex::applyAsAcc(const float& dt){
	/*for (Particle3D* ppart : m_pparticles){
		*(ppart->getPSpeed())+=getDistance(*m_ppoint, ppart->wp)*m_m*dt;//Il faut trouver le vecteur tangent au cercle.
	}*/
}

void VectorFieldVortex::applyAsSpeed(){
	/*for (Particle3D* ppart : m_pparticles){
		*(ppart->getPSpeed())+=*m_pv;
	}*/
}

void VectorFieldVortex::applyAsPos(){
	/*for (Particle3D* ppart : m_pparticles){
		//ppart->wp+=m_pv->getP2();
	}*/
}
