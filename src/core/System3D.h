/*
 * ParticleSystem3D.h
 *
 *  Created on: 7 juin 2024
 *      Author: esn
 */

#ifndef SYSTEM3D_H_
#define SYSTEM3D_H_

#include <unordered_set>

//#include "Particle3D.h"
#include "Oct.h"
#include "TimeSensitive.h"
#include "macros.h"

/*
 * ############
 *  System3D :)
 * ############
 * Can contain any object having .x, .y, .z, methods: .getX(), .getY(), .getZ()
 * If you want to use the functions (rrr, ...) you need a .getW() too
 */
template <typename T> class System3D : public TimeSensitive {
protected:
	LSN m_a;														// Lenght of the side of the zone.
	//std::unordered_set<Particle3D*> m_pparticles;					// Pointers to the Particles (useless: already in the octree)
	Oct<T>* m_poctree;												// Pointer to the Octree.
	LSN (*m_ptrLaw) (T*, T*);										// Pointer to a function operating on 2 particles (Todo List)

	long double m_dt;
	std::unordered_set<T*> m_pelements;

public:
	System3D();
	//System3D(const System3D &other);
	virtual ~System3D();

	LSN getA() const;
	void setA(const LSN& a);
	Oct<T>* getPOctree();
	//void setOctree(const float& alpha);
	float getAlpha() const;
	void setAlpha(const float& alpha);
	std::unordered_set<T*> getPElements() const;
	bool addPElement(T* pelement);
	std::unordered_set<T*> getPNeighbors(const T* pelement) const;				// Returns the list of neighbours, given the precision.
	//void removePParticle(Particle3D* ppart);
	void setPFunc(LSN (*ptrLaw) (T*, T*));
	//void setPFunc(void (*ptrLaw) (T*, T*, const long double&));
	void recalculate() const;
	void empty();

	virtual void setT(const long double& dt);	// From TimeSensitive
	virtual void apply();						// From Moveable
	//virtual void move(const Vector3D& dp);

	virtual std::string to_string(const bool& spread=false, const bool& full_info=false, const unsigned char& indent=0) const;// :)
	virtual void print(const bool& spread=false, const bool& full_info=false, const unsigned char& indent=0) const;// :)
};

//Functions
template <typename T> void rrr(T* p1, T* p2, const long double& dt);
template <typename T> LSN rrr2(T* p1, T* p2);// Returns l'acc exercée par p2 sur p1

/*
 * Returns the vector immediately (useless)
 */
void grav(Particle3D* pp1, Particle3D* pp2, const long double& dt);
void grav(Particle3D* pp1, Particle3D* pp2, const long double& dt){
	Vector3D* pv1=new Vector3D({pp1->x, pp1->y, pp1->z}, {pp2->x-pp1->x, pp2->y-pp1->y, pp2->z-pp1->z});
	Vector3D* pv2=new Vector3D({pp2->x, pp2->y, pp2->z}, {pp1->x-pp2->x, pp1->y-pp2->y, pp1->z-pp2->z});
	LSN d=getDistance({pp2->x-pp1->x, pp2->y-pp1->y, pp2->z-pp1->z});
	pv1->setNorm({1, 0});
	pv2->setNorm({1, 0});

	(*pv1)*=G;
	(*pv1)*=pp2->w;
	(*pv1)/=d;
	(*pv1)/=d;

	(*pv2)*=G;
	(*pv2)*=pp1->w;
	(*pv2)/=d;
	(*pv2)/=d;

	(*pv1)*=pow(dt, 2)/2;
	(*pv2)*=pow(dt, 2)/2;

	pp1->addSpeed(*pv1);
	pp2->addSpeed(*pv2);
}


template <typename T> System3D<T>::System3D() {
	m_a={1,2};				//100m sided box
	m_poctree=new Oct<T>(m_a);
	m_ptrLaw=NULL;
	m_dt=0;
}

/*System3D::System3D(const System3D &other) {
	// TODO Auto-generated constructor stub

}*/

template <typename T> System3D<T>::~System3D() {
	delete m_poctree;
	m_pelements.clear();
}



template <typename T> LSN System3D<T>::getA() const {
	return m_poctree->getA();
}

template <typename T> void System3D<T>::setA(const LSN& a) {
	m_poctree->setA(a);
	//this->recalculate();//Possible probleme
}

template <typename T> Oct<T>* System3D<T>::getPOctree() {
	return m_poctree;
}

template <typename T> float System3D<T>::getAlpha() const {
	return m_poctree->m_ALPHA;
}

template <typename T> void System3D<T>::setAlpha(const float& alpha) {
	m_poctree->m_ALPHA=alpha;
}

template <typename T> std::unordered_set<T*> System3D<T>::getPElements() const {
	return m_poctree->getPElements();
}

template <typename T> bool System3D<T>::addPElement(T* pelement) {
	bool success=false;
	if (pelement!=NULL) {
		success=m_poctree->insert(pelement);
		m_pelements.insert(pelement);
	}
	return success;
}

template <typename T> std::unordered_set<T*> System3D<T>::getPNeighbors(const T* pelement) const {
	return m_poctree->getPNeighbors(pelement);
}

