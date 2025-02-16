/*
 * Vector3D.hpp
 *
 *  Created on: 11 juin 2024
 *      Author: esn
 */

#ifndef VECTOR3D_HPP_

#define VECTOR3D_HPP_


#include <memory>

#include "Line3D.hpp"
#include "Point3D.hpp"

/*
 * ###############
 *  Vector3D<T> :)
 * ###############
 * T: Unit for distances
 */
template<typename T> class Vector3D : public Line3D<T> {
public:
	Vector3D();
	Vector3D(const Point3D<T>& p2);
	Vector3D(const Point3D<T>& p1, const Point3D<T>& p2);
	Vector3D(std::shared_ptr<Point3D<T>> pp1, std::shared_ptr<Point3D<T>> pp2);
	Vector3D(std::shared_ptr<Point3D<T>> pp1, const Point3D<T>& p2);
	Vector3D(const Point3D<T>& p1, std::shared_ptr<Point3D<T>> pp2);
	virtual ~Vector3D();//:)
	Vector3D(const Vector3D<T>& v);

	T getNorm() const;// :)
	void setNorm(const T& norm);// :)
	//Point3D<float, char> getOrigin() const;	//:)
	//std::shared_ptr<Point3D<T>> getPOrigin() const {return Line3D<T>::getPP1();};	//:)
	//void setOrigin(Point3D<float, char>& origin, const bool& delp=true);	//:)
	//void setPOrigin(Point3D<float, char>* porigin, const bool& delp=false);	//:)
	//void addOrigin(const Point3D<float, char>& dp);	//:)
	//Point3D<float, char> getEnd() const;	//:)
	//std::shared_ptr<Point3D<T>> getPEnd() const {return Line3D<T>::getPP2();};	//:)
	//void setEnd(Point3D<float, char>& end, const bool& delp=true);	//:)
	//void setPEnd(Point3D<float, char>* pend, const bool& delp=false);	//:)
	//void addEnd(const Point3D<float, char>& dp);	//:)

	virtual void operator=(const Vector3D<T>& v);// :)
	virtual void operator+=(const Vector3D<T>& v);// :)
	virtual void operator-=(const Vector3D<T>& v);// :)
//	virtual void operator*=(const M& k);// :)
//	virtual void operator/=(const M& k);// :)
	virtual void operator*=(const T& k);// :)
	virtual void operator*=(const int& k);// :)
	virtual void operator/=(const T& k);// :)
	virtual void operator/=(const int& k);// :)

	virtual bool operator==(const Vector3D<T>& v) const;// :)
	virtual bool operator<=(const Vector3D<T>& v) const;// :)
	virtual bool operator>=(const Vector3D<T>& v) const;// :)
};

template<typename T> Vector3D<T> operator+(const Vector3D<T>& v1, const Vector3D<T>& v2);// :)
//std::unique_ptr<Vector3D>& operator+(const std::unique_ptr<Vector3D>& pv1, const std::unique_ptr<Vector3D>& pv2);
template<typename T> Vector3D<T> operator-(const Vector3D<T>& v1, const Vector3D<T>& v2);// :)
template<typename T> Vector3D<T> operator*(const Vector3D<T>& v, const T& k);// :)
template<typename T> Vector3D<T> operator*(const Vector3D<T>& v, const int& k);// :)
template<typename T> Vector3D<T> operator/(const Vector3D<T>& v, const T& k);// :)
template<typename T> Vector3D<T> operator/(const Vector3D<T>& v, const int& k);// :)

//Scalar product
template<typename T> T operator*(const Vector3D<T>& v1, const Vector3D<T>& v2);// :)

//Vector product
template<typename T> Vector3D<T> operator^(const Vector3D<T>& v1, const Vector3D<T>& v2);// :)


//#############


/*:)
 * Constructor 1
 * By default constructor
 */
template<typename T> inline Vector3D<T>::Vector3D() : Line3D<T>() {
	this->pp1=NULL;//std::make_shared<Point3D<T>>();
	this->pp2=std::make_shared<Point3D<T>>((T)1,(T)1,(T)1);
}

/**
 * @brief A Vector3D is defined by two Point3D
 * @param p1 First point
 * @param p2 Second point
 * @param[in/out] p1 and p2 are copied
 */
