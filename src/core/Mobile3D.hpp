/*
 * Mobile3D.hpp
 *
 *  Created on: 31 janv. 2025
 *      Author: esn
 */

#ifndef MOBILE3D_HPP_

#define MOBILE3D_HPP_

#include <memory>

#include "CoordinateSystem3D.hpp"
#include "Point3D.hpp"
#include "TimeSensitive.hpp"
#include "../geometry/Shape3D.hpp"

/**
 * ###############
 *  Mobile3D<T> :)
 * ###############
 * Abstract class
 * TimeSensitive + Point3D + getX + CoordSystem
 */
template<typename T> class Mobile3D : public TimeSensitive {
public:
	std::shared_ptr<Point3D<T>> ppoint;				// Position
	bool fmove;
	//std::shared_ptr<CoordinateSystem3D<T>> pcoord_system;
	std::shared_ptr<Vector3D<T>> ps;											// Linear speed
	std::shared_ptr<Vector3D<T>> prs;											// Angular speed
	
	bool fcollide;																// Flag true if collide using the collision box
	std::shared_ptr<Shape3D<T>> phit_box;											// Pointer to the hibox (used for  
	
	Mobile3D();
	virtual ~Mobile3D();
	Mobile3D(const Mobile3D<T>& mobile);
	
	virtual T getX() const = 0;
	virtual T getY() const = 0;
	virtual T getZ() const = 0;
	virtual Point3D<T> getPosition() const = 0;
};





template<typename T> inline Mobile3D<T>::Mobile3D() : TimeSensitive() {
	this->ppoint=std::make_shared<Point3D<T>>();
	this->fmove=true;
	//this->pcoord_system=std::make_shared<CoordinateSystem3D<T>>();
	this->ps=std::make_shared<Vector3D<T>>();
	this->ps->setNorm((T)0);
	this->prs=std::make_shared<Vector3D<T>>();
	this->prs->setNorm((T)0);
	
	this->fcollide=false;
	this->phit_box=NULL;
}

template<typename T> inline Mobile3D<T>::~Mobile3D() {
	// TODO Auto-generated destructor stub
}

template<typename T> inline Mobile3D<T>::Mobile3D(const Mobile3D<T>& mobile) : TimeSensitive(mobile) {
	this->ppoint=mobile.ppoint;
	this->fmove=mobile.fmove;
	//this->pcoord_system=mobile.pcoord_system;
	this->ps=mobile.ps;
	this->prs=mobile.prs;
	
	this->fcollide=false;
	this->phit_box=mobile.phit_box;
}



template<typename T> inline T Mobile3D<T>::getX() const {
	return this->ppoint->x;
}

template<typename T> inline T Mobile3D<T>::getY() const {
	return this->ppoint->y;
}

template<typename T> inline T Mobile3D<T>::getZ() const {
	return this->ppoint->z;
}

template<typename T> inline Point3D<T> Mobile3D<T>::getPosition() const {
	return Point3D<T>{this->ppoint->x, this->ppoint->y, this->ppoint->z};
}




#endif /* MOBILE3D_HPP_ */
