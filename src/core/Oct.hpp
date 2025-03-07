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


#define TLFTree m_ptrees[0] 	// Top Left Front corner : is NULL if nothing
#define TRFTree m_ptrees[1]	// Top Right Front corner : is NULL if nothing
#define BRFTree m_ptrees[2]	// Bottom Right Front corner : is NULL if nothing
#define BLFTree m_ptrees[3]	// Bottom Left Front corner : is NULL if nothing
#define TLBTree m_ptrees[4]	// Top Left Back corner : is NULL if nothing
#define TRBTree m_ptrees[5]	// Top Right Back corner : is NULL if nothing
#define BRBTree m_ptrees[6]	// Bottom Right Back corner : is NULL if nothing
#define BLBTree m_ptrees[7]	// Bottom Left Back corner : is NULL if nothing


/**
 * #############
 *  Oct<U, T> :)
 * #############
 * @brief
 * U is the class for the objects stored.
 * T is the unit used for distance.
 * Can contain any object that has methods .getPosition, (pU->*ptr_getW)(), +=, constructor from ((T)x, (T)y, (T)z, (T)w)
 * We recommend using the methods provided to manipulate internal vars (methods marked as \\Crucial).
 * U needs a constructor from x, y, z and w (of unit T)
 * needs ->getPosition(), ptr_getW
 */
