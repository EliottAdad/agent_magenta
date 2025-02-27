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


/**
 * #############
 *  Oct<U, T> :)
 * #############
 * @brief
 * U is the class for the objects stored.
 * T is the unit used for distance.
 * Can contain any object that has methods .getPosition, (pU->*ptr_getW)(), +=, constructor from ((T)x, (T)y, (T)z, (T)w)
 * We recommend using the methods provided to manipulate internal vars (methods marked as \\Important).
 * U needs a constructor from x, y, z and w (of unit T)
 * needs ->getX,getY,getZ, ptr_getW
 */
template<typename U, typename T> class Oct {
protected:
	// Internal variables
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
	typedef T (*PtrGetW)(const U&);						// Defines a function's pointer (used locally)
	
	Oct<U, T>* poct_parent;							// Pointer to the parent oct;
	std::unique_ptr<Point3D<T>> ppoint;				// The center of the zone.
	std::unique_ptr<Point3D<T>> pbarycenter;			// The center of mass given the repartition of the WeightedPoints in the zone.

	T ha;												// Half of the length of the zone's border (better to make calculations).
	T lim_ha;						// This indicates the limit at which we stop subdividing (unused for now)
	
	T (*ptr_getW)(const U&);						// Pointer to the method to compute weights (called on U)
	T tot_weight;										// Total weight contained in this Oct.

	std::shared_ptr<U> pU;							// The content of this square (NULL if nothing).

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
	/**
	 * \\Critical
	 */
	std::unordered_set<std::shared_ptr<U>> setPtrGetW(PtrGetW ptr_getW) {
		this->ptr_getW=ptr_getW;
		return this->recalculate();
	}
	
	unsigned int getNB_OCTS() const;
	
	std::unordered_set<Oct<U, T>*> getPChilds() const;	//Returns all the trees directly under, contained by this tree.
	std::unordered_set<Oct<U, T>*> getPBrothers() const;	//Returns all the trees directly under, contained by this tree.
	std::unordered_set<Oct<U, T>*> getPUnderLeaves(const bool& mem=false) const;	//Returns all the trees that are leaves directly under, contained by this tree.
	std::unordered_set<std::shared_ptr<U>> getPElements(const bool& mem=false) const;					//:) Returns all the elements contained in the tree.
	std::unordered_set<std::shared_ptr<U>> getPNeighbors(const std::shared_ptr<U> pelement, const bool& mem=false) const;		//:) Returns all the neighbors.
	std::unordered_set<Oct<U, T>*> getPNeighbouringOcts(const bool& mem=false) const;		//:) Returns all the neighbouring octs.

	std::shared_ptr<U> insert(std::shared_ptr<U> pU);//:)
	bool remove(std::shared_ptr<U> pU);//:)
	//std::shared_ptr<U> search(const std::shared_ptr<Point3D<T>> ppoint) const;
	std::unordered_set<std::shared_ptr<U>> recalculate();
	void empty();

	// Tests
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
	this->poct_parent=NULL;
	this->ppoint=std::make_unique<Point3D<T>>();
	this->pbarycenter=std::make_unique<Point3D<T>>(*ppoint);

	this->ha=(T)50;		//100x100m sided box
	this->lim_ha=0.5;
	
	this->ptr_getW=NULL;
	this->tot_weight=(T)0;

	this->pU=NULL;

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
	this->m_NB_OCTS++;
	
	// External variables
	this->poct_parent=NULL;
	this->ppoint=std::make_unique<Point3D<T>>(p);
	this->pbarycenter=std::make_unique<Point3D<T>>(*ppoint);

	this->ha=a/(T)2;
	this->lim_ha=0.5;
	
	this->ptr_getW=NULL;
	this->tot_weight=(T)0;

	this->pU=NULL;

	for (unsigned char i(0) ; i<8 ; i++) {
		this->ptrees[i]=NULL;
	}
	this->alpha=0.5;
	this->ffuse=false;
}

/**
 * Destructor
 */
template<typename U, typename T> inline Oct<U, T>::~Oct() {
	this->poct_parent=NULL;
	this->ptr_getW=NULL;
	
	this->pU=NULL;
	
	this->empty();

	// There is one less Oct
	this->m_NB_OCTS--;
}

/**
 * Copy constructor
 */
template<typename U, typename T> inline Oct<U, T>::Oct(const Oct<U, T>& oct) {
	// Internal variables
	this->poct_parent=NULL;
	this->ppoint=std::make_unique<Point3D<T>>(oct.getPoint());
	this->pbarycenter=std::make_unique<Point3D<T>>(*ppoint);

	this->ha=oct.getA()/(T)2;
	this->lim_ha=0.5;			// TODO Copy from oct
	
	this->ptr_getW=oct.getPtrGetW();
	this->tot_weight=(T)0;

	this->pU=NULL;

	for (unsigned char i(0) ; i<8 ; i++) {
		this->ptrees[i]=NULL;
	}

	this->m_NB_OCTS++;
	
	// External variables
	this->alpha=oct.alpha;
	this->ffuse=oct.ffuse;

	// Reinsert the elements.
	this->insert(oct.getPElements());
}



