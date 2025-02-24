/*
 * Oct.hpp
 *
 *  Created on: 20 août 2024
 *      Author: esn
 */

#ifndef OCT_HPP_

#define OCT_HPP_

#include <memory>
#include <cstdio>
#include <unordered_set>

#include "SN.hpp"
#include "Point3D.hpp"
#include "../utilities/functions.hpp"


#define TLFTree ptrees[0] 	// Top Left Front corner : is NULL if nothing
#define TRFTree ptrees[1]	// Top Right Front corner : is NULL if nothing
#define BRFTree ptrees[2]	// Bottom Right Front corner : is NULL if nothing
#define BLFTree ptrees[3]	// Bottom Left Front corner : is NULL if nothing
#define TLBTree ptrees[4]	// Top Left Back corner : is NULL if nothing
#define TRBTree ptrees[5]	// Top Right Back corner : is NULL if nothing
#define BRBTree ptrees[6]	// Bottom Right Back corner : is NULL if nothing
#define BLBTree ptrees[7]	// Bottom Left Back corner : is NULL if nothing


/*
 * #############
 *  Oct<U, T> :)
 * #############
 * U is the class for the objects stored.
 * T is the unit used for distance.
 * Can contain any object that has methods .getPosition, (pU->*ptr_getW)(), +=
 */
template<typename U, typename T> class Oct {
protected:
	// Internal variables
	Oct<U, T>* m_poct_parent;							// Pointer to the parent oct;
	std::unique_ptr<Point3D<T>> m_ppoint;				// The center of the zone.
	std::unique_ptr<Point3D<T>> m_pbarycenter;			// The center of mass given the repartition of the WeightedPoints in the zone.

	T m_ha;												// Half of the length of the zone's border (better to make calculations).
	T m_lim_ha;						// This indicates the limit at which we stop subdividing (unused for now)
	
	T (*m_ptr_getW)(const U&);						// Pointer to the method to compute weights (called on U)
	T m_tot_weight;										// Total weight contained in this Oct.

	std::shared_ptr<U> m_pU;							// The content of this square (NULL if nothing).

	static unsigned int m_NB_OCTS;						// Keeps track of the number of Octs created.

	// Internal methods
	void insertTLFTree(std::shared_ptr<U> pU);//:)
	void insertTRFTree(std::shared_ptr<U> pU);//:)
	void insertBRFTree(std::shared_ptr<U> pU);//:)
	void insertBLFTree(std::shared_ptr<U> pU);//:)
	void insertTLBTree(std::shared_ptr<U> pU);//:)
	void insertTRBTree(std::shared_ptr<U> pU);//:)
	void insertBRBTree(std::shared_ptr<U> pU);//:)
	void insertBLBTree(std::shared_ptr<U> pU);//:)

public:
	typedef T (*PtrGetW)(const U&);				// Defines a function's pointer (used locally)
	//std::string weight_id;					// "mass" or "charge"
	float alpha;							// The threshold alpha=ha/d (with ha being half of the width of the zone and d the distance from the center of the quad) indicates at which point we can consider an agglomeration of bodies as one.
											// Plus alpha est petit plus on est precis
											
	std::unique_ptr<Oct<U, T>> ptrees[8];				// Contains the trees.
	static std::unordered_set<Oct<U, T>*> LEAVES;			// Keeps track of the Octs that are leaves.
	bool ffuse;											// Leaves the choice between fusing the elements at insertion if they are at the same coords, or not inserting them.
	
	Oct();
	Oct(const T& a, const Point3D<T>& p={(T)0,(T)0,(T)0});
	virtual ~Oct();
	Oct(const Oct<U, T>& oct);

	Point3D<T> getPoint() const;
	void setPoint(const Point3D<T>& point);
	Point3D<T> getBarycenter() const;
	T getA() const;
	std::unordered_set<std::shared_ptr<U>> setA(const T& a);
	T getTotWeight() const;
	std::shared_ptr<U> getPU() const;
	
	PtrGetW getPtrGetW() const {return this->m_ptr_getW;}
	std::unordered_set<std::shared_ptr<U>> setPtrGetW(PtrGetW ptr_getW) {
		this->m_ptr_getW=ptr_getW;
		return this->recalculate();
	}
	
	unsigned int getNB_OCTS() const;
	
	std::unordered_set<Oct<U, T>*> getPChilds() const;	//Returns all the trees directly under, contained by this tree.
	std::unordered_set<const Oct<U, T>*> getPUnderLeaves(const bool& mem=false) const;	//Returns all the trees that are leaves directly under, contained by this tree.
	std::unordered_set<std::shared_ptr<U>> getPElements(const bool& mem=false) const;					//:) Returns all the elements contained in the tree.
	std::unordered_set<std::shared_ptr<U>> getPNeighbors(const std::shared_ptr<U> pelement, const bool& mem=false) const;		//:) Returns all the neighbors.
	std::unordered_set<Oct<U, T>*> getPNeighbouringOcts() const;		//:) Returns all the neighbouring octs.

	std::shared_ptr<U> insert(std::shared_ptr<U> pU);//:)
	bool remove(std::shared_ptr<U> pU);//:)
	std::shared_ptr<U> search(const std::shared_ptr<Point3D<T>> ppoint) const;
	std::unordered_set<std::shared_ptr<U>> recalculate();
	void empty();

	bool isFull() const;
	bool isEmpty() const;
	bool isLeaf() const;
	bool isRoot() const;
};
template<typename U, typename T> unsigned int Oct<U, T>::m_NB_OCTS=0;
template<typename U, typename T> std::unordered_set<Oct<U, T>*> Oct<U, T>::LEAVES={};



