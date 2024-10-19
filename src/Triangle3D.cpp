/*
 * Triangle.cpp
 *
 *  Created on: 20 mai 2024
 *      Author: esn
 */

#include "Triangle.h"

Triangle::Triangle() {
	pp1=new Point3D({{1,0},{0,0},{0,0}});
	pp2=new Point3D({{0,0},{1,0},{0,0}});
	pp3=new Point3D({{0,0},{0,0},{1,0}});
	m_delP1=true;
	m_delP2=true;
	m_delP3=true;
}

Triangle::Triangle(const Point3D& p1, const Point3D& p2, const Point3D& p3) {
	pp1=new Point3D(p1);
	pp2=new Point3D(p2);
	pp3=new Point3D(p3);
	m_delP1=true;
	m_delP2=true;
	m_delP3=true;
}

Triangle::Triangle(Point3D* pp1, Point3D* pp2, Point3D* pp3) {
	this->pp1=pp1;
	this->pp2=pp2;
	this->pp3=pp3;
	m_delP1=false;
	m_delP2=false;
	m_delP3=false;
}

Triangle::~Triangle() {
	if (m_delP1){
		delete pp1;
	}else{
		pp1=NULL;
	}
	if (m_delP2){
		delete pp2;
	}else{
		pp2=NULL;
	}
	if (m_delP3){
		delete pp3;
	}else{
		pp3=NULL;
	}
}

/*Triangle::Triangle(const Triangle &other) {
	// TODO Auto-generated constructor stub

}*/



Point3D Triangle::getP1() const {
	return *pp1;
}

Point3D* Triangle::getPP1() {
	return pp1;
}

void Triangle::setP1(const Point3D& p1) {
	*pp1=p1;
}

Point3D Triangle::getP2() const {
	return *pp2;
}

Point3D* Triangle::getPP2() {
	return pp2;
}

void Triangle::setP2(const Point3D& p2) {
	*pp2=p2;
}

Point3D Triangle::getP3() const {
	return *pp3;
}

Point3D* Triangle::getPP3() {
	return pp3;
}

void Triangle::setP3(const Point3D& p3) {
	*pp3=p3;
}


std::string Triangle::to_string(const bool& spread, const bool& full_info, const unsigned int& indent) const {
	std::string mes=((spread)?"\n" : "");

	if (full_info){
		mes+="TRIANGLE ():";
		mes+=((spread)?"\n" : "");
	}
	/*for (Particle3D* ppart : m_poctree->getPElements()){
		mes+="	- ( ";
		mes+=ppart->to_string(false, false);
		mes+=" )";
		mes+="\n";
	}*/
	return mes;
}

void Triangle::print(const bool& spread, const bool& full_info, const unsigned int& indent) const {
	printTabs(indent);
	std::cout << this->to_string(spread, full_info, indent);
}

