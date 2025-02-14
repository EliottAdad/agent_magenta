/*
 * VectorField.hpp
 *
 *  Created on: 9 mai 2024
 *      Author: esn
 */

#ifndef VECTORFIELD_HPP_

#define VECTORFIELD_HPP_


#include <memory>
#include <vector>
#include <unordered_set>
#include <iostream>

//#include "Particle3DSet.hpp"
#include "TimeSensitive.hpp"
//#include "../utilities/Printable.hpp"


/*
 * ###############
 *  VectorField :)
 * ###############
 * Uses the weights of the particles.
 */
/*template <typename T> */
class VectorField {
protected:
	// @TODO change mode to integer where it indicates the degree of differenciation (acc, jerks, ...) no speed or displacement
	unsigned char m_mode;										// Indication about whether it should be applied to the particles as acceleration('a'), jerk('j') or displacement('d').
	float m_k;													// Coeff of proportionnality to apply.
	std::unordered_set<TimeSensitive*> m_pmoveables;					// Pointers to the TimeSensitives.

public:
	VectorField();
	//VectorField(std::unordered_set<Particle3D*>* pparts);
	virtual ~VectorField();
	VectorField(const VectorField &other);

	std::unordered_set<TimeSensitive*> getPMoveables() const;
	bool addPMoveable(TimeSensitive* pmoveable);
	unsigned char getMode() const;
	void setMode(const unsigned char& mode);

	/*virtual void applyAsAcc(const float& dt);
	virtual void applyAsSpeed();
	virtual void applyAsPos();*/
	virtual void setT(const float& dt);//Apply given the mode (a, j, p)
};




inline VectorField::VectorField() {
	m_mode=2;
	m_k=1;
}

/*VectorField::VectorField(std::unordered_set<Particle3D*>* pparts) {
	m_k=1;
	m_pparticles.insert(pparts);
}*/

inline VectorField::~VectorField() {
	/*for (Moveable* pmov : m_pmoveables){//Maybe not necessary.
		pmov=NULL;
	}*/
	//m_pmoveables.clear();
}

/*VectorField::VectorField(const VectorField &other) {
	;
}*/



inline std::unordered_set<TimeSensitive*> VectorField::getPMoveables() const {
	return m_pmoveables;
}

inline bool VectorField::addPMoveable(TimeSensitive* pmoveable) {
	bool success=false;
	if (pmoveable!=NULL){
		success=(m_pmoveables.insert(pmoveable)).second;
		//std::cout << "Success? " << (m_pmoveables.insert(pmoveable)).second;
		//m_pmoveables.insert(pmoveable);
	}
	return success;
}

inline unsigned char VectorField::getMode() const {
	return m_mode;
}

inline void VectorField::setMode(const unsigned char& mode) {
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

inline void VectorField::setT(const float& dt){
	;
}




#endif /* VECTORFIELD_HPP_ */
