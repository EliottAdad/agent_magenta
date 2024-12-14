/*
 * Particle3D.h
 *
 *  Created on: 14 mai 2024
 *      Author: esn
 */

#ifndef PARTICLE3D_H_

#define PARTICLE3D_H_

#include <memory>

#include "WeightedPoint3D.h"
#include "Vector3D.h"
#include "TimeSensitive.h"
#include "../display/Displayable.h"

/*
 * ####################
 *  Particle3D<M, E> pas pour l'instant:)
 * ####################
 * A weighted point with a speed.
 */
template<typename M, typename E> class Particle3D : public WeightedPoint3D<M, E>, public TimeSensitive, public Displayable<M, E> {
protected:
	float m_dt;
	//bool m_dels;

public:
	std::shared_ptr<Vector3D<M, E>> ps;// Necessary or else we cannot know where the particle will move if no forces are present (2nd Newton law).

	Particle3D();
	Particle3D(const Point3D<M, E>& p);
	Particle3D(const SN<M, E>& x, const SN<M, E>& y, const SN<M, E>& z);
	Particle3D(const WeightedPoint3D<M, E>& wp);
	//Particle3D(const Point3D<float, char>& p, const Vector3D& speed);
	//Particle3D(const WeightedPoint3D<float, char>& wp, const Vector3D& speed);
	Particle3D(const Particle3D<M, E>& p);
	virtual ~Particle3D();

	virtual SN<M, E> getX() const;
	virtual SN<M, E> getY() const;
	virtual SN<M, E> getZ() const;

	/*Vector3D getSpeed() const;
	Vector3D* getPSpeed() const;
	void setSpeed(const Vector3D& v);
	void setSpeed(const Point3D<float, char>& p);
	void addSpeed(const Vector3D& ds);
	void addSpeed(const Point3D<float, char>& p);*/

	virtual void addAsForce(const Vector3D<M, E>& v, const float& dt);
	virtual void addAsAcc(const Vector3D<M, E>& v, const float& dt);
	virtual void addAsSpeed(const Vector3D<M, E>& v);
	virtual void addAsPos(const Vector3D<M, E>& v);

	virtual void setT(const float& dt);
	virtual void apply();

	std::string to_string(const bool& spread=false, const bool& full_info=false, const unsigned char& indent=0) const;
	void print(const bool& spread=false, const bool& full_info=false, const unsigned char& indent=0) const;
};




