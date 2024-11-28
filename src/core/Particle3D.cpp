/*
 * Particle3D.cpp
 *
 *  Created on: 14 mai 2024
 *      Author: esn
 */


#include "Particle3D.h"



Particle3D::Particle3D() {
	this->x=SN<float, char>{1, 0};
	this->y=SN<float, char>{1, 0};
	this->z=SN<float, char>{1, 0};
	this->w=SN<float, char>{1, 0};														// Init the Weighted Point to {x=1, y=1, y=1, w=1}
	m_ps=new Vector3D(NULL, Point3D<float, char>{SN<float, char>{1, 0}, SN<float, char>{1, 0}, SN<float, char>{1, 0}});		// Vector3D init to end=(1, 1, 1)
	m_dels=true;
	m_dt=0;
}

/*Particle3D::Particle3D(const Point3D& p, Vector* pspeed) {
	x=p.x;
	y=p.y;
	z=p.z;
	w=LSN{1, 0};// Init the Weighted Point to {x, y, y, w=1}
	m_ps=pspeed;
	m_dels=false;
	m_dt=0;
}

Particle3D::Particle3D(const WeightedPoint3D& wp, Vector* pspeed) {
	x=wp.x;
	y=wp.y;
	z=wp.z;
	w=wp.w;// Init the Weighted Point to {x, y, y, w}
	m_ps=pspeed;
	m_dels=false;
	m_dt=0;
}*/

Particle3D::Particle3D(const Point3D<float, char>& p) {
	this->x=p.x;
	this->y=p.y;
	this->z=p.z;
	this->w=SN<float, char>{1, 0};// Init the Weighted Point to {x, y, y, w=1}
	m_ps=new Vector3D(NULL, {{1,0},{1,0},{1,0}});
	m_dels=true;
	m_dt=0;
}

Particle3D::Particle3D(const SN<float, char>& x, const SN<float, char>& y, const SN<float, char>& z) {
	this->x=x;
	this->y=y;
	this->z=z;
	this->w=SN<float, char>{1, 0};// Init the Weighted Point to {x, y, y, w=1}
	m_ps=new Vector3D(NULL, {{1,0},{1,0},{1,0}});
	m_dels=true;
	m_dt=0;
}

Particle3D::Particle3D(const WeightedPoint3D& wp) {
	this->x=wp.x;
	this->y=wp.y;
	this->z=wp.z;
	this->w=wp.w;// Init the Weighted Point to {x, y, y, w}
	m_ps=new Vector3D(NULL, {{1,0},{1,0},{1,0}});
	m_dels=true;
	m_dt=0;
}

Particle3D::Particle3D(const Point3D<float, char>& p, const Vector3D& speed) {
	this->x=p.x;
	this->y=p.y;
	this->z=p.z;
	this->w=SN<float, char>{1, 0};// Init the Weighted Point to {x, y, y, w=1}
	m_ps=new Vector3D(NULL, speed.getP2());
	m_dels=true;
	m_dt=0;
}

Particle3D::Particle3D(const WeightedPoint3D& wp, const Vector3D& speed) {
	this->x=wp.x;
	this->y=wp.y;
	this->z=wp.z;
	this->w=wp.w;// Init the Weighted Point to {x, y, y, w}
	m_ps=new Vector3D(NULL, speed.getP2());
	m_dels=true;
	m_dt=0;
}

Particle3D::~Particle3D() {
	if (m_dels){
		delete m_ps;
	}else{
		m_ps=NULL;
	}
}



SN<float, char> Particle3D::getX() const {
	return x;
}

SN<float, char> Particle3D::getY() const {
	return y;
}

SN<float, char> Particle3D::getZ() const {
	return z;
}

Vector3D Particle3D::getSpeed() const {
	return *m_ps;
}

Vector3D* Particle3D::getPSpeed() {
	return m_ps;
}

void Particle3D::setSpeed(const Vector3D& v) {
	*m_ps=v;
}

void Particle3D::setSpeed(const Point3D<float, char>& p) {
	*(m_ps->getPEnd())=p;
}

void Particle3D::addSpeed(const Vector3D& ds) {
	*m_ps+=ds;
}

void Particle3D::addSpeed(const Point3D<float, char>& p) {
	*(m_ps->getPEnd())+=p;
}

void Particle3D::addAsForce(const Vector3D& v, const float& dt) {
	SN<float, char> a=SN<float, char>{(float)dt, 0}/this->w;
	*m_ps+=*(v*a);
}

void Particle3D::addAsAcc(const Vector3D& v, const float& dt) {
	*m_ps+=*(v*dt);
}

void Particle3D::addAsSpeed(const Vector3D& v) {
	*m_ps+=v;
}

void Particle3D::addAsPos(const Vector3D& v) {
	this->x+=v.getP2().x;
	this->y+=v.getP2().y;
	this->z+=v.getP2().z;
}



void Particle3D::setT(const float& dt) {
	m_dt=dt;
	//printf("%Lf\n", dt);
}

void Particle3D::apply(){
	this->x=this->x+(m_ps->getP2().x)*m_dt;
	this->y=this->y+(m_ps->getP2().y)*m_dt;
	this->z=this->z+(m_ps->getP2().z)*m_dt;
	//this->x+=(m_ps->getP2().x)*m_dt;//THE PROBLEM
	//this->y+=(m_ps->getP2().y)*m_dt;
	//this->z+=(m_ps->getP2().z)*m_dt;
}




std::string Particle3D::to_string(const bool& spread, const bool& full_info, const unsigned char& indent) const {
	std::string mes=((spread)?"\n" : "");
	mes+=to_stringTabs(indent);

	if (full_info){
		mes+="PARTICLE3D[";
		std::stringstream ss;
		ss << this;
		mes+=ss.str();
		mes+="]:";
		mes+=((spread)?"\n" + to_stringTabs(1) : "");
	}

	mes+=to_stringTabs(indent);
	mes+="(" + this->getPosition().to_string();
	mes+=" |*| ";
	mes+=m_ps->to_string(false, false);
	mes+=")";
	return mes;
}

void Particle3D::print(const bool& spread, const bool& full_info, const unsigned char& indent) const {
	printTabs(indent);
	std::cout << this->to_string(spread, full_info, indent);
}