template<typename U, typename T> class Oct {
protected:
	// Internal variables
	T m_ha;											// Half of the length of the zone's border (better to make calculations).
	T m_tot_weight;									// Total weight contained in this Oct.
	std::shared_ptr<Point3D<T>> m_ppoint;				// The center of the zone (never NULL).
	std::unique_ptr<Point3D<T>> m_pbarycenter;		// The center of mass given the repartition of the WeightedPoints in the zone.

	// Content
	std::shared_ptr<U> m_pU;							// The content of this square (NULL if nothing).

	//Trees
	Oct<U, T>* m_poct_parent;							// Pointer to the parent oct;
	std::unique_ptr<Oct<U, T>> m_ptrees[8];			// Contains the trees under him.

	static std::unordered_set<Oct<U, T>*> m_LEAVES;			// Keeps track of the Octs that are leaves.
	static T (*m_PTR_GETW)(const U&);				// Pointer to the method to compute weights (called on U)
	static unsigned int m_NB_OCTS;					// Keeps track of the number of Octs created.
	static T m_LIM_A;								// This indicates the limit at which we stop subdividing (unused for now)

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
	typedef T (*PtrGetW)(const U&);					// Defines a function's pointer (used locally)
	
	float alpha;									// The threshold alpha=ha/d (with ha being half of the width of the zone and d the distance from the center of the quad) indicates at which point we can consider an agglomeration of bodies as one. The smaller alpha is, the more precise we are.
											
	bool ffuse;										// Leaves the choice between fusing the elements at insertion if they are at the same coords, or not inserting them.
	
	
	/*------------------------- x
	 * Constructors/Destructors
	 *------------------------- */
	Oct();
	Oct(const T& a, const Point3D<T>& p={(T)0,(T)0,(T)0}, Oct<U, T>* poct_parent=NULL);
	virtual ~Oct();
	Oct(const Oct<U, T>& oct);

	/*---------------- x
	 * Getters/Setters
	 *---------------- */
	/**
	 * @brief
	 * Returns the side lenght of the Oct
	 */
	T getA() const {return this->m_ha*(T)2;}
	/**
	 * @brief
	 * Sets the side lenght of the Oct
	 * \\Crucial
	 */
	std::unordered_set<std::shared_ptr<U>> setA(const T& a){this->m_ha=a/(T)2;	return this->recalculate();}
	/**
	 * @brief
	 * Returns the total weight stored in this Oct
	 */
	T getTotWeight() const {return this->m_tot_weight;}
	/**
	 * @brief
	 * Returns the point
	 */
	Point3D<T> getPoint() const {return *this->m_ppoint;}
	/**
	 * Returns the pointer to the point
	 */
	std::shared_ptr<Point3D<T>> getPPoint() const {return this->m_ppoint;}
	/**
	 * @brief
	 * Sets the point
	 * \\Crucial
	 */
	void setPoint(const Point3D<T>& point){*this->m_ppoint=point;	*this->m_pbarycenter=*this->m_ppoint;	this->recalculate();}	// Et le barycentre ?=>Verif
	/**
	 * @brief
	 * Returns the barycenter
	 */
	Point3D<T> getBarycenter() const {return *this->m_pbarycenter;}

	/**
	 * @brief
	 * Returns the element stored in this Oct
	 */
	std::shared_ptr<U> getPU() const {return this->m_pU;};

	/**
	 * @brief
	 * Returns the pointer to the parent Oct
	 */
	std::shared_ptr<U> getPOctParent() const {return this->m_poct_parent;}
	std::unordered_set<Oct<U, T>*> getPChildren() const;			//Returns all the trees directly under, contained by this tree.
	
	/**
	 * @brief
	 * Returns all the leaves
	 */
	static std::unordered_set<Oct<U, T>*> getLeaves() {return m_LEAVES;}
	/**
	 * @brief
	 * Returns the pointer to the function getting the weight of U
	 */
	static PtrGetW getPtrGetW() {return m_PTR_GETW;}
	/**
	 * @brief
	 * Sets the pointer and recalculate the oct.
	 * \\Critical
	 */
	std::unordered_set<std::shared_ptr<U>> setPtrGetW(PtrGetW ptr_getW) {m_PTR_GETW=ptr_getW;	return this->recalculate();}
	
	/**
	 * @brief
	 * Returns the number of Octs there is.
	 */
	static unsigned int getNB_OCTS() {return m_NB_OCTS;}
	//static unsigned int getLIM_A() {return m_NB_OCTS;}
	


	/*-------- x
	 * Methods
	 *-------- */
	std::unordered_set<Oct<U, T>*> getPBrothers();				//Returns all the trees directly under, contained by this tree.
	std::unordered_set<Oct<U, T>*> getPUnderLeaves(const bool& mem=false);					//Returns all the trees that are leaves directly under, contained by this tree.
	std::unordered_set<std::shared_ptr<U>> getPElements(const bool& mem=false) const;		//:) Returns all the elements contained in the tree.
	std::unordered_set<std::shared_ptr<U>> getPUnderElements(const bool& mem=false) const;	//:) Returns all the elements contained in the tree.
	std::unordered_set<std::shared_ptr<U>> getPNeighbors(const std::shared_ptr<U> pelement, const bool& mem=false) const;		//:) Returns all the neighbors.
	std::unordered_set<Oct<U, T>*> getPNeighbouringOcts(const bool& mem=false) const;		//:) Returns all the neighbouring octs.

	std::shared_ptr<U> insert(std::shared_ptr<U> pU);//:X Doesn't work.
	bool remove(std::shared_ptr<U> pU);//:)
	std::unordered_set<std::shared_ptr<U>> recalculate();
	void empty();

	/*------ x
	 * Tests
	 *------ */
	bool isFull() const;
	bool isEmpty() const;
	bool isWithoutChildren() const;
	bool isRoot() const;
};
template<typename U, typename T> std::unordered_set<Oct<U, T>*> Oct<U, T>::m_LEAVES={};
template<typename U, typename T> Oct<U, T>::PtrGetW Oct<U, T>::m_PTR_GETW=NULL;
template<typename U, typename T> unsigned int Oct<U, T>::m_NB_OCTS=0;
template<typename U, typename T> T Oct<U, T>::m_LIM_A=0.5;

//########################################################################################################################

/*
 * Constructor0
 */
