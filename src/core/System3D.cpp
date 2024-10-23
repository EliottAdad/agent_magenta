/*
 * ParticleSystem3D.cpp
 *
 *  Created on: 7 juin 2024
 *      Author: esn
 */

#include "System3D.h"

template <typename T> System3D<T>::System3D() {
	m_a={1,1};				//10m sided box
	m_poctree=new Oct<T>(m_a);
	m_dt=0;
}

/*System3D::System3D(const System3D &other) {
	// TODO Auto-generated constructor stub

}*/

template <typename T> System3D<T>::~System3D() {
	delete m_poctree;
}



template <typename T> LSN System3D<T>::getA() const {
	return m_poctree->getA();
}

/*template <typename T> void System3D<T>::setA(const LSN& a) {
	m_poctree->m_a=a;
}*/

template <typename T> Oct<T>* System3D<T>::getPOctree() {
	return m_poctree;
}

template <typename T> float System3D<T>::getAlpha() const {
	return m_poctree->m_ALPHA;
}

template <typename T> void System3D<T>::setAlpha(const float& alpha) {
	m_poctree->m_ALPHA=alpha;
}

template <typename T> std::unordered_set<T*> System3D<T>::getPElements() const {
	return m_poctree->getPElements();
}

template <typename T> bool System3D<T>::addPParticle(Particle3D* ppart) {
	bool success=false;
	if (ppart!=NULL) {
		success=m_poctree->insert(ppart);
	}
	return success;
}


template <typename T> void System3D<T>::setT(const long double& dt) {
	m_dt=dt;
	//this->apply()
}

template <typename T> void System3D<T>::apply(const Vector3D& dv){
	for (T* ppart : m_poctree->getPElements()){
		ppart->apply(dv);
	}
}


/*void System3D::move(const Vector3D& dv) {
	for (Particle3D* ppart : m_poctree->getPElements()){
		//ppart->wp+= dp.getP2();
		//ppart->addAsPos(dp);
	}
}*/



template <typename T> std::string System3D<T>::to_string(const bool& spread, const bool& full_info, const unsigned int& indent) const {
	std::string mes=((spread)?"\n" : "");

	if (full_info){
		mes+="SYSTEM ():";
		mes+=((spread)?"\n" : "");
	}
	for (T* ppart : m_poctree->getPElements()){
		mes+="	- ( ";
		mes+=ppart->to_string(false, false);
		mes+=" )";
		mes+="\n";
	}
	return mes;
}

template <typename T> void System3D<T>::print(const bool& spread, const bool& full_info, const unsigned int& indent) const {
	printTabs(indent);
	printf((this->to_string(spread, indent, full_info)).c_str());
}

