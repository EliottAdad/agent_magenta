/*
 * Oct.h
 *
 *  Created on: 20 août 2024
 *      Author: esn
 */

#ifndef OCT_H_

#define OCT_H_


#include <memory>
#include <cstdio>
//#include <cmath>
#include <unordered_set>

#include "SN.h"
#include "Particle3D.h"
#include "Point3D.h"
#include "../utilities/Printable.h"

/*
 * #######
 *  Oct :)
 * #######
 * Can contain any object that has x, y, z
 */
template <typename T, typename M, typename E> class Oct : public Printable {
protected:
	Point3D<M, E>* m_ppoint;					// The center of the zone.
	Point3D<M, E>* m_pbarycenter;				// The center of mass given the repartition of the WeightedPoints in the zone.
	bool m_delp;					// If the point should be deleted.

	SN<M, E> m_a;							// Length of the zone's border.
	SN<M, E> m_tot_weight;					// Total weight contained in this Oct.

	T* m_pT;							// The content of this square (NULL if nothing).
	//Particle3D* m_pparticle;			// The content of this node.

	Oct<T, M, E>* m_pTLFTree;					// Top Left corner : is NULL if nothing
	Oct<T, M, E>* m_pTRFTree;					// Top Right corner : is NULL if nothing
	Oct<T, M, E>* m_pBLFTree;					// Bottom Left corner : is NULL if nothing
	Oct<T, M, E>* m_pBRFTree;					// Bottom Right corner : is NULL if nothing
	Oct<T, M, E>* m_pTLBTree;					// Top Left corner : is NULL if nothing
	Oct<T, M, E>* m_pTRBTree;					// Top Right corner : is NULL if nothing
	Oct<T, M, E>* m_pBLBTree;					// Bottom Left corner : is NULL if nothing
	Oct<T, M, E>* m_pBRBTree;					// Bottom Right corner : is NULL if nothing

	static unsigned int m_NB_OCTS;		// Keeps track of the number of Octs created.

public:
	static SN<M, E> m_LIM_A;					// This indicates the limit at which we stop subdividing (useless)
	static float m_ALPHA;				// The threshold m_ALPHA=a/d (with a being the width of the zone and d the distance from the center of the quad) indicates at which point we can consider an agglomeration of bodies as one.

	Oct();
	Oct(const SN<M, E>& a);
	//Oct(const SN<M, E>& a, Point3D<M, E>* ppoint);
	Oct(const Oct<T, M, E>* poct);
	virtual ~Oct();

	//Point3D<M, E> getPoint() const;
	Point3D<M, E>* getPPoint() const;
	void setPoint(Point3D<M, E> point, bool delp=false);// delp indique s'il faudra delete le point passé en argument
	void setPPoint(Point3D<M, E>* ppoint, bool delp=true);// delp indique s'il faudra delete le point passé en argument
	Point3D<M, E> getBarycenter() const;
	//Point3D<M, E>* getPBarycenter() const;
	bool getDelP() const;
	SN<M, E> getA() const;
	void setA(const SN<M, E>& a);
	unsigned int getNB_OCTS() const;
	//float getAlpha();
	//static void setAlpha(float& alpha=0.5);
	std::unordered_set<Oct<T, M, E>*> getPTrees();						//Returns all the trees under, contained by this tree.
	std::unordered_set<T*> getPElements() const;					//Returns all the elements contained in the tree.
	std::unordered_set<T*> getPNeighbors(T* pelement) const;		//Returns all the neighbors.

	bool insert(T* pT);
	//bool insert(Particle3D* ppart);
	void find(const T& t, std::unordered_set<Oct<T, M, E>*>& pocts);// It adds to the list of Octs in parameter accordingly to the ratio m_ALPHA
	//void computeInverseSquareLawResultant(const T& t, Vector3D& v) const;// Useless
	//std::unordered_set<T*> find(const Point3D& point);
	T* search(const Point3D<M, E>* ppoint) const;
	void recalculate();
	bool empty();

	std::string to_string(const bool& spread=false, const bool& full_info=false, const unsigned char& indent=0) const;// :)
	void print(const bool& spread=false, const bool& full_info=false, const unsigned char& indent=0) const;// :)
};
template <typename T, typename M, typename E> unsigned int Oct<T, M, E>::m_NB_OCTS=0;
template <typename T, typename M, typename E> SN<M, E> Oct<T, M, E>::m_LIM_A={1, 0};
template <typename T, typename M, typename E> float Oct<T, M, E>::m_ALPHA=0.5;


/*
 * Constructor0
 */
template <typename T, typename M, typename E> Oct<T, M, E>::Oct() {
	m_ppoint=new Point3D<M, E>();
	m_pbarycenter=new Point3D<M, E>(*m_ppoint);
	m_delp=true;

	m_a={1,2};
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
}


/**
 * Constructor1
 * @param a{The side's lenght of the area}
 * @param point{The center on which is centered the Oct's area}
 */