template<typename U, typename T> inline Oct<U, T>::Oct() {
	// Internal variables
	this->m_ha=(T)50;		//100x100m sided box
	this->m_tot_weight=(T)0;
	this->m_ppoint=std::make_shared<Point3D<T>>();
	this->m_pbarycenter=std::make_unique<Point3D<T>>();

	this->m_pU=NULL;

	this->m_poct_parent=NULL;
	for (unsigned char i(0) ; i<8 ; i++) {
		this->m_ptrees[i]=NULL;
	}

	this->m_NB_OCTS++;

	// External variables
	this->alpha=0.5;
	this->ffuse=false;
}

/**
 * Constructor1
 * @param \a{The side's lenght of the area}
 * @param \p{The center on which is centered the Oct's area}
 */
template<typename U, typename T> inline Oct<U, T>::Oct(const T& a, const Point3D<T>& p, Oct<U, T>* poct_parent) {
	// Internal variables
	this->m_ha=a/(T)2;
	this->m_tot_weight=(T)0;
	this->m_ppoint=std::make_shared<Point3D<T>>(p);
	this->m_pbarycenter=std::make_unique<Point3D<T>>(p);

	this->m_pU=NULL;

	this->m_poct_parent=poct_parent;
	for (unsigned char i(0) ; i<8 ; i++) {
		this->m_ptrees[i]=NULL;
	}

	this->m_NB_OCTS++;
	
	// External variables
	this->alpha=0.5;
	this->ffuse=false;
}

/**
 * Destructor
 */
template<typename U, typename T> inline Oct<U, T>::~Oct() {
	this->m_poct_parent=NULL;
	
	this->empty();

	// There is one less Oct
	this->m_NB_OCTS--;
}

/**
 * Copy constructor
 */
template<typename U, typename T> inline Oct<U, T>::Oct(const Oct<U, T>& oct) {
	// Internal variables
	this->m_ha=oct.getA()/(T)2;
	this->m_tot_weight=(T)0;
	this->m_ppoint=oct.getPPoint();
	this->m_pbarycenter=std::make_unique<Point3D<T>>(oct.getPoint());

	this->m_pU=NULL;

	this->m_poct_parent=NULL;
	for (unsigned char i(0) ; i<8 ; i++) {
		this->m_ptrees[i]=NULL;
	}
	
	this->m_NB_OCTS++;

	// External variables
	this->alpha=oct.alpha;
	this->ffuse=oct.ffuse;
	
	// Reinsert the elements.
	this->insert(oct.getPUnderElements());
}









/**
 * @brief
 * Get octs a step under.
 */
template<typename U, typename T> inline std::unordered_set<Oct<U, T>*> Oct<U, T>::getPChildren() const {
	std::unordered_set<Oct<U, T>*> pchildren;
	
	for (unsigned char i(0) ; i<8 ; i++){
		if (this->m_ptrees[i]!=NULL){
			pchildren.insert(this->m_ptrees[i].get());
		}
	}
	
	return pchildren;
}

/**
 * @brief
 * Get its brothers (other Octs at the same level, itself excluded)
 */
template<typename U, typename T> inline std::unordered_set<Oct<U, T>*> Oct<U, T>::getPBrothers() {
	std::unordered_set<Oct<U, T>*> pbrothers;
	
	if (this->m_poct_parent!=NULL){
		pbrothers=this->m_poct_parent->getPChildren();
	}
	pbrothers.erase(this);
	
	return pbrothers;
}
	
/**
 * @brief
 * Returns all the trees that are leaves directly under (including this tree), contained by this tree.
 * mem: flag memorise (recursive call)
 */
template<typename U, typename T> inline std::unordered_set<Oct<U, T>*> Oct<U, T>::getPUnderLeaves(const bool& mem) {
	static std::unordered_set<Oct<U, T>*> pleaves;

	if (mem==false){
		pleaves.clear();
	}

	if (this->isWithoutChildren()){// If leaf, adds itself
		pleaves.insert(this);
	}

	for (Oct<U, T>* pchild : this->getPChildren()){
			pchild->getPUnderLeaves(true);
	}

	return pleaves;
}