template<typename T> inline Vector3D<T>::Vector3D(const Point3D<T>& p2) : Line3D<T>() {
	this->pp1=NULL;//std::make_shared<Point3D<T>>();
	this->pp2=std::make_shared<Point3D<T>>(p2);
}

/**
 * @brief A Vector3D is defined by two Point3D
 * @param p1 First point
 * @param p2 Second point
 * @param[in/out] p1 and p2 are copied
 */
template<typename T> inline Vector3D<T>::Vector3D(const Point3D<T>& p1, const Point3D<T>& p2) : Line3D<T>() {
	this->pp1=std::make_shared<Point3D<T>>(p1);
	this->pp2=std::make_shared<Point3D<T>>(p2);
}

/**
 * @brief A Vector3D is defined by two Point3D
 * @param p1 First point
 * @param p2 Second point
 * @param[in/out] Modifications to *pp1 or *pp2 outside of class definition will be passed onto p1 and p2
 */
template<typename T> inline Vector3D<T>::Vector3D(std::shared_ptr<Point3D<T>> pp1, std::shared_ptr<Point3D<T>> pp2) : Line3D<T>() {
	this->pp1=pp1;
	this->pp2=pp2;
}

/**
 * Constructor3
 * Defined by two points
 * @param pp1 Pointer to the first point
 * (modifications outside of class definition will be passed onto p1)
 * @param p2 Second point
 */
template<typename T> inline Vector3D<T>::Vector3D(std::shared_ptr<Point3D<T>> pp1, const Point3D<T>& p2) : Line3D<T>() {
	this->pp1=pp1;
	this->pp2=std::make_shared<Point3D<T>>(p2);
}

/**
 * Constructor4
 * Defined by two points
 * @param p1 First point
 * @param pp2 Pointer to the second point
 * (modifications outside of class definition will be passed onto p2)
 */
template<typename T> inline Vector3D<T>::Vector3D(const Point3D<T>& p1, std::shared_ptr<Point3D<T>> pp2) : Line3D<T>() {
	this->pp1=std::make_shared<Point3D<T>>(p1);
	this->pp2=pp2;
}

template<typename T> inline Vector3D<T>::~Vector3D() {
	;
}

/*
 * Constructor 6
 * Copy constructor
 */
template<typename T> inline Vector3D<T>::Vector3D(const Vector3D<T>& v) : Line3D<T>() {
	this->pp1=v.pp1;
	this->pp2=v.pp2;
}



/**
 * @return Returns the norm
 */
template<typename T> inline T Vector3D<T>::getNorm() const {
	return getDistance(*this->pp2, Point3D<T>{(T)0,(T)0,(T)0});
}

template<typename T> inline void Vector3D<T>::setNorm(const T& norm) {
	if (*this->pp2!=Point3D<T>{(T)0,(T)0,(T)0}){
		T k=norm/getDistance(*this->pp2, Point3D<T>{(T)0,(T)0,(T)0});
		*this->pp2*=k;
	}else{
		*this->pp2=Point3D<T>{(T)1,(T)1,(T)1};
		this->setNorm(norm);
	}
}

/*Point3D<float, char> Vector3D::getOrigin() const {
	return this->getP1();
}

Point3D<float, char>* Vector3D::getPOrigin() const {
	return this->getPP1();
}

void Vector3D::setOrigin(Point3D<float, char>& origin, const bool& delp) {
	this->setP1(origin);
}

void Vector3D::setPOrigin(Point3D<float, char>* porigin, const bool& delp) {
	this->setPP1(porigin);
}

void Vector3D::addOrigin(const Point3D<float, char>& dp) {
	*m_pp1+=dp;
}

Point3D<float, char> Vector3D::getEnd() const {
	return this->getP2();
}

Point3D<float, char>* Vector3D::getPEnd() const {
	return this->getPP2();
}

void Vector3D::setEnd(Point3D<float, char>& end, const bool& delp) {
	this->setP2(end);
}

void Vector3D::setPEnd(Point3D<float, char>* pend, const bool& delp) {
	this->setPP2(pend);
}

void Vector3D::addEnd(const Point3D<float, char>& dp) {
	*this->m_pp2+=dp;
}*/


