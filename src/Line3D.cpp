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
	return Point3D{*(this->m_pp1)};
}

Point3D* Line3D::getPP1() {
	Point3D* pp1=NULL;
	if (!m_delp1){
		pp1=this->m_pp1;
	}
	return pp1;
}

Point3D Line3D::getP2() const {
	return Point3D{*(this->m_pp2)};
}

Point3D* Line3D::getPP2() {
	Point3D* pp2=nullptr;
	// If it hasn't been defined locally.
	if (!m_delp2){
		pp2=this->m_pp2;
	}
	return pp2;
}

bool Line3D::getDelP1() const {
	return this->m_delp1;
}

bool Line3D::getDelP2() const {
	return this->m_delp2;
}


std::string Line3D::to_string(const bool& spread, const bool& full_info, const unsigned int& indent) const {
	std::string mes=((spread)?"\n" : "");
	mes+="LINE";

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

void Line3D::print(const bool& spread, const bool& full_info, const unsigned int& indent) const {
	printTabs(indent);
	std::cout << this->to_string(spread, full_info);
}

