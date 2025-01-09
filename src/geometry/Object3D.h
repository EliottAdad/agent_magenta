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
 * ##################
 *  Object3D<M, E> :)
 * ##################
 */
template<typename M, typename E> class Object3D : public Particle3D<M, E> {
public:
	Object3D();
	virtual ~Object3D();
	Object3D(const Object3D<M, E>& object);
};


template<typename M, typename E> Object3D<M, E>::Object3D() {
	// TODO Auto-generated constructor stub

}

template<typename M, typename E> Object3D<M, E>::~Object3D() {
	// TODO Auto-generated destructor stub
}

template<typename M, typename E> Object3D<M, E>::Object3D(const Object3D<M, E>& object) {
	// TODO Auto-generated constructor stub

}





#endif /* OBJECT3D_H_ */
