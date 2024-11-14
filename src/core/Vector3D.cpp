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
	m_delp1=true;
	m_delp2=true;
	m_pp1=new Point3D{{0, 0}, {0, 0}, {0, 0}};
	m_pp2=new Point3D{{1, 0}, {1, 0}, {1, 0}};
}

/**
 * @brief A Vector3D is defined by two Point3D
 * @param p1 First point
 * @param p2 Second point
 * @param[in/out] p1 and p2 are copied
 */
Vector3D::Vector3D(const Point3D& p1, const Point3D& p2) {
	m_delp1=true;
	m_delp2=true;
	this->m_pp1=new Point3D(p1);
	this->m_pp2=new Point3D(p2);
}

/**
 * @brief A Vector3D is defined by two Point3D
 * @param p1 First point
 * @param p2 Second point
 * @param[in/out] Modifications to *pp1 or *pp2 outside of class definition will be passed onto p1 and p2
 */
Vector3D::Vector3D(Point3D* pp1, Point3D* pp2) {
	if (pp1!=NULL){
		m_delp1=false;
		this->m_pp1=pp1;
	}else{
		m_delp1=true;
		this->m_pp1=new Point3D();
	}
	if (pp2!=NULL){
		m_delp2=false;
		this->m_pp2=pp2;
	}else{
		m_delp2=true;
		this->m_pp2=new Point3D();
	}
}

/**
 * Constructor3
 * Defined by two points
 * @param pp1 Pointer to the first point
 * (modifications outside of class definition will be passed onto p1)
 * @param p2 Second point
 */
Vector3D::Vector3D(Point3D* pp1, const Point3D& p2) {
	if (pp1!=NULL){
		m_delp1=false;
		this->m_pp1=pp1;
	}else{
		m_delp1=true;
		this->m_pp1=new Point3D();
	}

	m_delp2=true;
	this->m_pp2=new Point3D(p2);
}

/**
 * Constructor4
 * Defined by two points
 * @param p1 First point
 * @param pp2 Pointer to the second point
 * (modifications outside of class definition will be passed onto p2)
 */
Vector3D::Vector3D(const Point3D& p1, Point3D* pp2) {
	m_delp1=true;
	this->m_pp1=new Point3D();

	if (pp2!=NULL){
		m_delp2=false;
		this->m_pp2=pp2;
	}else{
		m_delp2=true;
		this->m_pp2=new Point3D();
	}
}

/*
 * Constructor 6
 * Copy constructor
 */
Vector3D::Vector3D(const Vector3D& v) {
	m_delp1=true;
	m_delp2=true;
	m_pp1=new Point3D(v.getP1());
	m_pp2=new Point3D(v.getP2());
}

Vector3D::~Vector3D() {
	if (m_delp1){
		delete m_pp1;
		printf("A delete p1");
	}else{
		m_pp1=NULL;
		printf("N'a pas delete p1");
	}
	if (m_delp2){
		delete m_pp2;
		printf("A delete p2");
	}else{
		m_pp2=NULL;
		printf("N'a pas delete p2");
	}
}



/**
 * @return Returns the norm
 */
LSN Vector3D::getNorm() const {
	return getDistance(*m_pp2);
}

void Vector3D::setNorm(const LSN& norm) {
	if (*m_pp2!=Point3D{{0,0},{0,0},{0,0}}){
		LSN k=norm/getDistance(*m_pp2);
		*m_pp2*=k;
	}else{
		*m_pp2=Point3D{{1,0},{1,0},{1,0}};
		this->setNorm(norm);
	}
}

Point3D Vector3D::getOrigin() const {
	return *m_pp1;
}

void Vector3D::setOrigin(const Point3D& origin) {
	*m_pp1=origin;
}

Point3D Vector3D::getEnd() const {
	return *m_pp2;
}

void Vector3D::setEnd(const Point3D& end) {
	*m_pp2=end;
}


void Vector3D::operator=(const Vector3D& v) {
	*this->m_pp2=v.getP2();
}

void Vector3D::operator+=(const Vector3D& v) {
	*this->m_pp2+=v.getP2();
}

void Vector3D::operator-=(const Vector3D& v) {
	*this->m_pp2-=v.getP2();
}

void Vector3D::operator*=(const long double& k) {
	*this->m_pp2*=k;
}

void Vector3D::operator/=(const long double& k) {
	*this->m_pp2/=k;
}

void Vector3D::operator*=(const LSN& k) {
	*this->m_pp2*=k;
}

void Vector3D::operator/=(const LSN& k) {
	*this->m_pp2/=k;
}


bool Vector3D::operator==(const Vector3D& v) const {
	if (*m_pp1==v.getP2()){
		return true;
	}
	return false;
}

bool Vector3D::operator<=(const Vector3D& v) const {
	if (*m_pp1<=v.getP2()){
		return true;
	}
	return false;
}

bool Vector3D::operator>=(const Vector3D& v) const {
	if (*m_pp1>=v.getP2()){
		return true;
	}
	return false;
}


std::string Vector3D::to_string(const bool& spread, const bool& full_info, const unsigned int& indent) const {
	std::string mes=((spread)?"\n" : "");
	mes+="Vector3D";

	if (full_info){
		mes+="():";//Pointer
		mes+=((spread)?"\n" : "");
	}
	mes+="(";
	if (full_info){
		mes+="P1" + this->getP1().to_string() + ", ";
	}
	mes+="P2" + this->getP2().to_string() + ")";

	return mes;
}

void Vector3D::print(const bool& spread, const bool& full_info, const unsigned int& indent) const {
	printTabs(indent);
	printf((this->to_string(spread, indent, full_info)).c_str());
}



Vector3D operator+(const Vector3D& v1, const Vector3D& v2) {
	Vector3D* pnv=new Vector3D(v1.getP1(), v1.getP2()+v2.getP2());
	return *pnv;
}

Vector3D operator-(const Vector3D& v1, const Vector3D& v2) {
	Vector3D* pnv=new Vector3D(v1.getP1(), v1.getP2()-v2.getP2());
	return *pnv;
}

Vector3D operator*(const Vector3D& v, const long double& k) {
	Vector3D* pnv=new Vector3D(v.getP1(), v.getP2()*k);
	return *pnv;
}

Vector3D operator*(const Vector3D& v, const LSN& k) {
	Vector3D* pnv=new Vector3D(v.getP1(), v.getP2()*k);
	return *pnv;
}

Vector3D operator/(const Vector3D& v, const long double& k) {
	Vector3D* pnv=new Vector3D(v.getP1(), v.getP2()/k);
	return *pnv;
}

Vector3D operator/(const Vector3D& v, const LSN& k) {
	Vector3D* pnv=new Vector3D(v.getP1(), v.getP2()/k);
	return *pnv;
}

LSN operator*(const Vector3D& v1, const Vector3D& v2) {
	return v1.getP2().x*v2.getP2().x + v1.getP2().y*v2.getP2().y + v1.getP2().z*v2.getP2().z;
}

Vector3D operator^(const Vector3D& v1, const Vector3D& v2) {
	Vector3D* pnv=new Vector3D(v1.getP1(), {
			{v1.getP2().y*v2.getP2().z-v1.getP2().z*v2.getP2().y},
			{v1.getP2().z*v2.getP2().x-v1.getP2().x*v2.getP2().z},
			{v1.getP2().x*v2.getP2().y-v1.getP2().y*v2.getP2().x}
	});
	return *pnv;
}