/**
 * Returns the point
 */
template<typename U, typename T> inline Point3D<T> Oct<U, T>::getPoint() const {
	return *this->ppoint;
}

/**
 * Sets the point
 * \\Crucial
 */
template<typename U, typename T> inline void Oct<U, T>::setPoint(const Point3D<T>& point) {
	*this->ppoint=point;
		// Et le barycentre ?=>Verif
	*this->pbarycenter=*this->ppoint;
	this->recalculate();
}

/**
 * Returns the barycenter
 */
template<typename U, typename T> inline Point3D<T> Oct<U, T>::getBarycenter() const {
	return *this->pbarycenter;
}

/**
 * Returns the side lenght of the Oct
 */
template<typename U, typename T> inline T Oct<U, T>::getA() const {
	return this->ha*(T)2;
}

/**
 * Sets the side lenght of the Oct
 * \\Crucial
 */
template<typename U, typename T> inline std::unordered_set<std::shared_ptr<U>> Oct<U, T>::setA(const T& a){
	this->ha=a/(T)2;
	return this->recalculate();
}

/**
 * Returns the total weight stored in this Oct
 */
template<typename U, typename T> inline T Oct<U, T>::getTotWeight() const {
	return this->tot_weight;
}

/**
 * Returns the element stored in this Oct
 */
template<typename U, typename T> inline std::shared_ptr<U> Oct<U, T>::getPU() const {
	return this->pU;
}

/**
 * Returns the number of Octs there is.
 */
template<typename U, typename T> inline unsigned int Oct<U, T>::getNB_OCTS() const {
	return this->m_NB_OCTS;
}

/**
 * Get octs a step under.
 */
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
 * Get its brothers (other Octs at the same level, itself excluded)
 */
template<typename U, typename T> inline std::unordered_set<Oct<U, T>*> Oct<U, T>::getPBrothers() const {
	std::unordered_set<Oct<U, T>*> pbrothers;
	if (this->m_poct_parent!=NULL){
		pbrothers=this->m_poct_parent->getChilds();
	}
	pbrothers.remove(this);
	return pbrothers;
}
	
/**
 * Returns all the trees that are leaves directly under (including this tree), contained by this tree.
 * mem: flag memorise (recursive call)
 */
template<typename U, typename T> inline std::unordered_set<Oct<U, T>*> Oct<U, T>::getPUnderLeaves(const bool& mem) const {
	static std::unordered_set<Oct<U, T>*> pleaves;

	if (mem==false){
		pleaves.clear();
	}

	if (this->isLeaf()){// If leaf, adds itself
		pleaves.insert((Oct<U, T>*)this);
	}

	for (Oct<U, T>* pchild : this->getPChilds()){
			pchild->getPUnderLeaves(true);
	}

	return pleaves;
}

/**
 * Returns all the elements that are stored under this Oct and all under Octs.
 * \mem: flag memorise (recursive call), false by default
 */
