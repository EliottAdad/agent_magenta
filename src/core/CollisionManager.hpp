/*
 * CollisionManager.hpp
 *
 *  Created on: 4 juin 2024
 *      Author: esn
 */

#ifndef COLLISION_MANAGER_HPP_

#define COLLISION_MANAGER_HPP_

#include <memory>
#include <unordered_set>

#include "TimeSensitive.hpp"
#include "System3D.hpp"



/*
 * ###############################
 *  CollisionManagerSystem3D<U> :)
 * ###############################
 * U: Unit of the target
 * Manages Mobiles3D
 * Not properly designed yet.
 */
template<typename U> class CollisionManagerSystem3D : public TimeSensitive {
public:
	std::shared_ptr<System3D<U>> psystem;					// Object to which 
	//ptrAlgo;			//Algo to sort
	
	CollisionManagerSystem3D();
	CollisionManagerSystem3D(std::shared_ptr<System3D<U>> psystem);
	virtual ~CollisionManagerSystem3D();
	CollisionManagerSystem3D(const CollisionManagerSystem3D<U>& collision_manager);
	
	// From TimeSensitive
	virtual float getT() const {return TimeSensitive::getT();}
	virtual void setT(const float& dt);
	virtual void apply();
};



template<typename U> CollisionManagerSystem3D<U>::CollisionManagerSystem3D() {
	;
}

template<typename U> CollisionManagerSystem3D<U>::CollisionManagerSystem3D(std::shared_ptr<U> pcollision_manager) {
	this->pmobiles=pcollision_manager->pmobiles;
}

template<typename U> CollisionManagerSystem3D<U>::~CollisionManagerSystem3D() {
	;
}

template<typename U> CollisionManagerSystem3D<U>::CollisionManagerSystem3D(const CollisionManagerSystem3D<U>& collision_manager) {
	this->ptarget=property_set.ptarget;
}


/*
 * From TimeSensitive
 */

/**
 * k
 */
template<typename U> inline void CollisionManagerSystem3D<U>::setT(const float& dt) {
	this->m_dt=dt;
	//printf("System3D: setT");
	// Set time for all objects.
	for (std::shared_ptr<U> pelement : this->m_pelements){
		pelement->setT(this->m_dt);
	}
	// If there is a law to apply... calls it
	if (this->ptrLaw!=NULL){
		//printf("System3D: setT2");
		(*ptrLaw)(this);
	}
}

template<typename U> inline void CollisionManagerSystem3D<U>::apply() {
	// We apply to each element
	if (this->psystem!=NULL){
		for (Oct<U, T>* pleaf : this->psystem->poctree->LEAVES){
			std::unordered_set<std::shared_ptr<U>> ppossible_collisions=this->psystem->getPossibleColliding(pleaf);
			//TODO : traitement des elemeents
			for (std::shared_ptr<U> pU : ppossible_collisions){
				;
			}
		}
	}
}






/**
 * ensemble des traces laissées par les objects durant cet interval de temps
 */
/*getDX(std::unordered_set<std::shared<Mobile3D>> pdx, float dt) {
	;
}*/


/**
 * pDx: ensemble des traces laissées par les objects durant cet interval de temps
 */
/*law(std::unordered_set<Line<T>> pdx) {
	;
}*/




#endif /* COLLISION_MANAGER_HPP_ */
