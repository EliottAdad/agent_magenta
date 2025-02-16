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
//#include "../utilities/Printable.hpp"
#include "../utilities/functions.hpp"


#define TLFTree m_ptrees[0] 	// Top Left Front corner : is NULL if nothing
#define TRFTree m_ptrees[1]		// Top Right Front corner : is NULL if nothing
#define BRFTree m_ptrees[2]		// Bottom Right Front corner : is NULL if nothing
#define BLFTree m_ptrees[3]		// Bottom Left Front corner : is NULL if nothing
#define TLBTree m_ptrees[4]		// Top Left Back corner : is NULL if nothing
#define TRBTree m_ptrees[5]		// Top Right Back corner : is NULL if nothing
#define BRBTree m_ptrees[6]		// Bottom Right Back corner : is NULL if nothing
#define BLBTree m_ptrees[7]		// Bottom Left Back corner : is NULL if nothing


/*
 * #############
 *  Oct<U, T> :)
 * #############
 * U is the class for the objects stored.
 * T is the unit used for distance.
 * Can contain any object that has x, y, z, w, getW()
 */
template<typename U, typename T> class Oct {
protected:
	std::shared_ptr<Point3D<T>> m_ppoint;					// The center of the zone.
	std::shared_ptr<Point3D<T>> m_pbarycenter;				// The center of mass given the repartition of the WeightedPoints in the zone.

	T m_ha;												// Half of the length of the zone's border (better to make calculations).
	T m_tot_weight;										// Total weight contained in this Oct.

	std::shared_ptr<U> m_pU;					// The content of this square (NULL if nothing).

	std::unique_ptr<Oct<U, T>> m_ptrees[8];					// Contains the trees.

	static unsigned int m_NB_OCTS;				// Keeps track of the number of Octs created.

	void insertTLFTree(std::shared_ptr<U> pU);//:)
	void insertTRFTree(std::shared_ptr<U> pU);//:)
	void insertBRFTree(std::shared_ptr<U> pU);//:)
	void insertBLFTree(std::shared_ptr<U> pU);//:)
	void insertTLBTree(std::shared_ptr<U> pU);//:)
	void insertTRBTree(std::shared_ptr<U> pU);//:)
	void insertBRBTree(std::shared_ptr<U> pU);//:)
	void insertBLBTree(std::shared_ptr<U> pU);//:)

public:
	static T m_LIM_HA;							// This indicates the limit at which we stop subdividing (useless)
	static float m_ALPHA;						// The threshold m_ALPHA=a/d (with a being the width of the zone and d the distance from the center of the quad) indicates at which point we can consider an agglomeration of bodies as one.
												// Plus alpha est petit plus on est precis

	Oct();
	Oct(const T& a, const Point3D<T>& p={(T)0,(T)0,(T)0});
	virtual ~Oct();
	Oct(const Oct<U, T>& oct);

	Point3D<T> getPoint() const;
	void setPoint(const Point3D<T>& point);
	Point3D<T> getBarycenter() const;
	T getA() const;
	std::unordered_set<std::shared_ptr<U>> setA(const T& a);
	unsigned int getNB_OCTS() const;
	//std::unordered_set<Oct<U, T>*> getPTrees();						//Returns all the trees under, contained by this tree.
	std::unordered_set<std::shared_ptr<U>> getPElements(const bool& mem=false) const;					//:) Returns all the elements contained in the tree.
	std::unordered_set<std::shared_ptr<U>> getPNeighbors(const std::shared_ptr<U> pelement, const bool& mem=false) const;		//:) Returns all the neighbors.

	std::shared_ptr<U> insert(std::shared_ptr<U> pU);//:)
	bool remove(std::shared_ptr<U> pU);//:)
	//void find(const T& t, std::unordered_set<Oct<U, T>*>& pocts);// It adds to the list of Octs in parameter accordingly to the ratio m_ALPHA
	//std::unordered_set<T*> find(const Point3D& point);
	std::shared_ptr<U> search(const std::shared_ptr<Point3D<T>> ppoint) const;
	std::unordered_set<std::shared_ptr<U>> recalculate();
	void empty();

	bool isFull() const;
	bool isEmpty() const;
	bool isLeaf() const;
};
template<typename U, typename T> unsigned int Oct<U, T>::m_NB_OCTS=0;
template<typename U, typename T> T Oct<U, T>::m_LIM_HA=(T)0.5;
template<typename U, typename T> float Oct<U, T>::m_ALPHA=0.5;




