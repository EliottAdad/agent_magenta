/*
 * Vector3D.h
 *
 *  Created on: 11 juin 2024
 *      Author: esn
 */

#ifndef VECTOR3D_H_

#define VECTOR3D_H_


#include <memory>

#include "Line3D.h"
#include "Point3D.h"

/*
 * ##################
 *  Vector3D<M, E> :)
 * ##################
 */
template<typename M, typename E> class Vector3D : public Line3D<M, E> {
public:
	Vector3D();
	Vector3D(const Point3D<M, E>& p2);
	Vector3D(const Point3D<M, E>& p1, const Point3D<M, E>& p2);
	Vector3D(std::shared_ptr<Point3D<M, E>> pp1, std::shared_ptr<Point3D<M, E>> pp2);
	Vector3D(std::shared_ptr<Point3D<M, E>> pp1, const Point3D<M, E>& p2);
	Vector3D(const Point3D<M, E>& p1, std::shared_ptr<Point3D<M, E>> pp2);
	Vector3D(const Vector3D<M, E>& v);
	virtual ~Vector3D();//:)

	//void setPPoint(Point3D<float, char>* ppoint, const bool& delp=true);
	//void setPoint(Point3D<float, char>& point, const bool& delp=false);

	SN<M, E> getNorm() const;// :)
	void setNorm(const SN<M, E>& norm);// :)
	//Point3D<float, char> getOrigin() const;	//:)
	//Point3D<float, char>* getPOrigin() const;	//:)
	//void setOrigin(Point3D<float, char>& origin, const bool& delp=true);	//:)
	//void setPOrigin(Point3D<float, char>* porigin, const bool& delp=false);	//:)
	//void addOrigin(const Point3D<float, char>& dp);	//:)
	//Point3D<float, char> getEnd() const;	//:)
	//Point3D<float, char>* getPEnd() const;	//:)
	//void setEnd(Point3D<float, char>& end, const bool& delp=true);	//:)
	//void setPEnd(Point3D<float, char>* pend, const bool& delp=false);	//:)
	//void addEnd(const Point3D<float, char>& dp);	//:)

	virtual void operator=(const Vector3D<M, E>& v);// :)
	virtual void operator+=(const Vector3D<M, E>& v);// :)
	virtual void operator-=(const Vector3D<M, E>& v);// :)
	virtual void operator*=(const M& k);// :)
	virtual void operator/=(const M& k);// :)
	virtual void operator*=(const SN<M, E>& k);// :)
	virtual void operator/=(const SN<M, E>& k);// :)

	virtual bool operator==(const Vector3D<M, E>& v) const;// :)
	virtual bool operator<=(const Vector3D<M, E>& v) const;// :)
	virtual bool operator>=(const Vector3D<M, E>& v) const;// :)

	virtual std::string to_string(const bool& spread=false, const bool& full_info=false, const unsigned char& indent=0) const;
	virtual void print(const bool& spread=false, const bool& full_info=false, const unsigned char& indent=0) const;
};

template<typename M, typename E> Vector3D<M, E> operator+(const Vector3D<M, E>& v1, const Vector3D<M, E>& v2);// :)
//std::unique_ptr<Vector3D>& operator+(const std::unique_ptr<Vector3D>& pv1, const std::unique_ptr<Vector3D>& pv2);
template<typename M, typename E> Vector3D<M, E> operator-(const Vector3D<M, E>& v1, const Vector3D<M, E>& v2);// :)
template<typename M, typename E> Vector3D<M, E> operator*(const Vector3D<M, E>& v, const M& k);// :)
template<typename M, typename E> Vector3D<M, E> operator*(const Vector3D<M, E>& v, const SN<M, E>& k);// :)
template<typename M, typename E> Vector3D<M, E> operator/(const Vector3D<M, E>& v, const M& k);// :)
template<typename M, typename E> Vector3D<M, E> operator/(const Vector3D<M, E>& v, const SN<M, E>& k);// :)

//Scalar product
template<typename M, typename E> SN<M, E> operator*(const Vector3D<M, E>& v1, const Vector3D<M, E>& v2);// :)

//Vector product
template<typename M, typename E> Vector3D<M, E> operator^(const Vector3D<M, E>& v1, const Vector3D<M, E>& v2);// :)


//#############


/*:)
 * Constructor 1
 * By default constructor
 */
template<typename M, typename E> Vector3D<M, E>::Vector3D() {
	this->pp1=std::make_shared<Point3D<M, E>>();
	this->pp2=std::make_shared<Point3D<M, E>>(SN<M, E>{1,0},SN<M, E>{1,0},SN<M, E>{1,0});
	//pp2=std::shared_ptr(new Point3D<float, char>{});
}