template<typename M, typename E> Particle3D<M, E>::Particle3D() {
	this->x=SN<M, E>{1,0};
	this->y=SN<M, E>{1,0};
	this->z=SN<M, E>{1,0};
	this->w=SN<M, E>{1,0};														// Init the Weighted Point to {x=1, y=1, y=1, w=1}
	ps=std::make_shared<Vector3D<M, E>>();		// Vector3D init to end=(1, 1, 1)
	this->pcolor=NULL;

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

template<typename M, typename E> Particle3D<M, E>::Particle3D(const Point3D<M, E>& p) {
	this->x=p.x;
	this->y=p.y;
	this->z=p.z;
	this->w=SN<float, char>{1., 0};// Init the Weighted Point to {x, y, y, w=1}
	ps=std::make_shared<Vector3D<M, E>>();
	this->pcolor=NULL;

	m_dt=0;
}

template<typename M, typename E> Particle3D<M, E>::Particle3D(const SN<M, E>& x, const SN<M, E>& y, const SN<M, E>& z) {
	this->x=x;
	this->y=y;
	this->z=z;
	this->w=SN<float, char>{1,0};// Init the Weighted Point to {x, y, y, w=1}
	ps=std::make_shared<Vector3D<M, E>>();
	this->pcolor=NULL;

	m_dt=0;
}

template<typename M, typename E> Particle3D<M, E>::Particle3D(const WeightedPoint3D<M, E>& wp) {
	this->x=wp.x;
	this->y=wp.y;
	this->z=wp.z;
	this->w=wp.w;// Init the Weighted Point to {x, y, y, w}
	ps=std::make_shared<Vector3D<M, E>>();
	this->pcolor=NULL;

	m_dt=0;
}

/*Particle3D::Particle3D(const Point3D<float, char>& p, const Vector3D& speed) {
	this->x=p.x;
	this->y=p.y;
	this->z=p.z;
	this->w=SN<float, char>{1,0};// Init the Weighted Point to {x, y, y, w=1}
	ps.reset(speed);
	pcolor=NULL;

	m_dt=0;
}

Particle3D::Particle3D(const WeightedPoint3D& wp, const Vector3D& speed) {
	this->x=wp.x;
	this->y=wp.y;
	this->z=wp.z;
	this->w=wp.w;// Init the Weighted Point to {x, y, y, w}
	ps.reset(&speed);
	pcolor=NULL;

	m_dt=0;
}*/

template<typename M, typename E> Particle3D<M, E>::Particle3D(const Particle3D<M, E>& p) {
	this->x=p.x;
	this->y=p.y;
	this->z=p.z;
	this->w=p.w;// Init the Weighted Point to {x, y, y, w}
	ps=p.ps;
	this->pcolor=p.pcolor;

	m_dt=0;
}

template<typename M, typename E> Particle3D<M, E>::~Particle3D() {
	;//this->~Displayable();
}



template<typename M, typename E> SN<M, E> Particle3D<M, E>::getX() const {
	return this->x;
}

template<typename M, typename E> SN<M, E> Particle3D<M, E>::getY() const {
	return this->y;
}

template<typename M, typename E> SN<M, E> Particle3D<M, E>::getZ() const {
	return this->z;
}

/*Vector3D Particle3D::getSpeed() const {//Yep because cant be null
	return *m_ps;
}

Vector3D* Particle3D::getPSpeed() const {
	Vector3D* ps=NULL;
	if (m_dels){
		ps=m_ps;
	}
	return ps;
}

void Particle3D::setSpeed(const Vector3D& v) {
	*m_ps=v;
}

void Particle3D::setSpeed(const Point3D<float, char>& p) {
	*(m_ps->pp2)=p;
}

void Particle3D::addSpeed(const Vector3D& ds) {
	*m_ps+=ds;
}

void Particle3D::addSpeed(const Point3D<float, char>& p) {
	*(m_ps->pp2)+=p;
}*/

template<typename M, typename E> void Particle3D<M, E>::addAsForce(const Vector3D<M, E>& v, const float& dt) {
	SN<M, E> a=SN<M, E>{(M)dt, 0}/this->w;
	if (ps!=NULL){
		*ps+=v*a;
	}else{
		ps=std::make_shared<Vector3D<M, E>>(v*a);
	}
}

template<typename M, typename E> void Particle3D<M, E>::addAsAcc(const Vector3D<M, E>& v, const float& dt) {
	if (ps!=NULL){
		*ps+=v*(M)dt;
	}else{
		ps=std::make_shared<Vector3D<M, E>>(v*(M)dt);
	}
}

template<typename M, typename E> void Particle3D<M, E>::addAsSpeed(const Vector3D<M, E>& v) {
	if (ps!=NULL){
		*ps+=v;
	}else{
		ps=std::make_shared<Vector3D<M, E>>(v);
	}
}

template<typename M, typename E> void Particle3D<M, E>::addAsPos(const Vector3D<M, E>& v) {
	this->x+=v.pp2->x;
	this->y+=v.pp2->y;
	this->z+=v.pp2->z;
}



template<typename M, typename E> void Particle3D<M, E>::setT(const float& dt) {
	m_dt=dt;
	//printf("dt:  %f\n", dt);
}

template<typename M, typename E> void Particle3D<M, E>::apply(){
	this->x+=(ps->pp2->x)*m_dt;
	this->y+=(ps->pp2->y)*m_dt;
	this->z+=(ps->pp2->z)*m_dt;

	printf("Particle3D\n");
	this->x.print(true, true, 2);

	//this->x+=(m_ps->getP2().x)*m_dt;//THE PROBLEM
	//this->y+=(m_ps->getP2().y)*m_dt;
	//this->z+=(m_ps->getP2().z)*m_dt;
}




template<typename M, typename E> std::string Particle3D<M, E>::to_string(const bool& spread, const bool& full_info, const unsigned char& indent) const {
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
	mes+=" | ";
	mes+=ps->to_string(false, false);
	mes+=")";
	return mes;
}

template<typename M, typename E> void Particle3D<M, E>::print(const bool& spread, const bool& full_info, const unsigned char& indent) const {
	printTabs(indent);
	std::cout << this->to_string(spread, full_info, indent);
}


#endif /* PARTICLE3D_H_ */