/*
 * Constructor0
 */
template<typename U, typename T> inline Oct<U, T>::Oct() {
	m_ppoint=std::make_shared<Point3D<T>>();
	m_pbarycenter=std::make_shared<Point3D<T>>(*m_ppoint);
	//printf("\nHein1 ? (Oct)\n");
	//m_pbarycenter->print();

	m_ha=(T)50;
	m_tot_weight=(T)0;

	m_pU=NULL;

	for (int i(0) ; i<8 ; i++) {
		m_ptrees[i]=NULL;
	}

	m_NB_OCTS++;
}


/**
 * Constructor1
 * @param a{The side's lenght of the area}
 * @param point{The center on which is centered the Oct's area}
 */
template<typename U, typename T> inline Oct<U, T>::Oct(const T& a, const Point3D<T>& p) {
	m_ppoint=std::make_shared<Point3D<T>>(p);
	m_pbarycenter=std::make_shared<Point3D<T>>(*m_ppoint);

	m_ha=a/(T)2;
	m_tot_weight=(T)0.;

	m_pU=NULL;

	for (int i(0) ; i<8 ; i++){
		m_ptrees[i]=NULL;
	}

	m_NB_OCTS++;
}

/**
 * Constructor1
 * @param a{The side's lenght of the area}
 * @param point{The center on which is centered the Oct's area}
 */
/*template<typename U, typename T> Oct<U, T>::Oct(const U& a, std::shared_ptr<Point3D<T>> ppoint) {
	m_ppoint=ppoint;
	m_pbarycenter=std::make_shared<Point3D<T>>(*m_ppoint);
	//m_delp=true;

	m_a=a;
	m_tot_weight=0.;

	m_pT=NULL;

	m_pTLFTree=NULL;
	m_pTRFTree=NULL;
	m_pBLFTree=NULL;
	m_pBRFTree=NULL;
	m_pTLBTree=NULL;
	m_pTRBTree=NULL;
	m_pBLBTree=NULL;
	m_pBRBTree=NULL;

	m_NB_OCTS++;
}*/

/*
 * Constructor2
 */
/*template<typename U, typename T> Oct<U, T>::Oct(const U& a, Point3D<T>* ppoint) {
	m_ppoint=ppoint;
	m_pbarycenter=new Point3D<T>(*m_ppoint);
	m_delp=false;

	m_a=a;
	m_tot_weight=0.;

	m_pT=NULL;

	m_pTLFTree=NULL;
	m_pTRFTree=NULL;
	m_pBLFTree=NULL;
	m_pBRFTree=NULL;
	m_pTLBTree=NULL;
	m_pTRBTree=NULL;
	m_pBLBTree=NULL;
	m_pBRBTree=NULL;

	m_NB_OCTS++;
}*/

template<typename U, typename T> inline Oct<U, T>::~Oct() {
	for (int i(0) ; i<8 ; i++){
		if (m_ptrees[i]!=NULL){
			m_ptrees[i]=NULL;
		}
	}
	// There is one less Oct
	m_NB_OCTS--;
}

/*
 * Copy constructor
 */
template<typename U, typename T> inline Oct<U, T>::Oct(const Oct<U, T>& oct) {
	m_ppoint=std::make_shared<Point3D<T>>(oct.getPoint());
	m_pbarycenter=std::make_shared<Point3D<T>>(*m_ppoint);

	m_ha=oct.getA()/(T)2;
	m_tot_weight=(T)0.;

	m_pU=NULL;

	for (int i(0) ; i<8 ; i++){
		m_ptrees[i]=NULL;
	}
	// There is one more Oct
	m_NB_OCTS++;
}




