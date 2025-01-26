/*
 * Vector3DS.h
 *
 *  Created on: 11 juin 2024
 *      Author: esn
 */

#ifndef VECTOR3DS_H_

#define VECTOR3DS_H_


#include <memory>

#include "../core/Line3DS.h"
#include "../core/Point3DS.h"

/*
 * ################
 *  Vector3DS<T> :)
 * ################
 */
template<typename T> class Vector3DS : public Line3DS<T> {
public:
	Vector3DS();
	Vector3DS(const Point3DS<T>& p2);
	Vector3DS(const Point3DS<T>& p1, const Point3DS<T>& p2);
	Vector3DS(std::shared_ptr<Point3DS<T>> pp1, std::shared_ptr<Point3DS<T>> pp2);
	Vector3DS(std::shared_ptr<Point3DS<T>> pp1, const Point3DS<T>& p2);
	Vector3DS(const Point3DS<T>& p1, std::shared_ptr<Point3DS<T>> pp2);
	Vector3DS(const Vector3DS<T>& v);
	virtual ~Vector3DS();//:)

	//void setPPoint(Point3DS<float, char>* ppoint, const bool& delp=true);
	//void setPoint(Point3DS<float, char>& point, const bool& delp=false);

	T getNorm() const;// :)
	void setNorm(const T& norm);// :)
	//Point3DS<float, char> getOrigin() const;	//:)
	//Point3DS<float, char>* getPOrigin() const;	//:)
	//void setOrigin(Point3DS<float, char>& origin, const bool& delp=true);	//:)
	//void setPOrigin(Point3DS<float, char>* porigin, const bool& delp=false);	//:)
	//void addOrigin(const Point3DS<float, char>& dp);	//:)
	//Point3DS<float, char> getEnd() const;	//:)
	//Point3DS<float, char>* getPEnd() const;	//:)
	//void setEnd(Point3DS<float, char>& end, const bool& delp=true);	//:)
	//void setPEnd(Point3DS<float, char>* pend, const bool& delp=false);	//:)
	//void addEnd(const Point3DS<float, char>& dp);	//:)

	virtual void operator=(const Vector3DS<T>& v);// :)
	virtual void operator+=(const Vector3DS<T>& v);// :)
	virtual void operator-=(const Vector3DS<T>& v);// :)
	virtual void operator*=(const M& k);// :)
	virtual void operator/=(const M& k);// :)
	virtual void operator*=(const T& k);// :)
	virtual void operator/=(const T& k);// :)

	virtual bool operator==(const Vector3DS<T>& v) const;// :)
	virtual bool operator<=(const Vector3DS<T>& v) const;// :)
	virtual bool operator>=(const Vector3DS<T>& v) const;// :)

	virtual std::string to_string(const bool& spread=false, const bool& full_info=false, const unsigned char& indent=0) const;
	virtual void print(const bool& spread=false, const bool& full_info=false, const unsigned char& indent=0) const;
};

template<typename T> Vector3DS<T> operator+(const Vector3DS<T>& v1, const Vector3DS<T>& v2);// :)
//std::unique_ptr<Vector3DS>& operator+(const std::unique_ptr<Vector3DS>& pv1, const std::unique_ptr<Vector3DS>& pv2);
template<typename T> Vector3DS<T> operator-(const Vector3DS<T>& v1, const Vector3DS<T>& v2);// :)
template<typename T> Vector3DS<T> operator*(const Vector3DS<T>& v, const T& k);// :)
template<typename T> Vector3DS<T> operator/(const Vector3DS<T>& v, const T& k);// :)

//Scalar product
template<typename T> T operator*(const Vector3DS<T>& v1, const Vector3DS<T>& v2);// :)

//Vector product
template<typename T> Vector3DS<T> operator^(const Vector3DS<T>& v1, const Vector3DS<T>& v2);// :)


//#############


/*:)
 * Constructor 1
 * By default constructor
 */
template<typename T> Vector3DS<T>::Vector3DS() {
	this->pp1=std::make_shared<Point3DS<T>>();
	this->pp2=std::make_shared<Point3DS<T>>((T)1,(T)1,(T)1);
	//pp2=std::shared_ptr(new Point3DS<float, char>{});
}

