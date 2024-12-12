/*
 * Vector3D.cpp
 *
 *  Created on: 11 juin 2024
 *      Author: esn
 */

#include "Vector3D.h"

/*:)
 * Constructor 1
 * By default constructor
 */
Vector3D::Vector3D() {
	pp1=std::make_shared<Point3D<float, char>>();
	pp2=std::make_shared<Point3D<float, char>>(SN<float, char>{1,0},SN<float, char>{1,0},SN<float, char>{1,0});
	//pp2=std::shared_ptr(new Point3D<float, char>{});
}

/**
 * @brief A Vector3D is defined by two Point3D
 * @param p1 First point
 * @param p2 Second point
 * @param[in/out] p1 and p2 are copied
 */
Vector3D::Vector3D(const Point3D<float, char>& p2) {
	pp1=std::make_shared<Point3D<float, char>>();
	pp2=std::make_shared<Point3D<float, char>>(p2);
}

/**
 * @brief A Vector3D is defined by two Point3D
 * @param p1 First point
 * @param p2 Second point
 * @param[in/out] p1 and p2 are copied
 */
Vector3D::Vector3D(const Point3D<float, char>& p1, const Point3D<float, char>& p2) {
	pp1=std::make_shared<Point3D<float, char>>(p1);
	pp2=std::make_shared<Point3D<float, char>>(p2);
}

/**
 * @brief A Vector3D is defined by two Point3D
 * @param p1 First point
 * @param p2 Second point
 * @param[in/out] Modifications to *pp1 or *pp2 outside of class definition will be passed onto p1 and p2
 */
Vector3D::Vector3D(std::shared_ptr<Point3D<float, char>> pp1, std::shared_ptr<Point3D<float, char>> pp2) {
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
Vector3D::Vector3D(std::shared_ptr<Point3D<float, char>> pp1, const Point3D<float, char>& p2) {
	this->pp1=pp1;
	pp2=std::make_shared<Point3D<float, char>>(p2);
}

/**
 * Constructor4
 * Defined by two points
 * @param p1 First point
 * @param pp2 Pointer to the second point
 * (modifications outside of class definition will be passed onto p2)
 */
Vector3D::Vector3D(const Point3D<float, char>& p1, std::shared_ptr<Point3D<float, char>> pp2) {
	pp1=std::make_shared<Point3D<float, char>>(p1);
	this->pp2=pp2;
}

/*
 * Constructor 6
 * Copy constructor
 */
Vector3D::Vector3D(const Vector3D& v) {
	pp1=v.pp1;
	pp2=v.pp2;
}

/*
 * Constructor 7
 * Copy constructor
 */
/*Vector3D::Vector3D(const Vector3D* pv) {
	pp1=pv->getP1());
	pp2=new Point3D<float, char>(pv->getP2());
}*/

Vector3D::~Vector3D() {
	;
}



/**
 * @return Returns the norm
 */
SN<float, char> Vector3D::getNorm() const {
	return getDistance(*pp2, Point3D<float, char>{{0,0},{0,0},{0,0}});
}

void Vector3D::setNorm(const SN<float, char>& norm) {
	if (*pp2!=Point3D<float, char>{{0,0},{0,0},{0,0}}){
		SN<float, char> k=norm/getDistance(*pp2, Point3D<float, char>{{0,0},{0,0},{0,0}});
		*pp2*=k;
	}else{
		*pp2=Point3D<float, char>{{1,0},{1,0},{1,0}};
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


void Vector3D::operator=(const Vector3D& v) {
	*this->pp2=*v.pp2;
}

void Vector3D::operator+=(const Vector3D& v) {// The end of the vector must be diff than null
	*this->pp2+=*v.pp2;
}

void Vector3D::operator-=(const Vector3D& v) {
	*this->pp2-=*v.pp2;
}

void Vector3D::operator*=(const float& k) {
	*this->pp2*=k;
}

void Vector3D::operator/=(const float& k) {
	*this->pp2/=k;
}

void Vector3D::operator*=(const SN<float, char>& k) {
	*this->pp2*=k;
}

void Vector3D::operator/=(const SN<float, char>& k) {
	*this->pp2/=k;
}


bool Vector3D::operator==(const Vector3D& v) const {
	if (*pp1==*v.pp2){
		return true;
	}
	return false;
}

bool Vector3D::operator<=(const Vector3D& v) const {
	if (*pp1<=*v.pp2){
		return true;
	}
	return false;
}

bool Vector3D::operator>=(const Vector3D& v) const {
	if (*pp1>=*v.pp2){
		return true;
	}
	return false;
}



std::string Vector3D::to_string(const bool& spread, const bool& full_info, const unsigned char& indent) const {
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
		mes+= (pp1==NULL)?" NULL": pp1->to_string();
		mes+=" ; ";
	}
	mes+="P2";
	mes+=(pp2==NULL)?" NULL": pp2->to_string();
	mes+=")";

	return mes;
}

void Vector3D::print(const bool& spread, const bool& full_info, const unsigned char& indent) const {
	printTabs(indent);
	std::cout << this->to_string(spread, full_info, indent);
}



Vector3D operator+(const Vector3D& v1, const Vector3D& v2) {
	std::shared_ptr<Vector3D> pnv(new Vector3D(v1.pp1, *v1.pp2+*v2.pp2));
	return *pnv;
}

/*std::unique_ptr<Vector3D>& operator+(const std::unique_ptr<Vector3D>& pv1, const std::unique_ptr<Vector3D>& pv2) {
	std::unique_ptr<Vector3D> pnv(new Vector3D(pv1->getP1(), pv1->getP2()+pv2->getP2()));
	return pnv;
}*/

Vector3D operator-(const Vector3D& v1, const Vector3D& v2) {
	std::shared_ptr<Vector3D> pnv(new Vector3D(v1.pp1, *v1.pp2-*v2.pp2));
	return *pnv;
}

Vector3D operator*(const Vector3D& v, const float& k) {
	std::shared_ptr<Vector3D> pnv(new Vector3D(v.pp1, *(v.pp2)*k));
	return *pnv;
}

Vector3D operator*(const Vector3D& v, const SN<float, char>& k) {
	std::shared_ptr<Vector3D> pnv(new Vector3D(v.pp1, *(v.pp2)*k));
	return *pnv;
}

Vector3D operator/(const Vector3D& v, const float& k) {
	std::shared_ptr<Vector3D> pnv(new Vector3D(v.pp1, *(v.pp2)/k));
	return *pnv;
}

Vector3D operator/(const Vector3D& v, const SN<float, char>& k) {
	std::shared_ptr<Vector3D> pnv(new Vector3D(v.pp1, *(v.pp2)/k));
	return *pnv;
}

SN<float, char> operator*(const Vector3D& v1, const Vector3D& v2) {
	return v1.pp2->x*v2.pp2->x + v1.pp2->y*v2.pp2->y + v1.pp2->z*v2.pp2->z;
}

Vector3D operator^(const Vector3D& v1, const Vector3D& v2) {
	std::shared_ptr<Vector3D> pnv(new Vector3D(v1.pp1, {
			{v1.pp2->y*v2.pp2->z-v1.pp2->z*v2.pp2->y},
			{v1.pp2->z*v2.pp2->x-v1.pp2->x*v2.pp2->z},
			{v1.pp2->x*v2.pp2->y-v1.pp2->y*v2.pp2->x}
	}));
	return *pnv;
}

