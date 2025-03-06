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
 * @brief
 * An coordinate system defined by
 * its 3 own unary vectors expressed
 * in world/reference coordinates
 */
template<typename T> class CoordinateSystem3D {
protected:
	// Axis
	std::shared_ptr<Vector3D<T>> m_pe1;
	std::shared_ptr<Vector3D<T>> m_pe2;
	std::shared_ptr<Vector3D<T>> m_pe3;

public:
	std::shared_ptr<CoordinateSystem3D> preference;// NULL if World space
	std::shared_ptr<Point3D<T>> ppoint;//The position is given from the reference position & orientation

	// Rotation (unused for now
	float alpha;	// Angle balayant l'equateur
	float beta;		// Angle depuis l'equateur (negatif si en dessous de l'équateur, positif si l'inverse)

	CoordinateSystem3D();
	virtual ~CoordinateSystem3D();
	CoordinateSystem3D(const CoordinateSystem3D<T>& coordinate_system);

	Vector3D<T> getE1() const {return *this->m_pe1;};
	std::shared_ptr<Vector3D<T>> getPE1() const {return this->m_pe1;};
	void setE1(const Point3D<T>& p1) {*this->m_pp1=p1;}
	void setPE1(std::shared_ptr<Vector3D<T>> pv);
	Vector3D<T> getE2() const {return *this->m_pe2;};
	std::shared_ptr<Vector3D<T>> getPE2() const {return this->m_pe2;};
	Vector3D<T> getE3() const {return *this->m_pe3;};
	std::shared_ptr<Vector3D<T>> getPE3() const {return this->m_pe3;};

	Eigen::Matrix<T, 3, 3> getM() const;
	void rotate(const Vector3D<T>& v);
};




/**
 * Automatically aligned on the world coordinates at its creation.
 */
template<typename T> inline CoordinateSystem3D<T>::CoordinateSystem3D() {
	this->preference=NULL;
	this->ppoint=std::make_shared<Point3D<T>>();
	
	this->m_pe1=std::make_shared<Vector3D<T>>(Point3D<T>((T)1,(T)0,(T)0));
	this->m_pe2=std::make_shared<Vector3D<T>>(Point3D<T>((T)0,(T)1,(T)0));
	this->m_pe3=std::make_shared<Vector3D<T>>(Point3D<T>((T)0,(T)0,(T)1));
	this->m_pe1->setPOrigin(this->ppoint);
	this->m_pe2->setPOrigin(this->ppoint);
	this->m_pe3->setPOrigin(this->ppoint);
	
	this->alpha=0;
	this->beta=0;
}

template<typename T> inline CoordinateSystem3D<T>::~CoordinateSystem3D() {
	// TODO Auto-generated destructor stub
}

template<typename T> inline CoordinateSystem3D<T>::CoordinateSystem3D(const CoordinateSystem3D& coordinate_system) {
	this->preference=coordinate_system.preference;
	this->ppoint=coordinate_system.ppoint;
	
	this->m_pe1=coordinate_system.pe1;
	this->m_pe2=coordinate_system.pe2;
	this->m_pe3=coordinate_system.pe3;
	this->m_pe1->setPOrigin(this->ppoint);
	this->m_pe2->setPOrigin(this->ppoint);
	this->m_pe3->setPOrigin(this->ppoint);
	
	this->alpha=coordinate_system.alpha;
	this->beta=coordinate_system.beta;
}

/**
 * returns the Identity matrix
 * between the world reference and the actual csystem
 * Id(B|B')
 */
template<typename T> inline Eigen::Matrix<T, 3, 3> CoordinateSystem3D<T>::getM() const{
	if (this->preference==NULL){
		return Eigen::Matrix<T, 3, 3>{
			{m_pe1->pp2->x,m_pe2->pp2->x,m_pe3->pp2->x},
			{m_pe2->pp2->y,m_pe2->pp2->y,m_pe2->pp2->y},
			{m_pe3->pp2->z,m_pe3->pp2->z,m_pe3->pp2->z}
		};
	}else{
		return Eigen::Matrix<T, 3, 3>{
			{m_pe1->pp2->x,m_pe2->pp2->x,m_pe3->pp2->x},
			{m_pe2->pp2->y,m_pe2->pp2->y,m_pe2->pp2->y},
			{m_pe3->pp2->z,m_pe3->pp2->z,m_pe3->pp2->z}
		} * this->preference->getM();
	}
}

/**
 * Rotates in the plane that the vector in argument is the normal.
 */
template<typename T> inline void CoordinateSystem3D<T>::rotate(const Vector3D<T>& v) {
	// Finds a normal vector using the scalar product.
	if (v.pp2->z!=0){		// If z3!=0
		std::shared_ptr<Vector3D<T>> px=std::make_shared<Vector3D<T>>(v);
		px->setNorm((T)1);
		std::shared_ptr<Vector3D<T>> py=std::make_shared<Vector3D<T>>(Point3D<T>((T)1,(T)1,(T)(-1)*(v.x+v.y)/v.z));// y3= -(z1.y1+z2.y2)/z3 =>(with y1=y2=1) y3= -(z1+z2)/z3
		py->setNorm((T)1);
		std::shared_ptr<Vector3D<T>> pz=std::make_shared<Vector3D<T>>(*px^*py);
		pz->setNorm((T)1);// For security
	}
	/*return Eigen::Matrix<T, 3, 3>{
		{e1.ppoint2->x,e2.ppoint2->x,e3.ppoint2->x},
		{e2.ppoint2->y,e2.ppoint2->y,e2.ppoint2->y},
		{e3.ppoint2->z,e3.ppoint2->z,e3.ppoint2->z}
	};*/
}



#endif /* COORDINATESYSTEM3D_HPP_ */
