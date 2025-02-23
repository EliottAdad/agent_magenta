/*
 * Quad.hpp
 *
 *  Created on: 18 mai 2024
 *      Author: esn
 */

#ifndef QUAD_HPP_

#define QUAD_HPP_

#include <memory>
#include <cstdio>
#include <unordered_set>

//#include "Particle3D.hpp"
#include "Point2D.hpp"


#define TLTree m_ptrees[0] 		// Top Left corner : is NULL if nothing
#define TRTree m_ptrees[1]		// Top Right corner : is NULL if nothing
#define BRTree m_ptrees[2]		// Bottom Right corner : is NULL if nothing
#define BLTree m_ptrees[3]		// Bottom Left corner : is NULL if nothing


/*
 * ##############
 *  Quad<U, T> :X
 * ##############
 * Todo: Copy from Oct
 * U is the class for the objects stored.
 * T is the unit used for distance.
 */
template<typename U, typename T> class Quad {
protected:
	std::shared_ptr<Point2D<T>> m_ppoint;		// The center of the zone.
	std::shared_ptr<Point3D<T>> m_pbarycenter;	// The center of mass given the repartition of the WeightedPoints in the zone.

	T m_ha;										// Half of the length of the zone's border.
	T m_tot_weight;								// Total weight contained in this Quad.

	std::shared_ptr<U> m_pU;					// The content of this square (NULL if nothing).

	Quad<U, T>* m_ptrees[4];					// Contains the trees.

	static unsigned int m_NB_QUADS;				// Keeps track of the number of Quad created.

	void insertTLTree(std::shared_ptr<U> pU);//:)
	void insertTRTree(std::shared_ptr<U> pU);//:)
	void insertBRTree(std::shared_ptr<U> pU);//:)
	void insertBLTree(std::shared_ptr<U> pU);//:)

public:
	static T m_LIM_HA;							// This indicates the limit at which we stop subdividing (useless)
	static float m_ALPHA;						// The threshold m_ALPHA=a/d (with a being the width of the zone and d the distance from the center of the quad) indicates at which point we can consider

	Quad();
	Quad(const T& a, const Point3D<T>& p={(T)0,(T)0,(T)0});
	virtual ~Quad();
	Quad(const Quad<U, T>& quad);

	Point3D<T> getPoint() const;
	void setPoint(const Point3D<T>& point);
	Point3D<T> getBarycenter() const;
	T getA() const;
	void setA(const T& a);
	unsigned int getNB_QUADS() const;
	//std::unordered_set<Quad<U, T>*> getPTrees();						//Returns all the trees under, contained by this tree.
	std::unordered_set<std::shared_ptr<U>> getPElements(const bool& mem=false) const;					//Returns all the elements contained in the tree.
	std::unordered_set<std::shared_ptr<U>> getPNeighbors(const std::shared_ptr<U> pelement, const bool& mem=false) const;		//Returns all the neighbors.

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
template<typename U, typename T> unsigned int Quad<U, T>::m_NB_QUADS=0;
template<typename U, typename T> T Quad<U, T>::m_LIM_HA=(T)0.5;
template<typename U, typename T> float Quad<U, T>::m_ALPHA=0.5;


/*
 * Constructor0
 */
template<typename U, typename T> inline Quad<U, T>::Quad() {
	m_ppoint=std::make_shared<Point3D<T>>();
	m_pbarycenter=std::make_shared<Point3D<T>>(*m_ppoint);
	//printf("\nHein1 ? (Oct)\n");
	//m_pbarycenter->print();

	m_ha=(T)50;
	m_tot_weight=(T)0;

	m_pU=NULL;

	for (int i(0) ; i<4 ; i++) {
		m_ptrees[i]=NULL;
	}

	// There is one more Quad
	m_NB_QUADS++;
}

/**
 * Constructor1
 * @param a{The side's lenght of the area}
 * @param point{The center on which is centered the Oct's area}
 */
template<typename U, typename T> inline Quad<U, T>::Quad(const T& a, const Point3D<T>& point) {
	m_ppoint=std::make_shared<Point3D<T>>(point);
	m_pbarycenter=std::make_shared<Point3D<T>>(*m_ppoint);

	m_ha=a/(T)2;
	m_tot_weight=(T)0;

	m_pU=NULL;

	for (int i(0) ; i<4 ; i++){
		m_ptrees[i]=NULL;
	}
	// There is one more Quad
	m_NB_QUADS++;
}

/*
 * Constructor2
 */
/*template <typename U, typename T> Quad<U, T>::Quad(const SN<T>& a, std::shared_ptr<Point3D<T>> ppoint) {
	m_ppoint=ppoint;
	m_pbarycenter=std::shared_ptr(new Point3D<T>(*m_ppoint));
	//m_delp=false;

	m_a=a;
	m_tot_weight=0.;

	m_pT=NULL;

	m_pTLTree=NULL;
	m_pTRTree=NULL;
	m_pBLTree=NULL;
	m_pBRTree=NULL;

	m_NB_QUADS++;
}*/

template<typename U, typename T> inline Quad<U, T>::~Quad() {
	for (int i(0) ; i<4 ; i++){
		if (m_ptrees[i]!=NULL){
			delete m_ptrees[i];
		}
	}
	// There is one less Quad
	m_NB_QUADS--;
}

/*
 * Copy constructor
 */
template<typename U, typename T> inline Quad<U, T>::Quad(const Quad<U, T>& quad) {
	m_ppoint=std::make_shared<Point3D<T>>(quad.getPoint());
	m_pbarycenter=std::make_shared<Point3D<T>>(*m_ppoint);

	m_ha=quad.getA()/(T)2;
	m_tot_weight=(T)0;

	m_pU=NULL;

	for (int i(0) ; i<4 ; i++){
		m_ptrees[i]=NULL;
	}

	m_NB_QUADS++;
}

template<typename U, typename T> inline Point3D<T> Quad<U, T>::getPoint() const {
	return *m_ppoint;
}

template<typename U, typename T> inline void Quad<U, T>::setPoint(const Point3D<T>& point) {
	if (m_ppoint!=NULL){
		*m_ppoint=point;
	}else{
		m_ppoint=std::make_shared<Point3D<T>>(point);
		// Et le barycentre ?
	}
	this->recalculate();
}

template<typename U, typename T> inline Point3D<T> Quad<U, T>::getBarycenter() const {
	return *m_pbarycenter;
}

template<typename U, typename T> inline T Quad<U, T>::getA() const {
	return m_ha*(T)2;
}

template<typename U, typename T> inline void Quad<U, T>::setA(const T& a) {
	m_ha=a/(T)2;
	this->recalculate();
}

template<typename U, typename T> inline unsigned int Quad<U, T>::getNB_QUADS() const {
	return m_NB_QUADS;
}

/**
 * mem: flag memorise (recursive call)
 */
template<typename U, typename T> inline std::unordered_set<std::shared_ptr<U>> Quad<U, T>::getPElements(const bool& mem) const {
	static std::unordered_set<std::shared_ptr<U>> elmts;

	if (mem==false){
		elmts.clear();
	}

	if (m_pU!=NULL && mem==true){
		elmts.insert(m_pU);
	}else{
		for (int i(0) ; i<4 ; i++){
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
template<typename U, typename T> inline std::unordered_set<std::shared_ptr<U>> Quad<U, T>::getPNeighbors(const std::shared_ptr<U> pelement, const bool& mem) const {//////LOOOOK HERE !
	static std::unordered_set<std::shared_ptr<U>> pneighbors;

	if (mem==false){
		pneighbors.clear();
	}

	if (pelement!=NULL){
		if (m_pU==NULL && (T)(m_ALPHA)/**abs(m_tot_weight)*/<=m_ha*(T)2/getDistance(*m_pbarycenter/**m_ppoint*/, *pelement)) {
			for (int i(0) ; i<4 ; i++) {
				if (m_ptrees[i]!=NULL){
					m_ptrees[i]->getPNeighbors(pelement, true);
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

template<typename U, typename T> inline std::shared_ptr<U> Quad<U, T>::insert(std::shared_ptr<U> pU) {
	if (pU!=NULL){
		Point3D<T> p={pU->x, pU->y, pU->z};
		Point3D<T> dp=p-*m_ppoint;
		//dp.print(true, true, 0);

		if (abs(dp.x)<=m_ha && abs(dp.y)<=m_ha){// If in the square centered on the point.
			// Manages the barycenter
			m_tot_weight+=pU->getW();//Add to tot_weight
			if (m_tot_weight!=(T)0){
				*m_pbarycenter+=p*(pU->getW()/m_tot_weight);//Add to the barycenter
			}else{
				*m_pbarycenter=*m_ppoint;
			}

			if (this->isEmpty() && this->isLeaf()){		// If empty and the cube has no Quads under (if it's a leaf)
				m_pU=pU;//We add in
			}else{										// Else it means it is an internal branch
				if (dp.x>=(T)0 && dp.y<=(T)0){//If square 1
					insertTLTree(pU);
				}else if (dp.x>=(T)0 && dp.y<=(T)0){//If square 2
					insertTRTree(pU);
				}else if (dp.x<=(T)0 && dp.y<=(T)0){//If square 3
					insertBRTree(pU);
				}else if (dp.x<=(T)0 && dp.y>=(T)0){//If square 4
					insertBLTree(pU);
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

template<typename U, typename T> inline void Quad<U, T>::insertTLTree(std::shared_ptr<U> pU) {//En private
	if (TLTree==NULL){//If there is not yet a tree we create it
		T a=m_ha/(T)2;
		Point3D<T> np{(T)(-1)*a, (T)(-1)*a, (T)(1)*a};
		TLTree=new Quad<U, T>(m_ha, *m_ppoint+np);
	}
	TLTree->insert(pU);
}

template<typename U, typename T> inline void Quad<U, T>::insertTRTree(std::shared_ptr<U> pU) {//En private
	if (TRTree==NULL){//If there is not yet a tree we create it
		T a=m_ha/(T)2;
		Point3D<T> np{(T)(1)*a, (T)(-1)*a, (T)(1)*a};
		TRTree=new Quad<U, T>(m_ha, *m_ppoint+np);
	}
	TRTree->insert(pU);
}

template<typename U, typename T> inline void Quad<U, T>::insertBRTree(std::shared_ptr<U> pU) {//En private
	if (BLTree==NULL){//If there is not yet a tree we create it
		T a=m_ha/(T)2;
		Point3D<T> np{(T)(1)*a, (T)(-1)*a, (T)(-1)*a};
		BLTree=new Quad<U, T>(m_ha, *m_ppoint+np);
	}
	BLTree->insert(pU);
}

template<typename U, typename T> inline void Quad<U, T>::insertBLTree(std::shared_ptr<U> pU) {//En private
	if (BLTree==NULL){//If there is not yet a tree we create it
		T a=m_ha/(T)2;
		Point3D<T> np{(T)(-1)*a, (T)(-1)*a, (T)(-1)*a};
		BLTree=new Quad<U, T>(m_ha, *m_ppoint+np);
	}
	BLTree->insert(pU);
}

template<typename U, typename T> inline bool Quad<U, T>::remove(std::shared_ptr<U> pU) {//:)
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

template<typename U, typename T> inline std::unordered_set<std::shared_ptr<U>> Quad<U, T>::recalculate() {
	std::unordered_set<std::shared_ptr<U>> pelements=this->getPElements();

	this->empty();

	for (std::shared_ptr<U> pelement : pelements){
		this->insert(pelement);//:)
	}
}

template<typename U, typename T> inline void Quad<U, T>::empty() {
	for (int i(0) ; i<4 ; i++){
		if (m_ptrees[i]!=NULL){
			delete m_ptrees[i];
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
template<typename U, typename T> inline bool Quad<U, T>::isFull() const {
	return !this->isEmpty();
}

/**
 * Returns true if doesn't contain an object.
 * False otherwise.
 */
template<typename U, typename T> inline bool Quad<U, T>::isEmpty() const {
	bool test=false;

	if (m_pU==NULL){
		test=true;
	}

	return test;
}

/**
 * Returns true if doesn't contain an object.
 * False otherwise.
 */
template<typename U, typename T> inline bool Quad<U, T>::isLeaf() const {
	bool test=true;

	for (int i(0) ; i<4 ; i++){
		if (m_ptrees[i]!=NULL){
			test=false;
			break;
		}
	}

	return test;
}

/*template<typename U, typename T> std::shared_ptr<T> Quad<U, T>::search(const std::shared_ptr<Point3D<T>> ppoint) const {
	std::shared_ptr<T> pT=NULL;

	if (ppoint!=NULL){
		M delta_x=(M)(ppoint->x-m_ppoint->x);
		M delta_y=(M)(ppoint->y-m_ppoint->y);

		if (abs(delta_x)<m_a/2 && abs(delta_y)<m_a/2){//If in the square centered on the point.

			if (m_pT!=NULL){// This means it is a square of the smallest size possible.
				pT=m_pT;
			}else{
				if (m_pTLTree!=NULL){
					pT=m_pTLTree->search(ppoint);
				}
				if (pT==NULL){//If it hasn't been initiated by the precedent line
					if (m_pTRTree!=NULL){
						pT=m_pTRTree->search(ppoint);
					}
					if (pT==NULL){//If it hasn't been initiated by the precedent line
						if (m_pBLTree!=NULL){
							pT=m_pBLTree->search(ppoint);
						}
						if (pT==NULL){//If it hasn't been initiated by the precedent line
							if (m_pBRTree!=NULL){
								pT=m_pBRTree->search(ppoint);
							}
						}
					}
				}
			}
		}
	}

	return pT;
}*/





#endif /* QUAD_HPP_ */