/**
 * @brief
 * Returns all the elements that are stored in the Octs.
 * \mem: flag memorise (recursive call), false by default
 */
template<typename U, typename T> inline std::unordered_set<std::shared_ptr<U>> Oct<U, T>::getPElements(const bool& mem) const {
	static std::unordered_set<std::shared_ptr<U>> elmts;

	if (mem==false){
		elmts.clear();
	}
	
	for (Oct<U, T>* pleaf : this->m_LEAVES){
		elmts.insert(pleaf->getPU());
	}

	return elmts;
}

/**
 * @brief
 * Returns all the elements that are stored under this Oct and all under Octs.
 * \mem: flag memorise (recursive call), false by default
 */
template<typename U, typename T> inline std::unordered_set<std::shared_ptr<U>> Oct<U, T>::getPUnderElements(const bool& mem) const {
	static std::unordered_set<std::shared_ptr<U>> elmts;

	if (mem==false){
		elmts.clear();
	}

	if (m_pU!=NULL){
		elmts.insert(m_pU);
	}else{
		for (unsigned char i(0) ; i<8 ; i++){
			if (this->m_ptrees[i]!=NULL){
				this->m_ptrees[i]->getPUnderElements(true);
			}
		}
	}

	return elmts;
}

/**
 * @brief
 * Gets the neighbouring elements based on U's position and the limit alpha given.
 * Create them from the weight and position of the Oct if the considered Oct is far enough.
 * To be used, U needs a constructor from x, y, z and w (of unit T)
 */
