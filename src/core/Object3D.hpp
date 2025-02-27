/*
 * Object3D.hpp
 *
 *  Created on: 23 oct. 2024
 *      Author: esn
 */

#ifndef OBJECT3D_HPP_

#define OBJECT3D_HPP_

#include "Mobile3D.hpp"
#include "Displayable3D.hpp"

/*
 * ###############
 *  Object3D<T> :)
 * ###############
 */
template<typename T> class Object3D : public Mobile3D<T>, public Displayable3D<T> {
public:
	Object3D();
	virtual ~Object3D();
	Object3D(const Object3D<T>& object);
	
	// From Displayable3D
	virtual std::unordered_set<Point3D<T>*> getPPoints() const;
	//virtual std::unordered_set<std::shared_ptr<Line3D<T>>> getPLines() const;

	// From TimeSensitive
	virtual float getT() const {return TimeSensitive::getT();}
	virtual void setT(const float& dt) {TimeSensitive::setT(dt);}
	virtual void apply();
};


template<typename T> inline Object3D<T>::Object3D() {
	// TODO Auto-generated constructor stub

}

template<typename T> inline Object3D<T>::~Object3D() {
	// TODO Auto-generated destructor stub
}

template<typename T> inline Object3D<T>::Object3D(const Object3D<T>& object) {
	// TODO Auto-generated constructor stub

}





#endif /* OBJECT3D_HPP_ */
