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
#include "../core/Mobile3D.hpp"
#include "../display/Displayable3D.hpp"
#include "../core/Vector3D.hpp"
#include "../core/PropertySet.hpp"

//template<typename T> enum<T> Property {T, };

/**
 * #################
 *  Particle3D<T> :)
 * #################
 * @brief
 * A point with a speed.
 */
template<typename T> class Particle3D : public Displayable3D<T> {
public:
	std::shared_ptr<PropertySet<Particle3D<T>, T>> pproperties;										// Properties
	
	Particle3D();
	Particle3D(const Point3D<T>& p);
	Particle3D(const T& x, const T& y, const T& z, const T& mass=(T)1);
	//Particle3D(const WeightedPoint3D<T>& wp);
	virtual ~Particle3D();
	Particle3D(const Particle3D<T>& p);
	
	static T getMass();
	static T getCharge();
	
	virtual void operator+=(const Vector3D<T>& v);// :)
	virtual void operator+=(const Particle3D<T>& p);// :)

	// From Mobile3D
	virtual T getX() const {return Mobile3D<T>::getX();};				//Gets the coords (for rendering)
	virtual T getY() const {return Mobile3D<T>::getY();};
	virtual T getZ() const {return Mobile3D<T>::getZ();};
	virtual Point3D<T> getPosition() const {return Mobile3D<T>::getPosition();};

	// From Displayable
	virtual std::unordered_set<std::shared_ptr<Point3D<T>>> getPPoints() const;
	//virtual std::unordered_set<std::shared_ptr<Line3D<T>>> getPLines() const;

	// From TimeSensitive
	virtual float getT() const {return TimeSensitive::getT();}
	virtual void setT(const float& dt) {TimeSensitive::setT(dt);}
	virtual void apply();
};

template<typename T> Particle3D<T> operator+(const Particle3D<T>& p1, const Particle3D<T>& p2);
// Mass, charge,...
template<typename T> T getMass(const Particle3D<T>& p);





template<typename T> inline Particle3D<T>::Particle3D() : Displayable3D<T>() {
	this->pproperties=std::make_shared<PropertySet<Particle3D<T>, T>>();
	this->pproperties->add("mass", std::make_shared<T>((T)1));
	this->pproperties->add("charge", std::make_shared<T>((T)1));
}

template<typename T> inline Particle3D<T>::Particle3D(const Point3D<T>& p) : Displayable3D<T>() {
	this->ppoint=std::make_shared<Point3D<T>>(p);

	this->pproperties=std::make_shared<PropertySet<Particle3D<T>, T>>();
	this->pproperties->add("mass", std::make_shared<T>((T)1));
	this->pproperties->add("charge", std::make_shared<T>((T)1));
}

template<typename T> inline Particle3D<T>::Particle3D(const T& x, const T& y, const T& z, const T& mass) : Displayable3D<T>() {
	//this->ppoint->x=x;
	//this->ppoint->y=y;
	//this->ppoint->z=z;
	this->ppoint=std::make_shared<Point3D<T>>(x, y, z);

	this->pproperties=std::make_shared<PropertySet<Particle3D<T>, T>>();
	this->pproperties->add("mass", std::make_shared<T>(mass));
	this->pproperties->add("charge", std::make_shared<T>((T)1));
}

template<typename T> inline Particle3D<T>::~Particle3D() {
	;
}

template<typename T> inline Particle3D<T>::Particle3D(const Particle3D<T>& p) : Displayable3D<T>() {
	this->ppoint=p.ppoint;
	this->pproperties=p->pproperties;// Copy the properties

	this->ps=p.ps;
	this->pcolor=p.pcolor;
}






template<typename T> inline void Particle3D<T>::operator+=(const Vector3D<T>& v){
	if (this->ps!=NULL){
		*this->ps+=v;
	}else{
		*this->ps=v;
	}
}

template<typename T> inline void Particle3D<T>::operator+=(const Particle3D<T>& p){
	if (this->pproperties!=NULL){
		*this->pproperties+=*p.pproperties;
	}else{
		this->pproperties=p.pproperties;
	}
}






/*
 * From Displayable
 */
 
/**
 * v
 */
template<typename T> inline std::unordered_set<std::shared_ptr<Point3D<T>>> Particle3D<T>::getPPoints() const {
	std::unordered_set<std::shared_ptr<Point3D<T>>> ppoints;
	ppoints.insert(std::make_shared<Point3D<T>>(this->getPosition()));
	return ppoints;
}


/*
 * From TimeSensitive
 */

/**
 * v
 */
/*float Particle3D<T>::getT() const {
	return TimeSensitive::getT();
}

void Particle3D<T>::setT(const float& dt) {
	m_dt=dt;
}

void Particle3D<T>::apply() {//Useless
	m_dt=0;
}*/


/*
 * From TimeSensitive
 */
 
/**
 * l
 */
template<typename T> inline void Particle3D<T>::apply(){
	//printf("Particle3D: apply %f, %f\n", this->m_dt, this->ps->getNorm().to_m_type());
	*this->ppoint+= *this->ps->pp2 * (T)this->m_dt;
	//this->x+=(this->ps->pp2->x)*(T)this->m_dt;
	//this->y+=(this->ps->pp2->y)*(T)this->m_dt;
	//this->z+=(this->ps->pp2->z)*(T)this->m_dt;
}

/*template<typename T> void Particle3D<T>::operator+=(const Particle3D<T>& p){
	if (this->ps!=NULL){
		*this->ps+=v;
	}else{
		*this->ps=v;
	}
}*/








template<typename T> inline Particle3D<T> operator+(const Particle3D<T>& p1, const Particle3D<T>& p2){
	std::shared_ptr<Particle3D<T>> pparticle=std::make_shared<Particle3D<T>>();

	*(pparticle->ps)=*(p1->ps)+*(p2->ps);
	*(pparticle->prs)=*(p1->prs)+*(p2->prs);

	pparticle->pfields=std::make_shared<std::unordered_map<std::string, std::shared_ptr<T>>>();
	if (p1->pfields!=NULL && p1->pfields->contains("mass") && p2->pfields!=NULL && p2->pfields->contains("mass")) {
		pparticle->pfields->insert({"mass", *(p1->pfields)["mass"]+*(p2->pfields)["mass"]});
	}
}










#endif /* PARTICLE3D_HPP_ */