template<typename T> inline void Vector3D<T>::operator=(const Vector3D<T>& v) {
	*this->pp2=*v.pp2;
}

template<typename T> inline void Vector3D<T>::operator+=(const Vector3D<T>& v) {// The end of the vector must be diff than null
	*this->pp2+=*v.pp2;
}

template<typename T> inline void Vector3D<T>::operator-=(const Vector3D<T>& v) {
	*this->pp2-=*v.pp2;
}

template<typename T> inline void Vector3D<T>::operator*=(const T& k) {
	*this->pp2*=k;
}

template<typename T> inline void Vector3D<T>::operator*=(const int& k) {
	*this->pp2*=k;
}

template<typename T> inline void Vector3D<T>::operator/=(const T& k) {
	*this->pp2/=k;
}

template<typename T> inline void Vector3D<T>::operator/=(const int& k) {
	*this->pp2/=k;
}


template<typename T> inline bool Vector3D<T>::operator==(const Vector3D<T>& v) const {
	if (*this->pp1==*v.pp2){
		return true;
	}
	return false;
}

template<typename T> inline bool Vector3D<T>::operator<=(const Vector3D<T>& v) const {
	if (*this->pp1<=*v.pp2){
		return true;
	}
	return false;
}

template<typename T> inline bool Vector3D<T>::operator>=(const Vector3D<T>& v) const {
	if (*this->pp1>=*v.pp2){
		return true;
	}
	return false;
}






template<typename T> inline Vector3D<T> operator+(const Vector3D<T>& v1, const Vector3D<T>& v2) {
	std::shared_ptr<Vector3D<T>> pnv(new Vector3D<T>(v1.pp1, *v1.pp2+*v2.pp2));
	return *pnv;
}

/*std::unique_ptr<Vector3D>& operator+(const std::unique_ptr<Vector3D>& pv1, const std::unique_ptr<Vector3D>& pv2) {
	std::unique_ptr<Vector3D> pnv(new Vector3D(pv1->getP1(), pv1->getP2()+pv2->getP2()));
	return pnv;
}*/

template<typename T> inline Vector3D<T> operator-(const Vector3D<T>& v1, const Vector3D<T>& v2) {
	std::shared_ptr<Vector3D<T>> pnv(new Vector3D<T>(v1.pp1, *v1.pp2-*v2.pp2));
	return *pnv;
}

template<typename T> inline Vector3D<T> operator*(const Vector3D<T>& v, const T& k) {
	std::shared_ptr<Vector3D<T>> pnv(new Vector3D<T>(v.pp1, *(v.pp2)*k));
	return *pnv;
}

template<typename T> inline Vector3D<T> operator*(const Vector3D<T>& v, const int& k) {
	std::shared_ptr<Vector3D<T>> pnv(new Vector3D<T>(v.pp1, *(v.pp2)*k));
	return *pnv;
}

template<typename T> inline Vector3D<T> operator/(const Vector3D<T>& v, const T& k) {
	std::shared_ptr<Vector3D<T>> pnv(new Vector3D<T>(v.pp1, *(v.pp2)/k));
	return *pnv;
}

template<typename T> inline Vector3D<T> operator/(const Vector3D<T>& v, const int& k) {
	std::shared_ptr<Vector3D<T>> pnv(new Vector3D<T>(v.pp1, *(v.pp2)/k));
	return *pnv;
}

template<typename T> inline T operator*(const Vector3D<T>& v1, const Vector3D<T>& v2) {
	return v1.pp2->x*v2.pp2->x + v1.pp2->y*v2.pp2->y + v1.pp2->z*v2.pp2->z;
}

template<typename T> inline Vector3D<T> operator^(const Vector3D<T>& v1, const Vector3D<T>& v2) {
	std::shared_ptr<Vector3D<T>> pnv(new Vector3D<T>(v1.pp1, {
			{v1.pp2->y*v2.pp2->z-v1.pp2->z*v2.pp2->y},
			{v1.pp2->z*v2.pp2->x-v1.pp2->x*v2.pp2->z},
			{v1.pp2->x*v2.pp2->y-v1.pp2->y*v2.pp2->x}
	}));
	return *pnv;
}






#endif /* VECTOR3D_HPP_ */
