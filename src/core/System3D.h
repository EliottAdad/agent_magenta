/*
 * System3D.h
 *
 *  Created on: 7 juin 2024
 *      Author: esn
 */

#ifndef SYSTEM3D_H_

#define SYSTEM3D_H_

#include <memory>
#include <unordered_set>

#include "../utilities/macros.h"
#include "../core/Vector3D.h"
#include "Oct.h"
#include "TimeSensitive.h"
#include "../display/Displayable.h"

/*
 * ##################
 *  System3D<T, U> :)
 * ##################
 * Can contain any object having .x, .y, .z, methods: .getX(), .getY(), .getZ(), .getPosition()
 * If you want to use the functions (rrr, ...) you need a .getW() too
 */
template<typename T, typename U> class System3D : public TimeSensitive, public Displayable<U>{
protected:
	std::unordered_set<std::shared_ptr<T>> m_pelements;

public:
	U a;																		// Lenght of the side of the zone.
	std::shared_ptr<Oct<T, U>> poctree;											// Pointer to the Octree.
	Vector3D<U> (*ptrLaw) (std::shared_ptr<T>, std::shared_ptr<T>);				// Pointer to a function operating on 2 particles (Todo List)

	System3D();
	virtual ~System3D();
	System3D(const System3D<T, U>& sys);

	void setA(const U& a);
	float getAlpha() const;
	void setAlpha(const float& alpha);
	std::unordered_set<std::shared_ptr<T>> getPElements() const;
	bool addPElement(std::shared_ptr<T> pelement);
	std::unordered_set<std::shared_ptr<T>> getPNeighbors(const std::shared_ptr<T> pelement) const;				// Returns the list of neighbours, given the precision.
	//void removePParticle(Particle3D* ppart);
	//void setPFunc(T (*ptrLaw) (T*, T*));
	//void setPFunc(void (*ptrLaw) (T*, T*, const long double&));
	void recalculate() const;
	void empty();

	// From TimeSensitive
	virtual void setT(const float& dt);
	virtual void apply();

	//From Displayable
	virtual U getX() const;
	virtual U getY() const;
	virtual U getZ() const;
	virtual Point3D<U> getPosition() const;
	//virtual std::unordered_set<std::shared_ptr<Point3D<U>>> getPPoints() const;

	//From Printable
	virtual std::string to_string(const bool& spread=false, const bool& full_info=false, const unsigned char& indent=0) const;// :)
	virtual void print(const bool& spread=false, const bool& full_info=false, const unsigned char& indent=0) const;// :)
};

//Functions
template<typename T, typename U> void rrr(std::shared_ptr<T> p1, std::shared_ptr<T> p2, const long double& dt);
template<typename T, typename U> U rrr2(std::shared_ptr<T> p1, std::shared_ptr<T> p2);// Returns l'acc exercée par p2 sur p1



template<typename T, typename U> System3D<T, U>::System3D() {
	this->a=(U)100;				//100m sided box
	poctree=std::make_shared<Oct<T, U>>(this->a);
	ptrLaw=NULL;
	m_dt=0;
}

template<typename T, typename U> System3D<T, U>::~System3D() {
	m_pelements.clear();
}

template<typename T, typename U> System3D<T, U>::System3D(const System3D<T, U>& sys) {
	this->a=sys.a;
	poctree=std::make_shared<Oct<T, U>>(this->a);
	for (std::shared_ptr<T> pT : sys.getPElements()) {
		this->addPElement(pT);
	}
	ptrLaw=sys.ptrLaw;
	m_dt=0;
}


/**
 * Alternative to setting than recompute manually.
 * Recomputes the structure for you.
 * :X
 */
template<typename T, typename U> void System3D<T, U>::setA(const U& a) {
	poctree->setA(a);
	//this->recalculate();//Possible probleme
}

/*template<typename T, typename U> Oct<T, U>* System3D<T, U>::getPOctree() {
	return m_poctree;
}*/

template<typename T, typename U> float System3D<T, U>::getAlpha() const {
	return poctree->m_ALPHA;
}

template<typename T, typename U> void System3D<T, U>::setAlpha(const float& alpha) {
	poctree->m_ALPHA=alpha;
}

template<typename T, typename U> std::unordered_set<std::shared_ptr<T>> System3D<T, U>::getPElements() const {
	return poctree->getPElements();
}

template<typename T, typename U> bool System3D<T, U>::addPElement(std::shared_ptr<T> pelement) {
	bool success=false;

	if (pelement!=NULL) {
		success=poctree->insert(pelement);
		m_pelements.insert(pelement);
	}

	return success;
}

template<typename T, typename U> std::unordered_set<std::shared_ptr<T>> System3D<T, U>::getPNeighbors(const std::shared_ptr<T> pelement) const {
	return poctree->getPNeighbors(pelement);
}

