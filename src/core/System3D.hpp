/*
 * System3D.hpp
 *
 *  Created on: 7 juin 2024
 *      Author: esn
 */

#ifndef SYSTEM3D_HPP_

#define SYSTEM3D_HPP_

#include <memory>
#include <unordered_set>

#include "../utilities/macros.hpp"
#include "../core/Vector3D.hpp"
#include "../core/CoordinateSystem3D.hpp"
#include "Oct.hpp"
#include "Mobile.hpp"
#include "../display/Displayable.hpp"

/*
 * ##################
 *  System3D<U, T> :)
 * ##################
 * U is the type of object stored, T is the unit
 * Can contain any object having .x, .y, .z, methods: .getX(), .getY(), .getZ(), .getPosition()
 * If you want to use the functions (rrr, ...) you need a .getW() too
 */
template<typename U, typename T> class System3D : public Displayable<T>, public Mobile<T> {
public:
	T a;																		// Lenght of the side of the zone.
	std::shared_ptr<Oct<U, T>> poctree;											// Pointer to the Octree.
	std::unordered_set<std::shared_ptr<U>> pelements;
	void (*ptrLaw) (System3D<U, T>* psys);											// Pointer to a function operating on the system
	//Vector3D<U> (*ptrLaw) (std::shared_ptr<T>, std::shared_ptr<T>);				// Pointer to a function operating on 2 particles (Todo List)
	std::shared_ptr<CoordinateSystem3D<T>> pcoord_sys;

	System3D();
	virtual ~System3D();
	System3D(const System3D<U, T>& sys);

	void setA(const T& a);
	float getAlpha() const;
	void setAlpha(const float& alpha);
	std::shared_ptr<U> addPElement(std::shared_ptr<U> pelement);
	std::unordered_set<std::shared_ptr<U>> getPNeighbors(const std::shared_ptr<U> pelement) const;				// Returns the list of neighbours, given the precision.
	std::unordered_set<std::shared_ptr<U>> recalculate();
	void empty();

	// From TimeSensitive
	virtual void setT(const float& dt);
	virtual void apply();

	//From Displayable
	virtual T getX() const;
	virtual T getY() const;
	virtual T getZ() const;
	virtual Point3D<T> getPosition() const;
	virtual std::unordered_set<std::shared_ptr<Point3D<T>>> getPPoints() const;

	//From Printable
	virtual std::string to_string(const bool& spread=false, const bool& full_info=false, const unsigned char& indent=0) const;// :)
	virtual void print(const bool& spread=false, const bool& full_info=false, const unsigned char& indent=0) const;// :)
};

//Functions
template<typename U, typename T> void gravitOptimised(System3D<U, T>* psystem);// Gravit Function Optimsed by Barnes-Hutt algorithm
template<typename U, typename T> void elecOptimised(System3D<U, T>* psystem);
template<typename U> Vector3D<SN<float, char>> rrr2(std::shared_ptr<U> pU1, std::shared_ptr<U> pU2);// Returns l'acc exercée par p2 sur p1
template<typename U> Vector3D<SN<float, char>> rrr3(std::shared_ptr<U> pU1, std::shared_ptr<U> pU2);


template<typename U, typename T> System3D<U, T>::System3D() {
	this->a=(T)100;				//100x100m sided box
	poctree=std::make_shared<Oct<U, T>>(this->a);
	ptrLaw=NULL;
	this->m_dt=0;
}

template<typename U, typename T> System3D<U, T>::~System3D() {
	pelements.clear();
}

template<typename U, typename T> System3D<U, T>::System3D(const System3D<U, T>& sys) {
	this->a=sys.a;
	poctree=std::make_shared<Oct<U, T>>(this->a);
	for (std::shared_ptr<U> pU : sys.getPElements()) {
		this->addPElement(pU);
	}
	ptrLaw=sys.ptrLaw;
	this->m_dt=0;
}


/**
 * Recomputes the structure for you.
 * An all in one alternative to: changing a and than recompute manually.
 * :X
 */
template<typename U, typename T> void System3D<U, T>::setA(const T& a) {
	poctree->setA(a);
	this->recalculate();//Possible probleme
}

template<typename U, typename T> float System3D<U, T>::getAlpha() const {
	return poctree->m_ALPHA;
}

