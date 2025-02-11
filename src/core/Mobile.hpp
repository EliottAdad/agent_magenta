/*
 * Mobile.hpp
 *
 *  Created on: 31 janv. 2025
 *      Author: esn
 */

#ifndef MOBILE_HPP_

#define MOBILE_HPP_

#include <memory>

#include "CoordinateSystem3D.hpp"
#include "Point3D.hpp"
#include "TimeSensitive.hpp"
#include "../utilities/Printable.hpp"

/**
 * #############
 *  Mobile<T> :)
 * #############
 * TimeSensitive + getX
 */
template<typename T> class Mobile : public TimeSensitive, public Point3D<T> {
public:
	std::shared_ptr<CoordinateSystem3D<T>> pcoord_system;
	std::shared_ptr<Vector3D<T>> ps;											// Necessary or else we cannot know where the particle will move if no forces are present (2nd Newton law).
	
	Mobile();
	virtual ~Mobile();
	Mobile(const Mobile<T>& mobile);
	
	virtual T getX() const;
	virtual T getY() const;
	virtual T getZ() const;
	virtual Point3D<T> getPosition() const;
	
	// From Printable
	std::string to_string(const bool& spread=false, const bool& full_info=false, const unsigned char& indent=0) const;// :)
	void print(const bool& spread=false, const bool& full_info=false, const unsigned char& indent=0) const;// :)

};

template<typename T> Mobile<T>::Mobile() {
	pcoord_system=NULL;
	ps=NULL;
}

template<typename T> Mobile<T>::~Mobile() {
	// TODO Auto-generated destructor stub
}

template<typename T> Mobile<T>::Mobile(const Mobile<T>& mobile) {
	pcoord_system=mobile.pcoord_system;
	ps=mobile.ps;
}



template<typename T> T Mobile<T>::getX() const {
	return this->x;
}

template<typename T> T Mobile<T>::getY() const {
	return this->y;
}

template<typename T> T Mobile<T>::getZ() const {
	return this->z;
}

template<typename T> Point3D<T> Mobile<T>::getPosition() const {
	return Point3D<T>{this->x, this->y, this->z};
}



template<typename T> std::string Mobile<T>::to_string(const bool& spread, const bool& full_info, const unsigned char& indent) const {// :)
	std::string mes=(spread)?"\n":"";

	mes+="MOBILE\n";

	return mes;
}

template<typename T> void Mobile<T>::print(const bool& spread, const bool& full_info, const unsigned char& indent) const {// :)
	printTabs(indent);
	std::cout << this->to_string(spread, full_info, indent);
}


#endif /* MOBILE_HPP_ */