/*
 * Constructor0
 */
template<typename U, typename T> inline Oct<U, T>::Oct() {
	// Internal variables
	this->m_poct_parent=NULL;
	this->m_ppoint=std::make_unique<Point3D<T>>();
	this->m_pbarycenter=std::make_unique<Point3D<T>>(*m_ppoint);

	this->m_ha=(T)50;		//100x100m sided box
	this->m_lim_ha=0.5;
	
	this->m_ptr_getW=NULL;
	this->m_tot_weight=(T)0;

	this->m_pU=NULL;

	for (unsigned char i(0) ; i<8 ; i++) {
		this->ptrees[i]=NULL;
	}

	this->m_NB_OCTS++;
	
	// External variables
	//this->weight_id="";					// "mass" or "charge"
	this->alpha=0.5;
	this->ffuse=false;
}

/**
 * Constructor1
 * @param \a{The side's lenght of the area}
 * @param \p{The center on which is centered the Oct's area}
 */
template<typename U, typename T> inline Oct<U, T>::Oct(const T& a, const Point3D<T>& p) {
	// Internal variables
	this->m_poct_parent=NULL;
	this->m_ppoint=std::make_unique<Point3D<T>>(p);
	this->m_pbarycenter=std::make_unique<Point3D<T>>(*m_ppoint);

	this->m_ha=a/(T)2;
	this->m_lim_ha=0.5;
	
	this->m_ptr_getW=NULL;
	this->m_tot_weight=(T)0;

	this->m_pU=NULL;

	for (unsigned char i(0) ; i<8 ; i++) {
		this->ptrees[i]=NULL;
	}

	this->m_NB_OCTS++;
	
	// External variables
	//this->weight_id="";					// "mass" or "charge"
	this->alpha=0.5;
	this->ffuse=false;
}

template<typename U, typename T> inline Oct<U, T>::~Oct() {
	
	this->m_poct_parent=NULL;
	this->m_ptr_getW=NULL;
	
	this->m_pU=NULL;
	
	this->empty();

	// There is one less Oct
	this->m_NB_OCTS--;
}

/*
 * Copy constructor
 */
template<typename U, typename T> inline Oct<U, T>::Oct(const Oct<U, T>& oct) {
	// Internal variables
	this->m_poct_parent=NULL;
	this->m_ppoint=std::make_unique<Point3D<T>>(oct.getPoint());
	this->m_pbarycenter=std::make_unique<Point3D<T>>(*m_ppoint);

	this->m_ha=oct.getA()/(T)2;
	this->m_lim_ha=0.5;			// TODO Copy from oct
	
	this->m_ptr_getW=oct.getPtrGetW();
	this->m_tot_weight=(T)0;

	this->m_pU=NULL;

	for (unsigned char i(0) ; i<8 ; i++) {
		this->ptrees[i]=NULL;
	}

	this->m_NB_OCTS++;
	
	// External variables
	//this->weight_id=oct.weight_id;					// "mass" or "charge"
	this->alpha=oct.alpha;
	this->ffuse=oct.ffuse;

	// Reinsert the elements.
	this->insert(oct.getPElements());
}




