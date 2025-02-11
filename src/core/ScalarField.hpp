/*
 * ScalarField.hpp
 *
 *  Created on: 28 janv. 2025
 *      Author: esn
 */

#ifndef SCALARFIELD_HPP_

#define SCALARFIELD_HPP_

#include "Point3D.hpp"

template<typename T> class ScalarField {
public:
	T (*pfunc)(Point3D<T> p);// Function to the scalar repartition

	ScalarField();
	virtual ~ScalarField();
	ScalarField(const ScalarField<T>& other);
};

template<typename T> ScalarField<T>::ScalarField() {
	// TODO Auto-generated constructor stub
	pfunc=NULL;
}

template<typename T> ScalarField<T>::~ScalarField() {
	// TODO Auto-generated destructor stub
}

template<typename T> ScalarField<T>::ScalarField(const ScalarField& other) {
	// TODO Auto-generated constructor stub
	pfunc=other.pfunc;
}


#endif /* SCALARFIELD_HPP_ */
