/*
 * Object3D.h
 *
 *  Created on: 23 oct. 2024
 *      Author: esn
 */

#ifndef OBJECT3D_H_
#define OBJECT3D_H_

#include "Particle3D.h"
#include "../geometry/Mesh3D.h"

/*
 * ############
 *  Object3D :)
 * ############
 */
class Object3D : public Particle3D {
public:
	Object3D();
	virtual ~Object3D();
	Object3D(const Object3D &other);
};




#endif /* CORE_OBJECT3D_H_ */