template<typename U, typename T> inline Point3D<T> Oct<U, T>::getPoint() const {// Because it can be NULL
	return *m_ppoint;
}

template<typename U, typename T> inline void Oct<U, T>::setPoint(const Point3D<T>& point) {
	if (m_ppoint!=NULL){
		*m_ppoint=point;
	}else{
		m_ppoint=std::make_shared<Point3D<T>>(point);
		// Et le barycentre ?
	}
	this->recalculate();
}

template<typename U, typename T> inline Point3D<T> Oct<U, T>::getBarycenter() const {
	return *m_pbarycenter;
}

template<typename U, typename T> inline T Oct<U, T>::getA() const {
	return m_ha*(T)2;
}

template<typename U, typename T> inline std::unordered_set<std::shared_ptr<U>> Oct<U, T>::setA(const T& a){
	m_ha=a/(T)2;
	return this->recalculate();
}

template<typename U, typename T> inline unsigned int Oct<U, T>::getNB_OCTS() const {
	return m_NB_OCTS;
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
		for (int i(0) ; i<8 ; i++){
			if (m_ptrees[i]!=NULL){
				m_ptrees[i]->getPElements(true);
			}
		}
	}

	return elmts;
}

/**
 * h
 */
template<typename U, typename T> inline std::unordered_set<std::shared_ptr<U>> Oct<U, T>::getPNeighbors(const std::shared_ptr<U> pelement, const bool& mem) const {//////LOOOOK HERE !
	static std::unordered_set<std::shared_ptr<U>> pneighbors;

	if (mem==false){
		pneighbors.clear();
	}

	if (pelement!=NULL){
		if (m_pU==NULL && (T)(m_ALPHA)/**abs(m_tot_weight)*/<=m_ha*(T)2/getDistance(*m_pbarycenter/**m_ppoint*/, *pelement)){//U{1., 0}/getDistance(*m_ppoint, *pelement)<=U{m_ALPHA, 0}
			for (int i(0) ; i<8 ; i++){
				if (m_ptrees[i]!=NULL){
					m_ptrees[i]->getPNeighbors(pelement, true);
					//printf("God4\n");
				}
			}
		}else{
			if (m_pU!=NULL){// If the cube is not empty
				if (m_pU!=pelement){
					pneighbors.insert(m_pU);
				}
			}else{			// Else if the place is empty
				std::shared_ptr<U> new_pU(new U(m_pbarycenter->x, m_pbarycenter->y, m_pbarycenter->z, m_tot_weight));
				pneighbors.insert(new_pU);
			}
		}
	}

	return pneighbors;
}

/**
 * returns
 * NULL if it was inserted successfully or if entered NULL pointer
 *  or the pointer that was passed in argument if it was enable.
 */