template<typename U, typename T> inline Point3D<T> Oct<U, T>::getPoint() const {// Because it can be NULL
	return *this->m_ppoint;
}

template<typename U, typename T> inline void Oct<U, T>::setPoint(const Point3D<T>& point) {
	*this->m_ppoint=point;
		// Et le barycentre ?
	*this->m_pbarycenter=*this->m_ppoint;
	this->recalculate();
}

template<typename U, typename T> inline Point3D<T> Oct<U, T>::getBarycenter() const {
	return *this->m_pbarycenter;
}

template<typename U, typename T> inline T Oct<U, T>::getA() const {
	return this->m_ha*(T)2;
}

template<typename U, typename T> inline std::unordered_set<std::shared_ptr<U>> Oct<U, T>::setA(const T& a){
	this->m_ha=a/(T)2;
	return this->recalculate();
}

template<typename U, typename T> inline T Oct<U, T>::getTotWeight() const {
	return this->m_tot_weight;
}

template<typename U, typename T> inline std::shared_ptr<U> Oct<U, T>::getPU() const {
	return this->m_pU;
}

/*
template<typename U, typename T> inline template<typename U, typename T> Oct<U, T>::PtrGetW Oct<U, T>::getPtrGetW() const {
	return this->m_ptr_getW;
}

template<typename U, typename T> inline bool Oct<U, T>::setPtrGetW(Oct<U, T>::PtrGetW ptr_getW) {
	this->m_ptr_getW=ptr_getW;
	
	return this->recalculate();
}*/

template<typename U, typename T> inline unsigned int Oct<U, T>::getNB_OCTS() const {
	return this->m_NB_OCTS;
}

template<typename U, typename T> inline std::unordered_set<Oct<U, T>*> Oct<U, T>::getPChilds() const {
	std::unordered_set<Oct<U, T>*> pchilds;
	for (unsigned char i(0) ; i<8 ; i++){
		if (this->ptrees[i]!=NULL){
			pchilds.insert(this->ptrees[i].get());
		}
	}
	return pchilds;
}

/**
 * Returns all the trees that are leaves directly under (including this tree), contained by this tree.
 * mem: flag memorise (recursive call)
 */
template<typename U, typename T> inline std::unordered_set<const Oct<U, T>*> Oct<U, T>::getPUnderLeaves(const bool& mem) const {
	static std::unordered_set<const Oct<U, T>*> pleaves={};

	if (mem==false){
		pleaves.clear();
	}

	if (this->isLeaf()){// If leaf, adds itself
		pleaves.insert(this);
	}

	for (Oct<U, T>* pchild : this->getPChilds()){
			pchild->getPUnderLeaves(true);
	}

	return pleaves;
}

/**
 * mem: flag memorise (recursive call)
 */
template<typename U, typename T> inline std::unordered_set<std::shared_ptr<U>> Oct<U, T>::getPElements(const bool& mem) const {
	static std::unordered_set<std::shared_ptr<U>> elmts;

	if (mem==false){
		elmts.clear();
	}

	if (m_pU!=NULL){
		elmts.insert(m_pU);
	}else{
		for (unsigned char i(0) ; i<8 ; i++){
			if (this->ptrees[i]!=NULL){
				this->ptrees[i]->getPElements(true);
			}
		}
	}

	return elmts;
}

/**
 * h
 * U needs a constructor from x, y, z and w (of unit T)
 */
