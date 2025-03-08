/*
 * Vector2D.hpp
 *
 *  Created on: 11 juin 2024
 *      Author: esn
 */

#ifndef VECTOR3D_HPP_

#define VECTOR3D_HPP_


#include <memory>

#include "Line2D.hpp"
#include "Point2D.hpp"

/*
 * ###############
 *  Vector2D<T> :)
 * ###############
 * T: Unit for distances
 */
template<typename T> class Vector2D : public Line2D<T> {
public:
	Vector2D();
	Vector2D(const Point2D<T>& p2);
	Vector2D(const Point2D<T>& p1, const Point2D<T>& p2);
	Vector2D(std::shared_ptr<Point2D<T>> pp1, std::shared_ptr<Point2D<T>> pp2);
	Vector2D(std::shared_ptr<Point2D<T>> pp1, const Point2D<T>& p2);
	Vector2D(const Point2D<T>& p1, std::shared_ptr<Point2D<T>> pp2);
	Vector2D(const Vector2D<T>& v);
	virtual ~Vector2D();//:)

	T getNorm() const;// :)
	void setNorm(const T& norm);// :)
	//Point2D<float, char> getOrigin() const;	//:)
	//Point2D<float, char>* getPOrigin() const;	//:)
	//void setOrigin(Point2D<float, char>& origin, const bool& delp=true);	//:)
	//void setPOrigin(Point2D<float, char>* porigin, const bool& delp=false);	//:)
	//void addOrigin(const Point2D<float, char>& dp);	//:)
	//Point2D<float, char> getEnd() const;	//:)
	//Point2D<float, char>* getPEnd() const;	//:)
	//void setEnd(Point2D<float, char>& end, const bool& delp=true);	//:)
	//void setPEnd(Point2D<float, char>* pend, const bool& delp=false);	//:)
	//void addEnd(const Point2D<float, char>& dp);	//:)

	virtual void operator=(const Vector2D<T>& v);// :)
	virtual void operator+=(const Vector2D<T>& v);// :)
	virtual void operator-=(const Vector2D<T>& v);// :)
//	virtual void operator*=(const M& k);// :)
//	virtual void operator/=(const M& k);// :)
	virtual void operator*=(const T& k);// :)
	virtual void operator*=(const int& k);// :)
	virtual void operator/=(const T& k);// :)
	virtual void operator/=(const int& k);// :)

	virtual bool operator==(const Vector2D<T>& v) const;// :)
	virtual bool operator<=(const Vector2D<T>& v) const;// :)
	virtual bool operator>=(const Vector2D<T>& v) const;// :)
};

template<typename T> Vector2D<T> operator+(const Vector2D<T>& v1, const Vector2D<T>& v2);// :)
//std::unique_ptr<Vector2D>& operator+(const std::unique_ptr<Vector2D>& pv1, const std::unique_ptr<Vector2D>& pv2);
template<typename T> Vector2D<T> operator-(const Vector2D<T>& v1, const Vector2D<T>& v2);// :)
template<typename T> Vector2D<T> operator*(const Vector2D<T>& v, const T& k);// :)
template<typename T> Vector2D<T> operator*(const Vector2D<T>& v, const int& k);// :)
template<typename T> Vector2D<T> operator/(const Vector2D<T>& v, const T& k);// :)
template<typename T> Vector2D<T> operator/(const Vector2D<T>& v, const int& k);// :)

//Scalar product
template<typename T> T operator*(const Vector2D<T>& v1, const Vector2D<T>& v2);// :)

//Vector product
template<typename T> Vector2D<T> operator^(const Vector2D<T>& v1, const Vector2D<T>& v2);// :)


//#############


/*:)
 * Constructor 1
 * By default constructor
 */
template<typename T> inline Vector2D<T>::Vector2D() {
	this->pp1=NULL;//std::make_shared<Point2D<T>>();
	this->pp2=std::make_shared<Point2D<T>>((T)1,(T)1,(T)1);
}

/**
 * @brief A Vector2D is defined by two Point2D
 * @param p1 First point
 * @param p2 Second point
 * @param[in/out] p1 and p2 are copied
 */