template <typename T, typename M, typename E> Oct<T, M, E>::Oct(const SN<M, E>& a) {
	m_ppoint=new Point3D<M, E>({{0, 0}, {0, 0}, {0, 0}});
	m_pbarycenter=new Point3D<M, E>(*m_ppoint);
	m_delp=true;

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
}

/*
 * Constructor2
 */
/*template <typename T, typename M, typename E> Oct<T, M, E>::Oct(const SN<M, E>& a, Point3D<M, E>* ppoint) {
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
template <typename T, typename M, typename E> Oct<T, M, E>::Oct(const Oct<T, M, E>* poct) {
	m_ppoint=new Point3D<M, E>(poct->getPPoint());
	m_pbarycenter=new Point3D<M, E>(*m_ppoint);
	m_delp=false;

	m_a=poct->getA();
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
}

template <typename T, typename M, typename E> Oct<T, M, E>::~Oct() {
	if (m_delp){
		delete m_ppoint;
	}else{
		m_ppoint=NULL;
	}
	delete m_pbarycenter;

	m_pT=NULL;

	if (m_pTLFTree!=NULL){
		delete m_pTLFTree;
	}
	if (m_pTRFTree!=NULL){
		delete m_pTRFTree;
	}
	if (m_pBLFTree!=NULL){
		delete m_pBLFTree;
	}
	if (m_pBRFTree!=NULL){
		delete m_pBRFTree;
	}
	if (m_pTLBTree!=NULL){
		delete m_pTLBTree;
	}
	if (m_pTRBTree!=NULL){
		delete m_pTRBTree;
	}
	if (m_pBLBTree!=NULL){
		delete m_pBLBTree;
	}
	if (m_pBRBTree!=NULL){
		delete m_pBRBTree;
	}
	// There is one less Oct
	m_NB_OCTS--;
}

/*template <typename T, typename M, typename E> Point3D<M, E> Oct<T, M, E>::getPoint() const {// Because it can be NULL
	return *m_ppoint;
}*/

template <typename T, typename M, typename E> Point3D<M, E>* Oct<T, M, E>::getPPoint() const {
	Point3D<M, E>* pp=NULL;
	// If it hasn't been created locally...
	if (!m_delp){
		pp=this->m_ppoint;
	}
	return pp;
}

template <typename T, typename M, typename E> void Oct<T, M, E>::setPoint(Point3D<M, E> point, bool delp) {
	if (m_delp){
		delete m_ppoint;
	}
	if (delp){
		m_ppoint=new Point3D<M, E>(point);
	}else{
		m_ppoint=&point;
	}
	m_delp=delp;

	this->recalculate();
}

template <typename T, typename M, typename E> void Oct<T, M, E>::setPPoint(Point3D<M, E>* ppoint, bool delp) {
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
}

template <typename T, typename M, typename E> Point3D<M, E> Oct<T, M, E>::getBarycenter() const {
	return *m_pbarycenter;
}

template <typename T, typename M, typename E> SN<M, E> Oct<T, M, E>::getA() const {
	return m_a;
}

template <typename T, typename M, typename E> void Oct<T, M, E>::setA(const SN<M, E>& a){
	m_a=a;

}

template <typename T, typename M, typename E> unsigned int Oct<T, M, E>::getNB_OCTS() const {
	return m_NB_OCTS;
}

/*
 * Returns all the trees under, contained by this tree.
 */
template <typename T, typename M, typename E> std::unordered_set<Oct<T, M, E>*> Oct<T, M, E>::getPTrees() {
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
}

template <typename T, typename M, typename E> std::unordered_set<T*> Oct<T, M, E>::getPElements() const {
	std::unordered_set<T*> elmts;

	if (m_pT!=NULL){
		elmts.insert(m_pT);
	}else{
		if (m_pTLFTree!=NULL){
			for (T* pt : m_pTLFTree->getPElements()){
				elmts.insert(pt);
			}
		}
		if (m_pTRFTree!=NULL){
			for (T* pt : m_pTRFTree->getPElements()){
				elmts.insert(pt);
			}
		}
		if (m_pBLFTree!=NULL){
			for (T* pt : m_pBLFTree->getPElements()){
				elmts.insert(pt);
			}
		}
		if (m_pBRFTree!=NULL){
			for (T* pt : m_pBRFTree->getPElements()){
				elmts.insert(pt);
			}
		}
		if (m_pTLBTree!=NULL){
			for (T* pt : m_pTLBTree->getPElements()){
				elmts.insert(pt);
			}
		}
		if (m_pTRBTree!=NULL){
			for (T* pt : m_pTRBTree->getPElements()){
				elmts.insert(pt);
			}
		}
		if (m_pBLBTree!=NULL){
			for (T* pt : m_pBLBTree->getPElements()){
				elmts.insert(pt);
			}
		}
		if (m_pBRBTree!=NULL){
			for (T* pt : m_pBRBTree->getPElements()){
				elmts.insert(pt);
			}
		}
	}

	return elmts;
}

