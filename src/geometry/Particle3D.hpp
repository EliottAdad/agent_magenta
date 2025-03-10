/*
 * Particle3D.hpp
 *
 *  Created on: 14 mai 2024
 *      Author: esn
 */

#ifndef PARTICLE3D_HPP_

#define PARTICLE3D_HPP_

#include <memory>
#include <unordered_set>
#include <string>
#include <unordered_map>

//#include "WeightedPoint3D.hpp"
#include "../core/CoordinateSystem3D.hpp"
#include "../core/Mobile.hpp"
#include "../display/Displayable.hpp"
#include "../core/Vector3D.hpp"

//template<typename T> enum<T> Property {T, };

/*
 * #################
 *  Particle3D<T> :)
 * #################
 * A point with a speed.
 */
template<typename T> class Particle3D : public Mobile<T>, public Displayable<T> {
public:
	//std::shared_ptr<Vector3D<T>> ps;											// Necessary or else we cannot know where the particle will move if no forces are present (2nd Newton law).
	std::shared_ptr<std::unordered_map<std::string, std::shared_ptr<T>>> pfields;		// Numeric fields
	//std::shared_ptr<std::map<std::string, std::shared_ptr<void>>> pproperties;		// Properties
	//std::shared_ptr<CoordinateSystem3D<T>> psys;								// The coords system in wich it is expressed


	Particle3D();
	Particle3D(const Point3D<T>& p);
	Particle3D(const T& x, const T& y, const T& z, const T& w=(T)1);
	//Particle3D(const WeightedPoint3D<T>& wp);
	virtual ~Particle3D();
	Particle3D(const Particle3D<T>& p);

	// From Mobile
	virtual T getX() const;
	virtual T getY() const;
	virtual T getZ() const;
	virtual Point3D<T> getPosition() const;
	
	// From Displayable
	virtual std::unordered_set<std::shared_ptr<Point3D<T>>> getPPoints() const;
	//virtual std::unordered_set<std::shared_ptr<Line3D<T>>> getPLines() const;

	virtual T getW() const;

	virtual void setT(const float& dt);
	virtual void apply();

	virtual void operator+=(const Vector3D<T>& v);// :)
	//virtual void operator+=(const Particle3D<T>& p);// :)

	// From Printable
	std::string to_string(const bool& spread=false, const bool& full_info=false, const unsigned char& indent=0) const;
	void print(const bool& spread=false, const bool& full_info=false, const unsigned char& indent=0) const;
};

template<typename T> Particle3D<T> operator+(const Particle3D<T>& p1, const Particle3D<T>& p2);



