/*
 * ScalarField.h
 *
 *  Created on: 28 janv. 2025
 *      Author: esn
 */

#ifndef SCALARFIELD_H_

#define SCALARFIELD_H_

#include "Point3D.h"

template<typename T> class ScalarField {
public:
	T (*pfunc)(Point3D<T> p);// Function to the scalar repartition

	ScalarField();
	virtual ~ScalarField();
	ScalarField(const ScalarField &other);
};

#endif /* SCALARFIELD_H_ */