template <typename T, typename M, typename E> std::unordered_set<T*> Oct<T, M, E>::getPNeighbors(T* pelement) const {//////LOOOOK HERE !
	static std::unordered_set<T*> neighbors;

	//printf("AB\n");
	SN<M, E> r=/*m_a*/SN<M, E>{1., 0}/*((long double)1.)*//getDistance(*m_ppoint, *pelement);
	//r.print(true, true, 0);
	SN<M, E> s=SN<M, E>{m_ALPHA, 0};
	//s.print(true, true, 0);
	//printf("\n%b\n", /*m_a*/SN<M, E>{1., 0}/*1.*//getDistance(*m_ppoint, *pelement)<=SN<M, E>{m_ALPHA, 0});

	if (/*m_a*/SN<M, E>{1., 0}/*1.*//getDistance(*m_ppoint, *pelement)<=SN<M, E>{m_ALPHA, 0}){
		//printf("AC\n");
		if (m_pT!=NULL){
			neighbors.insert(m_pT);
		}else{
			neighbors.insert(new T(m_ppoint->getX(), m_ppoint->getY(), m_ppoint->getZ()));
		}
	}else{
		//printf("AD\n");
		if (m_pTLFTree!=NULL){
			m_pTLFTree->getPNeighbors(pelement);
		}
		if (m_pTRFTree!=NULL){
			m_pTRFTree->getPNeighbors(pelement);
		}
		if (m_pBLFTree!=NULL){
			m_pBLFTree->getPNeighbors(pelement);
		}
		if (m_pBRFTree!=NULL){
			m_pBRFTree->getPNeighbors(pelement);
		}
		if (m_pTLBTree!=NULL){
			m_pTLBTree->getPNeighbors(pelement);
		}
		if (m_pTRBTree!=NULL){
			m_pTRBTree->getPNeighbors(pelement);
		}
		if (m_pBLBTree!=NULL){
			m_pBLBTree->getPNeighbors(pelement);
		}
		if (m_pBRBTree!=NULL){
			m_pBRBTree->getPNeighbors(pelement);
		}
	}

	return neighbors;
}

