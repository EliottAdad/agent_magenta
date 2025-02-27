/*
 * Static3D.hpp
 *
 *  Created on: 31 janv. 2025
 *      Author: esn
 */

#ifndef STATIC3D_HPP_

#define STATIC3D_HPP_

#include <memory>

#include "Point3D.hpp"
#include "CoordinateSystem3D.hpp"
#include "TimeSensitive.hpp"
#include "../geometry/Shape3D.hpp"

/**
 * ###############
 *  Static3D<T> :)
 * ###############
 * @brief
 * Abstract class
 * TimeSensitive + Point3D + getX(),Y(),Z() + getPosition() + CoordSystem + Hitbox
 * 
 */
template<typename T> class Static3D : public TimeSensitive {
public:
	std::shared_ptr<Point3D<T>> ppoint;				// Position
	std::shared_ptr<CoordinateSystem3D<T>> pcoord_system;
	
	std::shared_ptr<Shape3D<T>> phit_box;							// Pointer to the hibox (used for computing collisions)
	bool fcollide;													// Flag true if collide using the collision box
	
	Static3D();
	virtual ~Static3D();
	Static3D(const Static3D<T>& staticc);
	
	virtual T getX() const = 0;
	virtual T getY() const = 0;
	virtual T getZ() const = 0;
	virtual Point3D<T> getPosition() const = 0;
};





template<typename T> inline Static3D<T>::Static3D() : TimeSensitive() {
	this->ppoint=std::make_shared<Point3D<T>>();
	this->pcoord_system=std::make_shared<CoordinateSystem3D<T>>();
	
	this->phit_box=NULL;
	this->fcollide=false;
}

template<typename T> inline Static3D<T>::~Static3D() {
	// TODO Auto-generated destructor stub
}

template<typename T> inline Static3D<T>::Static3D(const Static3D<T>& staticc) : TimeSensitive(staticc) {
	this->ppoint=staticc.ppoint;
	this->pcoord_system=staticc.pcoord_system;
	
	this->phit_box=staticc.phit_box;
	this->fcollide=staticc.fcollide;
}



template<typename T> inline T Static3D<T>::getX() const {
	return this->ppoint->x;
}

template<typename T> inline T Static3D<T>::getY() const {
	return this->ppoint->y;
}

template<typename T> inline T Static3D<T>::getZ() const {
	return this->ppoint->z;
}

template<typename T> inline Point3D<T> Static3D<T>::getPosition() const {
	return Point3D<T>{this->ppoint->x, this->ppoint->y, this->ppoint->z};
}




#endif /* STATIC3D_HPP_ */