template<typename U, typename T> inline std::shared_ptr<U> Oct<U, T>::insert(std::shared_ptr<U> pU) {
	if (pU!=NULL){
		Point3D<T> p={pU->x, pU->y, pU->z};
		Point3D<T> dp=p-*m_ppoint;
		//dp.print(true, true, 0);

		if (abs(dp.x)<=m_ha && abs(dp.y)<=m_ha && abs(dp.z)<=m_ha){// If in the cube centered on the point.
			// Manages the barycenter
			m_tot_weight+=pU->getW();//Add to tot_weight
			if (m_tot_weight!=(T)0){
				*m_pbarycenter+=p*(pU->getW()/m_tot_weight);//Add to the barycenter
			}else{
				*m_pbarycenter=*m_ppoint;
			}

			if (this->isEmpty() && this->isLeaf()){		// If empty and the cube has no Octs under (if it's a leaf)
				m_pU=pU;//We add in
			}else{																				// Else it means it is an internal branch
				if (dp.x<=(T)0 && dp.y<=(T)0 && dp.z>=(T)0){//If cube 1
					insertTLFTree(pU);
				}else if (dp.x>=(T)0 && dp.y<=(T)0 && dp.z>=(T)0){//If cube 2
					insertTRFTree(pU);
				}else if (dp.x>=(T)0 && dp.y<=(T)0 && dp.z<=(T)0){//If cube 3
					insertBRFTree(pU);
				}else if (dp.x<=(T)0 && dp.y<=(T)0 && dp.z<=(T)0){//If cube 4
					insertBLFTree(pU);
				}else if (dp.x<=(T)0 && dp.y>=(T)0 && dp.z>=(T)0){//If cube 5
					insertTLBTree(pU);
				}else if (dp.x>=(T)0 && dp.y>=(T)0 && dp.z>=(T)0){//If cube 6
					insertTRBTree(pU);
				}else if (dp.x>=(T)0 && dp.y>=(T)0 && dp.z<=(T)0){//If cube 7
					insertBRBTree(pU);
				}else if (dp.x<=(T)0 && dp.y>=(T)0 && dp.z<=(T)0){//If cube 8
					insertBLBTree(pU);
				}

				// We reinsert the object already present(can be null if it wasn't a leaf).
				if (m_pU!=NULL){
					m_tot_weight-=m_pU->getW();//Subtract the w of the already present obj to tot_weight
					std::shared_ptr<U> pU2;//Init to null
					pU2.swap(m_pU);// Set m_pU to NULL and pU2 to m_pU
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
		T a=m_ha/(T)2;
		Point3D<T> np{(T)(-1)*a, (T)(-1)*a, (T)(1)*a};
		TLFTree=std::make_shared<Oct<U, T>>(m_ha, *m_ppoint+np);
	}
	TLFTree->insert(pU);
}

template<typename U, typename T> inline void Oct<U, T>::insertTRFTree(std::shared_ptr<U> pU) {//En private
	if (TRFTree==NULL){//If there is not yet a tree we create it
		T a=m_ha/(T)2;
		Point3D<T> np{(T)(1)*a, (T)(-1)*a, (T)(1)*a};
		TRFTree=std::make_shared<Oct<U, T>>(m_ha, *m_ppoint+np);
	}
	TRFTree->insert(pU);
}

template<typename U, typename T> inline void Oct<U, T>::insertBRFTree(std::shared_ptr<U> pU) {//En private
	if (BLBTree==NULL){//If there is not yet a tree we create it
		T a=m_ha/(T)2;
		Point3D<T> np{(T)(1)*a, (T)(-1)*a, (T)(-1)*a};
		BLBTree=std::make_shared<Oct<U, T>>(m_ha, *m_ppoint+np);
	}
	BLBTree->insert(pU);
}

template<typename U, typename T> inline void Oct<U, T>::insertBLFTree(std::shared_ptr<U> pU) {//En private
	if (BLFTree==NULL){//If there is not yet a tree we create it
		T a=m_ha/(T)2;
		Point3D<T> np{(T)(-1)*a, (T)(-1)*a, (T)(-1)*a};
		BLFTree=std::make_shared<Oct<U, T>>(m_ha, *m_ppoint+np);
	}
	BLFTree->insert(pU);
}

template<typename U, typename T> inline void Oct<U, T>::insertTLBTree(std::shared_ptr<U> pU) {//En private
	if (TLBTree==NULL){//If there is not yet a tree we create it
		T a=m_ha/(T)2;
		Point3D<T> np{(T)(-1)*a, (T)(1)*a, (T)(1)*a};
		TLBTree=std::make_shared<Oct<U, T>>(m_ha, *m_ppoint+np);
	}
	TLBTree->insert(pU);
}

template<typename U, typename T> inline void Oct<U, T>::insertTRBTree(std::shared_ptr<U> pU) {//En private
	if (TRBTree==NULL){//If there is not yet a tree we create it
		T a=m_ha/(T)2;
		Point3D<T> np{(T)(1)*a, (T)(1)*a, (T)(1)*a};
		TRBTree=std::make_shared<Oct<U, T>>(m_ha, *m_ppoint+np);
	}
	TRBTree->insert(pU);
}

template<typename U, typename T> inline void Oct<U, T>::insertBRBTree(std::shared_ptr<U> pU) {//En private
	if (BRBTree==NULL){//If there is not yet a tree we create it
		T a=m_ha/(T)2;
		Point3D<T> np{(T)(1)*a, (T)(1)*a, (T)(-1)*a};
		BRBTree=std::make_shared<Oct<U, T>>(m_ha, *m_ppoint+np);
	}
	BRBTree->insert(pU);
}

template<typename U, typename T> inline void Oct<U, T>::insertBLBTree(std::shared_ptr<U> pU) {//En private
	if (BLBTree==NULL){//If there is not yet a tree we create it
		T a=m_ha/(T)2;
		Point3D<T> np{(T)(-1)*a, (T)(1)*a, (T)(-1)*a};
		BLBTree=std::make_shared<Oct<U, T>>(m_ha, *m_ppoint+np);
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
	// No more under Octs
	for (int i(0) ; i<8 ; i++){
		if (m_ptrees[i]!=NULL){
			m_ptrees[i]=NULL;
		}
	}

	*m_pbarycenter=*m_ppoint;
	m_tot_weight=(T)0;
	m_pU=NULL;
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

	if (m_pU==NULL){
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

	for (int i(0) ; i<8 ; i++){
		if (m_ptrees[i]!=NULL){
			test=false;
			break;
		}
	}

	return test;
}

/*template<typename U, typename T> std::shared_ptr<T> Oct<U, T>::search(const std::shared_ptr<Point3D<T>> ppoint) const {
	std::shared_ptr<T> pT=NULL;

	if (ppoint!=NULL){
		T delta_x=(T)(ppoint->x-this->m_ppoint->x);
		T delta_y=(T)(ppoint->y-this->m_ppoint->y);
		T delta_z=(T)(ppoint->z-this->m_ppoint->z);

		if (abs(delta_x)<m_a/2 && abs(delta_y)<m_a/2 && abs(delta_z)<m_a/2){//If in the square centered on the point.

			if (m_pT!=NULL){// This means it is a square of the smallest size possible.
				pT=m_pT;
			}else{
				if (TLFTree!=NULL){//Cube 1
					pT=TLFTree->search(ppoint);
				}
				if (pT==NULL){//If it hasn't been initiated by the precedent line
					if (TRFTree!=NULL){//Cube 2
						pT=TRFTree->search(ppoint);
					}
					if (pT==NULL){//If it hasn't been initiated by the precedent line
						if (BLFTree!=NULL){//Cube 3
							pT=BLFTree->search(ppoint);
						}
						if (pT==NULL){//If it hasn't been initiated by the precedent line
							if (BRFTree!=NULL){//Cube 4
								pT=BRFTree->search(ppoint);
							}
							if (pT==NULL){//If it hasn't been initiated by the precedent line
								if (TLBTree!=NULL){//Cube 5
									pT=TLBTree->search(ppoint);
								}
								if (pT==NULL){//If it hasn't been initiated by the precedent line
									if (TRBTree!=NULL){//Cube 6
										pT=TRBTree->search(ppoint);
									}
									if (pT==NULL){//If it hasn't been initiated by the precedent line
										if (BLBTree!=NULL){//Cube 7
											pT=BLBTree->search(ppoint);
										}
										if (pT==NULL){//If it hasn't been initiated by the precedent line
											if (BRBTree!=NULL){//Cube 8
												pT=BRBTree->search(ppoint);
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
	return pT;
}*/



#endif /* OCT_HPP_ */
