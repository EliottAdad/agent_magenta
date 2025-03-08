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
#include "Vector3D.hpp"
#include "CoordinateSystem3D.hpp"
#include "Oct.hpp"
#include "Mobile3D.hpp"
#include "Displayable3D.hpp"
#include "TimeSensitive.hpp"
#include "../utilities/macros.hpp"

/*
 * ##################
 *  System3D<U, T> :)
 * ##################
 * @brief
 * U is the type of object stored, T is the unit
 * Can contain any object having .x, .y, .z, methods: .getX(), .getY(), .getZ(), .getPosition(), that is a TimeSensitive(setT), ->getPPoints()
 * Can contain objects derived from TimeSensitive and Displayable3D with a pointer to a function ->getW()
 * If you want to use the functions (rrr, ...) you need a .getW() 
 * TODO : Surcharger le cas U=TimeSensitive
 */
template<typename U, typename T> class System3D : public Static3D<T>, public Displayable3D<T> {
protected:
	std::shared_ptr<Oct<U, T>> m_poctree;											// Pointer to the Octree.
	std::unordered_set<std::shared_ptr<U>> m_pelements;
	
public:
	typedef T (*PtrGetW)(const U&);				// Defines a function's pointer (used locally)
	void (*ptrLaw) (const System3D<U, T>& sys);											// Pointer to a function operating on the system
	//Vector3D<U> (*ptrLaw) (std::shared_ptr<T>, std::shared_ptr<T>);				// Pointer to a function operating on 2 particles (Todo List)

	System3D();
	virtual ~System3D();
	System3D(const System3D<U, T>& sys);

	std::unordered_set<std::shared_ptr<U>> getPossibleColliding(Oct<U, T>* poct);
	// Over Oct
	T getA() const {return m_poctree->getA();}
	std::unordered_set<std::shared_ptr<U>>  setA(const T& a) {return m_poctree->setA(a);}
	Point3D<T> getPoint() const {return this->m_poctree->getPoint();}
	void setPoint(const Point3D<T>& point) {this->m_poctree->setPoint(point);}
	Point3D<T> getBarycenter() const {return this->m_poctree->getBarycenter();}
	float getAlpha() const {return this->m_poctree->alpha;}
	void setAlpha(const float& alpha) {this->m_poctree->alpha=alpha;}
	PtrGetW getPtrGetW() const {return this->m_poctree->getPtrGetW();}
	std::unordered_set<std::shared_ptr<U>> setPtrGetW(PtrGetW ptr_getW) {printf("System3S: setPtrGetW\n");return this->m_poctree->setPtrGetW(ptr_getW);}
	unsigned int getNB_OCTS() const {return this->poctree->getNB_OCTS();}
	
	std::unordered_set<std::shared_ptr<U>> getPElements() const {return this->m_pelements;}					//:) Returns all the elements contained in the tree.
	std::unordered_set<std::shared_ptr<U>> getPNeighbors(const std::shared_ptr<U> pelement) const {return this->m_poctree->getPNeighbors(pelement);}		//:) Returns all the neighbors.
	std::shared_ptr<U> insert(std::shared_ptr<U> pU) {
		m_pelements.insert(pU);
		return this->m_poctree->insert(pU);
	}
	bool remove(std::shared_ptr<U> pU) {
		this->m_pelements.erase(pU);
		return this->m_poctree->remove(pU);
	}
	std::shared_ptr<U> search(const std::shared_ptr<Point3D<T>> ppoint) const {return this->poctree->search(ppoint);}	// Useless i think
	std::unordered_set<std::shared_ptr<U>> recalculate() {
		std::unordered_set<std::shared_ptr<U>> perrored=this->m_poctree->recalculate();
		for (std::shared_ptr<U> pU : perrored){
			this->m_pelements.erase(pU);
		}
		return perrored;
	}
	void empty() {
		this->m_pelements.clear();
		this->m_poctree->empty();
	}

	// From TimeSensitive
	virtual float getT() const {return TimeSensitive::getT();};
	virtual void setT(const float& dt);
	virtual void apply();

	// From Static3D
	virtual T getX() const;
	virtual T getY() const;
	virtual T getZ() const;
	virtual Point3D<T> getPosition() const;
	
	// From Displayable3D
	virtual std::unordered_set<Point3D<T>*> getPPoints(const CoordinateSystem3D<T>& coord_system_caller) const;
};