template<typename U, typename T> void System3D<U, T>::setAlpha(const float& alpha) {
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
template<typename U, typename T> std::shared_ptr<U> System3D<U, T>::addPElement(std::shared_ptr<U> pelement) {
	 std::shared_ptr<U> pU=NULL;

	if (pelement!=NULL) {
		pU=poctree->insert(pelement);
		if (pU==NULL){
			pelements.insert(pelement);
		}
	}

	return pU;
}

template<typename U, typename T> std::unordered_set<std::shared_ptr<U>> System3D<U, T>::getPNeighbors(const std::shared_ptr<U> pelement) const {
	return poctree->getPNeighbors(pelement);
}

template<typename U, typename T> void System3D<U, T>::setT(const float& dt) {
	this->m_dt=dt;

	// Set time for all objects.
	for (std::shared_ptr<U> pelement : pelements){
		pelement->setT(this->m_dt);
	}
	// If there is a law to apply... calls it
	if (ptrLaw!=NULL){
		(*ptrLaw)(this);
	}
}

template<typename U, typename T> void System3D<U, T>::apply() {
	for (std::shared_ptr<U> pelement : pelements){
		pelement->apply();
	}
	//Than we recalculate the System
	this->recalculate();
}


template<typename U, typename T> T System3D<U, T>::getX() const {
	return poctree->getPoint().x;
}

template<typename U, typename T> T System3D<U, T>::getY() const {
	return poctree->getPoint().y;
}

template<typename U, typename T> T System3D<U, T>::getZ() const {
	return poctree->getPoint().z;
}

template<typename U, typename T> Point3D<T> System3D<U, T>::getPosition() const {
	return poctree->getPoint();
}

template<typename U, typename T> std::unordered_set<std::shared_ptr<Point3D<T>>> System3D<U, T>::getPPoints() const{
	std::unordered_set<std::shared_ptr<Point3D<T>>> ppoints;
	for (std::shared_ptr<U> pelement : pelements){
		std::unordered_set<std::shared_ptr<Point3D<T>>> ppoints_element=pelement->getPPoints();
		for (std::shared_ptr<Point3D<T>> ppoint : ppoints_element){
			ppoints.insert(ppoint);
		}
	}
	return ppoints;
}

template<typename U, typename T> std::unordered_set<std::shared_ptr<U>> System3D<U, T>::recalculate() {//Than we recalculate the Oct.
	std::unordered_set<std::shared_ptr<U>> perrored_elements=poctree->recalculate();//Stores the objects that are now outside of the Oct
	// We get rid of them (not sure it works)
	for (std::shared_ptr<U> perrored_element : perrored_elements){
		printf("Forget this element !\n");
		pelements.erase(perrored_element);
	}
	return perrored_elements;
}

template<typename U, typename T> void System3D<U, T>::empty() {
	poctree->empty();
}


template<typename U, typename T> std::string System3D<U, T>::to_string(const bool& spread, const bool& full_info, const unsigned char& indent) const {
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

template<typename U, typename T> void System3D<U, T>::print(const bool& spread, const bool& full_info, const unsigned char& indent) const {
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
template<typename U, typename T> void gravitOptimised(System3D<U, T>* psystem) {
	for (std::shared_ptr<U> pelement : psystem->pelements) {

		std::unordered_set<std::shared_ptr<U>> pneighbors=psystem->poctree->getPNeighbors(pelement);

		// Apply the grav law
		for (std::shared_ptr<U> pneighbor : pneighbors) {
			Vector3D<SN<float, char>> da=rrr2(pneighbor, pelement);				// Get the acceleration
			*pelement+=da*(SN<float, char>)psystem->getT();						//Surcharger l'op += entre U et Vector3D
		}
	}
}

/**
 * function that will be applied.
 */
template<typename U, typename T> void elecOptimised(System3D<U, T>* psystem) {
	for (std::shared_ptr<U> pelement : psystem->pelements) {

		std::unordered_set<std::shared_ptr<U>> pneighbors=psystem->poctree->getPNeighbors(pelement);

		// Apply the grav law
		for (std::shared_ptr<U> pneighbor : pneighbors) {
			Vector3D<SN<float, char>> da=rrr3(pneighbor, pelement);				// Get the acceleration
			*pelement+=da*(SN<float, char>)psystem->getU();							//Surcharger l'op += entre T et Vector3D
		}
	}
}

/*
 * Gravitation
 * Returns the acc (in norm) felt by pT2 due to pT1
 * @param : pT1: src, pT2: target
 */
template<typename U> Vector3D<SN<float, char>> rrr2(std::shared_ptr<U> pU1, std::shared_ptr<U> pU2) {
	std::shared_ptr<Vector3D<SN<float, char>>> pv(new Vector3D<SN<float, char>>());
	*pv->pp1=(Point3D<SN<float, char>>)pU2->getPosition();
	*pv->pp2=Point3D<SN<float, char>>{(SN<float, char>)0,(SN<float, char>)0,(SN<float, char>)0};

	if (pU1!=NULL && pU2!=NULL && pU1->pfields!=NULL) {// && pT1->pfields->contains("mass")
		*pv->pp2=pU1->getPosition()-pU2->getPosition();

		SN<float, char> d=getDistance((Point3D<SN<float, char>>)pU1->getPosition(), (Point3D<SN<float, char>>)pU2->getPosition());
		//printf("\n############d\n");
		//d.print();						// Probleme: 2 objects sont sur la meme pos (getNeighbors ne fait pas son job)
		//printf("\n############d\n");
		//SN<float, char> n=G*abs(*((*pT1->pfields)["mass"]))/(d*d);
		//n.print(true, true, 0);
		pv->setNorm(G*abs(*((*pU1->pfields)["mass"]))/(d*d));
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
template<typename U> Vector3D<SN<float, char>> rrr3(std::shared_ptr<U> pU1, std::shared_ptr<U> pU2) {
	std::shared_ptr<Vector3D<SN<float, char>>> pv(new Vector3D<SN<float, char>>());
	*pv->pp1=(Point3D<SN<float, char>>)pU2->getPosition();
	*pv->pp2=Point3D<SN<float, char>>{(SN<float, char>)0,(SN<float, char>)0,(SN<float, char>)0};

	if (pU1!=NULL && pU2!=NULL && pU1->pfields!=NULL) {// && pT1->pfields->contains("mass")
		*pv->pp2=pU1->getPosition()-pU2->getPosition();

		SN<float, char> d=getDistance((Point3D<SN<float, char>>)pU1->getPosition(), (Point3D<SN<float, char>>)pU2->getPosition());// Probleme: 2 objects sont sur la meme pos (getNeighbors ne fait pas son job)
		pv->setNorm(K*abs(*((*pU1->pfields)["charge"]))/(d*d));
	}

	return *pv;
}



#endif /* SYSTEM3D_HPP_ */
