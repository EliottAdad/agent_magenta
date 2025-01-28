/*
 * Object3D.h
 *
 *  Created on: 23 oct. 2024
 *      Author: esn
 */

#ifndef OBJECT3D_H_

#define OBJECT3D_H_

#include "Particle3D.h"
#include "Mesh3D.h"

/*
 * ###############
 *  Object3D<T> :)
 * ###############
 */
template<typename T> class Object3D : public Particle3D<T> {
public:
	Object3D();
	virtual ~Object3D();
	Object3D(const Object3D<T>& object);
};


template<typename T> Object3D<T>::Object3D() {
	// TODO Auto-generated constructor stub

}

template<typename T> Object3D<T>::~Object3D() {
	// TODO Auto-generated destructor stub
}

template<typename T> Object3D<T>::Object3D(const Object3D<T>& object) {
	// TODO Auto-generated constructor stub

}





#endif /* OBJECT3D_H_ */