//Functions
template<typename U, typename T> void gravitOptimised(System3D<U, T>* psystem);// Gravit Function Optimsed by Barnes-Hutt algorithm
template<typename U, typename T> void elecOptimised(System3D<U, T>* psystem);
template<typename T, typename U> Vector3D<T> apply_gravitOptimised(std::shared_ptr<U> pU1, std::shared_ptr<U> pU2, T (*ptr_getW)(const U&));// Returns l'acc exercée par p2 sur p1
template<typename T, typename U> Vector3D<T> apply_elecOptimised(std::shared_ptr<U> pU1, std::shared_ptr<U> pU2, T (*ptr_getW)(const U&));






template<typename U, typename T> inline System3D<U, T>::System3D() : Displayable3D<T>(), Static3D<T>() {
	this->m_poctree=std::make_shared<Oct<U, T>>();
	this->ptrLaw=NULL;
}

/*template<typename T> inline System3D<Particle3D<T>, T>::System3D() : Displayable3D<T>() {
	this->poctree=std::make_shared<Oct<U, T>>();
	this->ptrLaw=NULL;
}*/

template<typename U, typename T> inline System3D<U, T>::~System3D() {
	this->m_pelements.clear();
	this->ptrLaw=NULL;
}

template<typename U, typename T> inline System3D<U, T>::System3D(const System3D<U, T>& sys) : Displayable3D<T>(sys), Static3D<T>(sys) {
	
	this->m_poctree=std::make_shared<Oct<U, T>>(*sys.m_poctree);
	this->ptrLaw=sys.ptrLaw;
	
	for (std::shared_ptr<U> pU : sys.getPElements()) {
		this->addPElement(pU);
	}
}



template<typename U, typename T> inline std::unordered_set<std::shared_ptr<U>> System3D<U, T>::getPossibleColliding(Oct<U, T>* poct) {
	std::unordered_set<std::shared_ptr<U>> pUin_neighs;
	std::unordered_set<Oct<U, T>*> pneigh_octs=this->m_poctree->getPNeighbouringOcts(poct);
	
	for (Oct<U, T>* pneigh_oct : pneigh_octs){
		pUin_neighs.insert(pneigh_oct->getPElements());
	}
	
	return pUin_neighs;
}





/*
 * From TimeSensitive
 */

/**
 * Need TimeSensitives
 */
template<typename U, typename T> inline void System3D<U, T>::setT(const float& dt) {
	this->m_dt=dt;
	//printf("System3D: setT");
	// Set time for all objects.
	for (std::shared_ptr<U> pelement : this->m_pelements){
		pelement->setT(this->m_dt);
	}
	// If there is a law to apply... calls it
	if (this->ptrLaw!=NULL){
		//printf("System3D: setT2");
		(*ptrLaw)(*(this));
	}
}

template<typename U, typename T> inline void System3D<U, T>::apply() {
	// We aaply to each element
	//printf("System3D: apply");
	for (std::shared_ptr<U> pelement : this->m_pelements){
		pelement->apply();
	}
	// Than we recalculate the System3D
	this->recalculate();
}


/*
 * From Mobile
 */

/**
 * l
 */
template<typename U, typename T> inline T System3D<U, T>::getX() const {
	return this->m_poctree->getPoint().x;
}

template<typename U, typename T> inline T System3D<U, T>::getY() const {
	return this->m_poctree->getPoint().y;
}

template<typename U, typename T> inline T System3D<U, T>::getZ() const {
	return this->m_poctree->getPoint().z;
}

template<typename U, typename T> inline Point3D<T> System3D<U, T>::getPosition() const {
	return this->m_poctree->getPoint();
}

/*
 * From Displayable
 */

/**
 * l
 */
template<typename U, typename T> inline std::unordered_set<Point3D<T>*> System3D<U, T>::getPPoints(const CoordinateSystem3D<T>& coord_system_caller) const {
	std::unordered_set<Point3D<T>*> ppoints;
	for (std::shared_ptr<U> pelement : this->m_pelements){
		std::unordered_set<Point3D<T>*> ppoints_element=pelement->getPPoints(*this->pcoord_system);
		for (Point3D<T>* ppoint : ppoints_element){
			ppoints.insert(ppoint);
		}
	}
	return ppoints;
}







/*
 * Functions
 */


