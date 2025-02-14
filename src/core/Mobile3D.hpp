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

/**
 * ###############
 *  Mobile3D<T> :)
 * ###############
 * Abstract class
 * TimeSensitive + Point3D + getX + CoordSystem
 */
template<typename T> class Mobile3D : public TimeSensitive, public Point3D<T> {
public:
	std::shared_ptr<CoordinateSystem3D<T>> pcoord_system;
	std::shared_ptr<Vector3D<T>> ps;											// Linear speed
	std::shared_ptr<Vector3D<T>> prs;											// Angular speed
	
	Mobile3D();
	virtual ~Mobile3D();
	Mobile3D(const Mobile3D<T>& mobile);
	
	virtual T getX() const = 0;
	virtual T getY() const = 0;
	virtual T getZ() const = 0;
	virtual Point3D<T> getPosition() const = 0;
};

template<typename T> inline Mobile3D<T>::Mobile3D() {
	pcoord_system=NULL;
	ps=NULL;
}

template<typename T> inline Mobile3D<T>::~Mobile3D() {
	// TODO Auto-generated destructor stub
}

template<typename T> inline Mobile3D<T>::Mobile3D(const Mobile3D<T>& mobile) {
	pcoord_system=mobile.pcoord_system;
	ps=mobile.ps;
}



template<typename T> inline T Mobile3D<T>::getX() const {
	return this->x;
}

template<typename T> inline T Mobile3D<T>::getY() const {
	return this->y;
}

template<typename T> inline T Mobile3D<T>::getZ() const {
	return this->z;
}

template<typename T> inline Point3D<T> Mobile3D<T>::getPosition() const {
	return Point3D<T>{this->x, this->y, this->z};
}




#endif /* MOBILE3D_HPP_ */
