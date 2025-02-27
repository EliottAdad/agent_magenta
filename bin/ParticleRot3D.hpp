/*
 * ParticleRot3D.hpp
 *
 *  Created on: 12 jan. 2025
 *      Author: esn
 */

#ifndef PARTICLEROT3D_HPP_

#define PARTICLEROT3D_HPP_

#include "Particle3D.hpp"

//template<typename T> enum<T> Property {T, };

/*
 * ####################
 *  ParticleRot3D<T> :)
 * ####################
 * A particle with added rotational capabilities
 */
template<typename T> class ParticleRot3D : public Particle3D<T>{
public:
	std::shared_ptr<Vector3D<T>> prs;										// Rotational speed.

	ParticleRot3D();
	ParticleRot3D(const Point3D<T>& p);
	ParticleRot3D(const T& x, const T& y, const T& z, const T& w=(T)1);
	ParticleRot3D(const WeightedPoint3D<T>& wp);
	virtual ~ParticleRot3D();
	ParticleRot3D(const ParticleRot3D<T>& p);

	virtual void setT(const float& dt);
	virtual void apply();

	virtual void operator+=(const Vector3D<T>& v);// :)
	//virtual void operator+=(const ParticleRot3D<T>& p);// :)
};

template<typename T> ParticleRot3D<T> operator+(const ParticleRot3D<T>& p1, const ParticleRot3D<T>& p2);



template<typename T> inline ParticleRot3D<T>::ParticleRot3D() {
	this->x=(T)1;						// Init the Weighted Point to {x=1, y=1, y=1, w=1}
	this->y=(T)1;
	this->z=(T)1;
	pfields=std::make_shared<std::unordered_map<std::string, std::shared_ptr<T>>>();
	pfields->insert({"mass", std::make_shared<T>((T)1)});

	ps=std::make_shared<Vector3D<T>>();		// Vector3D init to end=(1, 1, 1)
	this->pcolor=NULL;

	m_dt=0;
}

/*ParticleRot3D::ParticleRot3D(const Point3D& p, Vector* pspeed) {
	x=p.x;
	y=p.y;
	z=p.z;
	w=LSN{1, 0};// Init the Weighted Point to {x, y, y, w=1}
	m_ps=pspeed;
	m_dels=false;
	m_dt=0;
}

ParticleRot3D::ParticleRot3D(const WeightedPoint3D& wp, Vector* pspeed) {
	x=wp.x;
	y=wp.y;
	z=wp.z;
	w=wp.w;// Init the Weighted Point to {x, y, y, w}
	m_ps=pspeed;
	m_dels=false;
	m_dt=0;
}*/

template<typename T> inline ParticleRot3D<T>::ParticleRot3D(const Point3D<T>& p) {
	this->x=p.x;
	this->y=p.y;
	this->z=p.z;
	//this->w=T{1,0};// Init the Weighted Point to {x, y, y, w=1}
	pfields=std::make_shared<std::unordered_map<std::string, std::shared_ptr<T>>>();
	pfields->insert({"mass", std::make_shared<T>((T)1)});

	ps=std::make_shared<Vector3D<T>>();
	this->pcolor=NULL;

	m_dt=0;
}

template<typename T> inline ParticleRot3D<T>::ParticleRot3D(const T& x, const T& y, const T& z, const T& w) {
	this->x=x;
	this->y=y;
	this->z=z;
	pfields=std::make_shared<std::unordered_map<std::string, std::shared_ptr<T>>>();
	pfields->insert({"mass", std::make_shared<T>(w)});

	ps=std::make_shared<Vector3D<T>>();
	this->pcolor=NULL;

	m_dt=0;
}

template<typename T> inline ParticleRot3D<T>::ParticleRot3D(const WeightedPoint3D<T>& wp) {
	this->x=wp.x;			// Init the Weighted Point to {x, y, y, w}
	this->y=wp.y;
	this->z=wp.z;
	pfields=std::make_shared<std::unordered_map<std::string, std::shared_ptr<T>>>();
	pfields->insert({"mass", std::make_shared<T>(wp.w)});

	ps=std::make_shared<Vector3D<T>>();
	this->pcolor=NULL;

	m_dt=0;
}

