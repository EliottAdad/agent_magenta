/*
 * Cube.h
 *
 *  Created on: 26 sept. 2024
 *      Author: esn
 */

#ifndef CUBE_H_

#define CUBE_H_

#include "Polyhedron.h"

template<typename M, typename E> class Cube : public Polyhedron<M, E> {
public:
	Cube();
	virtual ~Cube();
	Cube(const Cube<M, E> &other);
};

#endif /* CUBE_H_ */