template <typename T, typename M, typename E> bool Oct<T, M, E>::insert(T* pT) {
	if (pT!=NULL){
		Point3D<M, E> p={pT->x, pT->y, pT->z};
		Point3D<M, E> dp={pT->x-m_ppoint->x, pT->y-m_ppoint->y, pT->z-m_ppoint->z};

		if (abs(dp.x)<=m_a/(M)2. && abs(dp.y)<=m_a/(M)2. && abs(dp.z)<=m_a/(M)2.){// If in the cube centered on the point.
			if (m_pT==NULL){		// If empty
				//printf("Empty\n");
				if (m_pTLFTree==NULL and m_pTRFTree==NULL and m_pBLFTree==NULL and m_pBRFTree==NULL
						and m_pTRBTree==NULL and m_pTLBTree==NULL and m_pBLBTree==NULL and m_pBRBTree==NULL){	// If the cube has no Octs under (external branch)
					m_pT=pT;//We add in
					m_tot_weight=(M)1.;//Set the tot_weight
					*m_pbarycenter=p;//Set the barycenter
					//printf("A\n");
					//printf("\n#############\n");
					//m_pT->print(true, true, 0);
					//m_tot_weight.print(true, true, 0);
					//m_pbarycenter->print(true, true, 0);
					//printf("\n#############\n");
				}else{																				// Else it means it is an internal branch
					//printf("B\n");
					m_tot_weight+=1.;//Add to tot_weight
					*m_pbarycenter+=p*((M)(1.)/m_tot_weight);//Add to the barycenter

					if (dp.x<=(M)0. && dp.y<=(M)0. && dp.z<=(M)0.){//If cube 1
						//printf("C\n");
						if (m_pBLBTree==NULL){//If there is not yet a tree we create it
							SN<M, E> a=m_a/(M)4.;
							Point3D<M, E> np{(M)(-1.)*a, (M)(-1.)*a, (M)(-1.)*a};
							m_pBLBTree=new Oct<T, M, E>(m_a/(M)2.);
							m_pBLBTree->setPoint(*m_ppoint+np);
						}
						m_pBLBTree->insert(pT);
					}else if (dp.x>=(M)0. && dp.y<=(M)0. && dp.z<=(M)0.){//If cube 2
						//printf("D\n");
						if (m_pBRBTree==NULL){//If there is not yet a tree we create it
							SN<M, E> a=m_a/(M)4.;
							Point3D<M, E> np{a, (M)(-1.)*a, (M)(-1.)*a};
							m_pBRBTree=new Oct<T, M, E>(m_a/(M)2.);
							m_pBRBTree->setPoint(*m_ppoint+np);
						}
						m_pBRBTree->insert(pT);
					}else if (dp.x>=(M)0. && dp.y>=(M)0. && dp.z<=(M)0.){//If cube 3
						//printf("E\n");
						if (m_pBRFTree==NULL){//If there is not yet a tree we create it
							SN<M, E> a=m_a/(M)4;
							Point3D<M, E> np{a, a, (M)(-1.)*a};
							m_pBRFTree=new Oct<T, M, E>(m_a/(M)2.);
							m_pBRFTree->setPoint(*m_ppoint+np);
						}
						m_pBRFTree->insert(pT);
					}else if (dp.x<=(M)0. && dp.y>=(M)0. && dp.z<=(M)0.){//If cube 4
						//printf("F\n");
						if (m_pBLFTree==NULL){//If there is not yet a tree we create it
							SN<M, E> a=m_a/(M)4.;
							Point3D<M, E> np{(M)(-1.)*a, a, (M)(-1.)*a};
							m_pBLFTree=new Oct<T, M, E>(m_a/(M)2.);
							m_pBLFTree->setPoint(*m_ppoint+np);
						}
						m_pBLFTree->insert(pT);
					}else if (dp.x<=(M)0. && dp.y<=(M)0. && dp.z>=(M)0.){//If cube 5
						//printf("G\n");
						if (m_pTLBTree==NULL){//If there is not yet a tree we create it
							SN<M, E> a=m_a/(M)4.;
							Point3D<M, E> np{(M)(-1.)*a, (M)(-1.)*a, a};
							m_pTLBTree=new Oct<T, M, E>(m_a/(M)2.);
							m_pTLBTree->setPoint(*m_ppoint+np);
						}
						m_pTLBTree->insert(pT);
					}else if (dp.x>=(M)0. && dp.y<=(M)0. && dp.z>=(M)0.){//If cube 6
						//printf("H\n");
						if (m_pTRBTree==NULL){//If there is not yet a tree we create it
							SN<M, E> a=m_a/(M)4.;
							Point3D<M, E> np{a, (M)(-1.)*a, a};
							m_pTRBTree=new Oct<T, M, E>(m_a/(M)2.);
							m_pTRBTree->setPoint(*m_ppoint+np);
						}
						m_pTRBTree->insert(pT);
					}else if (dp.x>=(M)0. && dp.y>=(M)0. && dp.z>=(M)0.){//If cube 7
						//printf("I\n");
						if (m_pTRFTree==NULL){//If there is not yet a tree we create it
							SN<M, E> a=m_a/(M)4.;
							Point3D<M, E> np{a, a, a};
							m_pTRFTree=new Oct<T, M, E>(m_a/(M)2.);
							m_pTRFTree->setPoint(*m_ppoint+np);
						}
						m_pTRFTree->insert(pT);
					}else if (dp.x<=(M)0. && dp.y>=(M)0. && dp.z>=(M)0.){//If cube 8
						//printf("J\n");
						if (m_pTLFTree==NULL){//If there is not yet a tree we create it
							SN<M, E> a=m_a/(M)4.;
							Point3D<M, E> np{(M)(-1.)*a, a, a};
							m_pTLFTree=new Oct<T, M, E>(m_a/(M)2.);
							m_pTLFTree->setPoint(*m_ppoint+np);
						}
						m_pTLFTree->insert(pT);
					}
				}
			}else{					// Else if full

				m_tot_weight={(M)1., (E)0.};//Set the tot_weight
				*m_pbarycenter=p;//Set the barycenter

				//printf("Full\n");

				if (dp.x<=(M)0. && dp.y<=(M)0. && dp.z<=(M)0.){//If cube 1
					//printf("K\n");
					if (m_pBLBTree==NULL){//If there is not yet a tree we create it
						SN<M, E> a=m_a/(M)4.;
						Point3D<M, E> np{(M)(-1.)*a, (M)(-1.)*a, (M)(-1.)*a};
						m_pBLBTree=new Oct<T, M, E>(m_a/(M)2.);
						m_pBLBTree->setPoint(*m_ppoint+np);
					}
					m_pBLBTree->insert(pT);
				}else if (dp.x>=(M)0. && dp.y<=(M)0. && dp.z<=(M)0.){//If cube 2
					//printf("L\n");
					if (m_pBRBTree==NULL){//If there is not yet a tree we create it
						SN<M, E> a=m_a/(M)4.;
						Point3D<M, E> np{a, (M)(-1.)*a, (M)(-1.)*a};
						m_pBRBTree=new Oct<T, M, E>(m_a/(M)2.);
						m_pBRBTree->setPoint(*m_ppoint+np);
					}
					m_pBRBTree->insert(pT);
				}else if (dp.x>=(M)0. && dp.y>=(M)0. && dp.z<=(M)0.){//If cube 3
					//printf("M\n");
					if (m_pBRFTree==NULL){//If there is not yet a tree we create it
						SN<M, E> a=m_a/(M)4.;
						Point3D<M, E> np{a, a, (M)(-1.)*a};
						m_pBRFTree=new Oct<T, M, E>(m_a/(M)2.);
						m_pBRFTree->setPoint(*m_ppoint+np);
					}
					m_pBRFTree->insert(pT);
				}else if (dp.x<=(M)0. && dp.y>=(M)0. && dp.z<=(M)0.){//If cube 4
					//printf("N\n");
					if (m_pBLFTree==NULL){//If there is not yet a tree we create it
						SN<M, E> a=m_a/(M)4.;
						Point3D<M, E> np{(M)(-1.)*a, a, (M)(-1.)*a};
						m_pBLFTree=new Oct<T, M, E>(m_a/(M)2.);
						m_pBLFTree->setPoint(*m_ppoint+np);
					}
					m_pBLFTree->insert(pT);
				}else if (dp.x<=(M)0. && dp.y<=(M)0. && dp.z>=(M)0.){//If cube 5
					//printf("O\n");
					if (m_pTLBTree==NULL){//If there is not yet a tree we create it
						SN<M, E> a=m_a/(M)4.;
						Point3D<M, E> np{(M)(-1.)*a, (M)(-1.)*a, a};
						m_pTLBTree=new Oct<T, M, E>(m_a/(M)2.);
						m_pTLBTree->setPoint(*m_ppoint+np);
					}
					m_pTLBTree->insert(pT);
				}else if (dp.x>=(M)0. && dp.y<=(M)0. && dp.z>=(M)0.){//If cube 6
					//printf("P\n");
					if (m_pTRBTree==NULL){//If there is not yet a tree we create it
						SN<M, E> a=m_a/(M)4.;
						Point3D<M, E> np{a, (M)(-1.)*a, a};
						m_pTRBTree=new Oct<T, M, E>(m_a/(M)2.);
						m_pTRBTree->setPoint(*m_ppoint+np);
					}
					m_pTRBTree->insert(pT);
				}else if (dp.x>=(M)0. && dp.y>=(M)0. && dp.z>=(M)0.){//If cube 7
					//printf("Q\n");
					if (m_pTRFTree==NULL){//If there is not yet a tree we create it
						SN<M, E> a=m_a/(M)4.;
						Point3D<M, E> np{a,a,a};
						m_pTRFTree=new Oct<T, M, E>(m_a/(M)2.);
						m_pTRFTree->setPoint(*m_ppoint+np);
					}
					m_pTRFTree->insert(pT);
				}else if (dp.x<=(M)0. && dp.y>=(M)0. && dp.z>=(M)0.){//If cube 8
					//printf("Q\n");
					if (m_pTLFTree==NULL){//If there is not yet a tree we create it
						SN<M, E> a=m_a/(M)4.;
						Point3D<M, E> np{(M)(-1.)*a, a, a};
						m_pTLFTree=new Oct<T, M, E>(m_a/(M)2.);
						m_pTLFTree->setPoint(*m_ppoint+np);
					}
					m_pTLFTree->insert(pT);
				}

				// We reinsert the object already present.
				T* pT2=m_pT;
				m_pT=NULL;
				this->insert(pT2);
			}
		}
	}
	return true;
}

