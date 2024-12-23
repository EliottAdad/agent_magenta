/*
 * Oct.h
 *
 *  Created on: 20 août 2024
 *      Author: esn
 */

#ifndef OCT_H_

#define OCT_H_

#define TLFTree m_ptrees[0] 	// Top Left Front corner : is NULL if nothing
#define TRFTree m_ptrees[1]		// Top Right Front corner : is NULL if nothing
#define BRFTree m_ptrees[2]		// Bottom Right Front corner : is NULL if nothing
#define BLFTree m_ptrees[3]		// Bottom Left Front corner : is NULL if nothing
#define TLBTree m_ptrees[4]		// Top Left Back corner : is NULL if nothing
#define TRBTree m_ptrees[5]		// Top Right Back corner : is NULL if nothing
#define BRBTree m_ptrees[6]		// Bottom Right Back corner : is NULL if nothing
#define BLBTree m_ptrees[7]		// Bottom Left Back corner : is NULL if nothing

#include <memory>
#include <cstdio>
//#include <cmath>
#include <unordered_set>

#include "SN.h"
#include "Particle3D.h"
#include "Point3D.h"
#include "../utilities/Printable.h"


/*
 * ################
 *  Oct<T, M, E> :)
 * ################
 * Can contain any object that has x, y, z, w
 */
template<typename T, typename M, typename E> class Oct : public Printable {
protected:
	std::shared_ptr<Point3D<M, E>> m_ppoint;					// The center of the zone.
	std::shared_ptr<Point3D<M, E>> m_pbarycenter;				// The center of mass given the repartition of the WeightedPoints in the zone.

	SN<M, E> m_a;												// Length of the zone's border.
	SN<M, E> m_tot_weight;										// Total weight contained in this Oct.

	std::shared_ptr<T> m_pT;					// The content of this square (NULL if nothing).
	//Particle3D* m_pparticle;					// The content of this node.

	//Oct<T, M, E>* m_pTLFTree;					// Top Left corner : is NULL if nothing
	//Oct<T, M, E>* m_pTRFTree;					// Top Right corner : is NULL if nothing
	//Oct<T, M, E>* m_pBLFTree;					// Bottom Left corner : is NULL if nothing
	//Oct<T, M, E>* m_pBRFTree;					// Bottom Right corner : is NULL if nothing
	//Oct<T, M, E>* m_pTLBTree;					// Top Left corner : is NULL if nothing
	//Oct<T, M, E>* m_pTRBTree;					// Top Right corner : is NULL if nothing
	//Oct<T, M, E>* m_pBLBTree;					// Bottom Left corner : is NULL if nothing
	//Oct<T, M, E>* m_pBRBTree;					// Bottom Right corner : is NULL if nothing
	Oct<T, M, E>* m_ptrees[8];					// Contains the trees.

	static unsigned int m_NB_OCTS;				// Keeps track of the number of Octs created.

	void insertTLFTree(std::shared_ptr<T> pT);//:)
	void insertTRFTree(std::shared_ptr<T> pT);//:)
	void insertBRFTree(std::shared_ptr<T> pT);//:)
	void insertBLFTree(std::shared_ptr<T> pT);//:)
	void insertTLBTree(std::shared_ptr<T> pT);//:)
	void insertTRBTree(std::shared_ptr<T> pT);//:)
	void insertBRBTree(std::shared_ptr<T> pT);//:)
	void insertBLBTree(std::shared_ptr<T> pT);//:)

public:
	static SN<M, E> m_LIM_A;					// This indicates the limit at which we stop subdividing (useless)
	static float m_ALPHA;						// The threshold m_ALPHA=d/a (with a being the width of the zone and d the distance from the center of the quad) indicates at which point we can consider an agglomeration of bodies as one.

	Oct();
	Oct(const SN<M, E>& a, const Point3D<M, E>& p={{0,0},{0,0},{0,0}});
	//Oct(const SN<M, E>& a, std::shared_ptr<Point3D<M, E>> ppoint);
	Oct(const Oct<T, M, E>& oct);
	virtual ~Oct();

	Point3D<M, E> getPoint() const;
	void setPoint(const Point3D<M, E>& point);
	//void setPPoint(Point3D<M, E>* ppoint, bool delp=true);// delp indique s'il faudra delete le point passé en argument
	Point3D<M, E> getBarycenter() const;
	//Point3D<M, E>* getPBarycenter() const;
	//bool getDelP() const;
	SN<M, E> getA() const;
	void setA(const SN<M, E>& a);
	unsigned int getNB_OCTS() const;
	//float getAlpha();
	//static void setAlpha(float& alpha=0.5);
	//std::unordered_set<Oct<T, M, E>*> getPTrees();						//Returns all the trees under, contained by this tree.
	std::unordered_set<std::shared_ptr<T>> getPElements(const bool& mem=false) const;					//:) Returns all the elements contained in the tree.
	std::unordered_set<std::shared_ptr<T>> getPNeighbors(const std::shared_ptr<T> pelement, const bool& mem=false) const;		//:) Returns all the neighbors.

	bool insert(std::shared_ptr<T> pT);//:)
	//bool insert(Particle3D* ppart);
	//void find(const T& t, std::unordered_set<Oct<T, M, E>*>& pocts);// It adds to the list of Octs in parameter accordingly to the ratio m_ALPHA
	//void computeInverseSquareLawResultant(const T& t, Vector3D& v) const;// Useless
	//std::unordered_set<T*> find(const Point3D& point);
	std::shared_ptr<T> search(const std::shared_ptr<Point3D<M, E>> ppoint) const;
	void recalculate();
	void empty();

	bool isLeaf();
	bool isEmpty();

	std::string to_string(const bool& spread=false, const bool& full_info=false, const unsigned char& indent=0) const;// :)
	void print(const bool& spread=false, const bool& full_info=false, const unsigned char& indent=0) const;// :)
};
template<typename T, typename M, typename E> unsigned int Oct<T, M, E>::m_NB_OCTS=0;
template<typename T, typename M, typename E> SN<M, E> Oct<T, M, E>::m_LIM_A={1,0};
template<typename T, typename M, typename E> float Oct<T, M, E>::m_ALPHA=0.5;