template<typename T> Particle3D<T>::Particle3D() {
	this->x=(T)1;// Init to {x=1, y=1, y=1, w=1}
	this->y=(T)1;
	this->z=(T)1;
	pfields=std::make_shared<std::unordered_map<std::string, std::shared_ptr<T>>>();
	pfields->insert({"mass", std::make_shared<T>((T)1)});

	this->ps=std::make_shared<Vector3D<T>>();		// Vector3D init to end=(1, 1, 1)
	this->pcolor=NULL;

	this->m_dt=0;
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

template<typename T> Particle3D<T>::Particle3D(const Point3D<T>& p) {
	this->x=p.x;// Init to {x, y, y, w=1}
	this->y=p.y;
	this->z=p.z;
	pfields=std::make_shared<std::unordered_map<std::string, std::shared_ptr<T>>>();
	pfields->insert({"mass", std::make_shared<T>((T)1)});

	this->ps=std::make_shared<Vector3D<T>>();
	this->pcolor=NULL;

	this->m_dt=0;
}

template<typename T> Particle3D<T>::Particle3D(const T& x, const T& y, const T& z, const T& w) {
	this->x=x;
	this->y=y;
	this->z=z;
	pfields=std::make_shared<std::unordered_map<std::string, std::shared_ptr<T>>>();
	pfields->insert({"mass", std::make_shared<T>(w)});

	this->ps=std::make_shared<Vector3D<T>>();
	this->pcolor=NULL;

	this->m_dt=0;
}

/*template<typename T> Particle3D<T>::Particle3D(const WeightedPoint3D<T>& wp) {
	this->x=wp.x;// Init to {x, y, y, w}
	this->y=wp.y;
	this->z=wp.z;
	pfields=std::make_shared<std::unordered_map<std::string, std::shared_ptr<T>>>();
	pfields->insert({"mass", std::make_shared<T>(wp.w)});

	this->ps=std::make_shared<Vector3D<T>>();
	this->pcolor=NULL;

	this->m_dt=0;
}*/

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

template<typename T> Particle3D<T>::~Particle3D() {
	;
}

template<typename T> Particle3D<T>::Particle3D(const Particle3D<T>& p) {
	this->x=p.x;// Init the Weighted Point to {x, y, y}
	this->y=p.y;
	this->z=p.z;
	pfields=p.pfields;// Copy the properties

	this->ps=p.ps;
	this->pcolor=p.pcolor;

	this->m_dt=0;
}


// From Displayable
template<typename T> T Particle3D<T>::getX() const {
	return this->x;
}

template<typename T> T Particle3D<T>::getY() const {
	return this->y;
}

template<typename T> T Particle3D<T>::getZ() const {
	return this->z;
}

template<typename T> Point3D<T> Particle3D<T>::getPosition() const {
	return Point3D<T>{this->getX(), this->getY(), this->getZ()};
}

template<typename T> std::unordered_set<std::shared_ptr<Point3D<T>>> Particle3D<T>::getPPoints() const {
	std::unordered_set<std::shared_ptr<Point3D<T>>> ppoints;
	ppoints.insert(std::make_shared<Point3D<T>>(this->getPosition()));
	return ppoints;
}


template<typename T> T Particle3D<T>::getW() const {
	T w=(T)1;

	if (pfields!=NULL /*&& pfields->contains("mass")*/){
		w=*((*pfields)["mass"]);
	}

	return w;
}

/*template<typename T> Point3D<T> Particle3D<T>::getPosition() const {
	return this->z;
}*/

template<typename T> void Particle3D<T>::setT(const float& dt) {
	this->m_dt=dt;
}

template<typename T> void Particle3D<T>::apply(){
	((T)this->m_dt).to_string(true, true, 0);
	//printf("m_dt:%f", (T)m_dt);
	//printf("speed*m_dt:%f");
	//this->x+=(ps->pp2->x)*m_dt;
	//this->y+=(ps->pp2->y)*m_dt;
	//this->z+=(ps->pp2->z)*m_dt;
	this->x+=(this->ps->pp2->x)*(T)this->m_dt;
	this->y+=(this->ps->pp2->y)*(T)this->m_dt;
	this->z+=(this->ps->pp2->z)*(T)this->m_dt;
}


template<typename T> void Particle3D<T>::operator+=(const Vector3D<T>& v){
	if (this->ps!=NULL){
		*this->ps+=v;
	}else{
		*this->ps=v;
	}
}

/*template<typename T> void Particle3D<T>::operator+=(const Particle3D<T>& p){
	if (this->ps!=NULL){
		*this->ps+=v;
	}else{
		*this->ps=v;
	}
}*/



template<typename T> std::string Particle3D<T>::to_string(const bool& spread, const bool& full_info, const unsigned char& indent) const {
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
	for (auto pairr : *(this->pfields)) {
		mes+=pairr.first+" "+pairr.second->to_string()+" | ";//"w:" + this->fields["mass"].to_string();
	}
	//mes+=" | ";
	mes+=(this->ps==NULL)?"NULL":this->ps->to_string(false, false);
	mes+=")";
	return mes;
}

template<typename T> void Particle3D<T>::print(const bool& spread, const bool& full_info, const unsigned char& indent) const {
	printTabs(indent);
	std::cout << this->to_string(spread, full_info, indent);
}

template<typename T> Particle3D<T> operator+(const Particle3D<T>& p1, const Particle3D<T>& p2){
	std::shared_ptr<Particle3D<T>> pparticle=std::make_shared<Particle3D<T>>();

	*(pparticle->ps)=*(p1->ps)+*(p2->ps);
	*(pparticle->prs)=*(p1->prs)+*(p2->prs);

	pparticle->pfields=std::make_shared<std::unordered_map<std::string, std::shared_ptr<T>>>();
	if (p1->pfields!=NULL && p1->pfields->contains("mass") && p2->pfields!=NULL && p2->pfields->contains("mass")) {
		pparticle->pfields->insert({"mass", *(p1->pfields)["mass"]+*(p2->pfields)["mass"]});
	}
}




#endif /* PARTICLE3D_HPP_ */
