/*
 * Cube.h
 *
 *  Created on: 26 sept. 2024
 *      Author: esn
 */

#ifndef CUBE_H_
#define CUBE_H_

#include "Polyhedron.h"

class Cube : public Polyhedron {
public:
	Cube();
	virtual ~Cube();
	Cube(const Cube &other);
};

#endif /* CUBE_H_ */