/*ParticleRot3D::ParticleRot3D(const Point3D<float, char>& p, const Vector3D& speed) {
	this->x=p.x;
	this->y=p.y;
	this->z=p.z;
	this->w=SN<float, char>{1,0};// Init the Weighted Point to {x, y, y, w=1}
	ps.reset(speed);
	pcolor=NULL;

	m_dt=0;
}

ParticleRot3D::ParticleRot3D(const WeightedPoint3D& wp, const Vector3D& speed) {
	this->x=wp.x;
	this->y=wp.y;
	this->z=wp.z;
	this->w=wp.w;// Init the Weighted Point to {x, y, y, w}
	ps.reset(&speed);
	pcolor=NULL;

	m_dt=0;
}*/

template<typename T> inline ParticleRot3D<T>::~ParticleRot3D() {
	;//this->~Displayable();
}

template<typename T> inline ParticleRot3D<T>::ParticleRot3D(const ParticleRot3D<T>& p) {
	this->x=p.x;
	this->y=p.y;
	this->z=p.z;
	//this->w=p.w;// Init the Weighted Point to {x, y, y, w}
	//pfields=std::make_shared<std::unordered_map<std::string, std::shared_ptr<T>>>();
	pfields=p->pfields;

	ps=p.ps;
	this->pcolor=p.pcolor;

	m_dt=0;
}



template<typename T> inline T ParticleRot3D<T>::getX() const {
	return this->x;
}

template<typename T> inline T ParticleRot3D<T>::getY() const {
	return this->y;
}

template<typename T> inline T ParticleRot3D<T>::getZ() const {
	return this->z;
}

template<typename T> inline T ParticleRot3D<T>::getW() const {
	T w=(T)1;

	if (pfields!=NULL /*&& pfields->contains("mass")*/){
		w=*((*pfields)["mass"]);
	}

	return w;
}

template<typename T> inline void ParticleRot3D<T>::setT(const float& dt) {
	m_dt=dt;
}

template<typename T> inline void ParticleRot3D<T>::apply(){
	this->x+=(ps->pp2->x)*m_dt;
	this->y+=(ps->pp2->y)*m_dt;
	this->z+=(ps->pp2->z)*m_dt;
	//this->x+=(ps->pp2->x)*(T)m_dt;
	//this->y+=(ps->pp2->y)*(T)m_dt;
	//this->z+=(ps->pp2->z)*(T)m_dt;
}


template<typename T> inline void ParticleRot3D<T>::operator+=(const Vector3D<T>& v){
	if (this->ps!=NULL){
		*this->ps+=v;
	}else{
		*this->ps=v;
	}
}

/*template<typename T> void ParticleRot3D<T>::operator+=(const ParticleRot3D<T>& p){
	if (this->ps!=NULL){
		*this->ps+=v;
	}else{
		*this->ps=v;
	}
}*/



template<typename T> inline ParticleRot3D<T> operator+(const ParticleRot3D<T>& p1, const ParticleRot3D<T>& p2){
	std::shared_ptr<ParticleRot3D<T>> pparticle=std::make_shared<ParticleRot3D<T>>();

	*(pparticle->ps)=*(p1->ps)+*(p2->ps);
	*(pparticle->prs)=*(p1->prs)+*(p2->prs);

	pparticle->pfields=std::make_shared<std::unordered_map<std::string, std::shared_ptr<T>>>();
	if (p1->pfields!=NULL && p1->pfields->contains("mass") && p2->pfields!=NULL && p2->pfields->contains("mass")) {
		pparticle->pfields->insert({"mass", *(p1->pfields)["mass"]+*(p2->pfields)["mass"]});
	}
}




#endif /* PARTICLE3D_HPP_ */
