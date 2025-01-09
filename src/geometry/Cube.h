/*
 * Cube.h
 *
 *  Created on: 26 sept. 2024
 *      Author: esn
 */

#ifndef CUBE_H_

#define CUBE_H_

#include "Polyhedron.h"

/*
 * ##############
 *  Cube<M, E> :)
 * ##############
 * A cube.
 */
template<typename M, typename E> class Cube : public Polyhedron<M, E> {
public:
	Cube();
	virtual ~Cube();
	Cube(const Cube<M, E>& cube);
};


template<typename M, typename E> Cube<M, E>::Cube() {
	// TODO Auto-generated constructor stub

}

template<typename M, typename E> Cube<M, E>::~Cube() {
	// TODO Auto-generated destructor stub
}

template<typename M, typename E> Cube<M, E>::Cube(const Cube<M, E>& other) {
	// TODO Auto-generated constructor stub

}


#endif /* CUBE_H_ */
