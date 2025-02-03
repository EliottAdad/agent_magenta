/*
 * Moveable.h
 *
 *  Created on: 31 janv. 2025
 *      Author: esn
 */

#ifndef MOVEABLE_H_

#define MOVEABLE_H_

#include <memory>

#include "../core/CoordinateSystem3D.h"

/**
 * ###############
 *  Moveable<T> :)
 * ###############
 * useless ?
 */
template<typename T> class Moveable {
public:
	std::shared_ptr<CoordinateSystem3D<T>> pcoord_system;

	Moveable();
	virtual ~Moveable();
	Moveable(const Moveable<T>& moveable);
};

#endif /* MOVEABLE_H_ */