/*template<> bool Oct<Point3D>::insert(Point3D* ppoint){//Doesn't work for some reason.
	return true;
}*/

/*template<> bool Oct<Particle3D>::insert(Particle3D* ppart){//Doesn't work for some reason.
	if (ppart!=NULL){
		Point3D p={ppart->x, ppart->y, ppart->z};
		Point3D dp={ppart->x-m_ppoint->x, ppart->y-m_ppoint->y, ppart->z-m_ppoint->z};

		if (abs(dp.x)<=m_a/2 && abs(dp.y)<=m_a/2 && abs(dp.z)<=m_a/2){// If in the cube centered on the point.
			if (m_pT==NULL){		// If empty
				//printf("Empty\n");
				if (m_pTLFTree==NULL and m_pTRFTree==NULL and m_pBLFTree==NULL and m_pBRFTree==NULL
						and m_pTRBTree==NULL and m_pTLBTree==NULL and m_pBLBTree==NULL and m_pBRBTree==NULL){	// If the cube has no Octs under (external branch)
					m_pT=ppart;//We add in
					m_tot_weight=ppart->w;//Set the tot_weight
					*m_pbarycenter=p;//Set the barycenter
				}else{																				// Else it means it is an internal branch

					m_tot_weight+=ppart->w;//Add to tot_weight
					*m_pbarycenter+=p*(ppart->w/m_tot_weight);//Add to the barycenter

					if (dp.x<=0. && dp.y<=0. && dp.z<=0.){//If cube 1
						if (m_pBLBTree==NULL){//If there is not yet a tree we create it
							LSN a=m_a/4;
							Point3D np{a*-1,a*-1,a*-1};
							m_pBLBTree=new Oct<Particle3D>(m_a/2, *m_ppoint+np);
						}
						//m_pBLBTree->insert((Particle3D*)ppart);
					}else if (dp.x>=0. && dp.y<=0. && dp.z<=0.){//If cube 2
						if (m_pBRBTree==NULL){//If there is not yet a tree we create it
							LSN a=m_a/4;
							Point3D np{a,a*-1,a*-1};
							m_pBRBTree=new Oct<Particle3D>(m_a/2, *m_ppoint+np);
						}
						//m_pBRBTree->insert(ppart);
					}else if (dp.x>=0. && dp.y>=0. && dp.z<=0.){//If cube 3
						if (m_pBRFTree==NULL){//If there is not yet a tree we create it
							LSN a=m_a/4;
							Point3D np{a,a,a*-1};
							m_pBRFTree=new Oct<Particle3D>(m_a/2, *m_ppoint+np);
						}
						//m_pBRFTree->insert(ppart);
					}else if (dp.x<=0. && dp.y>=0. && dp.z<=0.){//If cube 4
						if (m_pBLFTree==NULL){//If there is not yet a tree we create it
							LSN a=m_a/4;
							Point3D np{a*-1,a,a*-1};
							m_pBLFTree=new Oct<Particle3D>(m_a/2, *m_ppoint+np);
						}
						//m_pBLFTree->insert(ppart);
					}else if (dp.x<=0. && dp.y<=0. && dp.z>=0.){//If cube 5
						if (m_pTLBTree==NULL){//If there is not yet a tree we create it
							LSN a=m_a/4;
							Point3D np{a*-1,a*-1,a};
							m_pTLBTree=new Oct<Particle3D>(m_a/2, *m_ppoint+np);
						}
						//m_pTLBTree->insert(ppart);
					}else if (dp.x>=0. && dp.y<=0. && dp.z>=0.){//If cube 6
						if (m_pTRBTree==NULL){//If there is not yet a tree we create it
							LSN a=m_a/4;
							Point3D np{a,a*-1,a};
							m_pTRBTree=new Oct<Particle3D>(m_a/2, *m_ppoint+np);
						}
						//m_pTRBTree->insert(ppart);
					}else if (dp.x>=0. && dp.y>=0. && dp.z>=0.){//If cube 7
						if (m_pTRFTree==NULL){//If there is not yet a tree we create it
							LSN a=m_a/4;
							Point3D np{a,a,a};
							m_pTRFTree=new Oct<Particle3D>(m_a/2, *m_ppoint+np);
						}
						//m_pTRFTree->insert(ppart);
					}else if (dp.x<=0. && dp.y>=0. && dp.z>=0.){//If cube 8
						if (m_pTLFTree==NULL){//If there is not yet a tree we create it
							LSN a=m_a/4;
							Point3D np{a*-1,a,a};
							m_pTLFTree=new Oct<Particle3D>(m_a/2, *m_ppoint+np);
						}
						//m_pTLFTree->insert(ppart);
					}
				}
			}else{					// Else if full

				m_tot_weight=1.;//Set the tot_weight
				*m_pbarycenter=p;//Set the barycenter

				//printf("Full\n");

				if (dp.x<=0. && dp.y<=0. && dp.z<=0.){//If cube 1
					if (m_pBLBTree==NULL){//If there is not yet a tree we create it
						LSN a=m_a/4;
						Point3D np{a*-1,a*-1,a*-1};
						m_pBLBTree=new Oct<Particle3D>(m_a/2, *m_ppoint+np);
					}
					//m_pBLBTree->insert(ppart);
				}else if (dp.x>=0. && dp.y<=0. && dp.z<=0.){//If cube 2
					if (m_pBRBTree==NULL){//If there is not yet a tree we create it
						LSN a=m_a/4;
						Point3D np{a,a*-1,a*-1};
						m_pBRBTree=new Oct<Particle3D>(m_a/2, *m_ppoint+np);
					}
					//m_pBRBTree->insert(ppart);
				}else if (dp.x>=0. && dp.y>=0. && dp.z<=0.){//If cube 3
					if (m_pBRFTree==NULL){//If there is not yet a tree we create it
						LSN a=m_a/4;
						Point3D np{a,a,a*-1};
						m_pBRFTree=new Oct<Particle3D>(m_a/2, *m_ppoint+np);
					}
					//m_pBRFTree->insert(ppart);
				}else if (dp.x<=0. && dp.y>=0. && dp.z<=0.){//If cube 4
					if (m_pBLFTree==NULL){//If there is not yet a tree we create it
						LSN a=m_a/4;
						Point3D np{a*-1,a,a*-1};
						m_pBLFTree=new Oct<Particle3D>(m_a/2, *m_ppoint+np);
					}
					//m_pBLFTree->insert(ppart);
				}else if (dp.x<=0. && dp.y<=0. && dp.z>=0.){//If cube 5
					if (m_pTLBTree==NULL){//If there is not yet a tree we create it
						LSN a=m_a/4;
						Point3D np{a*-1,a*-1,a};
						m_pTLBTree=new Oct<Particle3D>(m_a/2, *m_ppoint+np);
					}
					//m_pTLBTree->insert(ppart);
				}else if (dp.x>=0. && dp.y<=0. && dp.z>=0.){//If cube 6
					if (m_pTRBTree==NULL){//If there is not yet a tree we create it
						LSN a=m_a/4;
						Point3D np{a,a*-1,a};
						m_pTRBTree=new Oct<Particle3D>(m_a/2, *m_ppoint+np);
					}
					//m_pTRBTree->insert(ppart);
				}else if (dp.x>=0. && dp.y>=0. && dp.z>=0.){//If cube 7
					if (m_pTRFTree==NULL){//If there is not yet a tree we create it
						LSN a=m_a/4;
						Point3D np{a,a,a};
						m_pTRFTree=new Oct<Particle3D>(m_a/2, *m_ppoint+np);
					}
					//m_pTRFTree->insert(ppart);
				}else if (dp.x<=0. && dp.y>=0. && dp.z>=0.){//If cube 8
					if (m_pTLFTree==NULL){//If there is not yet a tree we create it
						LSN a=m_a/4;
						Point3D np{a*-1,a,a};
						m_pTLFTree=new Oct<Particle3D>(m_a/2, *m_ppoint+np);
					}
					//m_pTLFTree->insert(ppart);
				}

				// We reinsert the object already present.
				Particle3D* pT2=m_pT;
				m_pT=NULL;
				//this->insert(pT2);
			}
		}
	}
	return true;
}*/