template<typename T, typename U> void System3D<T, U>::setT(const float& dt) {
	//printf("setT (System3D)\n");
	m_dt=dt;

	//printf("Set T (System3D)\n");
	//printf("%f\n", m_dt);
	//printf("A: %ld\n", m_pelements.size());
	for (std::shared_ptr<T> pelement : m_pelements){
		pelement->setT(m_dt);
		//printf("B\n");

		// If there is a law to apply
		if (ptrLaw!=NULL){
			std::unordered_set<std::shared_ptr<T>> pneighbors=poctree->getPNeighbors(pelement);
			//printf("C: %ld\n", pneighbors.size());
			if(pneighbors.empty()){
				//printf("Pas de neighbors\n");
			}else{
				//printf("Neighbors\n");
			}
			// Apply the law
			for (std::shared_ptr<T> pneighbor : pneighbors) {// ERROR: Get neighbours doesn't work
				//printf("D\n");
				//(*m_ptrLaw)(pelement, pneighbor, m_dt);// Probleme qd appel loi
				Vector3D<U> da=(*ptrLaw)(pneighbor, pelement);// Get the acceleration
				//da.print(true, true, 3);
				//Line3D<float, char> l;//Works
				//Vector3D<float, char> v;//X Error (arrete l'execution)
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
				*pelement+=da*(U)dt;//Surcharger l'op += entre T et Vector3D
				//pelement->y+=sn;
				//pelement->z+=sn;
			}
		}
	}
}

template<typename T, typename U> void System3D<T, U>::apply(){
	//printf("Apply (System3D)\n");
	for (std::shared_ptr<T> pelement : m_pelements){
		pelement->apply();
	}
}


template<typename T, typename U> U System3D<T, U>::getX() const {
	return poctree->getPoint().x;
}

template<typename T, typename U> U System3D<T, U>::getY() const {
	return poctree->getPoint().y;
}

template<typename T, typename U> U System3D<T, U>::getZ() const {
	return poctree->getPoint().z;
}

template<typename T, typename U> Point3D<U> System3D<T, U>::getPosition() const {
	return poctree->getPoint();
}


/*template<typename T, typename U> std::unordered_set<std::shared_ptr<Point3D<U>>> getPPoints() const{
	std::unordered_set<std::shared_ptr<Point3D<T>>> ppoints;
	return ppoints;
}*/


/*template<typename T> void System3D<T, U>::setPFunc(void (*ptrLaw) (T*, T*, const long double&)){
	m_ptrLaw=ptrLaw;
	//printf("%p\n", m_ptrLaw);
}*/

/*template<typename T, typename U> void System3D<T, U>::setPFunc(T (*ptrLaw) (T*, T*)){
	m_ptrLaw=ptrLaw;
	//printf("%p\n", m_ptrLaw);
}*/

template<typename T, typename U> void System3D<T, U>::recalculate() const {
	poctree->recalculate();
}

template<typename T, typename U> void System3D<T, U>::empty() {
	poctree->empty();
}


template<typename T, typename U> std::string System3D<T, U>::to_string(const bool& spread, const bool& full_info, const unsigned char& indent) const {
	//printf("AAAAAA1\n");
	std::string mes=((spread)?"\n" : "");
	mes+=to_stringTabs(indent);

	mes+="SYSTEM3D[";
	std::stringstream ss;
	ss << this;
	mes+=ss.str();
	mes+="]:\n";
	mes+=to_stringTabs(indent+1);
	mes+="a=" + this->a.to_string(false, false, 0);
	mes+=((spread)?"\n" : "");

	if (full_info){			// Problem
		mes+=poctree->to_string(spread, full_info, indent+1);
	}

	return mes;
}

template<typename T, typename U> void System3D<T, U>::print(const bool& spread, const bool& full_info, const unsigned char& indent) const {
	printTabs(indent);
	std::cout << this->to_string(spread, full_info, indent);
	//printf("\nAAAAAA2\n");
}



/*
 * Functions
 */
/*template<typename T, typename U> void rrr(std::shared_ptr<T> p1, std::shared_ptr<T> p2, const long double& dt) {
	//printf("Function (rrr)\n");
	Vector3D<float, char> v;//=new Vector3D(NULL, Point3D{p2->getX(), p2->getY(), p2->getZ()}-Point3D{p1->getX(), p1->getY(), p1->getZ()});
	//Vector3D* pv=new Vector3D(NULL, Point3D{p2->getX(), p2->getY(), p2->getZ()}-Point3D{p1->getX(), p1->getY(), p1->getZ()});
	SN<float, char> d=v.getNorm();
	//LSN d=pv->getNorm();
	v/=d;
	// *pv/=d;
	v.setNorm(G*p2->getW()/(d*d));
	//pv->setNorm(G*p2->getW()/(d*d));
	//printf("d:\n");
	//d.print(true, true, 1);
	//printf("\n");

	p1->getPSpeed()->addEnd({{dt,0},{0,0},{0,0}});
	//p1->getPSpeed()->addEnd(pv->getEnd()*dt);//+=;//Problem
	//printf("d2\n");
	//delete pv;
}*/

