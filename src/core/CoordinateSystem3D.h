/*
 * CoordinateSystem3D.h
 *
 *  Created on: 12 janv. 2025
 *      Author: esn
 */

#ifndef COORDINATESYSTEM3D_H_

#define COORDINATESYSTEM3D_H_

#include <eigen3/Eigen/Dense>

#include "../core/Vector3D.h"

/*
 * ############################
 *  CoordinateSystem3D<M, E> :)
 * ############################
 * An coordinate system defined by
 * its 3 own unary vectors expressed
 * in world coordinates
 */
template<typename M, typename E> struct CoordinateSystem3D {
	Vector3D<M, E> e1;
	Vector3D<M, E> e2;
	Vector3D<M, E> e3;

	CoordinateSystem3D();
	virtual ~CoordinateSystem3D();
	CoordinateSystem3D(const CoordinateSystem3D<M, E>& coordsystem);

	Eigen::Matrix<SN<M, E>, 3, 3> getM() const;
};

/**
 * Automatically aligned on the world coordinates at its creation.
 */
template<typename M, typename E> CoordinateSystem3D<M, E>::CoordinateSystem3D() {
	e1.setEnd(Point3D<M, E>{{1,0},{0,0},{0,0}});
	e2.setEnd(Point3D<M, E>{{0,0},{1,0},{0,0}});
	e3.setEnd(Point3D<M, E>{{0,0},{0,0},{1,0}});
}

template<typename M, typename E> CoordinateSystem3D<M, E>::~CoordinateSystem3D() {
	// TODO Auto-generated destructor stub
}

template<typename M, typename E> CoordinateSystem3D<M, E>::CoordinateSystem3D(const CoordinateSystem3D& coordsystem) {
	e1=coordsystem.e1;
	e2=coordsystem.e2;
	e3=coordsystem.e3;
}

template<typename M, typename E> Eigen::Matrix<SN<M, E>, 3, 3> CoordinateSystem3D<M, E>::getM() const{
	return Eigen::Matrix<SN<M, E>, 3, 3>{
		{e1.ppoint2->x,e2.ppoint2->x,e3.ppoint2->x},
		{e2.ppoint2->y,e2.ppoint2->y,e2.ppoint2->y},
		{e3.ppoint2->z,e3.ppoint2->z,e3.ppoint2->z}
	};
}

#endif /* COORDINATESYSTEM3D_H_ */
