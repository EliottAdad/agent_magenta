/*
 * Line3D.cpp
 *
 *  Created on: 20 août 2024
 *      Author: esn
 */

#include "Line3D.h"

Line3D::Line3D(){
	m_delp1=true;
	m_delp2=true;
	m_pp1=new Point3D{{0, 0}, {0, 0}, {0, 0}};
	m_pp2=new Point3D{{1, 0}, {1, 0}, {1, 0}};
}

Line3D::Line3D(const Point3D& p1, const Point3D& p2){//:)
	m_delp1=true;
	m_delp2=true;
	this->m_pp1=new Point3D(p1);
	this->m_pp2=new Point3D(p2);
}

Line3D::Line3D(Point3D* pp1, Point3D* pp2){//:)
	m_delp1=false;
	m_delp2=false;
	this->m_pp1=pp1;
	this->m_pp2=pp2;
}

/*
 * Copy constructor
 */
Line3D::Line3D(const Line3D& l){
	m_delp1=true;
	m_delp2=true;
	m_pp1=new Point3D(l.getP1());
	m_pp2=new Point3D(l.getP2());
}

Line3D::~Line3D() {
	if (m_delp1){
		delete m_pp1;
	}else{
		m_pp1=NULL;
	}
	if (m_delp2){
		delete m_pp2;
	}else{
		m_pp2=NULL;
	}
}



Point3D Line3D::getP1() const {
	//return Point3D{*(this->m_pp1)};
	return *m_pp1;
}

/**
 * Returns the pointer to p1 (if p1 has been
 * defined externally) or NULL in the other case
 */
Point3D* Line3D::getPP1() const {
	Point3D* pp1=NULL;
	// If it hasn't been created locally...
	if (!m_delp1){
		pp1=this->m_pp1;
	}
	return pp1;
}

void Line3D::setP1(Point3D& p1, const bool& delp) {
	if (delp){
		if (m_delp1){
			delete m_pp2;
		}
		m_pp1=new Point3D(p1);
	}else{
		m_pp1=&p1;
	}
	m_delp1=delp;
}

void Line3D::setPP1(Point3D* pp1, const bool& delp) {
	if (delp){
		if (m_delp1){
			delete m_pp2;
		}
		m_pp1=new Point3D(*pp1);
	}else{
		m_pp1=pp1;
	}
	m_delp1=delp;
}

Point3D Line3D::getP2() const {
	//return Point3D{*(this->m_pp2)};
	return *m_pp2;
}

/**
 * Returns the pointer to p2 (if p2 has been
 * defined externally) or NULL in the other case
 */
Point3D* Line3D::getPP2() const {
	Point3D* pp2=nullptr;
	// If it hasn't been created locally...
	if (!m_delp2){
		pp2=this->m_pp2;
	}
	return pp2;
}

void Line3D::setP2(Point3D& p2, const bool& delp) {
	if (delp){
		if (m_delp1){
			delete m_pp2;
		}
		m_pp1=new Point3D(p2);
	}else{
		m_pp2=&p2;
	}
	m_delp2=delp;
}


bool Line3D::getDelP1() const {
	return this->m_delp1;
}

bool Line3D::getDelP2() const {
	return this->m_delp2;
}


std::string Line3D::to_string(const bool& spread, const bool& full_info, const unsigned char& indent) const {
	std::string mes=((spread)?"\n" : "");

	if (full_info){
		mes+="LINE[";
		std::stringstream ss;
		ss << this;
		mes+=ss.str();
		mes+="]:";
		mes+=((spread)?"\n" : "");
	}
	mes+="(";
	if (full_info){
		mes+="P1" + this->getP1().to_string() + ", ";
	}
	mes+="P2" + this->getP2().to_string() + ")";

	return mes;
}

void Line3D::print(const bool& spread, const bool& full_info, const unsigned char& indent) const {
	printTabs(indent);
	std::cout << this->to_string(spread, full_info, indent);
}