template<typename U, typename T> inline std::unordered_set<std::shared_ptr<U>> Oct<U, T>::getPNeighbors(const std::shared_ptr<U> pelement, const bool& mem) const {//////LOOOOK HERE !
	static std::unordered_set<std::shared_ptr<U>> pneighbors;

	if (mem==false){
		pneighbors.clear();
	}

	if (pelement!=NULL){
		if (this->m_pU==NULL && (T)(this->alpha)<=m_ha/getDistance(*this->m_pbarycenter, pelement->getPosition())){//U{1., 0}/getDistance(*m_ppoint, *pelement)<=U{m_ALPHA, 0}
			for (unsigned char i(0) ; i<8 ; i++){
				if (this->ptrees[i]!=NULL){
					this->ptrees[i]->getPNeighbors(pelement, true);
				}
			}
		}else{
			if (this->m_pU!=NULL){// If the cube is not empty
				if (this->m_pU!=pelement){
					pneighbors.insert(this->m_pU);
				}
			}else{			// Else if the place is empty
				printf("Oct: getPNeighbors %f, %f, %f, %f\n", this->m_pbarycenter->x.to_m_type(), this->m_pbarycenter->y.to_m_type(), this->m_pbarycenter->z.to_m_type(), this->m_tot_weight.to_m_type());
				std::shared_ptr<U> new_pU=std::make_shared<U>(
												this->m_pbarycenter->x, 
												this->m_pbarycenter->y, 
												this->m_pbarycenter->z, 
												this->m_tot_weight);
				pneighbors.insert(new_pU);
			}
		}
	}

	return pneighbors;
}

/**
 * Returns the neighboring Octs
 */
template<typename U, typename T> inline std::unordered_set<Oct<U, T>*> Oct<U, T>::getPNeighbouringOcts() const {
	static pneigh_octs;
	pchilds;
	if (this->m_poct_parent!=NULL){
		pchilds=this->m_poct_parent->getChilds();
	}
	pchilds.remove(this);

	for (pchild : pchilds){
		d=getDistance(*this->m_ppoint, pchild->getPoint())
		if (this->getA()+pchild->getA() == 2*d){// Facade
			+=pow(pchild->getA(), 2);		//Must be >=pow(this->getA(), 2) on every face when done
		}else if(sqrt(2)*(this->getA()+pchild->getA())==d){// Corner
			corner+=pchild->getA();		// Must be 12*this->getA() when done
		}else if(sqrt(3)*(this->getA()+pchild->getA())==d){//Corner corner
			corner2+=1			// Must be 8 when done
		}
	}
	if (){//If les conds ne sont pas reunies regarde plus haut.
		this->m_poct_parent->getPNeighbouringOcts();
	}
}

/**
 * returns
 * NULL if it was inserted successfully or if entered NULL pointer
 *  or the pointer that was passed in argument if it was enable.
 * needs ->getX,getY,getZ, ptr_getW
 */
template<typename U, typename T> inline std::shared_ptr<U> Oct<U, T>::insert(std::shared_ptr<U> pU) {
	printf("Oct: insert\n");
	// If the object to insert is not NULL
	if (pU!=NULL){
		Point3D<T> p=pU->getPosition();
		Point3D<T> dp=p-*this->m_ppoint;

		if (abs(dp.x)<=m_ha && 
				abs(dp.y)<=this->m_ha && 
				abs(dp.z)<=this->m_ha && 
				this->m_ptr_getW!=NULL){// If in the cube centered on the point.

			printf("Oct: insert2\n");
			// Manages the barycenter
			this->m_tot_weight+=(*(this->m_ptr_getW))(*pU);//Add to tot_weight
			if (this->m_tot_weight!=(T)0){
				*this->m_pbarycenter+=p * (*(this->m_ptr_getW))(*pU)/m_tot_weight;//Add to the barycenter
			}else{
				*this->m_pbarycenter=*this->m_ppoint;
			}

			printf("Oct: insert3\n");
			if (this->isEmpty() && this->isLeaf()){		// If empty and the cube has no Octs under (if it's a leaf)
				this->m_pU=pU;//We add in
				this->LEAVES.insert(this);// Marked as a leaf
				printf("Oct: insert4\n");
			}else{										// Else it means it is an internal branch (or a leaf already full)
				printf("Oct: insert5\n");
				if (this->isFull() && p==this->m_pU->getPosition()){// If pU and m_pU at the same location
					if (this->ffuse){
						*this->m_pU+=*pU;
					}else{
						return pU;
					}
				}else if (dp.x<=(T)0 && dp.y<=(T)0 && dp.z>=(T)0){	//If cube 1
					insertTLFTree(pU);
				}else if (dp.x>=(T)0 && dp.y<=(T)0 && dp.z>=(T)0){	//If cube 2
					insertTRFTree(pU);
				}else if (dp.x>=(T)0 && dp.y<=(T)0 && dp.z<=(T)0){	//If cube 3
					insertBRFTree(pU);
				}else if (dp.x<=(T)0 && dp.y<=(T)0 && dp.z<=(T)0){	//If cube 4
					insertBLFTree(pU);
				}else if (dp.x<=(T)0 && dp.y>=(T)0 && dp.z>=(T)0){	//If cube 5
					insertTLBTree(pU);
				}else if (dp.x>=(T)0 && dp.y>=(T)0 && dp.z>=(T)0){	//If cube 6
					insertTRBTree(pU);
				}else if (dp.x>=(T)0 && dp.y>=(T)0 && dp.z<=(T)0){	//If cube 7
					insertBRBTree(pU);
				}else if (dp.x<=(T)0 && dp.y>=(T)0 && dp.z<=(T)0){	//If cube 8
					insertBLBTree(pU);
				}
				printf("Oct: insert6\n");

				// We reinsert the object already present(can be null if it wasn't a leaf).
				if (this->m_pU!=NULL){
					printf("Oct: insert7\n");
					this->m_tot_weight-=(*(this->m_ptr_getW))(*pU);//Subtract the w of the already present obj to tot_weight
					std::shared_ptr<U> pU2;//Init to null
					pU2.swap(m_pU);// Set m_pU to NULL and pU2 to m_pU
					printf("Oct: insert8\n");
					this->insert(pU2);
				}
			}
		}else{
			return pU;
		}
	}else{
		return NULL;
	}
	return NULL;
}