template <typename T> void System3D<T>::setT(const long double& dt) {
	m_dt=dt;

	printf("Set T (System3D)\n");
	printf("%Lf\n", m_dt);
	for (T* pelement : m_pelements){
		pelement->setT(m_dt);

		// If there is a law to apply
		if (m_ptrLaw!=NULL){
			printf("A\n");
			std::unordered_set<T*> pneighbors=m_poctree->getPNeighbors(pelement);
			printf("B\n");
			if(pneighbors.empty()){
				printf("Pas de neighbors\n");
			}else{
				printf("Neighbors\n");
			}
			// Apply the law
			for (T* pneighbor : pneighbors){
				//(*m_ptrLaw)(pelement, pneighbor, m_dt);// Probleme qd appel loi
				LSN norm=(*m_ptrLaw)(pelement, pneighbor);// Get the norm of the acceleration
				Line3D l;//Works
				Vector3D v;//X Error (arrete l'execution)
				/*Vector3D v((Point3D)(pelement->getPosition()), (Point3D)(pneighbor->getPosition()));
				v.setNorm(norm);
				Point3D dv=v.getEnd();
				pelement->x+=dv.x;
				pelement->y+=dv.y;
				pelement->z+=dv.z;*/
				/*pelement->x+=norm;
				pelement->y+=norm;
				pelement->z+=norm;*/
				/*pelement->addSpeed(Point3D{norm, {0, 0}, {0, 0}});*///
				LSN lsn{dt/10., 0};
				lsn.recal();
				pelement->x-=lsn;
				pelement->y+=lsn;
				pelement->z+=lsn;
			}
		}
	}
}

template <typename T> void System3D<T>::apply(){
	printf("Apply (System3D)\n");
	for (T* pelement : m_pelements){
		pelement->apply();
	}
}


/*void System3D::move(const Vector3D& dv) {
	for (Particle3D* ppart : m_poctree->getPElements()){
		//ppart->wp+= dp.getP2();
		//ppart->addAsPos(dp);
	}
}*/


/*template <typename T> void System3D<T>::setPFunc(void (*ptrLaw) (T*, T*, const long double&)){
	m_ptrLaw=ptrLaw;
	//printf("%p\n", m_ptrLaw);
}*/

template <typename T> void System3D<T>::setPFunc(LSN (*ptrLaw) (T*, T*)){
	m_ptrLaw=ptrLaw;
	//printf("%p\n", m_ptrLaw);
}

template <typename T> void System3D<T>::recalculate() const {
	/*for (Oct<T>* ptree : m_poctree->getPTrees()){
		delete ptree;
	}
	for (T* pelement : m_pelements){
		m_poctree->insert(pelement);
	}*/
	m_poctree->recalculate();
}

template <typename T> void System3D<T>::empty() {
	m_poctree->empty();
}


template <typename T> std::string System3D<T>::to_string(const bool& spread, const bool& full_info, const unsigned char& indent) const {
	std::string mes=((spread)?"\n" : "");
	mes+=to_stringTabs(indent);

	if (full_info){
		mes+="SYSTEM[";
		std::stringstream ss;
		ss << this;
		mes+=ss.str();
		mes+="]:\n";
		mes+=to_stringTabs(indent+1);
		mes+="a=" + m_a.to_string(false, false, 0);
		mes+=((spread)?"\n" : "");
	}
	if (full_info){
		/*for (T* pelement : m_poctree->getPElements()){
			mes+=to_stringTabs(indent+1);
			mes+="* ";
			mes+=pelement->to_string(false, false, 0);
			mes+="\n";
		}*/
		mes+=m_poctree->to_string(spread, full_info, indent+1);
	}

	return mes;
}

template <typename T> void System3D<T>::print(const bool& spread, const bool& full_info, const unsigned char& indent) const {
	printTabs(indent);
	std::cout << this->to_string(spread, indent, full_info);
}



/*
 * Functions
 */
template <typename T> void rrr(T* p1, T* p2, const long double& dt) {
	printf("Function (rrr)\n");
	Vector3D v;//=new Vector3D(NULL, Point3D{p2->getX(), p2->getY(), p2->getZ()}-Point3D{p1->getX(), p1->getY(), p1->getZ()});
	//Vector3D* pv=new Vector3D(NULL, Point3D{p2->getX(), p2->getY(), p2->getZ()}-Point3D{p1->getX(), p1->getY(), p1->getZ()});
	LSN d=v.getNorm();
	//LSN d=pv->getNorm();
	v/=d;
	//*pv/=d;
	v.setNorm(G*p2->getW()/(d*d));
	//pv->setNorm(G*p2->getW()/(d*d));
	printf("d:\n");
	d.print(true, true, 1);
	printf("\n");

	p1->getPSpeed()->addEnd({{dt, 0}, {0, 0}, {0, 0}});
	//p1->getPSpeed()->addEnd(pv->getEnd()*dt);//+=;//Problem
	printf("d2\n");
	//delete pv;
}

/*
 * Returns the acc (in norm) felt by p1 due to p2
 */
template <typename T> LSN rrr2(T* p1, T* p2) {
	printf("Function (rrr2)\n");
	LSN d=getDistance(*p1, *p2);
	return G*p2->getW()/(d*d);
}



#endif /* SYSTEM3D_H_ */
