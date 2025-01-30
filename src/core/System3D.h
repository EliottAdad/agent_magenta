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
#include "../core/CoordinateSystem3D.h"
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
public:
	U a;																		// Lenght of the side of the zone.
	std::shared_ptr<Oct<T, U>> poctree;											// Pointer to the Octree.
	std::unordered_set<std::shared_ptr<T>> pelements;
	void (*ptrLaw) (System3D<T, U>* psys);											// Pointer to a function operating on the system
	//Vector3D<U> (*ptrLaw) (std::shared_ptr<T>, std::shared_ptr<T>);				// Pointer to a function operating on 2 particles (Todo List)
	std::shared_ptr<CoordinateSystem3D<T>> pcoord_sys;

	System3D();
	virtual ~System3D();
	System3D(const System3D<T, U>& sys);

	void setA(const U& a);
	float getAlpha() const;
	void setAlpha(const float& alpha);
	std::shared_ptr<T> addPElement(std::shared_ptr<T> pelement);
	std::unordered_set<std::shared_ptr<T>> getPNeighbors(const std::shared_ptr<T> pelement) const;				// Returns the list of neighbours, given the precision.
	std::unordered_set<std::shared_ptr<T>> recalculate();
	void empty();

	// From TimeSensitive
	virtual void setT(const float& dt);
	virtual void apply();

	//From Displayable
	virtual U getX() const;
	virtual U getY() const;
	virtual U getZ() const;
	virtual Point3D<U> getPosition() const;
	virtual std::unordered_set<std::shared_ptr<Point3D<U>>> getPPoints() const;

	//From Printable
	virtual std::string to_string(const bool& spread=false, const bool& full_info=false, const unsigned char& indent=0) const;// :)
	virtual void print(const bool& spread=false, const bool& full_info=false, const unsigned char& indent=0) const;// :)
};

//Functions
template<typename T, typename U> void gravitOptimised(System3D<T, U>* psystem);// Gravit Function Optimsed by Barnes-Hutt algorithm
template<typename T, typename U> void elecOptimised(System3D<T, U>* psystem);
template<typename T> Vector3D<SN<float, char>> rrr2(std::shared_ptr<T> pT1, std::shared_ptr<T> pT2);// Returns l'acc exercée par p2 sur p1
template<typename T> Vector3D<SN<float, char>> rrr3(std::shared_ptr<T> pT1, std::shared_ptr<T> pT2);


template<typename T, typename U> System3D<T, U>::System3D() {
	this->a=(U)100;				//100x100m sided box
	poctree=std::make_shared<Oct<T, U>>(this->a);
	ptrLaw=NULL;
	m_dt=0;
}

