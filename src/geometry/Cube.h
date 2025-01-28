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
 * ###########
 *  Cube<T> :)
 * ###########
 * A cube.
 */
template<typename T> class Cube : public Polyhedron<T> {
public:
	Cube();
	virtual ~Cube();
	Cube(const Cube<T>& cube);
};


template<typename T> Cube<T>::Cube() {
	// TODO Auto-generated constructor stub

}

template<typename T> Cube<T>::~Cube() {
	// TODO Auto-generated destructor stub
}

template<typename T> Cube<T>::Cube(const Cube<T>& other) {
	// TODO Auto-generated constructor stub

}


#endif /* CUBE_H_ */