template <typename T, typename M, typename E> void Oct<T, M, E>::recalculate() {
	std::unordered_set<T*> pelements=this->getPElements();

	this->empty();

	for (T* pelement : pelements){
		this->insert(pelement);
	}
}

template <typename T, typename M, typename E> bool Oct<T, M, E>::empty() {
	for (Oct<T, M, E>* ptree : this->getPTrees()){
		delete ptree;
	}

	m_pTLFTree=NULL;
	m_pTRFTree=NULL;
	m_pBLFTree=NULL;
	m_pBRFTree=NULL;
	m_pTLBTree=NULL;
	m_pTRBTree=NULL;
	m_pBLBTree=NULL;
	m_pBRBTree=NULL;

	*m_pbarycenter=*m_ppoint;
	m_tot_weight={(M)0., (E)0};
	m_pT=NULL;

	return true;
}

template <typename T, typename M, typename E> void Oct<T, M, E>::find(const T& t, std::unordered_set<Oct<T, M, E>*>& pocts) {
	Point3D<M, E> p={t.x, t.y, {0, 0}};

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
}

//Useless
/*template <typename T> void Oct<T>::computeInverseSquareLawResultant(const T& t, Vector3D& v) const {
	if (&t!=m_pT){
		Point3D p={t.x, t.y, t.z};

		LSN s=this->m_a;

		LSN d=getDistance(p, *m_pbarycenter);
		LSN alpha=s/d;
		//std::cout<<"\n"<<alpha.to_string()<<"\n";

		if (alpha>=m_ALPHA){
			Vector3D* pdv=new Vector3D(p, *m_pbarycenter);
			LSN nb=t.w*this->m_tot_weight;
			LSN nb2=nb/pow(d, 2);
			pdv->setNorm(nb2);

			v+=*pdv;
		}else{
			if (m_pBLBTree!=NULL){
				m_pBLBTree->computeInverseSquareLawResultant(t, v);
			}
			if (m_pBRBTree!=NULL){
				m_pBRBTree->computeInverseSquareLawResultant(t, v);
			}
			if (m_pBRFTree!=NULL){
				m_pBRFTree->computeInverseSquareLawResultant(t, v);
			}
			if (m_pBLFTree!=NULL){
				m_pBLFTree->computeInverseSquareLawResultant(t, v);
			}
			if (m_pTLBTree!=NULL){
				m_pTLBTree->computeInverseSquareLawResultant(t, v);
			}
			if (m_pTRBTree!=NULL){
				m_pTRBTree->computeInverseSquareLawResultant(t, v);
			}
			if (m_pTRFTree!=NULL){
				m_pTRFTree->computeInverseSquareLawResultant(t, v);
			}
			if (m_pTLFTree!=NULL){
				m_pTLFTree->computeInverseSquareLawResultant(t, v);
			}
		}
	}
}*/