template<typename T, typename U> System3D<T, U>::~System3D() {
	pelements.clear();
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
 * Recomputes the structure for you.
 * An all in one alternative to: changing a and than recompute manually.
 * :X
 */
template<typename T, typename U> void System3D<T, U>::setA(const U& a) {
	poctree->setA(a);
	this->recalculate();//Possible probleme
}

template<typename T, typename U> float System3D<T, U>::getAlpha() const {
	return poctree->m_ALPHA;
}

template<typename T, typename U> void System3D<T, U>::setAlpha(const float& alpha) {
	poctree->m_ALPHA=alpha;
}

/**
 * Correct way to add an element to a System.
 * Adds to the octree and update the unordered_set.
 * returns
 * NULL if it was inserted successfully
 *  or the pointer that was passed in argument if it was enable.
 *  if entered NULL pointer returns NULL
 */
template<typename T, typename U> std::shared_ptr<T> System3D<T, U>::addPElement(std::shared_ptr<T> pelement) {
	 std::shared_ptr<T> pT=NULL;

	if (pelement!=NULL) {
		pT=poctree->insert(pelement);
		if (pT==NULL){
			pelements.insert(pelement);
		}
	}

	return pT;
}

template<typename T, typename U> std::unordered_set<std::shared_ptr<T>> System3D<T, U>::getPNeighbors(const std::shared_ptr<T> pelement) const {
	return poctree->getPNeighbors(pelement);
}

template<typename T, typename U> void System3D<T, U>::setT(const float& dt) {
	m_dt=dt;

	// Set time for all objects.
	for (std::shared_ptr<T> pelement : pelements){
		pelement->setT(m_dt);
	}
	// If there is a law to apply... calls it
	if (ptrLaw!=NULL){
		(*ptrLaw)(this);
	}
}

template<typename T, typename U> void System3D<T, U>::apply() {
	for (std::shared_ptr<T> pelement : pelements){
		pelement->apply();
	}
	//Than we recalculate the System
	this->recalculate();
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

template<typename T, typename U> std::unordered_set<std::shared_ptr<Point3D<U>>> System3D<T, U>::getPPoints() const{
	std::unordered_set<std::shared_ptr<Point3D<U>>> ppoints;
	for (std::shared_ptr<T> pelement : pelements){
		std::unordered_set<std::shared_ptr<Point3D<U>>> ppoints_element=pelement->getPPoints();
		for (std::shared_ptr<Point3D<U>> ppoint : ppoints_element){
			ppoints.insert(ppoint);
		}
	}
	return ppoints;
}

template<typename T, typename U> std::unordered_set<std::shared_ptr<T>> System3D<T, U>::recalculate() {//Than we recalculate the Oct.
	std::unordered_set<std::shared_ptr<T>> perrored_elements=poctree->recalculate();//Stores the objects that are now outside of the Oct
	// We get rid of them (not sure it works)
	for (std::shared_ptr<T> perrored_element : perrored_elements){
		printf("Forget this element !\n");
		pelements.erase(perrored_element);
	}
	return perrored_elements;
}

template<typename T, typename U> void System3D<T, U>::empty() {
	poctree->empty();
}


template<typename T, typename U> std::string System3D<T, U>::to_string(const bool& spread, const bool& full_info, const unsigned char& indent) const {
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
}



/*
 * Functions
 */


/**
 * Gravitational force optimised by Barnes-Hutt's algo
 * function that will be applied.
 */
template<typename T, typename U> void gravitOptimised(System3D<T, U>* psystem) {
	for (std::shared_ptr<T> pelement : psystem->pelements) {

		std::unordered_set<std::shared_ptr<T>> pneighbors=psystem->poctree->getPNeighbors(pelement);

		// Apply the grav law
		for (std::shared_ptr<T> pneighbor : pneighbors) {
			Vector3D<SN<float, char>> da=rrr2(pneighbor, pelement);				// Get the acceleration
			*pelement+=da*(SN<float, char>)psystem->getT();							//Surcharger l'op += entre T et Vector3D
		}
	}
}

/**
 * function that will be applied.
 */
template<typename T, typename U> void elecOptimised(System3D<T, U>* psystem) {
	for (std::shared_ptr<T> pelement : psystem->pelements) {

		std::unordered_set<std::shared_ptr<T>> pneighbors=psystem->poctree->getPNeighbors(pelement);

		// Apply the grav law
		for (std::shared_ptr<T> pneighbor : pneighbors) {
			Vector3D<SN<float, char>> da=rrr3(pneighbor, pelement);				// Get the acceleration
			*pelement+=da*(SN<float, char>)psystem->getT();							//Surcharger l'op += entre T et Vector3D
		}
	}
}

/*
 * Gravitation
 * Returns the acc (in norm) felt by pT2 due to pT1
 * @param : pT1: src, pT2: target
 */
template<typename T> Vector3D<SN<float, char>> rrr2(std::shared_ptr<T> pT1, std::shared_ptr<T> pT2) {
	std::shared_ptr<Vector3D<SN<float, char>>> pv(new Vector3D<SN<float, char>>());
	*pv->pp1=(Point3D<SN<float, char>>)pT2->getPosition();
	*pv->pp2=Point3D<SN<float, char>>{(SN<float, char>)0,(SN<float, char>)0,(SN<float, char>)0};

	if (pT1!=NULL && pT2!=NULL && pT1->pfields!=NULL) {// && pT1->pfields->contains("mass")
		*pv->pp2=pT1->getPosition()-pT2->getPosition();

		SN<float, char> d=getDistance((Point3D<SN<float, char>>)pT1->getPosition(), (Point3D<SN<float, char>>)pT2->getPosition());
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
template<typename T> Vector3D<SN<float, char>> rrr3(std::shared_ptr<T> pT1, std::shared_ptr<T> pT2) {
	std::shared_ptr<Vector3D<SN<float, char>>> pv(new Vector3D<SN<float, char>>());
	*pv->pp1=(Point3D<SN<float, char>>)pT2->getPosition();
	*pv->pp2=Point3D<SN<float, char>>{(SN<float, char>)0,(SN<float, char>)0,(SN<float, char>)0};

	if (pT1!=NULL && pT2!=NULL && pT1->pfields!=NULL) {// && pT1->pfields->contains("mass")
		*pv->pp2=pT1->getPosition()-pT2->getPosition();

		SN<float, char> d=getDistance((Point3D<SN<float, char>>)pT1->getPosition(), (Point3D<SN<float, char>>)pT2->getPosition());// Probleme: 2 objects sont sur la meme pos (getNeighbors ne fait pas son job)
		pv->setNorm(K*abs(*((*pT1->pfields)["charge"]))/(d*d));
	}

	return *pv;
}



#endif /* SYSTEM3D_H_ */
