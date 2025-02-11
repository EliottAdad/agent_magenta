/*
 * CoordinateSystem3D.hpp
 *
 *  Created on: 12 janv. 2025
 *      Author: esn
 */

#ifndef COORDINATESYSTEM3D_HPP_

#define COORDINATESYSTEM3D_HPP_

#include <memory>
#include <eigen3/Eigen/Dense>

#include "Vector3D.hpp"

/*
 * #########################
 *  CoordinateSystem3D<T> :)
 * #########################
 * An coordinate system defined by
 * its 3 own unary vectors expressed
 * in world coordinates
 */
template<typename T> class CoordinateSystem3D {
public:
	std::shared_ptr<CoordinateSystem3D> preference;// NULL if World space
	// Axis
	std::shared_ptr<Point3D<T>> ppoint;//The position is given from the reference position & orientation
	Vector3D<T> e1;
	Vector3D<T> e2;
	Vector3D<T> e3;
	// Rotation
	float alpha;	// Angle balayant l'equateur
	float beta;		// Angle depuis l'equateur (negatif si en dessous de l'équateur, positif si l'inverse)

	CoordinateSystem3D();
	virtual ~CoordinateSystem3D();
	CoordinateSystem3D(const CoordinateSystem3D<T>& coordsystem);

	Eigen::Matrix<T, 3, 3> getM() const;
	void rotate(const Vector3D<T>& v);
};

/**
 * Automatically aligned on the world coordinates at its creation.
 */
template<typename T> CoordinateSystem3D<T>::CoordinateSystem3D() {
	preference=NULL;
	ppoint=std::make_shared<Point3D<T>>();
	e1.pp1=ppoint;
	e2.pp1=ppoint;
	e3.pp1=ppoint;
	e1.setEnd(Point3D<T>{(T)1,(T)0,(T)0});
	e2.setEnd(Point3D<T>{(T)0,(T)1,(T)0});
	e3.setEnd(Point3D<T>{(T)0,(T)0,(T)1});
	alpha=0;
	beta=0;
}

template<typename T> CoordinateSystem3D<T>::~CoordinateSystem3D() {
	// TODO Auto-generated destructor stub
}

template<typename T> CoordinateSystem3D<T>::CoordinateSystem3D(const CoordinateSystem3D& coordsystem) {
	e1=coordsystem.e1;
	e2=coordsystem.e2;
	e3=coordsystem.e3;
	alpha=coordsystem.alpha;
	beta=coordsystem.beta;
}

/**
 * returns the Identity matrix
 * Id(B|B')
 */
template<typename T> Eigen::Matrix<T, 3, 3> CoordinateSystem3D<T>::getM() const{
	return Eigen::Matrix<T, 3, 3>{
		{e1.ppoint2->x,e2.ppoint2->x,e3.ppoint2->x},
		{e2.ppoint2->y,e2.ppoint2->y,e2.ppoint2->y},
		{e3.ppoint2->z,e3.ppoint2->z,e3.ppoint2->z}
	};
}

template<typename T> void CoordinateSystem3D<T>::rotate(const Vector3D<T>& v) {
	/*return Eigen::Matrix<T, 3, 3>{
		{e1.ppoint2->x,e2.ppoint2->x,e3.ppoint2->x},
		{e2.ppoint2->y,e2.ppoint2->y,e2.ppoint2->y},
		{e3.ppoint2->z,e3.ppoint2->z,e3.ppoint2->z}
	};*/
}

#endif /* COORDINATESYSTEM3D_HPP_ */