/**
 * @brief
 * Gravitational force optimised by Barnes-Hutt's algo
 * function that will be applied.
 */
template<typename U, typename T> inline void gravitOptimised(const System3D<U, T>& system) {
	printf("System3D: gravitOptimised1\n");
	for (std::shared_ptr<U> pelement : system.getPElements()) {

		// YES
		std::unordered_set<std::shared_ptr<U>> pneighbors=system.getPNeighbors(pelement);// PROBLEM
		
		//printf("System3D: gravitOptimised2\n");
		// Apply the grav law
		for (std::shared_ptr<U> pneighbor : pneighbors) {
			//NO
			printf("System3D: gravitOptimised3\n");
			Vector3D<T> da=apply_gravitOptimised(pneighbor, pelement, system.getPtrGetW());				// Get the acceleration
			//printf("System3D: gravitOptimised4\n");
			*pelement+=da*(T)system.getT();						//Surcharger l'op += entre U et Vector3D
		}
	}
	//printf("System3D: gravitOptimised4\n");
}

/**
 * @brief
 * function that will be applied.
 */
template<typename U, typename T> inline void elecOptimised(const System3D<U, T>& system) {
	for (std::shared_ptr<U> pelement : system.getPElements()) {

		std::unordered_set<std::shared_ptr<U>> pneighbors=system.getPNeighbors(pelement);

		// Apply the grav law
		for (std::shared_ptr<U> pneighbor : pneighbors) {
			Vector3D<T> da=apply_elecOptimised(pneighbor, pelement, system.getPtrGetW());				// Get the acceleration
			*pelement+=da*(T)system.getT();							//Surcharger l'op += entre T et Vector3D
		}
	}
}

/**
 * @brief
 * Gravitation
 * Returns the acc (in norm) felt by pU2 due to pU1
 * @param : pU1: src, pU2: target (not NULL)
 */
template<typename T, typename U> inline Vector3D<T> apply_gravitOptimised(std::shared_ptr<U> pU1, std::shared_ptr<U> pU2, T (*ptr_getW)(const U&)) {
	printf("System3D: rrr2 1\n");
	std::shared_ptr<Vector3D<T>> pv=std::make_shared<Vector3D<T>>(pU2->getPosition(), Point3D<T>{(T)0,(T)0,(T)0});
	//printf("System3D: rrr2 2\n");
	//pv->setP1(pU2->getPosition());
	//printf("System3D: rrr2 3\n");
	//pv->setpp2=std::make_shared<Point3D<T>>((T)0,(T)0,(T)0);
	
	//printf("System3D: rrr2 4\n");

	if (ptr_getW!=NULL) {// && pT1->pfields->contains("mass")
		//*pv->pp2=pU1->getPosition()-pU2->getPosition();
		pv->setP2(pU1->getPosition()-pU2->getPosition());

		T d=getDistance(
					(Point3D<T>)pU1->getPosition(), 
					(Point3D<T>)pU2->getPosition()
					);
		//d.print();						// Probleme: 2 objects sont sur la meme pos (getNeighbors ne fait pas son job)
		pv->setNorm(G(T) * abs((*ptr_getW)(*pU1))/(d*d));
	}
	//printf("System3D: rrr2 5\n");
	
	return *pv;
}

/**
 * @brief
 * Electromagnetics
 * Returns the acc (in norm) felt by pU2 due to pU1
 * @param : pU1: src, pU2: target (not NULL pls)
 */
template<typename T, typename U> inline Vector3D<T> apply_elecOptimised(std::shared_ptr<U> pU1, std::shared_ptr<U> pU2, T (*ptr_getW)(const U&)) {
	std::shared_ptr<Vector3D<T>> pv=std::make_shared<Vector3D<T>>(pU2->getPosition(), Point3D<T>{(T)0,(T)0,(T)0});
	
	if (ptr_getW!=NULL) {
		pv->setP2(pU1->getPosition()-pU2->getPosition());

		T d=getDistance(
					(Point3D<T>)pU1->getPosition(), 
					(Point3D<T>)pU2->getPosition()
					);// Probleme: 2 objects sont sur la meme pos (getNeighbors ne fait pas son job)
		pv->setNorm(K(T) * abs((*ptr_getW)(*pU1))/(d*d));
	}

	return *pv;
}



#endif /* SYSTEM3D_HPP_ */
