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
//#include "../utilities/Printable.hpp"

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
	std::shared_ptr<Point3D<T>> ppoint;//The position is given from the reference position & orientation
	// Axis
	std::shared_ptr<Vector3D<T>> pe1;
	std::shared_ptr<Vector3D<T>> pe2;
	std::shared_ptr<Vector3D<T>> pe3;
	// Rotation
	float alpha;	// Angle balayant l'equateur
	float beta;		// Angle depuis l'equateur (negatif si en dessous de l'équateur, positif si l'inverse)

	CoordinateSystem3D();
	virtual ~CoordinateSystem3D();
	CoordinateSystem3D(const CoordinateSystem3D<T>& coordinate_system);

	Eigen::Matrix<T, 3, 3> getM() const;
	void rotate(const Vector3D<T>& v);
};




/**
 * Automatically aligned on the world coordinates at its creation.
 */
template<typename T> inline CoordinateSystem3D<T>::CoordinateSystem3D() {
	preference=NULL;
	ppoint=std::make_shared<Point3D<T>>();
	
	pe1->pp1=ppoint;
	pe2->pp1=ppoint;
	pe3->pp1=ppoint;
	pe1->pp2=std::make_shared<Point3D<T>>((T)1,(T)0,(T)0);
	pe2->pp2=std::make_shared<Point3D<T>>((T)0,(T)1,(T)0);
	pe3->pp2=std::make_shared<Point3D<T>>((T)0,(T)0,(T)1);
	
	alpha=0;
	beta=0;
}

template<typename T> inline CoordinateSystem3D<T>::~CoordinateSystem3D() {
	// TODO Auto-generated destructor stub
}

template<typename T> inline CoordinateSystem3D<T>::CoordinateSystem3D(const CoordinateSystem3D& coordinate_system) {
	preference=coordinate_system.preference;
	ppoint=coordinate_system.ppoint;
	
	pe1=coordinate_system.pe1;
	pe2=coordinate_system.pe2;
	pe3=coordinate_system.pe3;
	
	alpha=coordinate_system.alpha;
	beta=coordinate_system.beta;
}

/**
 * returns the Identity matrix
 * between the world reference and the actual csystem
 * Id(B|B')
 */
template<typename T> inline Eigen::Matrix<T, 3, 3> CoordinateSystem3D<T>::getM() const{
	if (preference==NULL){
		return Eigen::Matrix<T, 3, 3>{
			{pe1->pp2->x,pe2->pp2->x,pe3->pp2->x},
			{pe2->pp2->y,pe2->pp2->y,pe2->pp2->y},
			{pe3->pp2->z,pe3->pp2->z,pe3->pp2->z}
		};
	}else{
		return Eigen::Matrix<T, 3, 3>{
			{pe1->pp2->x,pe2->pp2->x,pe3->pp2->x},
			{pe2->pp2->y,pe2->pp2->y,pe2->pp2->y},
			{pe3->pp2->z,pe3->pp2->z,pe3->pp2->z}
		}*preference->getM();
	}
}

template<typename T> inline void CoordinateSystem3D<T>::rotate(const Vector3D<T>& v) {
	/*return Eigen::Matrix<T, 3, 3>{
		{e1.ppoint2->x,e2.ppoint2->x,e3.ppoint2->x},
		{e2.ppoint2->y,e2.ppoint2->y,e2.ppoint2->y},
		{e3.ppoint2->z,e3.ppoint2->z,e3.ppoint2->z}
	};*/
}



#endif /* COORDINATESYSTEM3D_HPP_ */
