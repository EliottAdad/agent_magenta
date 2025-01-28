/*
 * CoordinateSystem3D.h
 *
 *  Created on: 12 janv. 2025
 *      Author: esn
 */

#ifndef COORDINATESYSTEM3D_H_

#define COORDINATESYSTEM3D_H_

#include <eigen3/Eigen/Dense>

#include "Vector3D.h"

/*
 * #########################
 *  CoordinateSystem3D<T> :)
 * #########################
 * An coordinate system defined by
 * its 3 own unary vectors expressed
 * in world coordinates
 */
template<typename T> struct CoordinateSystem3D {
	Vector3D<T> e1;
	Vector3D<T> e2;
	Vector3D<T> e3;

	CoordinateSystem3D();
	virtual ~CoordinateSystem3D();
	CoordinateSystem3D(const CoordinateSystem3D<T>& coordsystem);

	Eigen::Matrix<T, 3, 3> getM() const;
	void rotate(const Vector3D<T>& v) const;
};

/**
 * Automatically aligned on the world coordinates at its creation.
 */
template<typename T> CoordinateSystem3D<T>::CoordinateSystem3D() {
	e1.setEnd(Point3D<T>{{1,0},{0,0},{0,0}});
	e2.setEnd(Point3D<T>{{0,0},{1,0},{0,0}});
	e3.setEnd(Point3D<T>{{0,0},{0,0},{1,0}});
}

template<typename T> CoordinateSystem3D<T>::~CoordinateSystem3D() {
	// TODO Auto-generated destructor stub
}

template<typename T> CoordinateSystem3D<T>::CoordinateSystem3D(const CoordinateSystem3D& coordsystem) {
	e1=coordsystem.e1;
	e2=coordsystem.e2;
	e3=coordsystem.e3;
}

template<typename T> Eigen::Matrix<T, 3, 3> CoordinateSystem3D<T>::getM() const{
	return Eigen::Matrix<T, 3, 3>{
		{e1.ppoint2->x,e2.ppoint2->x,e3.ppoint2->x},
		{e2.ppoint2->y,e2.ppoint2->y,e2.ppoint2->y},
		{e3.ppoint2->z,e3.ppoint2->z,e3.ppoint2->z}
	};
}

#endif /* COORDINATESYSTEM3D_H_ */
