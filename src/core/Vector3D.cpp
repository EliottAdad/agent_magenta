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
	m_pp1=new Point3D<float, char>{{0.,0}, {0.,0}, {0.,0}};
	m_pp2=new Point3D<float, char>{{1.,0}, {1.,0}, {1.,0}};
	m_delp1=true;
	m_delp2=true;
}

/**
 * @brief A Vector3D is defined by two Point3D
 * @param p1 First point
 * @param p2 Second point
 * @param[in/out] p1 and p2 are copied
 */
Vector3D::Vector3D(const Point3D<float, char>& p1, const Point3D<float, char>& p2) {
	this->m_pp1=new Point3D<float, char>(p1);
	this->m_pp2=new Point3D<float, char>(p2);
	m_delp1=true;
	m_delp2=true;
}

/**
 * @brief A Vector3D is defined by two Point3D
 * @param p1 First point
 * @param p2 Second point
 * @param[in/out] Modifications to *pp1 or *pp2 outside of class definition will be passed onto p1 and p2
 */
Vector3D::Vector3D(Point3D<float, char>* pp1, Point3D<float, char>* pp2) {
	if (pp1!=NULL){
		this->m_pp1=pp1;
		m_delp1=false;
	}else{
		this->m_pp1=new Point3D<float, char>{{0,0}, {0,0}, {0,0}};
		m_delp1=true;
	}
	if (pp2!=NULL){
		this->m_pp2=pp2;
		m_delp2=false;
	}else{
		this->m_pp2=new Point3D<float, char>{{1,0}, {1,0}, {1,0}};
		m_delp2=true;
	}
}

/**
 * Constructor3
 * Defined by two points
 * @param pp1 Pointer to the first point
 * (modifications outside of class definition will be passed onto p1)
 * @param p2 Second point
 */
Vector3D::Vector3D(Point3D<float, char>* pp1, const Point3D<float, char>& p2) {
	if (pp1!=NULL){
		this->m_pp1=pp1;
		m_delp1=false;
	}else{
		this->m_pp1=new Point3D<float, char>{{0,0}, {0,0}, {0,0}};
		m_delp1=true;
	}

	this->m_pp2=new Point3D<float, char>(p2);
	m_delp2=true;
}

/**
 * Constructor4
 * Defined by two points
 * @param p1 First point
 * @param pp2 Pointer to the second point
 * (modifications outside of class definition will be passed onto p2)
 */
Vector3D::Vector3D(const Point3D<float, char>& p1, Point3D<float, char>* pp2) {
	this->m_pp1=new Point3D<float, char>{{0,0}, {0,0}, {0,0}};
	m_delp1=true;

	if (pp2!=NULL){
		this->m_pp2=pp2;
		m_delp2=false;
	}else{
		this->m_pp2=new Point3D<float, char>{{1,0}, {1,0}, {1,0}};
		m_delp2=true;
	}
}

/*
 * Constructor 6
 * Copy constructor
 */
Vector3D::Vector3D(const Vector3D& v) {
	m_pp1=new Point3D<float, char>(v.getP1());
	m_pp2=new Point3D<float, char>(v.getP2());
	m_delp1=true;
	m_delp2=true;
}

/*
 * Constructor 7
 * Copy constructor
 */
Vector3D::Vector3D(const Vector3D* pv) {
	m_pp1=new Point3D<float, char>(pv->getP1());
	m_pp2=new Point3D<float, char>(pv->getP2());
	m_delp1=true;
	m_delp2=true;
}

Vector3D::~Vector3D() {
	if (m_delp1){
		delete m_pp1;
		//printf("A delete p1");
	}/*else{
		m_pp1=NULL;
		//printf("N'a pas delete p1");
	}*/
	if (m_delp2){
		delete m_pp2;
		//printf("A delete p2");
	}/*else{
		m_pp2=NULL;
		//printf("N'a pas delete p2");
	}*/
}



/**
 * @return Returns the norm
 */
SN<float, char> Vector3D::getNorm() const {
	return getDistance(*m_pp2, Point3D<float, char>{{0.,0},{0.,0},{0.,0}});
}

void Vector3D::setNorm(const SN<float, char>& norm) {
	if (*m_pp2!=Point3D<float, char>{{0.,0},{0.,0},{0.,0}}){
		SN<float, char> k=norm/getDistance(*m_pp2, Point3D<float, char>{{0.,0},{0.,0},{0.,0}});
		*m_pp2*=k;
	}else{
		*m_pp2=Point3D<float, char>{{1.,0},{1.,0},{1.,0}};
		this->setNorm(norm);
	}
}