template<typename U, typename T> inline std::unordered_set<std::shared_ptr<U>> Oct<U, T>::getPElements(const bool& mem) const {
	static std::unordered_set<std::shared_ptr<U>> elmts;

	if (mem==false){
		elmts.clear();
	}

	if (pU!=NULL){
		elmts.insert(pU);
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
 * Gets the neighbouring elements based on the limit alpha given.
 * Create them from the weight and position of the Oct if the considered Oct is far enough.
 * To be used, U needs a constructor from x, y, z and w (of unit T)
 */
template<typename U, typename T> inline std::unordered_set<std::shared_ptr<U>> Oct<U, T>::getPNeighbors(const std::shared_ptr<U> pelement, const bool& mem) const {//////LOOOOK HERE !
	static std::unordered_set<std::shared_ptr<U>> pneighbors;

	if (mem==false){
		pneighbors.clear();
	}

	if (pelement!=NULL){
		if (this->pU==NULL && (T)(this->alpha)<=ha/getDistance(*this->pbarycenter, pelement->getPosition())){//U{1., 0}/getDistance(*m_ppoint, *pelement)<=U{m_ALPHA, 0}
			for (unsigned char i(0) ; i<8 ; i++){
				if (this->ptrees[i]!=NULL){
					this->ptrees[i]->getPNeighbors(pelement, true);
				}
			}
		}else{
			if (this->pU!=NULL){// If the cube is not empty
				if (this->pU!=pelement){
					pneighbors.insert(this->pU);
				}
			}else{			// Else if the place is empty
				//printf("Oct: getPNeighbors %f, %f, %f, %f\n", this->m_pbarycenter->x.to_m_type(), this->m_pbarycenter->y.to_m_type(), this->m_pbarycenter->z.to_m_type(), this->m_tot_weight.to_m_type());
				std::shared_ptr<U> new_pU=std::make_shared<U>(
												this->pbarycenter->x, 
												this->pbarycenter->y, 
												this->pbarycenter->z, 
												this->tot_weight);
				pneighbors.insert(new_pU);
			}
		}
	}

	return pneighbors;
}

/**
 * Returns the Octs sharing a limit with this considered Oct.
 * \mem: flag memorise (recursive call), false by default
 */
template<typename U, typename T> inline std::unordered_set<Oct<U, T>*> Oct<U, T>::getPNeighbouringOcts(const bool& mem) const {
	static Oct<U, T>* target_oct=this;
	static std::unordered_set<Oct<U, T>*> pneigh_octs;
	
	if (mem==false){
		target_oct=NULL;
		pneigh_octs.empty();
	}
	
	std::unordered_set<Oct<U, T>*> pbrothers=this->getBrothers();

	bool recurs=false;// If we should lauch another recursive call
	for (Oct<U, T>* pbrother : pbrothers){
		T d=getDistance(*target_oct->m_ppoint, pbrother->getPoint());
		if (2*d <= sqrt(3)*(target_oct->getA()+pbrother->getA())){// If in the sphere close enough (max corners2)
			pneigh_octs.insert(pbrother);
			recurs=true;
		}
	}
	if (recurs==true){//
		this->poct_parent->getPNeighbouringOcts(true);
	}
	return pneigh_octs;
}

/**
 * Inserts a new element in the structure.
 * Returns :
 * NULL if it was inserted successfully or if NULL is entered pointer,
 *  or the pointer that was passed in argument if it was enable.
 * needs ->getX,getY,getZ, ptr_getW
 * \\Critical
 */
template<typename U, typename T> inline std::shared_ptr<U> Oct<U, T>::insert(std::shared_ptr<U> pU) {
	// If the object to insert is not NULL
	if (pU!=NULL){
		Point3D<T> p=pU->getPosition();
		Point3D<T> dp=p-*this->ppoint;

		if (abs(dp.x)<=ha && 
				abs(dp.y)<=this->ha && 
				abs(dp.z)<=this->ha && 
				this->ptr_getW!=NULL){// If in the cube centered on the point.

			// Manages the barycenter
			this->tot_weight+=(*(this->ptr_getW))(*pU);//Add to tot_weight
			if (this->tot_weight!=(T)0){
				*this->pbarycenter+=p * (*(this->ptr_getW))(*pU)/tot_weight;//Add to the barycenter
			}else{
				*this->pbarycenter=*this->ppoint;
			}

			if (this->isEmpty() && this->isLeaf()){		// If empty and the cube has no Octs under (if it's a leaf)
				this->pU=pU;//We add in
				this->LEAVES.insert(this);// Marked as a leaf
			}else{										// Else it means it is an internal branch (or a leaf already full)
				if (this->isFull() && p==this->pU->getPosition()){// If pU and m_pU at the same location
					if (this->ffuse){
						*this->pU+=*pU;
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

				// We reinsert the object already present(can be null if it wasn't a leaf).
				if (this->pU!=NULL){
					this->tot_weight-=(*(this->ptr_getW))(*pU);//Subtract the w of the already present obj to tot_weight
					std::shared_ptr<U> pU2;//Init to null
					pU2.swap(pU);// Set this->pU to NULL and pU2 to this->pU
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
		T a=this->ha/(T)2;
		Point3D<T> np{(T)(-1)*a, (T)(-1)*a, (T)(1)*a};
		TLFTree=std::make_unique<Oct<U, T>>(this->ha, *this->ppoint+np);
		TLFTree->poct_parent=this;
	}
	TLFTree->insert(pU);
}

template<typename U, typename T> inline void Oct<U, T>::insertTRFTree(std::shared_ptr<U> pU) {//En private
	if (TRFTree==NULL){//If there is not yet a tree we create it
		T a=this->ha/(T)2;
		Point3D<T> np{(T)(1)*a, (T)(-1)*a, (T)(1)*a};
		TRFTree=std::make_unique<Oct<U, T>>(this->ha, *this->ppoint+np);
		TRFTree->poct_parent=this;
	}
	TRFTree->insert(pU);
}

template<typename U, typename T> inline void Oct<U, T>::insertBRFTree(std::shared_ptr<U> pU) {//En private
	if (BLBTree==NULL){//If there is not yet a tree we create it
		T a=this->ha/(T)2;
		Point3D<T> np{(T)(1)*a, (T)(-1)*a, (T)(-1)*a};
		BLBTree=std::make_unique<Oct<U, T>>(this->ha, *this->ppoint+np);
		BLBTree->poct_parent=this;
	}
	BLBTree->insert(pU);
}

template<typename U, typename T> inline void Oct<U, T>::insertBLFTree(std::shared_ptr<U> pU) {//En private
	if (BLFTree==NULL){//If there is not yet a tree we create it
		T a=this->ha/(T)2;
		Point3D<T> np{(T)(-1)*a, (T)(-1)*a, (T)(-1)*a};
		BLFTree=std::make_unique<Oct<U, T>>(this->ha, *this->ppoint+np);
		BLFTree->poct_parent=this;
	}
	BLFTree->insert(pU);
}

template<typename U, typename T> inline void Oct<U, T>::insertTLBTree(std::shared_ptr<U> pU) {//En private
	if (TLBTree==NULL){//If there is not yet a tree we create it
		T a=this->ha/(T)2;
		Point3D<T> np{(T)(-1)*a, (T)(1)*a, (T)(1)*a};
		TLBTree=std::make_unique<Oct<U, T>>(this->ha, *this->ppoint+np);
		TLBTree->poct_parent=this;
	}
	TLBTree->insert(pU);
}

template<typename U, typename T> inline void Oct<U, T>::insertTRBTree(std::shared_ptr<U> pU) {//En private
	if (TRBTree==NULL){//If there is not yet a tree we create it
		T a=this->ha/(T)2;
		Point3D<T> np{(T)(1)*a, (T)(1)*a, (T)(1)*a};
		TRBTree=std::make_unique<Oct<U, T>>(this->ha, *this->ppoint+np);
		TRBTree->poct_parent=this;
	}
	TRBTree->insert(pU);
}

template<typename U, typename T> inline void Oct<U, T>::insertBRBTree(std::shared_ptr<U> pU) {//En private
	if (BRBTree==NULL){//If there is not yet a tree we create it
		T a=this->ha/(T)2;
		Point3D<T> np{(T)(1)*a, (T)(1)*a, (T)(-1)*a};
		BRBTree=std::make_unique<Oct<U, T>>(this->ha, *this->ppoint+np);
		BRBTree->poct_parent=this;
	}
	BRBTree->insert(pU);
}

template<typename U, typename T> inline void Oct<U, T>::insertBLBTree(std::shared_ptr<U> pU) {//En private
	if (BLBTree==NULL){//If there is not yet a tree we create it
		T a=this->ha/(T)2;
		Point3D<T> np{(T)(-1)*a, (T)(1)*a, (T)(-1)*a};
		BLBTree=std::make_unique<Oct<U, T>>(this->ha, *this->ppoint+np);
		BLBTree->poct_parent=this;
	}
	BLBTree->insert(pU);
}

/**
 * Removes the given object and reconstructs the tree.
 * Returns true if the element was present, false if not.
 * \\Critical
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
 * Recalculate the tree.
 * Gives up objects that are outside of range, that are no longer in bounds of the tree.
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
 * @brief
 * Empty the octree from all elements and subtrees.
 * \\Crucial
 */
template<typename U, typename T> inline void Oct<U, T>::empty() {
	// Gets the leaves under.
	std::unordered_set<Oct<U, T>*> under_leaves=this->getPUnderLeaves();
	// Suppress the leaves under from the leaves list.
	for (Oct<U, T>* poct : under_leaves){
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

	*this->pbarycenter=*this->ppoint;
	this->tot_weight=(T)0;
	this->pU=NULL;
}

/**
 * @brief
 * Test is the Oct is full.
 * @return
 * Returns true if contains an object.
 * False otherwise.
 */
template<typename U, typename T> inline bool Oct<U, T>::isFull() const {
	return !this->isEmpty();
}

/**
 * @brief
 * Test is the Oct is empty.
 * @return
 * Returns true if doesn't contain an object.
 * False otherwise.
 */
template<typename U, typename T> inline bool Oct<U, T>::isEmpty() const {
	if (this->pU==NULL){
		return true;
	}
	return false;
}

/**
 * @brief
 * Test is the Oct is a leaf.
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
 * @brief
 * Tests if the Oct is a root.
 * @return
 * Returns true if it has no upper tree.
 * False otherwise.
 */
template<typename U, typename T> inline bool Oct<U, T>::isRoot() const {
	if (this->poct_parent==NULL){
		return true;
	}
	return false;
}




#endif /* OCT_HPP_ */