template<typename T> inline Vector2D<T>::Vector2D(const Point2D<T>& p2) {
	this->pp1=NULL;//std::make_shared<Point2D<T>>();
	this->pp2=std::make_shared<Point2D<T>>(p2);
}

/**
 * @brief A Vector2D is defined by two Point2D
 * @param p1 First point
 * @param p2 Second point
 * @param[in/out] p1 and p2 are copied
 */
template<typename T> inline Vector2D<T>::Vector2D(const Point2D<T>& p1, const Point2D<T>& p2) {
	this->pp1=std::make_shared<Point2D<T>>(p1);
	this->pp2=std::make_shared<Point2D<T>>(p2);
}

/**
 * @brief A Vector2D is defined by two Point2D
 * @param p1 First point
 * @param p2 Second point
 * @param[in/out] Modifications to *pp1 or *pp2 outside of class definition will be passed onto p1 and p2
 */
template<typename T> inline Vector2D<T>::Vector2D(std::shared_ptr<Point2D<T>> pp1, std::shared_ptr<Point2D<T>> pp2) {
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
template<typename T> inline Vector2D<T>::Vector2D(std::shared_ptr<Point2D<T>> pp1, const Point2D<T>& p2) {
	this->pp1=pp1;
	this->pp2=std::make_shared<Point2D<T>>(p2);
}

/**
 * Constructor4
 * Defined by two points
 * @param p1 First point
 * @param pp2 Pointer to the second point
 * (modifications outside of class definition will be passed onto p2)
 */
template<typename T> inline Vector2D<T>::Vector2D(const Point2D<T>& p1, std::shared_ptr<Point2D<T>> pp2) {
	this->pp1=std::make_shared<Point2D<T>>(p1);
	this->pp2=pp2;
}

/*
 * Constructor 6
 * Copy constructor
 */
template<typename T> inline Vector2D<T>::Vector2D(const Vector2D<T>& v) {
	this->pp1=v.pp1;
	this->pp2=v.pp2;
}

template<typename T> inline Vector2D<T>::~Vector2D() {
	;
}



/**
 * @return Returns the norm
 */
template<typename T> inline T Vector2D<T>::getNorm() const {
	return getDistance(*this->pp2, Point2D<T>{(T)0,(T)0,(T)0});
}

template<typename T> inline void Vector2D<T>::setNorm(const T& norm) {
	if (*this->pp2!=Point2D<T>{(T)0,(T)0,(T)0}){
		T k=norm/getDistance(*this->pp2, Point2D<T>{(T)0,(T)0,(T)0});
		*this->pp2*=k;
	}else{
		*this->pp2=Point2D<T>{(T)1,(T)1,(T)1};
		this->setNorm(norm);
	}
}

/*Point2D<float, char> Vector2D::getOrigin() const {
	return this->getP1();
}

Point2D<float, char>* Vector2D::getPOrigin() const {
	return this->getPP1();
}

void Vector2D::setOrigin(Point2D<float, char>& origin, const bool& delp) {
	this->setP1(origin);
}

void Vector2D::setPOrigin(Point2D<float, char>* porigin, const bool& delp) {
	this->setPP1(porigin);
}

void Vector2D::addOrigin(const Point2D<float, char>& dp) {
	*m_pp1+=dp;
}

Point2D<float, char> Vector2D::getEnd() const {
	return this->getP2();
}

Point2D<float, char>* Vector2D::getPEnd() const {
	return this->getPP2();
}

void Vector2D::setEnd(Point2D<float, char>& end, const bool& delp) {
	this->setP2(end);
}

void Vector2D::setPEnd(Point2D<float, char>* pend, const bool& delp) {
	this->setPP2(pend);
}

void Vector2D::addEnd(const Point2D<float, char>& dp) {
	*this->m_pp2+=dp;
}*/


template<typename T> inline void Vector2D<T>::operator=(const Vector2D<T>& v) {
	*this->pp2=*v.pp2;
}

template<typename T> inline void Vector2D<T>::operator+=(const Vector2D<T>& v) {// The end of the vector must be diff than null
	*this->pp2+=*v.pp2;
}

template<typename T> inline void Vector2D<T>::operator-=(const Vector2D<T>& v) {
	*this->pp2-=*v.pp2;
}

template<typename T> inline void Vector2D<T>::operator*=(const T& k) {
	*this->pp2*=k;
}

template<typename T> inline void Vector2D<T>::operator*=(const int& k) {
	*this->pp2*=k;
}

template<typename T> inline void Vector2D<T>::operator/=(const T& k) {
	*this->pp2/=k;
}

template<typename T> inline void Vector2D<T>::operator/=(const int& k) {
	*this->pp2/=k;
}


template<typename T> inline bool Vector2D<T>::operator==(const Vector2D<T>& v) const {
	if (*this->pp1==*v.pp2){
		return true;
	}
	return false;
}

template<typename T> inline bool Vector2D<T>::operator<=(const Vector2D<T>& v) const {
	if (*this->pp1<=*v.pp2){
		return true;
	}
	return false;
}

template<typename T> inline bool Vector2D<T>::operator>=(const Vector2D<T>& v) const {
	if (*this->pp1>=*v.pp2){
		return true;
	}
	return false;
}






template<typename T> inline Vector2D<T> operator+(const Vector2D<T>& v1, const Vector2D<T>& v2) {
	std::shared_ptr<Vector2D<T>> pnv(new Vector2D<T>(v1.pp1, *v1.pp2+*v2.pp2));
	return *pnv;
}

/*std::unique_ptr<Vector2D>& operator+(const std::unique_ptr<Vector2D>& pv1, const std::unique_ptr<Vector2D>& pv2) {
	std::unique_ptr<Vector2D> pnv(new Vector2D(pv1->getP1(), pv1->getP2()+pv2->getP2()));
	return pnv;
}*/

template<typename T> inline Vector2D<T> operator-(const Vector2D<T>& v1, const Vector2D<T>& v2) {
	std::shared_ptr<Vector2D<T>> pnv(new Vector2D<T>(v1.pp1, *v1.pp2-*v2.pp2));
	return *pnv;
}

template<typename T> inline Vector2D<T> operator*(const Vector2D<T>& v, const T& k) {
	std::shared_ptr<Vector2D<T>> pnv(new Vector2D<T>(v.pp1, *(v.pp2)*k));
	return *pnv;
}

template<typename T> inline Vector2D<T> operator*(const Vector2D<T>& v, const int& k) {
	std::shared_ptr<Vector2D<T>> pnv(new Vector2D<T>(v.pp1, *(v.pp2)*k));
	return *pnv;
}

template<typename T> inline Vector2D<T> operator/(const Vector2D<T>& v, const T& k) {
	std::shared_ptr<Vector2D<T>> pnv(new Vector2D<T>(v.pp1, *(v.pp2)/k));
	return *pnv;
}

template<typename T> inline Vector2D<T> operator/(const Vector2D<T>& v, const int& k) {
	std::shared_ptr<Vector2D<T>> pnv(new Vector2D<T>(v.pp1, *(v.pp2)/k));
	return *pnv;
}

template<typename T> inline T operator*(const Vector2D<T>& v1, const Vector2D<T>& v2) {
	return v1.pp2->x*v2.pp2->x + v1.pp2->y*v2.pp2->y + v1.pp2->z*v2.pp2->z;
}

template<typename T> inline Vector2D<T> operator^(const Vector2D<T>& v1, const Vector2D<T>& v2) {
	std::shared_ptr<Vector2D<T>> pnv(new Vector2D<T>(v1.pp1, {
			{v1.pp2->y*v2.pp2->z-v1.pp2->z*v2.pp2->y},
			{v1.pp2->z*v2.pp2->x-v1.pp2->x*v2.pp2->z},
			{v1.pp2->x*v2.pp2->y-v1.pp2->y*v2.pp2->x}
	}));
	return *pnv;
}






#endif /* VECTOR3D_HPP_ */