template<typename U, typename T> inline void Oct<U, T>::insertTLFTree(std::shared_ptr<U> pU) {//In private
	if (TLFTree==NULL){//If there is not yet a tree we create it
		T a=this->m_ha/(T)2;
		Point3D<T> np{(T)(-1)*a, (T)(-1)*a, (T)(1)*a};
		TLFTree=std::make_unique<Oct<U, T>>(this->m_ha, *this->m_ppoint+np);
		TLFTree->m_poct_parent=this;
	}
	TLFTree->insert(pU);
}

template<typename U, typename T> inline void Oct<U, T>::insertTRFTree(std::shared_ptr<U> pU) {//En private
	if (TRFTree==NULL){//If there is not yet a tree we create it
		T a=this->m_ha/(T)2;
		Point3D<T> np{(T)(1)*a, (T)(-1)*a, (T)(1)*a};
		TRFTree=std::make_unique<Oct<U, T>>(this->m_ha, *this->m_ppoint+np);
		TRFTree->m_poct_parent=this;
	}
	TRFTree->insert(pU);
}

template<typename U, typename T> inline void Oct<U, T>::insertBRFTree(std::shared_ptr<U> pU) {//En private
	if (BLBTree==NULL){//If there is not yet a tree we create it
		T a=this->m_ha/(T)2;
		Point3D<T> np{(T)(1)*a, (T)(-1)*a, (T)(-1)*a};
		BLBTree=std::make_unique<Oct<U, T>>(this->m_ha, *this->m_ppoint+np);
		BLBTree->m_poct_parent=this;
	}
	BLBTree->insert(pU);
}

template<typename U, typename T> inline void Oct<U, T>::insertBLFTree(std::shared_ptr<U> pU) {//En private
	if (BLFTree==NULL){//If there is not yet a tree we create it
		T a=this->m_ha/(T)2;
		Point3D<T> np{(T)(-1)*a, (T)(-1)*a, (T)(-1)*a};
		BLFTree=std::make_unique<Oct<U, T>>(this->m_ha, *this->m_ppoint+np);
		BLFTree->m_poct_parent=this;
	}
	BLFTree->insert(pU);
}

template<typename U, typename T> inline void Oct<U, T>::insertTLBTree(std::shared_ptr<U> pU) {//En private
	if (TLBTree==NULL){//If there is not yet a tree we create it
		T a=this->m_ha/(T)2;
		Point3D<T> np{(T)(-1)*a, (T)(1)*a, (T)(1)*a};
		TLBTree=std::make_unique<Oct<U, T>>(this->m_ha, *this->m_ppoint+np);
		TLBTree->m_poct_parent=this;
	}
	TLBTree->insert(pU);
}

template<typename U, typename T> inline void Oct<U, T>::insertTRBTree(std::shared_ptr<U> pU) {//En private
	if (TRBTree==NULL){//If there is not yet a tree we create it
		T a=this->m_ha/(T)2;
		Point3D<T> np{(T)(1)*a, (T)(1)*a, (T)(1)*a};
		TRBTree=std::make_unique<Oct<U, T>>(this->m_ha, *this->m_ppoint+np);
		TRBTree->m_poct_parent=this;
	}
	TRBTree->insert(pU);
}

