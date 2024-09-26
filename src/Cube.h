/*
 * Cube.h
 *
 *  Created on: 26 sept. 2024
 *      Author: esn
 */

#ifndef CUBE_H_
#define CUBE_H_

#include "Mesh3D.h"

class Cube: public Mesh3D {
public:
	Cube();
	virtual ~Cube();
	Cube(const Cube &other);
};

#endif /* CUBE_H_ */
