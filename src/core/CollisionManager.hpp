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
#include "Mobile3D.hpp"



/*
 * #######################
 *  CollisionManager<U> :)
 * #######################
 * U: Unit of the target
 * P: Type of the property (SN<float, char>, float, bool, ...)
 * Not properly designed yet.
 */
template<typename U> class CollisionManager : public TimeSensitive {
public:
	std::unordered_set<Mobile3D<U>> pmobiles;					// Object to which 
	ptrAlgo;			//Algo to sort
	
	CollisionManager();
	CollisionManager(std::unordered_set<Mobile3D<T>> pmobiles);
	virtual ~CollisionManager();
	CollisionManager(const CollisionManager<U>& collision_manager);
	
	// From TimeSensitive
	virtual float getT() const {return TimeSensitive::getT();};
	virtual void setT(const float& dt);
	virtual void apply();
};



template<typename U> CollisionManager<U>::CollisionManager() {
	;
}

template<typename U> CollisionManager<U>::CollisionManager(std::shared_ptr<U> pcollision_manager) {
	this->pmobiles=pcollision_manager->pmobiles;
}

template<typename U> CollisionManager<U>::~CollisionManager() {
	;
}

template<typename U> CollisionManager<U>::CollisionManager(const CollisionManager<U>& pcollision_manager) {
	this->ptarget=property_set.ptarget;
}


/*
 * From TimeSensitive
 */

/**
 * k
 */
template<typename U> inline void CollisionManager<U>::setT(const float& dt) {
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

template<typename U> inline void CollisionManager<U>::apply() {
	// We aaply to each element
	//printf("System3D: apply");
	for (std::shared_ptr<U> pelement : this->m_pelements){
		pelement->apply();
	}
	// Than we recalculate the System3D
	this->recalculate();
}






/**
 * ensemble des traces laissées par les objects durant cet interval de temps
 */
getDX(std::unordered_set<std::shared<Mobile3D>> pdx, float dt) {
	;
}


/**
 * pDx: ensemble des traces laissées par les objects durant cet interval de temps
 */
law(std::unordered_set<Line<T>> pdx) {
	;
}




#endif /* COLLISION_MANAGER_HPP_ */