Point3D<float, char> Vector3D::getOrigin() const {
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
}


void Vector3D::operator=(const Vector3D& v) {
	*this->m_pp2=v.getEnd();
}

void Vector3D::operator+=(const Vector3D& v) {
	*this->m_pp2+=v.getEnd();
}

void Vector3D::operator-=(const Vector3D& v) {
	*this->m_pp2-=v.getEnd();
}

void Vector3D::operator*=(const float& k) {
	*this->m_pp2*=k;
}

void Vector3D::operator/=(const float& k) {
	*this->m_pp2/=k;
}

void Vector3D::operator*=(const SN<float, char>& k) {
	*this->m_pp2*=k;
}

void Vector3D::operator/=(const SN<float, char>& k) {
	*this->m_pp2/=k;
}


bool Vector3D::operator==(const Vector3D& v) const {
	if (*m_pp1==v.getEnd()){
		return true;
	}
	return false;
}

bool Vector3D::operator<=(const Vector3D& v) const {
	if (*m_pp1<=v.getEnd()){
		return true;
	}
	return false;
}

bool Vector3D::operator>=(const Vector3D& v) const {
	if (*m_pp1>=v.getEnd()){
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
		mes+="P1" + this->getOrigin().to_string() + " ; ";
	}
	mes+="P2" + this->getEnd().to_string() + ")";

	return mes;
}

void Vector3D::print(const bool& spread, const bool& full_info, const unsigned char& indent) const {
	printTabs(indent);
	std::cout << this->to_string(spread, full_info, indent);
}



std::unique_ptr<Vector3D> operator+(const Vector3D& v1, const Vector3D& v2) {
	std::unique_ptr<Vector3D> pnv(new Vector3D(v1.getP1(), v1.getP2()+v2.getP2()));
	return pnv;
}

/*std::unique_ptr<Vector3D>& operator+(const std::unique_ptr<Vector3D>& pv1, const std::unique_ptr<Vector3D>& pv2) {
	std::unique_ptr<Vector3D> pnv(new Vector3D(pv1->getP1(), pv1->getP2()+pv2->getP2()));
	return pnv;
}*/

std::unique_ptr<Vector3D> operator-(const Vector3D& v1, const Vector3D& v2) {
	std::unique_ptr<Vector3D> pnv(new Vector3D(v1.getP1(), v1.getEnd()-v2.getEnd()));
	return pnv;
}

std::unique_ptr<Vector3D> operator*(const Vector3D& v, const float& k) {
	std::unique_ptr<Vector3D> pnv(new Vector3D(v.getP1(), v.getEnd()*k));
	return pnv;
}

std::unique_ptr<Vector3D> operator*(const Vector3D& v, const SN<float, char>& k) {
	std::unique_ptr<Vector3D> pnv(new Vector3D(v.getP1(), v.getEnd()*k));
	return pnv;
}

std::unique_ptr<Vector3D> operator/(const Vector3D& v, const float& k) {
	std::unique_ptr<Vector3D> pnv(new Vector3D(v.getP1(), v.getEnd()/k));
	return pnv;
}

std::unique_ptr<Vector3D> operator/(const Vector3D& v, const SN<float, char>& k) {
	std::unique_ptr<Vector3D> pnv(new Vector3D(v.getOrigin(), v.getEnd()/k));
	return pnv;
}

SN<float, char> operator*(const Vector3D& v1, const Vector3D& v2) {
	return v1.getEnd().x*v2.getEnd().x + v1.getEnd().y*v2.getEnd().y + v1.getEnd().z*v2.getEnd().z;
}

std::unique_ptr<Vector3D> operator^(const Vector3D& v1, const Vector3D& v2) {
	std::unique_ptr<Vector3D> pnv(new Vector3D(v1.getOrigin(), {
			{v1.getEnd().y*v2.getEnd().z-v1.getEnd().z*v2.getEnd().y},
			{v1.getEnd().z*v2.getEnd().x-v1.getEnd().x*v2.getEnd().z},
			{v1.getEnd().x*v2.getEnd().y-v1.getEnd().y*v2.getEnd().x}
	}));
	return pnv;
}

