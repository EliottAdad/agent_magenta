/*
 * ParticleRot3D.h
 *
 *  Created on: 12 jan. 2025
 *      Author: esn
 */

#ifndef PARTICLEROT3D_H_

#define PARTICLEROT3D_H_

#include "Particle3D.h"

//template<typename M, typename E> enum<M, E> Property {SN<M, E>, };

/*
 * #######################
 *  ParticleRot3D<M, E> :)
 * #######################
 * A particle with added rotational capabilities
 */
template<typename M, typename E> class ParticleRot3D : public Particle3D<M, E>{
public:
	std::shared_ptr<Vector3D<M, E>> prs;										// Rotational speed.

	ParticleRot3D();
	ParticleRot3D(const Point3D<M, E>& p);
	ParticleRot3D(const SN<M, E>& x, const SN<M, E>& y, const SN<M, E>& z, const SN<M, E>& w={1, 0});
	ParticleRot3D(const WeightedPoint3D<M, E>& wp);
	virtual ~ParticleRot3D();
	ParticleRot3D(const ParticleRot3D<M, E>& p);

	virtual void setT(const float& dt);
	virtual void apply();

	virtual void operator+=(const Vector3D<M, E>& v);// :)
	//virtual void operator+=(const ParticleRot3D<M, E>& p);// :)

	std::string to_string(const bool& spread=false, const bool& full_info=false, const unsigned char& indent=0) const;
	void print(const bool& spread=false, const bool& full_info=false, const unsigned char& indent=0) const;
};

template<typename M, typename E> ParticleRot3D<M, E> operator+(const ParticleRot3D<M, E>& p1, const ParticleRot3D<M, E>& p2);



template<typename M, typename E> ParticleRot3D<M, E>::ParticleRot3D() {
	this->x=SN<M, E>{1,0};
	this->y=SN<M, E>{1,0};
	this->z=SN<M, E>{1,0};
	//this->w=SN<M, E>{1,0};						// Init the Weighted Point to {x=1, y=1, y=1, w=1}
	pfields=std::make_shared<std::unordered_map<std::string, std::shared_ptr<SN<M, E>>>>();
	pfields->insert({"mass", std::make_shared<SN<M, E>>(SN<M, E>{1,0})});

	ps=std::make_shared<Vector3D<M, E>>();		// Vector3D init to end=(1, 1, 1)
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

template<typename M, typename E> ParticleRot3D<M, E>::ParticleRot3D(const Point3D<M, E>& p) {
	this->x=p.x;
	this->y=p.y;
	this->z=p.z;
	//this->w=SN<M, E>{1,0};// Init the Weighted Point to {x, y, y, w=1}
	pfields=std::make_shared<std::unordered_map<std::string, std::shared_ptr<SN<M, E>>>>();
	pfields->insert({"mass", std::make_shared<SN<M, E>>(SN<M, E>{1,0})});

	ps=std::make_shared<Vector3D<M, E>>();
	this->pcolor=NULL;

	m_dt=0;
}

template<typename M, typename E> ParticleRot3D<M, E>::ParticleRot3D(const SN<M, E>& x, const SN<M, E>& y, const SN<M, E>& z, const SN<M, E>& w) {
	this->x=x;
	this->y=y;
	this->z=z;
	pfields=std::make_shared<std::unordered_map<std::string, std::shared_ptr<SN<M, E>>>>();
	pfields->insert({"mass", std::make_shared<SN<M, E>>(w)});

	ps=std::make_shared<Vector3D<M, E>>();
	this->pcolor=NULL;

	m_dt=0;
}

template<typename M, typename E> ParticleRot3D<M, E>::ParticleRot3D(const WeightedPoint3D<M, E>& wp) {
	this->x=wp.x;
	this->y=wp.y;
	this->z=wp.z;
	//this->w=wp.w;// Init the Weighted Point to {x, y, y, w}
	pfields=std::make_shared<std::unordered_map<std::string, std::shared_ptr<SN<M, E>>>>();
	pfields->insert({"mass", std::make_shared<SN<M, E>>(wp.w)});

	ps=std::make_shared<Vector3D<M, E>>();
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

template<typename M, typename E> ParticleRot3D<M, E>::~ParticleRot3D() {
	;//this->~Displayable();
}

template<typename M, typename E> ParticleRot3D<M, E>::ParticleRot3D(const ParticleRot3D<M, E>& p) {
	this->x=p.x;
	this->y=p.y;
	this->z=p.z;
	//this->w=p.w;// Init the Weighted Point to {x, y, y, w}
	//pfields=std::make_shared<std::unordered_map<std::string, std::shared_ptr<SN<M, E>>>>();
	pfields=p->pfields;

	ps=p.ps;
	this->pcolor=p.pcolor;

	m_dt=0;
}



template<typename M, typename E> SN<M, E> ParticleRot3D<M, E>::getX() const {
	return this->x;
}

template<typename M, typename E> SN<M, E> ParticleRot3D<M, E>::getY() const {
	return this->y;
}

template<typename M, typename E> SN<M, E> ParticleRot3D<M, E>::getZ() const {
	return this->z;
}

template<typename M, typename E> SN<M, E> ParticleRot3D<M, E>::getW() const {
	SN<M, E> w{1,0};

	if (pfields!=NULL /*&& pfields->contains("mass")*/){
		w=*((*pfields)["mass"]);
	}

	return w;
}

template<typename M, typename E> void ParticleRot3D<M, E>::setT(const float& dt) {
	m_dt=dt;
}

template<typename M, typename E> void ParticleRot3D<M, E>::apply(){
	this->x+=(ps->pp2->x)*m_dt;
	this->y+=(ps->pp2->y)*m_dt;
	this->z+=(ps->pp2->z)*m_dt;
}


template<typename M, typename E> void ParticleRot3D<M, E>::operator+=(const Vector3D<M, E>& v){
	if (this->ps!=NULL){
		*this->ps+=v;
	}else{
		*this->ps=v;
	}
}

/*template<typename M, typename E> void ParticleRot3D<M, E>::operator+=(const ParticleRot3D<M, E>& p){
	if (this->ps!=NULL){
		*this->ps+=v;
	}else{
		*this->ps=v;
	}
}*/



template<typename M, typename E> std::string ParticleRot3D<M, E>::to_string(const bool& spread, const bool& full_info, const unsigned char& indent) const {
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
	mes+="w:";// + this->w.to_string();
	mes+=" | ";
	mes+=(ps==NULL)?"NULL":ps->to_string(false, false);
	mes+=")";
	return mes;
}

template<typename M, typename E> void ParticleRot3D<M, E>::print(const bool& spread, const bool& full_info, const unsigned char& indent) const {
	printTabs(indent);
	std::cout << this->to_string(spread, full_info, indent);
}

template<typename M, typename E> ParticleRot3D<M, E> operator+(const ParticleRot3D<M, E>& p1, const ParticleRot3D<M, E>& p2){
	std::shared_ptr<ParticleRot3D<M, E>> pparticle=std::make_shared<ParticleRot3D<M, E>>();
	*(pparticle->ps)=*(p1->ps)+*(p2->ps);
	*(pparticle->prs)=*(p1->prs)+*(p2->prs);
	pparticle->pfields=std::make_shared<std::unordered_map<std::string, std::shared_ptr<SN<M, E>>>>();
	if (p1->pfields!=NULL && p1->pfields->contains("mass") && p2->pfields!=NULL && p2->pfields->contains("mass")) {
		pparticle->pfields->insert({"mass", *(p1->pfields)["mass"]+*(p2->pfields)["mass"]});
	}
}




#endif /* PARTICLE3D_H_ */