/**
 * @brief A Vector3DS is defined by two Point3DS
 * @param p1 First point
 * @param p2 Second point
 * @param[in/out] p1 and p2 are copied
 */
template<typename T> Vector3DS<T>::Vector3DS(const Point3DS<T>& p2) {
	this->pp1=std::make_shared<Point3DS<T>>();
	this->pp2=std::make_shared<Point3DS<T>>(p2);
}

/**
 * @brief A Vector3DS is defined by two Point3DS
 * @param p1 First point
 * @param p2 Second point
 * @param[in/out] p1 and p2 are copied
 */
template<typename T> Vector3DS<T>::Vector3DS(const Point3DS<T>& p1, const Point3DS<T>& p2) {
	this->pp1=std::make_shared<Point3DS<T>>(p1);
	this->pp2=std::make_shared<Point3DS<T>>(p2);
}

/**
 * @brief A Vector3DS is defined by two Point3DS
 * @param p1 First point
 * @param p2 Second point
 * @param[in/out] Modifications to *pp1 or *pp2 outside of class definition will be passed onto p1 and p2
 */
template<typename T> Vector3DS<T>::Vector3DS(std::shared_ptr<Point3DS<T>> pp1, std::shared_ptr<Point3DS<T>> pp2) {
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
template<typename T> Vector3DS<T>::Vector3DS(std::shared_ptr<Point3DS<T>> pp1, const Point3DS<T>& p2) {
	this->pp1=pp1;
	this->pp2=std::make_shared<Point3DS<T>>(p2);
}

/**
 * Constructor4
 * Defined by two points
 * @param p1 First point
 * @param pp2 Pointer to the second point
 * (modifications outside of class definition will be passed onto p2)
 */
template<typename T> Vector3DS<T>::Vector3DS(const Point3DS<T>& p1, std::shared_ptr<Point3DS<T>> pp2) {
	this->pp1=std::make_shared<Point3DS<T>>(p1);
	this->pp2=pp2;
}

/*
 * Constructor 6
 * Copy constructor
 */
template<typename T> Vector3DS<T>::Vector3DS(const Vector3DS& v) {
	this->pp1=v.pp1;
	this->pp2=v.pp2;
}

/*
 * Constructor 7
 * Copy constructor
 */
/*Vector3DS::Vector3DS(const Vector3DS* pv) {
	pp1=pv->getP1());
	pp2=new Point3DS<float, char>(pv->getP2());
}*/

template<typename T> Vector3DS<T>::~Vector3DS() {
	;
}



/**
 * @return Returns the norm
 */
template<typename T> T Vector3DS<T>::getNorm() const {
	return getDistance(*this->pp2, Point3DS<T>{(T)0,(T)0,(T)0});
}

template<typename T> void Vector3DS<T>::setNorm(const T& norm) {
	if (*this->pp2!=Point3DS<T>{{0,0},{0,0},{0,0}}){
		T k=norm/getDistance(*this->pp2, Point3DS<T>{(T)0,(T)0,(T)0});
		*this->pp2*=k;
	}else{
		*this->pp2=Point3DS<T>{(T)1,(T)1,(T)1};
		this->setNorm(norm);
	}
}

/*Point3DS<float, char> Vector3DS::getOrigin() const {
	return this->getP1();
}

Point3DS<float, char>* Vector3DS::getPOrigin() const {
	return this->getPP1();
}

void Vector3DS::setOrigin(Point3DS<float, char>& origin, const bool& delp) {
	this->setP1(origin);
}

void Vector3DS::setPOrigin(Point3DS<float, char>* porigin, const bool& delp) {
	this->setPP1(porigin);
}

void Vector3DS::addOrigin(const Point3DS<float, char>& dp) {
	*m_pp1+=dp;
}

Point3DS<float, char> Vector3DS::getEnd() const {
	return this->getP2();
}

Point3DS<float, char>* Vector3DS::getPEnd() const {
	return this->getPP2();
}

void Vector3DS::setEnd(Point3DS<float, char>& end, const bool& delp) {
	this->setP2(end);
}

void Vector3DS::setPEnd(Point3DS<float, char>* pend, const bool& delp) {
	this->setPP2(pend);
}

void Vector3DS::addEnd(const Point3DS<float, char>& dp) {
	*this->m_pp2+=dp;
}*/


template<typename T> void Vector3DS<T>::operator=(const Vector3DS<T>& v) {
	*this->pp2=*v.pp2;
}

template<typename T> void Vector3DS<T>::operator+=(const Vector3DS<T>& v) {// The end of the vector must be diff than null
	*this->pp2+=*v.pp2;
}

template<typename T> void Vector3DS<T>::operator-=(const Vector3DS<T>& v) {
	*this->pp2-=*v.pp2;
}

template<typename T> void Vector3DS<T>::operator*=(const T& k) {
	*this->pp2*=k;
}

template<typename T> void Vector3DS<T>::operator/=(const T& k) {
	*this->pp2/=k;
}


template<typename T> bool Vector3DS<T>::operator==(const Vector3DS<T>& v) const {
	if (*this->pp1==*v.pp2){
		return true;
	}
	return false;
}

template<typename T> bool Vector3DS<T>::operator<=(const Vector3DS<T>& v) const {
	if (*this->pp1<=*v.pp2){
		return true;
	}
	return false;
}

template<typename T> bool Vector3DS<T>::operator>=(const Vector3DS<T>& v) const {
	if (*this->pp1>=*v.pp2){
		return true;
	}
	return false;
}



template<typename T> std::string Vector3DS<T>::to_string(const bool& spread, const bool& full_info, const unsigned char& indent) const {
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

template<typename T> void Vector3DS<T>::print(const bool& spread, const bool& full_info, const unsigned char& indent) const {
	printTabs(indent);
	std::cout << this->to_string(spread, full_info, indent);
}



template<typename T> Vector3DS<T> operator+(const Vector3DS<T>& v1, const Vector3DS<T>& v2) {
	std::shared_ptr<Vector3DS<T>> pnv(new Vector3DS<T>(v1.pp1, *v1.pp2+*v2.pp2));
	return *pnv;
}

/*std::unique_ptr<Vector3DS>& operator+(const std::unique_ptr<Vector3DS>& pv1, const std::unique_ptr<Vector3DS>& pv2) {
	std::unique_ptr<Vector3DS> pnv(new Vector3DS(pv1->getP1(), pv1->getP2()+pv2->getP2()));
	return pnv;
}*/

template<typename T> Vector3DS<T> operator-(const Vector3DS<T>& v1, const Vector3DS<T>& v2) {
	std::shared_ptr<Vector3DS<T>> pnv(new Vector3DS<T>(v1.pp1, *v1.pp2-*v2.pp2));
	return *pnv;
}

template<typename T> Vector3DS<T> operator*(const Vector3DS<T>& v, const T& k) {
	std::shared_ptr<Vector3DS<T>> pnv(new Vector3DS<T>(v.pp1, *(v.pp2)*k));
	return *pnv;
}

template<typename T> Vector3DS<T> operator/(const Vector3DS<T>& v, const T& k) {
	std::shared_ptr<Vector3DS<T>> pnv(new Vector3DS<T>(v.pp1, *(v.pp2)/k));
	return *pnv;
}

template<typename T> T operator*(const Vector3DS<T>& v1, const Vector3DS<T>& v2) {
	return v1.pp2->x*v2.pp2->x + v1.pp2->y*v2.pp2->y + v1.pp2->z*v2.pp2->z;
}

template<typename T> Vector3DS<T> operator^(const Vector3DS<T>& v1, const Vector3DS<T>& v2) {
	std::shared_ptr<Vector3DS<T>> pnv(new Vector3DS<T>(v1.pp1, {
			{v1.pp2->y*v2.pp2->z-v1.pp2->z*v2.pp2->y},
			{v1.pp2->z*v2.pp2->x-v1.pp2->x*v2.pp2->z},
			{v1.pp2->x*v2.pp2->y-v1.pp2->y*v2.pp2->x}
	}));
	return *pnv;
}






#endif /* VECTOR3D_H_ */
