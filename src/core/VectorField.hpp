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

#include "TimeSensitive.hpp"
//#include "../utilities/Printable.hpp"


/*
 * ###############
 *  VectorField :)
 * ###############
 * Uses the weights of the particles.
 */
template <typename T> class VectorField : public TimeSensitive {
protected:

public:
	std::shared_ptr<Vector3D<T>> pv;
	std::unordered_set<std::shared_ptr<Mobile3D<T>>> pmobiles;					// Pointers to the Mobiles.
	// @TODO change mode to integer where it indicates the degree of differenciation (acc, jerks, ...) no speed or displacement
	unsigned char mode;										// Indication about whether it should be applied to the particles as acceleration('a'), jerk('j') or displacement('d').
	float k;													// Coeff of proportionnality to apply.

	VectorField();
	//VectorField(std::unordered_set<Particle3D*>* pparts);
	virtual ~VectorField();
	VectorField(const VectorField<T>& vector_flied);

	bool add(std::shared_ptr<Mobile3D<T>> pmobile);
	bool remove(std::shared_ptr<Mobile3D<T>> pmobile);

	// From TimeSensitive
	virtual float getT() const {return TimeSensitive::getT();};
	virtual void setT(const float& dt) {TimeSensitive::setT(dt);};//Apply given the mode (a, j, p)
	virtual void apply() {TimeSensitive::apply();};
};




template<typename T> inline VectorField<T>::VectorField() {
	mode=2;
	k=1;
}

template<typename T> inline VectorField<T>::~VectorField() {
	/*for (Moveable* pmov : m_pmoveables){//Maybe not necessary.
		pmov=NULL;
	}*/
	//m_pmoveables.clear();
}

template<typename T> inline VectorField<T>::VectorField(const VectorField& vector_field) {
	;
}





template<typename T> inline bool VectorField<T>::add(std::shared_ptr<Mobile3D<T>> pmobile) {
	bool success=false;
	if (pmobile!=NULL){
		success=(pmobiles.insert(pmobile)).second;
		//std::cout << "Success? " << (m_pmoveables.insert(pmoveable)).second;
		//m_pmoveables.insert(pmoveable);
	}
	return success;
}
/**
 * True if was there before
 * false if not
 */
template<typename T> inline bool VectorField<T>::remove(std::shared_ptr<Mobile3D<T>> pmoveable) {
	return pmobiles.erase(pmoveable)==0?false:true;
}



/*void VectorField::applyAsAcc(const double& dt){
	;
}

void VectorField::applyAsSpeed(){
	;
}

void VectorField::applyAsPos(){

}*/



#endif /* VECTORFIELD_HPP_ */