/*
 * Returns the acc (in norm) felt by pT2 due to pT1
 * @param : pT1: src, pT2: target
 */
/*template<typename T, typename U> Vector3D<T> rrr2(std::shared_ptr<T> pT1, std::shared_ptr<T> pT2) {
	std::shared_ptr<Vector3D<T>> pv(new Vector3D<T>();
	*pv->pp2=Point3D<T>{{0,0},{0,0},{0,0}};

	if (pT1!=NULL && pT2!=NULL) {
		pv=std::make_shared<Vector3D<T>>(pT2->getPosition()-pT1->getPosition());

		T d=getDistance(pT1->getPosition(), pT2->getPosition());
		pv->setNorm(G*pT1->getW()/(d*d));
	}
	return *pv;
}*/

/*
 * Gravitation
 * Returns the acc (in norm) felt by pT2 due to pT1
 * @param : pT1: src, pT2: target
 */
/*template<typename T> Vector3D<T> rrr2(std::shared_ptr<Particle3D<T>> pT1, std::shared_ptr<Particle3D<T>> pT2) {
	std::shared_ptr<Vector3D<T>> pv(new Vector3D<T>());
	*pv->pp1=pT2->getPosition();
	*pv->pp2=Point3D<T>{(T)0,(T)0,(T)0};

	if (pT1!=NULL && pT2!=NULL && pT1->pfields!=NULL && pT1->pfields->contains("mass")) {
		*pv->pp2=pT1->getPosition()-pT2->getPosition();

		T d=getDistance(pT1->getPosition(), pT2->getPosition());
		//printf("\n############d\n");
		//d.print();						// Probleme: 2 objects sont sur la meme pos (getNeighbors ne fait pas son job)
		//printf("\n############d\n");
		pv->setNorm(G*abs(*((*pT1->pfields)["mass"]))/(d*d));
	}
	//printf("\n############pv\n");
	//pv->print();
	//printf("\n############pv\n");
	return *pv;
}
*/
template<typename T, typename U> Vector3D<U> rrr2(std::shared_ptr<T> pT1, std::shared_ptr<T> pT2) {
	std::shared_ptr<Vector3D<U>> pv(new Vector3D<U>());
	*pv->pp1=pT2->getPosition();
	*pv->pp2=Point3D<U>{(U)0,(U)0,(U)0};

	if (pT1!=NULL && pT2!=NULL && pT1->pfields!=NULL) {// && pT1->pfields->contains("mass")
		*pv->pp2=pT1->getPosition()-pT2->getPosition();

		U d=getDistance(pT1->getPosition(), pT2->getPosition());
		//printf("\n############d\n");
		//d.print();						// Probleme: 2 objects sont sur la meme pos (getNeighbors ne fait pas son job)
		//printf("\n############d\n");
		//SN<float, char> n=G*abs(*((*pT1->pfields)["mass"]))/(d*d);
		//n.print(true, true, 0);
		pv->setNorm(G*abs(*((*pT1->pfields)["mass"]))/(d*d));
	}
	//printf("\n############pv\n");
	//pv->print();
	//printf("\n############pv\n");
	return *pv;
}

/*
 * Electromagnetics
 * Returns the acc (in norm) felt by pT2 due to pT1
 * @param : pT1: src, pT2: target
 */
template<typename T> Vector3D<T> rrr3(std::shared_ptr<Particle3D<T>> pT1, std::shared_ptr<Particle3D<T>> pT2) {
	std::shared_ptr<Vector3D<T>> pv(new Vector3D<T>());
	*pv->pp1=pT2->getPosition();
	*pv->pp2=Point3D<T>{(T)0,(T)0,(T)0};

	if (pT1!=NULL && pT2!=NULL) {
		*pv->pp2=pT1->getPosition()-pT2->getPosition();

		T d=getDistance(pT1->getPosition(), pT2->getPosition());
		//printf("\n############d\n");
		//d.print();						// Probleme: 2 objects sont sur la meme pos (getNeighbors ne fait pas son job)
		//printf("\n############d\n");
		pv->setNorm((T)(-1)*K*pT1->getW()*pT2->getW()/(d*d*abs(pT2->getW())));
	}
	//printf("\n############pv\n");
	//pv->print();
	//printf("\n############pv\n");
	return *pv;
}



#endif /* SYSTEM3D_H_ */