template<typename U, typename T> inline std::unordered_set<std::shared_ptr<U>> Oct<U, T>::getPNeighbors(const std::shared_ptr<U> pelement, const bool& mem) const {
	static std::unordered_set<std::shared_ptr<U>> pneighbors;

	if (mem==false){
		pneighbors.clear();
	}

	if (pelement!=NULL){
		if (this->m_pU==NULL && (T)(this->alpha)<=m_ha/getDistance(*this->m_pbarycenter, pelement->getPosition())){//U{1., 0}/getDistance(*m_ppoint, *pelement)<=U{m_ALPHA, 0}
			static std::unordered_set<Oct<U, T>*> pchildren;
			for (Oct<U, T>* pchild : pchildren){
				pchild->getPNeighbors(pelement, true);
			}
		}else{
			if (this->m_pU!=NULL){// If the cube is not empty
				if (this->m_pU!=pelement){
					pneighbors.insert(this->m_pU);
				}
			}else{			// Else if the place is empty
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
 * @brief
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
 * @brief
 * Inserts a new element in the structure.
 * Returns :
 * NULL if it was inserted successfully or if NULL is entered pointer,
 *  or the pointer that was passed in argument if it was enable.
 * needs ->getPosition(), ptr_getW
 * \\Critical
 */
template<typename U, typename T> inline std::shared_ptr<U> Oct<U, T>::insert(std::shared_ptr<U> pU) {
	// If the object to insert is not NULL
	if (pU!=NULL){
		Point3D<T> p=pU->getPosition();
		Point3D<T> dp=p-*this->m_ppoint;

		/*if (m_PTR_GETW==NULL){
			//printf("\nm_PTR_GETW is NULL\n");
		}
		if (abs(dp.x)<=this->m_ha){
			//printf("\nabs(dp.x)<=this->ha\n");
		}else{
			//printf("\nabs(dp.x)>this->ha\n");
		}*/
		if (abs(dp.x)<=this->m_ha &&
				abs(dp.y)<=this->m_ha &&
				abs(dp.z)<=this->m_ha &&
				m_PTR_GETW!=NULL){// If in the cube centered on the Oct's position.

			// Manages the barycenter
			this->m_tot_weight+=(*(m_PTR_GETW))(*pU);//Add to tot_weight
			if (this->m_tot_weight!=(T)0){
				*this->m_pbarycenter+=p * (*(m_PTR_GETW))(*pU)/m_tot_weight;//Add to the barycenter
			}else{
				*this->m_pbarycenter=*this->m_ppoint;
			}

			if (this->isEmpty() && this->isWithoutChildren()){		// If empty and the cube has no Octs under (if it's an empty leaf)
				this->m_pU=pU;//We add in
				this->m_LEAVES.insert(this);// Marked as a leaf
			}else if(this->isFull() && p==this->m_pU->getPosition()){// If pU and this->pU at the same location
				// Same location object management
				if (this->ffuse){
					printf("\nFusing particles\n");
					*this->m_pU+=*pU;
				}else{
					return pU;
				}
			}else{										// Else it means it is an internal branch (or a leaf already full)
				if (dp.x<=(T)0 && dp.y<=(T)0 && dp.z>=(T)0){	//If cube 1
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

				// We reinsert the object already present.
				if (this->m_pU!=NULL){
					this->m_tot_weight-=(*(m_PTR_GETW))(*this->m_pU);//Subtract the w of the already present obj to tot_weight but do not change anything for the barycenter because it is still present down the line.
					std::shared_ptr<U> pU2;//Pointer to U type data, init to null
					pU2.swap(this->m_pU);// Set this->m_pU to NULL and pU2 to this->m_pU
					this->insert(pU2);
				}
			}
		}else{
			//printf("\nFailed1\n");
			return pU;
		}
	}else{
		//printf("\nFailed2\n");
		return NULL;
	}
	return NULL;
}

template<typename U, typename T> inline void Oct<U, T>::insertTLFTree(std::shared_ptr<U> pU) {//In private
	if (TLFTree==NULL){//If there is not yet a tree we create it
		T a=this->m_ha/(T)2;
		Point3D<T> np{(T)(-1)*a, (T)(-1)*a, (T)(1)*a};
		TLFTree=std::make_unique<Oct<U, T>>(this->m_ha, *this->m_ppoint+np, this);
		// Suppress this oct from the leaves as it now has a child.
		m_LEAVES.erase(this);
	}
	TLFTree->insert(pU);
}

template<typename U, typename T> inline void Oct<U, T>::insertTRFTree(std::shared_ptr<U> pU) {//En private
	if (TRFTree==NULL){//If there is not yet a tree we create it
		T a=this->m_ha/(T)2;
		Point3D<T> np{(T)(1)*a, (T)(-1)*a, (T)(1)*a};
		TRFTree=std::make_unique<Oct<U, T>>(this->m_ha, *this->m_ppoint+np, this);
		// Suppress this oct from the leaves as it now has a child.
		m_LEAVES.erase(this);
	}
	TRFTree->insert(pU);
}

template<typename U, typename T> inline void Oct<U, T>::insertBRFTree(std::shared_ptr<U> pU) {//En private
	if (BLBTree==NULL){//If there is not yet a tree we create it
		T a=this->m_ha/(T)2;
		Point3D<T> np{(T)(1)*a, (T)(-1)*a, (T)(-1)*a};
		BLBTree=std::make_unique<Oct<U, T>>(this->m_ha, *this->m_ppoint+np, this);
		// Suppress this oct from the leaves as it now has a child.
		m_LEAVES.erase(this);
	}
	BLBTree->insert(pU);
}

template<typename U, typename T> inline void Oct<U, T>::insertBLFTree(std::shared_ptr<U> pU) {//En private
	if (BLFTree==NULL){//If there is not yet a tree we create it
		T a=this->m_ha/(T)2;
		Point3D<T> np{(T)(-1)*a, (T)(-1)*a, (T)(-1)*a};
		BLFTree=std::make_unique<Oct<U, T>>(this->m_ha, *this->m_ppoint+np, this);
		// Suppress this oct from the leaves as it now has a child.
		m_LEAVES.erase(this);
	}
	BLFTree->insert(pU);
}

template<typename U, typename T> inline void Oct<U, T>::insertTLBTree(std::shared_ptr<U> pU) {//En private
	if (TLBTree==NULL){//If there is not yet a tree we create it
		T a=this->m_ha/(T)2;
		Point3D<T> np{(T)(-1)*a, (T)(1)*a, (T)(1)*a};
		TLBTree=std::make_unique<Oct<U, T>>(this->m_ha, *this->m_ppoint+np, this);
		// Suppress this oct from the leaves as it now has a child.
		m_LEAVES.erase(this);
	}
	TLBTree->insert(pU);
}

template<typename U, typename T> inline void Oct<U, T>::insertTRBTree(std::shared_ptr<U> pU) {//En private
	if (TRBTree==NULL){//If there is not yet a tree we create it
		T a=this->m_ha/(T)2;
		Point3D<T> np{(T)(1)*a, (T)(1)*a, (T)(1)*a};
		TRBTree=std::make_unique<Oct<U, T>>(this->m_ha, *this->m_ppoint+np, this);
		// Suppress this oct from the leaves as it now has a child.
		m_LEAVES.erase(this);
	}
	TRBTree->insert(pU);
}

template<typename U, typename T> inline void Oct<U, T>::insertBRBTree(std::shared_ptr<U> pU) {//En private
	if (BRBTree==NULL){//If there is not yet a tree we create it
		T a=this->m_ha/(T)2;
		Point3D<T> np{(T)(1)*a, (T)(1)*a, (T)(-1)*a};
		BRBTree=std::make_unique<Oct<U, T>>(this->m_ha, *this->m_ppoint+np, this);
		// Suppress this oct from the leaves as it now has a child.
		m_LEAVES.erase(this);
	}
	BRBTree->insert(pU);
}

template<typename U, typename T> inline void Oct<U, T>::insertBLBTree(std::shared_ptr<U> pU) {//En private
	if (BLBTree==NULL){//If there is not yet a tree we create it
		T a=this->m_ha/(T)2;
		Point3D<T> np{(T)(-1)*a, (T)(1)*a, (T)(-1)*a};
		BLBTree=std::make_unique<Oct<U, T>>(this->m_ha, *this->m_ppoint+np, this);
		// Suppress this oct from the leaves as it now has a child.
		m_LEAVES.erase(this);
	}
	BLBTree->insert(pU);
}

/**
 * @brief
 * Removes the given object and reconstructs the tree.
 * Returns true if the element was present, false if not.
 * \\Critical
 */
template<typename U, typename T> inline bool Oct<U, T>::remove(std::shared_ptr<U> pU) {
	bool test=false;
	std::unordered_set<std::shared_ptr<U>> pelements=this->getPUnderElements();

	// Empty everything under
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
 * @brief
 * Recalculate the tree.
 * Gives up objects that are outside of range, that are no longer in bounds of the tree.
 */
template<typename U, typename T> inline std::unordered_set<std::shared_ptr<U>> Oct<U, T>::recalculate() {
	std::unordered_set<std::shared_ptr<U>> pelements=this->getPUnderElements();
	std::unordered_set<std::shared_ptr<U>> perrored_elements;

	// Empty everything under
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
		this->m_LEAVES.erase(poct);
	}

	// No more under Octs
	for (unsigned char i(0) ; i<8 ; i++){
		if (this->m_ptrees[i]!=NULL){
			this->m_ptrees[i]=NULL;
		}
	}

	*this->m_pbarycenter=*this->m_ppoint;
	this->m_tot_weight=(T)0;
	this->m_pU=NULL;
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
	if (this->m_pU==NULL){
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
template<typename U, typename T> inline bool Oct<U, T>::isWithoutChildren() const {
	bool test=true;

	for (unsigned char i(0) ; i<8 ; i++){
		if (this->m_ptrees[i]!=NULL){
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
	if (this->m_poct_parent==NULL){
		return true;
	}
	return false;
}




#endif /* OCT_HPP_ */
