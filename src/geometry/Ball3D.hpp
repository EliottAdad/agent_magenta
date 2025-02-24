/*
 * Ball3D.hpp
 *
 *  Created on: 22 oct. 2024
 *      Author: esn
 */

#ifndef BALL3D_HPP_

#define BALL3D_HPP_

#include "../core/SN.hpp"
#include "Particle3D.hpp"

/*
 * #############
 *  Ball3D<T> :)
 * #############
 * @brief
 * Particle3D with radius (useless)
 */
template<typename T> class Ball3D : public Particle3D<T> {
public:
	T r;

	Ball3D();
	virtual ~Ball3D();
	Ball3D(const Ball3D<T>& ball);
};




template<typename T> inline Ball3D<T>::Ball3D() {
	r=(T)1;
}

template<typename T> inline Ball3D<T>::~Ball3D() {
	;
}

template<typename T> inline Ball3D<T>::Ball3D(const Ball3D<T>& ball) {
	r=ball.r;
}


#endif /* BALL3D_HPP_ */
