/*
 * VectorField3D.hpp
 *
 *  Created on: 9 mai 2024
 *      Author: esn
 */

#ifndef VECTORFIELD3D_HPP_

#define VECTORFIELD3D_HPP_


#include <memory>
#include <vector>
#include <unordered_set>
#include <iostream>

#include "TimeSensitive.hpp"
//#include "../utilities/Printable.hpp"


/*
 * #################
 *  VectorField3D :)
 * #################
 * @brief
 * Uses the weights of the particles.
 */
template <typename T> class VectorField3D : public TimeSensitive {
public:
	std::shared_ptr<Vector3D<T>> pv;
	std::unordered_set<std::shared_ptr<Mobile3D<T>>> pmobiles;					// Pointers to the Mobiles.
	// @TODO change mode to integer where it indicates the degree of differenciation (acc, jerks, ...) no speed or displacement
	unsigned char mode;										// Indication about whether it should be applied to the particles as acceleration('a'), jerk('j') or displacement('d').
	float k;													// Coeff of proportionnality to apply.

	VectorField3D();
	//VectorField3D(std::unordered_set<Particle3D*>* pparts);
	virtual ~VectorField3D();
	VectorField3D(const VectorField3D<T>& vector_flied);

	bool add(std::shared_ptr<Mobile3D<T>> pmobile);
	bool remove(std::shared_ptr<Mobile3D<T>> pmobile);

	// From TimeSensitive
	virtual float getT() const {return TimeSensitive::getT();}
	virtual void setT(const float& dt) {TimeSensitive::setT(dt);}//Apply given the mode (a, j, p)
	virtual void apply() {TimeSensitive::apply();}
};




template<typename T> inline VectorField3D<T>::VectorField3D() : TimeSensitive() {
	mode=2;
	k=1;
}

template<typename T> inline VectorField3D<T>::~VectorField3D() {
	/*for (Moveable* pmov : m_pmoveables){//Maybe not necessary.
		pmov=NULL;
	}*/
	//m_pmoveables.clear();
}

template<typename T> inline VectorField3D<T>::VectorField3D(const VectorField3D& vector_field) : TimeSensitive(vector_field) {
	;
}





template<typename T> inline bool VectorField3D<T>::add(std::shared_ptr<Mobile3D<T>> pmobile) {
	bool success=false;
	if (pmobile!=NULL){
		success=(pmobiles.insert(pmobile)).second;
		//std::cout << "Success? " << (m_pmoveables.insert(pmoveable)).second;
		//m_pmoveables.insert(pmoveable);
	}
	return success;
}

/**
 * @brief
 * True if was there before
 * false if not
 */
template<typename T> inline bool VectorField3D<T>::remove(std::shared_ptr<Mobile3D<T>> pmoveable) {
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



#endif /* VECTORFIELD3D_HPP_ */
