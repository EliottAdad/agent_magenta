/*
 * Mobile3D.hpp
 *
 *  Created on: 31 janv. 2025
 *      Author: esn
 */

#ifndef MOBILE3D_HPP_

#define MOBILE3D_HPP_

#include <memory>

#include "Static3D.hpp"

/**
 * ###############
 *  Mobile3D<T> :)
 * ###############
 * @brief
 * Abstract class
 * The idea is to have a class that has everything to manage movements.
 * Static3D + Speed + RotSpeed
 * Same as Static3D but with speed.
 */
template<typename T> class Mobile3D : public Static3D<T> {
public:
	bool fmove;
	
	std::shared_ptr<Vector3D<T>> ps;											// Linear speed
	std::shared_ptr<Vector3D<T>> prs;											// Angular speed
	
	Mobile3D();
	virtual ~Mobile3D();
	Mobile3D(const Mobile3D<T>& mobile);
	
	virtual Vector3D<T> getSpeed() const = 0;
	virtual Vector3D<T> getRotSpeed() const = 0;
};





template<typename T> inline Mobile3D<T>::Mobile3D() : Static3D<T>() {
	this->fmove=true;
	
	this->ps=std::make_shared<Vector3D<T>>();
	this->ps->setNorm((T)0);
	this->prs=std::make_shared<Vector3D<T>>();
	this->prs->setNorm((T)0);
}

template<typename T> inline Mobile3D<T>::~Mobile3D() {
	// TODO Auto-generated destructor stub
}

template<typename T> inline Mobile3D<T>::Mobile3D(const Mobile3D<T>& mobile) : Static3D<T>(mobile) {
	this->fmove=mobile.fmove;
	
	this->ps=mobile.ps;
	this->prs=mobile.prs;
}



/**
 * Returns the speed
 */
template<typename T> inline Vector3D<T> Mobile3D<T>::getSpeed() const {
	return *(this->ps);
}

/**
 * Returns the rot speed
 */
template<typename T> inline Vector3D<T> Mobile3D<T>::getRotSpeed() const {
	return *(this->prs);
}



#endif /* MOBILE3D_HPP_ */
