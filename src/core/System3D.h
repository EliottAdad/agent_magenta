/*
 * ParticleSystem3D.h
 *
 *  Created on: 7 juin 2024
 *      Author: esn
 */

#ifndef SYSTEM3D_H_
#define SYSTEM3D_H_

#include <unordered_set>

#include "Particle3D.h"
#include "Oct.h"
#include "TimeSensitive.h"

/*
 * ############
 *  System3D :)
 * ############
 * Can contain any object having ->x, ->y, ->z and ->w
 */
template <typename T> class System3D: public TimeSensitive {
protected:
	LSN m_a;														// Lenght of the side of the zone
	//std::unordered_set<Particle3D*> m_pparticles;					// Pointers to the Particles (useless: already in the octree)
	Oct<T>* m_poctree;												// Pointer to the Octree.
	long double m_dt;

public:
	System3D();
	//System3D(const System3D &other);
	virtual ~System3D();

	LSN getA() const;
	/*void setA(const LSN& a);*/
	Oct<T>* getPOctree();
	//void setOctree(const float& alpha);
	float getAlpha() const;
	void setAlpha(const float& alpha);
	std::unordered_set<T*> getPElements() const;
	bool addPElement(T* pelement);
	//void removePParticle(Particle3D* ppart);
	//void empty();

	virtual void setT(const long double& dt);	// TimeSensitive
	virtual void apply(const Vector3D& dv);		// Moveable
	//virtual void move(const Vector3D& dp);

	virtual std::string to_string(const bool& spread=false, const bool& full_info=false, const unsigned int& indent=0) const;// :)
	virtual void print(const bool& spread=false, const bool& full_info=false, const unsigned int& indent=0) const;// :)
};

/*
 * Returns the vector immediately
 */
//Vector3D grav(const Particle3D& p1, const Particle3D& p2);


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

template <typename T> bool System3D<T>::addPElement(T* pelement) {
	bool success=false;
	if (pelement!=NULL) {
		success=m_poctree->insert(pelement);
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




#endif /* SYSTEM3D_H_ */