/*
 * Stores the octs that are to be considered given alpha.
 */
/*template <typename T> std::unordered_set<T*> Oct<T>::find(const Point3D& point) {
	;
}*/

template <typename T, typename M, typename E> T* Oct<T, M, E>::search(const Point3D<M, E>* ppoint) const {
	T* pT=NULL;

	if (ppoint!=NULL){
		long double delta_x=(long double)(ppoint->x-m_ppoint->x);
		long double delta_y=(long double)(ppoint->y-m_ppoint->y);
		long double delta_z=(long double)(ppoint->z-m_ppoint->z);

		if (abs(delta_x)<m_a/2 && abs(delta_y)<m_a/2 && abs(delta_z)<m_a/2){//If in the square centered on the point.

			if (m_pT!=NULL){// This means it is a square of the smallest size possible.
				pT=m_pT;
			}else{
				if (m_pTLFTree!=NULL){//Cube 1
					pT=m_pTLFTree->search(ppoint);
				}
				if (pT==NULL){//If it hasn't been initiated by the precedent line
					if (m_pTRFTree!=NULL){//Cube 2
						pT=m_pTRFTree->search(ppoint);
					}
					if (pT==NULL){//If it hasn't been initiated by the precedent line
						if (m_pBLFTree!=NULL){//Cube 3
							pT=m_pBLFTree->search(ppoint);
						}
						if (pT==NULL){//If it hasn't been initiated by the precedent line
							if (m_pBRFTree!=NULL){//Cube 4
								pT=m_pBRFTree->search(ppoint);
							}
							if (pT==NULL){//If it hasn't been initiated by the precedent line
								if (m_pTLBTree!=NULL){//Cube 5
									pT=m_pTLBTree->search(ppoint);
								}
								if (pT==NULL){//If it hasn't been initiated by the precedent line
									if (m_pTRBTree!=NULL){//Cube 6
										pT=m_pTRBTree->search(ppoint);
									}
									if (pT==NULL){//If it hasn't been initiated by the precedent line
										if (m_pBLBTree!=NULL){//Cube 7
											pT=m_pBLBTree->search(ppoint);
										}
										if (pT==NULL){//If it hasn't been initiated by the precedent line
											if (m_pBRBTree!=NULL){//Cube 8
												pT=m_pBRBTree->search(ppoint);
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



template <typename T, typename M, typename E> std::string Oct<T, M, E>::to_string(const bool& spread, const bool& full_info, const unsigned char& indent) const {
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
	mes+="|*|";
	//printf("AAAAAA123\n");
	std::cout << m_ppoint << "\n";
	mes+=m_ppoint->to_string(false, false, 0);			//Point ERROR
	mes+="|*|";
	//printf("AAAAAA124\n");
	mes+=m_pbarycenter->to_string(false, false, 0);		//Barycenter
	mes+="|*|";
	//printf("AAAAAA125\n");
	std::stringstream ss2;
	ss2 << m_pT;
	mes+=ss2.str();
	mes+="|*|";
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
		mes+=(m_pBLBTree==NULL)?nulll : m_pBLBTree->to_string(spread, full_info, indent+1);
		mes+=to_stringTabs(indent+1);
		//printf("AAAAAA14\n");
		mes+=(m_pBRBTree==NULL)?nulll : m_pBRBTree->to_string(spread, full_info, indent+1);
		mes+=to_stringTabs(indent+1);
		//printf("AAAAAA15\n");
		mes+=(m_pBRFTree==NULL)?nulll : m_pBRFTree->to_string(spread, full_info, indent+1);
		mes+=to_stringTabs(indent+1);
		//printf("AAAAAA16\n");
		mes+=(m_pBLFTree==NULL)?nulll : m_pBLFTree->to_string(spread, full_info, indent+1);
		mes+=to_stringTabs(indent+1);
		//printf("AAAAAA17\n");
		mes+=(m_pTLBTree==NULL)?nulll : m_pTLBTree->to_string(spread, full_info, indent+1);
		mes+=to_stringTabs(indent+1);
		//printf("AAAAAA18\n");
		mes+=(m_pTRBTree==NULL)?nulll : m_pTRBTree->to_string(spread, full_info, indent+1);
		mes+=to_stringTabs(indent+1);
		//printf("AAAAAA19\n");
		mes+=(m_pTRFTree==NULL)?nulll : m_pTRFTree->to_string(spread, full_info, indent+1);
		mes+=to_stringTabs(indent+1);
		//printf("AAAAAA20\n");
		mes+=(m_pTLFTree==NULL)?nulll : m_pTLFTree->to_string(spread, full_info, indent+1);
		//mes+=((spread)?to_stringTabs(indent+1) : "");


		mes.erase(mes.length()-2);
		mes+=((spread)?"\n" : "");
		mes+=((spread)?to_stringTabs(indent+1) : "");
		mes+=")";
	}

	return mes;
}

template <typename T, typename M, typename E> void Oct<T, M, E>::print(const bool& spread, const bool& full_info, const unsigned char& indent) const {
	printTabs(indent);
	std::cout << this->to_string(spread, full_info, indent);
}


#endif /* OCT_H_ */
