/*
 * Cube.hpp
 *
 *  Created on: 26 sept. 2024
 *      Author: esn
 */

#ifndef CUBE_HPP_

#define CUBE_HPP_

#include "Polyhedron.hpp"

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


template<typename T> inline Cube<T>::Cube() {
	// TODO Auto-generated constructor stub

}

template<typename T> inline Cube<T>::~Cube() {
	// TODO Auto-generated destructor stub
}

template<typename T> inline Cube<T>::Cube(const Cube<T>& other) {
	// TODO Auto-generated constructor stub

}


#endif /* CUBE_HPP_ */