template<typename U, typename T> inline void Oct<U, T>::insertBRBTree(std::shared_ptr<U> pU) {//En private
	if (BRBTree==NULL){//If there is not yet a tree we create it
		T a=this->m_ha/(T)2;
		Point3D<T> np{(T)(1)*a, (T)(1)*a, (T)(-1)*a};
		BRBTree=std::make_unique<Oct<U, T>>(this->m_ha, *this->m_ppoint+np);
		BRBTree->m_poct_parent=this;
	}
	BRBTree->insert(pU);
}

template<typename U, typename T> inline void Oct<U, T>::insertBLBTree(std::shared_ptr<U> pU) {//En private
	if (BLBTree==NULL){//If there is not yet a tree we create it
		T a=this->m_ha/(T)2;
		Point3D<T> np{(T)(-1)*a, (T)(1)*a, (T)(-1)*a};
		BLBTree=std::make_unique<Oct<U, T>>(this->m_ha, *this->m_ppoint+np);
		BLBTree->m_poct_parent=this;
	}
	BLBTree->insert(pU);
}

/**
 * Removes the given object and reconstructs the tree.
 * Returns true if the element was present, false if not.
 */
template<typename U, typename T> inline bool Oct<U, T>::remove(std::shared_ptr<U> pU) {
	bool test=false;
	std::unordered_set<std::shared_ptr<U>> pelements=this->getPElements();

	this->empty();

	for (std::shared_ptr<U> pelement : pelements){
		if (pelement != pU){
			this->insert(pelement);//:)
		}else{
			test=true;
		}
	}
	return test;
}

/**
 * Gives up objects that are outside of the range.
 */
template<typename U, typename T> inline std::unordered_set<std::shared_ptr<U>> Oct<U, T>::recalculate() {
	std::unordered_set<std::shared_ptr<U>> pelements=this->getPElements();
	std::unordered_set<std::shared_ptr<U>> perrored_elements;

	this->empty();

	for (std::shared_ptr<U> pelement : pelements){
		std::shared_ptr<U> perrored=this->insert(pelement);//:)
		if (perrored!=NULL){
			perrored_elements.insert(perrored);
		}
	}
	return perrored_elements;
}

/**
 * Empty the octree from all elements ans subtrees.
 */
template<typename U, typename T> inline void Oct<U, T>::empty() {
	// Gets the leaves under.
	std::unordered_set<const Oct<U, T>*> under_leaves=getPUnderLeaves();
	// Suppress the leaves under from the leaves list.
	for (const Oct<U, T>* poct : under_leaves){
		if (this->LEAVES.contains(poct)){
			this->LEAVES.erase(poct);
		}
	}

	// No more under Octs
	for (unsigned char i(0) ; i<8 ; i++){
		if (this->ptrees[i]!=NULL){
			this->ptrees[i]=NULL;
		}
	}

	*this->m_pbarycenter=*this->m_ppoint;
	this->m_tot_weight=(T)0;
	this->m_pU=NULL;
}

/**
 * Returns true if contains an object.
 * False otherwise.
 */
template<typename U, typename T> inline bool Oct<U, T>::isFull() const {
	return !this->isEmpty();
}

/**
 * Returns true if doesn't contain an object.
 * False otherwise.
 */
template<typename U, typename T> inline bool Oct<U, T>::isEmpty() const {
	bool test=false;

	if (this->m_pU==NULL){
		test=true;
	}

	return test;
}

/**
 * @return
 * Returns false if contains at least a subtree.
 * True otherwise.
 */
template<typename U, typename T> inline bool Oct<U, T>::isLeaf() const {
	bool test=true;

	for (unsigned char i(0) ; i<8 ; i++){
		if (this->ptrees[i]!=NULL){
			test=false;
			break;
		}
	}

	return test;
}

/**
 * @return
 * Returns true if it has no upper tree.
 * False otherwise.
 */
template<typename U, typename T> inline bool Oct<U, T>::isRoot() const {
	if (this->poct_parent==NULL){
		return true;
	}else{
		return false;
	}
}




#endif /* OCT_HPP_ */