/*
 * Constructor0
 */
template<typename T, typename M, typename E> Oct<T, M, E>::Oct() {
	m_ppoint=std::make_shared<Point3D<M, E>>();
	m_pbarycenter=std::make_shared<Point3D<M, E>>(*m_ppoint);
	//printf("\nHein1 ? (Oct)\n");
	//m_pbarycenter->print();

	m_a={1,2};
	m_tot_weight=(M)0.;

	m_pT=NULL;

	for (int i(0) ; i<8 ; i++){
		m_ptrees[i]=NULL;
	}

	m_NB_OCTS++;
	//printf("\nHein2 ? (Oct)\n");
}


/**
 * Constructor1
 * @param a{The side's lenght of the area}
 * @param point{The center on which is centered the Oct's area}
 */
template<typename T, typename M, typename E> Oct<T, M, E>::Oct(const SN<M, E>& a, const Point3D<M, E>& p) {
	m_ppoint=std::make_shared<Point3D<M, E>>(p);
	m_pbarycenter=std::make_shared<Point3D<M, E>>(*m_ppoint);
	//m_delp=true;

	m_a=a;
	m_tot_weight=(M)0.;

	m_pT=NULL;

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
/*template<typename T, typename M, typename E> Oct<T, M, E>::Oct(const SN<M, E>& a, std::shared_ptr<Point3D<M, E>> ppoint) {
	m_ppoint=ppoint;
	m_pbarycenter=std::make_shared<Point3D<M, E>>(*m_ppoint);
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
/*template<typename T, typename M, typename E> Oct<T, M, E>::Oct(const SN<M, E>& a, Point3D<M, E>* ppoint) {
	m_ppoint=ppoint;
	m_pbarycenter=new Point3D<M, E>(*m_ppoint);
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

/*
 * Copy constructor
 */
template<typename T, typename M, typename E> Oct<T, M, E>::Oct(const Oct<T, M, E>& oct) {
	m_ppoint=std::make_shared<Point3D<M, E>>(oct.getPoint());
	m_pbarycenter=std::make_shared<Point3D<M, E>>(*m_ppoint);

	m_a=oct.getA();
	m_tot_weight=(M)0.;

	m_pT=NULL;

	for (int i(0) ; i<8 ; i++){
		m_ptrees[i]=NULL;
	}
	// There is one more Oct
	m_NB_OCTS++;
}

template<typename T, typename M, typename E> Oct<T, M, E>::~Oct() {
	for (int i(0) ; i<8 ; i++){
		if (m_ptrees[i]!=NULL){
			delete m_ptrees[i];
		}
	}
	// There is one less Oct
	m_NB_OCTS--;
}

template<typename T, typename M, typename E> Point3D<M, E> Oct<T, M, E>::getPoint() const {// Because it can be NULL
	return *m_ppoint;
}

/*template <typename T, typename M, typename E> Point3D<M, E>* Oct<T, M, E>::getPPoint() const {
	return this->m_ppoint;
}*/

template<typename T, typename M, typename E> void Oct<T, M, E>::setPoint(const Point3D<M, E>& point) {
	if (m_ppoint!=NULL){
		*m_ppoint=point;
	}else{
		m_ppoint=std::make_shared<Point3D<M, E>>(point);
		// Et le barycentre ?
	}
	this->recalculate();
}

/*template<typename T, typename M, typename E> void Oct<T, M, E>::setPPoint(Point3D<M, E>* ppoint, bool delp) {
	if (ppoint!=NULL){
		if (m_delp){
			delete m_ppoint;
		}
		if (delp){
			m_ppoint=new Point3D<M, E>(*ppoint);
		}else{
			m_ppoint=ppoint;
		}
		m_delp=delp;

		this->recalculate();
	}
}*/

template<typename T, typename M, typename E> Point3D<M, E> Oct<T, M, E>::getBarycenter() const {
	/*Point3D<M, E> barycenter;
	SN<M, E> tot_w;
	for (std::shared_ptr<T> pelement : this->getPElements()){
		barycenter+=pelement->getPosition()*pelement->getW();
		tot_w+=pelement->getW();
	}
	if(tot_w!=0){
		barycenter/=tot_w;
	}else{
		barycenter=*m_ppoint;
	}
	return barycenter;*/
	return *m_pbarycenter;
}

template<typename T, typename M, typename E> SN<M, E> Oct<T, M, E>::getA() const {
	return m_a;
}

template<typename T, typename M, typename E> void Oct<T, M, E>::setA(const SN<M, E>& a){
	m_a=a;
	this->recalculate();
}

template<typename T, typename M, typename E> unsigned int Oct<T, M, E>::getNB_OCTS() const {
	return m_NB_OCTS;
}

/*
 * Returns all the trees under, contained by this tree.
 */
/*template<typename T, typename M, typename E> std::unordered_set<Oct<T, M, E>*> Oct<T, M, E>::getPTrees() {
	std::unordered_set<Oct<T, M, E>*> ptrees;
	if (m_pTLFTree!=NULL){
		ptrees.insert(m_pTLFTree);
	}else if (m_pTRFTree!=NULL){
		ptrees.insert(m_pTRFTree);
	}else if (m_pBLFTree!=NULL){
		ptrees.insert(m_pBLFTree);
	}else if (m_pBRFTree!=NULL){
		ptrees.insert(m_pBRFTree);
	}else if (m_pTLBTree!=NULL){
		ptrees.insert(m_pTLBTree);
	}else if (m_pTRBTree!=NULL){
		ptrees.insert(m_pTRBTree);
	}else if (m_pBLBTree!=NULL){
		ptrees.insert(m_pBLBTree);
	}else if (m_pBRBTree!=NULL){
		ptrees.insert(m_pBRBTree);
	}
	return ptrees;
}*/
/**
 * mem: flag memorise
 */
template<typename T, typename M, typename E> std::unordered_set<std::shared_ptr<T>> Oct<T, M, E>::getPElements(const bool& mem) const {
	static std::unordered_set<std::shared_ptr<T>> elmts;

	if (mem==false){
		elmts.clear();
	}

	if (m_pT!=NULL && mem==true){
		elmts.insert(m_pT);
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
template<typename T, typename M, typename E> std::unordered_set<std::shared_ptr<T>> Oct<T, M, E>::getPNeighbors(const std::shared_ptr<T> pelement, const bool& mem) const {//////LOOOOK HERE !
	static std::unordered_set<std::shared_ptr<T>> pneighbors;

	if (mem==false){
		pneighbors.clear();
	}

	if (pelement!=NULL){
		//printf("God0\n");
		//getDistance(/**m_pbarycenter*/*m_ppoint, *pelement).print();
		//printf("\n");
		//(getDistance(/**m_pbarycenter*/*m_ppoint, *pelement)/m_a).print();
		//printf("\n");
		if (m_pT==NULL && (M)(m_ALPHA)/**abs(m_tot_weight)*/>=getDistance(*m_pbarycenter/**m_ppoint*/, *pelement)/m_a){//SN<M, E>{1., 0}/getDistance(*m_ppoint, *pelement)<=SN<M, E>{m_ALPHA, 0}
			//printf("God3\n");
			for (int i(0) ; i<8 ; i++){
				if (m_ptrees[i]!=NULL){
					m_ptrees[i]->getPNeighbors(pelement, true);
					//printf("God4\n");
				}
			}
		}else{
			if (m_pT!=NULL){// If the cube is not empty
				if (m_pT!=pelement){
					pneighbors.insert(m_pT);
				}
				//printf("God1\n");
			}else{			// Else if the place is empty
				std::shared_ptr<T> new_pT(new T(m_pbarycenter->getX(), m_pbarycenter->getY(), m_pbarycenter->getZ(), m_tot_weight));
				pneighbors.insert(new_pT);
				//printf("God2\n");
			}
		}
	}

	return pneighbors;
}

template <typename T, typename M, typename E> bool Oct<T, M, E>::insert(std::shared_ptr<T> pT) {
	//printf("A0\n");
	if (pT!=NULL){
		Point3D<M, E> p={pT->x, pT->y, pT->z};
		Point3D<M, E> dp=p-*m_ppoint;//{pT->x-m_ppoint->x, pT->y-m_ppoint->y, pT->z-m_ppoint->z};
		//printf("A0_2: ");
		//m_ppoint->print();
		//p.print();
		//abs(dp).print();
		//printf("\n");

		if (abs(dp.x)<=m_a/(M)2. && abs(dp.y)<=m_a/(M)2. && abs(dp.z)<=m_a/(M)2.){// If in the cube centered on the point.

			//printf("A1\n");
			// Manage the barycenter
			m_tot_weight+=pT->getW();//Add to tot_weight
			if (m_tot_weight!=(M)0.){
				*m_pbarycenter+=p*(pT->getW()/m_tot_weight);//Add to the barycenter
			}else{
				*m_pbarycenter=*m_ppoint;
			}

			if (this->isEmpty() && this->isLeaf()){		// If empty and the cube has no Octs under (if it's a leaf)
				printf("A3\n");
				m_pT=pT;//We add in
				//printf("AAAAAAAAAAAA%b\n", m_pT==NULL);
				//m_pT->print();
				//printf("\nAAAAAAAAAAAA\n");
			}else{																				// Else it means it is an internal branch
				if (dp.x<=(M)0. && dp.y<=(M)0. && dp.z>=(M)0.){//If cube 1
					//printf("D\n");
					insertTLFTree(pT);
				}else if (dp.x>=(M)0. && dp.y<=(M)0. && dp.z>=(M)0.){//If cube 2
					//printf("E\n");
					insertTRFTree(pT);
				}else if (dp.x>=(M)0. && dp.y<=(M)0. && dp.z<=(M)0.){//If cube 3
					//printf("F\n");
					insertBRFTree(pT);
				}else if (dp.x<=(M)0. && dp.y<=(M)0. && dp.z<=(M)0.){//If cube 4
					//printf("G\n");
					insertBLFTree(pT);
				}else if (dp.x<=(M)0. && dp.y>=(M)0. && dp.z>=(M)0.){//If cube 5
					//printf("H\n");
					insertTLBTree(pT);
				}else if (dp.x>=(M)0. && dp.y>=(M)0. && dp.z>=(M)0.){//If cube 6
					//printf("I\n");
					insertTRBTree(pT);
				}else if (dp.x>=(M)0. && dp.y>=(M)0. && dp.z<=(M)0.){//If cube 7
					//printf("J\n");
					insertBRBTree(pT);
				}else if (dp.x<=(M)0. && dp.y>=(M)0. && dp.z<=(M)0.){//If cube 8
					//printf("K\n");
					insertBLBTree(pT);
				}

				// We reinsert the object already present(can be null if it wasn't a leaf).
				if (m_pT!=NULL){
					m_tot_weight-=m_pT->getW();//Subtract the w of the already present obj to tot_weight
					std::shared_ptr<T> pT2;//Init to null
					//printf("###############%b\n", pT2==NULL);
					/*pT2=m_pT;
					m_pT=NULL;*/
					pT2.swap(m_pT);// Set m_pT to NULL and pT2 to m_pT
					//printf("###############\n");
					this->insert(pT2);
					//printf("###############%b\n", m_pT==NULL);
				}
			}
		}
	}
	return true;
}

template<typename T, typename M, typename E> void Oct<T, M, E>::insertTLFTree(std::shared_ptr<T> pT) {//En private
	if (TLFTree==NULL){//If there is not yet a tree we create it
		SN<M, E> a=m_a/(M)4.;
		Point3D<M, E> np{(M)(-1.)*a, (M)(-1.)*a, (M)(1.)*a};
		TLFTree=new Oct<T, M, E>(m_a/(M)2., *m_ppoint+np);
	}
	TLFTree->insert(pT);
}

template<typename T, typename M, typename E> void Oct<T, M, E>::insertTRFTree(std::shared_ptr<T> pT) {//En private
	if (TRFTree==NULL){//If there is not yet a tree we create it
		SN<M, E> a=m_a/(M)4.;
		Point3D<M, E> np{(M)(1.)*a, (M)(-1.)*a, (M)(1.)*a};
		TRFTree=new Oct<T, M, E>(m_a/(M)2., *m_ppoint+np);
	}
	TRFTree->insert(pT);
}

template<typename T, typename M, typename E> void Oct<T, M, E>::insertBRFTree(std::shared_ptr<T> pT) {//En private
	if (BLBTree==NULL){//If there is not yet a tree we create it
		SN<M, E> a=m_a/(M)4.;
		Point3D<M, E> np{(M)(1.)*a, (M)(-1.)*a, (M)(-1.)*a};
		BLBTree=new Oct<T, M, E>(m_a/(M)2., *m_ppoint+np);
	}
	BLBTree->insert(pT);
}

template<typename T, typename M, typename E> void Oct<T, M, E>::insertBLFTree(std::shared_ptr<T> pT) {//En private
	if (BLFTree==NULL){//If there is not yet a tree we create it
		SN<M, E> a=m_a/(M)4.;
		Point3D<M, E> np{(M)(-1.)*a, (M)(-1.)*a, (M)(-1.)*a};
		BLFTree=new Oct<T, M, E>(m_a/(M)2., *m_ppoint+np);
	}
	BLFTree->insert(pT);
}

template<typename T, typename M, typename E> void Oct<T, M, E>::insertTLBTree(std::shared_ptr<T> pT) {//En private
	if (TLBTree==NULL){//If there is not yet a tree we create it
		SN<M, E> a=m_a/(M)4.;
		Point3D<M, E> np{(M)(-1.)*a, (M)(1.)*a, (M)(1.)*a};
		TLBTree=new Oct<T, M, E>(m_a/(M)2., *m_ppoint+np);
	}
	TLBTree->insert(pT);
}

template<typename T, typename M, typename E> void Oct<T, M, E>::insertTRBTree(std::shared_ptr<T> pT) {//En private
	if (TRBTree==NULL){//If there is not yet a tree we create it
		SN<M, E> a=m_a/(M)4.;
		Point3D<M, E> np{(M)(1.)*a, (M)(1.)*a, (M)(1.)*a};
		TRBTree=new Oct<T, M, E>(m_a/(M)2., *m_ppoint+np);
	}
	TRBTree->insert(pT);
}

template<typename T, typename M, typename E> void Oct<T, M, E>::insertBRBTree(std::shared_ptr<T> pT) {//En private
	if (BRBTree==NULL){//If there is not yet a tree we create it
		SN<M, E> a=m_a/(M)4.;
		Point3D<M, E> np{(M)(1.)*a, (M)(1.)*a, (M)(-1.)*a};
		BRBTree=new Oct<T, M, E>(m_a/(M)2., *m_ppoint+np);
	}
	BRBTree->insert(pT);
}

template<typename T, typename M, typename E> void Oct<T, M, E>::insertBLBTree(std::shared_ptr<T> pT) {//En private
	if (BLBTree==NULL){//If there is not yet a tree we create it
		SN<M, E> a=m_a/(M)4.;
		Point3D<M, E> np{(M)(-1.)*a, (M)(1.)*a, (M)(-1.)*a};
		BLBTree=new Oct<T, M, E>(m_a/(M)2., *m_ppoint+np);
	}
	BLBTree->insert(pT);
}

template<typename T, typename M, typename E> void Oct<T, M, E>::recalculate() {
	std::unordered_set<std::shared_ptr<T>> pelements=this->getPElements();

	this->empty();

	for (std::shared_ptr<T> pelement : pelements){
		this->insert(pelement);//:)
	}
}

template<typename T, typename M, typename E> void Oct<T, M, E>::empty() {
	for (int i(0) ; i<8 ; i++){
		if (m_ptrees[i]!=NULL){
			delete m_ptrees[i];
		}
	}

	*m_pbarycenter=*m_ppoint;
	m_tot_weight={(M)0,(E)0};
	m_pT=NULL;
}

template<typename T, typename M, typename E> bool Oct<T, M, E>::isLeaf() {
	bool test=false;

	if (m_pT==NULL){
		test=true;
	}

	return test;
}

template<typename T, typename M, typename E> bool Oct<T, M, E>::isEmpty() {
	bool test=true;

	for (int i(0) ; i<8 ; i++){
		if (m_ptrees[i]!=NULL){
			test=false;
			break;
		}
	}

	return test;
}

/*template<typename T, typename M, typename E> void Oct<T, M, E>::find(const T& t, std::unordered_set<Oct<T, M, E>*>& pocts) {
	Point3D<M, E> p={t.x, t.y, {0,0}};

	SN<M, E> s=this->m_a;
	SN<M, E> d=getDistance(p, *m_pbarycenter);
	SN<M, E> alpha=s/d;
	//std::cout<<"\n"<<alpha.to_string()<<"\n";

	if (alpha>=m_ALPHA){
		pocts.insert(this);
	}else{
		if (m_pTLBTree!=NULL){
			m_pTLBTree->find(t, pocts);
		}
		if (m_pTRBTree!=NULL){
			m_pTRBTree->find(t, pocts);
		}
		if (m_pBLBTree!=NULL){
			m_pBLBTree->find(t, pocts);
		}
		if (m_pBRBTree!=NULL){
			m_pBRBTree->find(t, pocts);
		}
		if (m_pTLFTree!=NULL){
			m_pTLFTree->find(t, pocts);
		}
		if (m_pTRFTree!=NULL){
			m_pTRFTree->find(t, pocts);
		}
		if (m_pBLFTree!=NULL){
			m_pBLFTree->find(t, pocts);
		}
		if (m_pBRFTree!=NULL){
			m_pBRFTree->find(t, pocts);
		}
	}
}*/

template<typename T, typename M, typename E> std::shared_ptr<T> Oct<T, M, E>::search(const std::shared_ptr<Point3D<M, E>> ppoint) const {
	std::shared_ptr<T> pT=NULL;

	if (ppoint!=NULL){
		M delta_x=(M)(ppoint->x-this->m_ppoint->x);
		M delta_y=(M)(ppoint->y-this->m_ppoint->y);
		M delta_z=(M)(ppoint->z-this->m_ppoint->z);

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
}



template<typename T, typename M, typename E> std::string Oct<T, M, E>::to_string(const bool& spread, const bool& full_info, const unsigned char& indent) const {
	//printf("AAAAAA12\n");
	std::string mes=((spread)?"\n" : "");
	mes+=to_stringTabs(indent);

	mes+="OCT[";
	std::stringstream ss;
	ss << this;
	//printf("AAAAAA122\n");
	mes+=ss.str();
	mes+="]:";
	mes+=m_a.to_string(false, false, 0);								//a
	mes+=" | ";
	//printf("AAAAAA123\n");
	//std::cout << ppoint << "\n";
	mes+=(m_ppoint==NULL)? "NULL" : m_ppoint->to_string(false, false, 0);			//Point ERROR
	mes+=" | ";
	//printf("AAAAAA124\n");
	mes+=(m_pbarycenter==NULL)? "NULL" : m_pbarycenter->to_string(false, false, 0);		//Barycenter
	mes+=" | ";
	//printf("AAAAAA125\n");
	std::stringstream ss2;
	ss2 << m_pT;
	mes+=ss2.str();
	mes+=" | ";
	//printf("AAAAAA126\n");
	mes+="w:" + std::to_string(m_tot_weight.to_m_type());
	mes+="]";
	//mes+=((spread)?"\n" : "");
	mes+="\n";
	//printf("AAAAAA127\n");

	mes+=to_stringTabs(indent+1);
	if (full_info){
		mes+="(";
		std::string nulll=((spread)?"\n" : "");
		nulll+=((spread)?to_stringTabs(indent+1) : "");
		nulll+="NULL";
		nulll+=", ";
		//nulll+=((spread)?"\n" : "");

		//printf("AAAAAA13\n");
		mes+=(BLBTree==NULL)?nulll : BLBTree->to_string(spread, full_info, indent+1);
		mes+=to_stringTabs(indent+1);
		//printf("AAAAAA14\n");
		mes+=(BRBTree==NULL)?nulll : BRBTree->to_string(spread, full_info, indent+1);
		mes+=to_stringTabs(indent+1);
		//printf("AAAAAA15\n");
		mes+=(BRFTree==NULL)?nulll : BRFTree->to_string(spread, full_info, indent+1);
		mes+=to_stringTabs(indent+1);
		//printf("AAAAAA16\n");
		mes+=(BLFTree==NULL)?nulll : BLFTree->to_string(spread, full_info, indent+1);
		mes+=to_stringTabs(indent+1);
		//printf("AAAAAA17\n");
		mes+=(TLBTree==NULL)?nulll : TLBTree->to_string(spread, full_info, indent+1);
		mes+=to_stringTabs(indent+1);
		//printf("AAAAAA18\n");
		mes+=(TRBTree==NULL)?nulll : TRBTree->to_string(spread, full_info, indent+1);
		mes+=to_stringTabs(indent+1);
		//printf("AAAAAA19\n");
		mes+=(TRFTree==NULL)?nulll : TRFTree->to_string(spread, full_info, indent+1);
		mes+=to_stringTabs(indent+1);
		//printf("AAAAAA20\n");
		mes+=(TLFTree==NULL)?nulll : TLFTree->to_string(spread, full_info, indent+1);
		//mes+=((spread)?to_stringTabs(indent+1) : "");


		mes.erase(mes.length()-2);
		mes+=((spread)?"\n" : "");
		mes+=((spread)?to_stringTabs(indent+1) : "");
		mes+=")";
	}

	return mes;
}

template<typename T, typename M, typename E> void Oct<T, M, E>::print(const bool& spread, const bool& full_info, const unsigned char& indent) const {
	printTabs(indent);
	std::cout << this->to_string(spread, full_info, indent);
}


#endif /* OCT_H_ */