/**
 * @brief A Vector3D is defined by two Point3D
 * @param p1 First point
 * @param p2 Second point
 * @param[in/out] p1 and p2 are copied
 */
template<typename M, typename E> Vector3D<M, E>::Vector3D(const Point3D<M, E>& p2) {
	this->pp1=std::make_shared<Point3D<M, E>>();
	this->pp2=std::make_shared<Point3D<M, E>>(p2);
}

/**
 * @brief A Vector3D is defined by two Point3D
 * @param p1 First point
 * @param p2 Second point
 * @param[in/out] p1 and p2 are copied
 */
template<typename M, typename E> Vector3D<M, E>::Vector3D(const Point3D<M, E>& p1, const Point3D<M, E>& p2) {
	this->pp1=std::make_shared<Point3D<M, E>>(p1);
	this->pp2=std::make_shared<Point3D<M, E>>(p2);
}

/**
 * @brief A Vector3D is defined by two Point3D
 * @param p1 First point
 * @param p2 Second point
 * @param[in/out] Modifications to *pp1 or *pp2 outside of class definition will be passed onto p1 and p2
 */
template<typename M, typename E> Vector3D<M, E>::Vector3D(std::shared_ptr<Point3D<M, E>> pp1, std::shared_ptr<Point3D<M, E>> pp2) {
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
template<typename M, typename E> Vector3D<M, E>::Vector3D(std::shared_ptr<Point3D<M, E>> pp1, const Point3D<M, E>& p2) {
	this->pp1=pp1;
	this->pp2=std::make_shared<Point3D<M, E>>(p2);
}

/**
 * Constructor4
 * Defined by two points
 * @param p1 First point
 * @param pp2 Pointer to the second point
 * (modifications outside of class definition will be passed onto p2)
 */
template<typename M, typename E> Vector3D<M, E>::Vector3D(const Point3D<M, E>& p1, std::shared_ptr<Point3D<M, E>> pp2) {
	this->pp1=std::make_shared<Point3D<M, E>>(p1);
	this->pp2=pp2;
}

/*
 * Constructor 6
 * Copy constructor
 */
template<typename M, typename E> Vector3D<M, E>::Vector3D(const Vector3D& v) {
	this->pp1=v.pp1;
	this->pp2=v.pp2;
}

/*
 * Constructor 7
 * Copy constructor
 */
/*Vector3D::Vector3D(const Vector3D* pv) {
	pp1=pv->getP1());
	pp2=new Point3D<float, char>(pv->getP2());
}*/

template<typename M, typename E> Vector3D<M, E>::~Vector3D() {
	;
}



/**
 * @return Returns the norm
 */
template<typename M, typename E> SN<M, E> Vector3D<M, E>::getNorm() const {
	return getDistance(*this->pp2, Point3D<M, E>{{0,0},{0,0},{0,0}});
}

template<typename M, typename E> void Vector3D<M, E>::setNorm(const SN<M, E>& norm) {
	if (*this->pp2!=Point3D<M, E>{{0,0},{0,0},{0,0}}){
		SN<M, E> k=norm/getDistance(*this->pp2, Point3D<M, E>{{0,0},{0,0},{0,0}});
		*this->pp2*=k;
	}else{
		*this->pp2=Point3D<M, E>{{1,0},{1,0},{1,0}};
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


template<typename M, typename E> void Vector3D<M, E>::operator=(const Vector3D<M, E>& v) {
	*this->pp2=*v.pp2;
}

template<typename M, typename E> void Vector3D<M, E>::operator+=(const Vector3D<M, E>& v) {// The end of the vector must be diff than null
	*this->pp2+=*v.pp2;
}

template<typename M, typename E> void Vector3D<M, E>::operator-=(const Vector3D<M, E>& v) {
	*this->pp2-=*v.pp2;
}

template<typename M, typename E> void Vector3D<M, E>::operator*=(const M& k) {
	*this->pp2*=k;
}

template<typename M, typename E> void Vector3D<M, E>::operator/=(const M& k) {
	*this->pp2/=k;
}

template<typename M, typename E> void Vector3D<M, E>::operator*=(const SN<M, E>& k) {
	*this->pp2*=k;
}

template<typename M, typename E> void Vector3D<M, E>::operator/=(const SN<M, E>& k) {
	*this->pp2/=k;
}


template<typename M, typename E> bool Vector3D<M, E>::operator==(const Vector3D<M, E>& v) const {
	if (*this->pp1==*v.pp2){
		return true;
	}
	return false;
}

template<typename M, typename E> bool Vector3D<M, E>::operator<=(const Vector3D<M, E>& v) const {
	if (*this->pp1<=*v.pp2){
		return true;
	}
	return false;
}

template<typename M, typename E> bool Vector3D<M, E>::operator>=(const Vector3D<M, E>& v) const {
	if (*this->pp1>=*v.pp2){
		return true;
	}
	return false;
}



template<typename M, typename E> std::string Vector3D<M, E>::to_string(const bool& spread, const bool& full_info, const unsigned char& indent) const {
	std::string mes=((spread)?"\n" : "");

	if (full_info){
		mes+="VECTOR3D[";
		std::stringstream ss;
		ss << this;
		mes+=ss.str();
		mes+="]:";
		mes+=((spread)?"\n" + to_stringTabs(1) : "");
	}
	mes+=to_stringTabs(indent);
	mes+="(";
	if (full_info){
		mes+="P1";
		mes+= (this->pp1==NULL)?" NULL": this->pp1->to_string();
		mes+=" ; ";
	}
	mes+="P2";
	mes+=(this->pp2==NULL)?" NULL": this->pp2->to_string();
	mes+=")";

	return mes;
}

template<typename M, typename E> void Vector3D<M, E>::print(const bool& spread, const bool& full_info, const unsigned char& indent) const {
	printTabs(indent);
	std::cout << this->to_string(spread, full_info, indent);
}



template<typename M, typename E> Vector3D<M, E> operator+(const Vector3D<M, E>& v1, const Vector3D<M, E>& v2) {
	std::shared_ptr<Vector3D<M, E>> pnv(new Vector3D<M, E>(v1.pp1, *v1.pp2+*v2.pp2));
	return *pnv;
}

/*std::unique_ptr<Vector3D>& operator+(const std::unique_ptr<Vector3D>& pv1, const std::unique_ptr<Vector3D>& pv2) {
	std::unique_ptr<Vector3D> pnv(new Vector3D(pv1->getP1(), pv1->getP2()+pv2->getP2()));
	return pnv;
}*/

template<typename M, typename E> Vector3D<M, E> operator-(const Vector3D<M, E>& v1, const Vector3D<M, E>& v2) {
	std::shared_ptr<Vector3D<M, E>> pnv(new Vector3D<M, E>(v1.pp1, *v1.pp2-*v2.pp2));
	return *pnv;
}

template<typename M, typename E> Vector3D<M, E> operator*(const Vector3D<M, E>& v, const M& k) {
	std::shared_ptr<Vector3D<M, E>> pnv(new Vector3D<M, E>(v.pp1, *(v.pp2)*k));
	return *pnv;
}

template<typename M, typename E> Vector3D<M, E> operator*(const Vector3D<M, E>& v, const SN<M, E>& k) {
	std::shared_ptr<Vector3D<M, E>> pnv(new Vector3D<M, E>(v.pp1, *(v.pp2)*k));
	return *pnv;
}

template<typename M, typename E> Vector3D<M, E> operator/(const Vector3D<M, E>& v, const M& k) {
	std::shared_ptr<Vector3D<M, E>> pnv(new Vector3D<M, E>(v.pp1, *(v.pp2)/k));
	return *pnv;
}

template<typename M, typename E> Vector3D<M, E> operator/(const Vector3D<M, E>& v, const SN<M, E>& k) {
	std::shared_ptr<Vector3D<M, E>> pnv(new Vector3D<M, E>(v.pp1, *(v.pp2)/k));
	return *pnv;
}

template<typename M, typename E> SN<M, E> operator*(const Vector3D<M, E>& v1, const Vector3D<M, E>& v2) {
	return v1.pp2->x*v2.pp2->x + v1.pp2->y*v2.pp2->y + v1.pp2->z*v2.pp2->z;
}

template<typename M, typename E> Vector3D<M, E> operator^(const Vector3D<M, E>& v1, const Vector3D<M, E>& v2) {
	std::shared_ptr<Vector3D<M, E>> pnv(new Vector3D<M, E>(v1.pp1, {
			{v1.pp2->y*v2.pp2->z-v1.pp2->z*v2.pp2->y},
			{v1.pp2->z*v2.pp2->x-v1.pp2->x*v2.pp2->z},
			{v1.pp2->x*v2.pp2->y-v1.pp2->y*v2.pp2->x}
	}));
	return *pnv;
}






#endif /* VECTOR3D_H_ */
