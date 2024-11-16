/*
 * Oct.h
 *
 *  Created on: 20 août 2024
 *      Author: esn
 */

#ifndef OCT_H_
#define OCT_H_


#include <iostream>
#include <cmath>
#include <unordered_set>
//#include "Particle3D.h"
#include "Point3D.h"
#include "../utilities/Printable.h"

/*
 * #######
 *  Oct :)
 * #######
 * Can contain any object that has x, y, z
 */
template <typename T> class Oct : public Printable {
protected:
	Point3D* m_ppoint;					// The center of the zone.
	Point3D* m_pbarycenter;				// The center of mass given the repartition of the WeightedPoints in the zone.
	bool m_delppoint;					// If the point should be deleted.

	LSN m_a;							// Length of the zone's border.
	LSN m_tot_weight;					// Total weight contained in this Oct.

	T* m_pT;							// The content of this square (NULL if nothing).
	//Particle3D* m_pparticle;			// The content of this node.

	Oct* m_pTLFTree;					// Top Left corner : is NULL if nothing
	Oct* m_pTRFTree;					// Top Right corner : is NULL if nothing
	Oct* m_pBLFTree;					// Bottom Left corner : is NULL if nothing
	Oct* m_pBRFTree;					// Bottom Right corner : is NULL if nothing
	Oct* m_pTLBTree;					// Top Left corner : is NULL if nothing
	Oct* m_pTRBTree;					// Top Right corner : is NULL if nothing
	Oct* m_pBLBTree;					// Bottom Left corner : is NULL if nothing
	Oct* m_pBRBTree;					// Bottom Right corner : is NULL if nothing

	static unsigned int m_NB_OCTS;		// Keeps track of the number of Octs created.

public:
	static LSN m_LIM_A;					// This indicates the limit at which we stop subdividing (useless)
	static float m_ALPHA;				// The threshold m_ALPHA=a/d (with a being the width of the zone and d the distance from the center of the quad) indicates at which point we can consider an agglomeration of bodies as one.

	//Oct();
	/*
	 * Constructor1
	 * @param a{The side's lenght of the area}
	 * @param point{The center on which is centered the Oct's area}
	 */
	Oct(const LSN& a, const Point3D& p={{0,0},{0,0},{0,0}});
	Oct(const LSN& a, Point3D* ppoint);
	virtual ~Oct();

	LSN getA() const;
	void setA(const LSN& a);
	unsigned int getNB_OCTS() const;
	//float getAlpha();
	//void setAlpha(float& alpha=0.5);
	std::unordered_set<Oct<T>*> getPTrees();			//Returns all the trees under, contained by this tree.
	std::unordered_set<T*> getPElements() const;		//Returns all the elements contained in the tree.
	std::unordered_set<T*> getPNeighbors(T* pelement) const;		//Returns all the neighbors.

	bool insert(T* pT);
	void find(const T& t, std::unordered_set<Oct<T>*>& pquads);// It adds to the list of Octs in parameter accordingly to the ratio m_ALPHA
	void computeInverseSquareLawResultant(const T& t, Vector3D& v) const;
	//std::unordered_set<T*> find(const Point3D& point);
	T* search(Point3D* ppoint) const;
	void recalculate();
	bool empty();

	std::string to_string(const bool& spread=false, const bool& full_info=false, const unsigned int& indent=0) const;// :)
	void print(const bool& spread=false, const bool& full_info=false, const unsigned int& indent=0) const;// :)
};
template <typename T> unsigned int Oct<T>::m_NB_OCTS=0;
template <typename T> LSN Oct<T>::m_LIM_A={1, 0};
template <typename T> float Oct<T>::m_ALPHA=0.5;


/*
 * Constructor0
 */
/*template <typename T> Oct<T>::Oct() {
	m_ppoint=new Point3D();
	m_pbarycenter=new Point3D(*m_ppoint);
	m_delppoint=true;

	m_a=0;
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

	m_NB_QUADS++;
}*/


/*
 * Constructor1
 */
template <typename T> Oct<T>::Oct(const LSN& a, const Point3D& point) {
	m_ppoint=new Point3D(point);
	m_pbarycenter=new Point3D(*m_ppoint);
	m_delppoint=true;

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
template <typename T> Oct<T>::Oct(const LSN& a, Point3D* ppoint) {
	m_ppoint=ppoint;
	m_pbarycenter=new Point3D(*m_ppoint);
	m_delppoint=false;

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

template <typename T> Oct<T>::~Oct() {
	if (m_delppoint){
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

template <typename T> LSN Oct<T>::getA() const {
	return m_a;
}

template <typename T> void Oct<T>::setA(const LSN& a){
	m_a=a;

}

template <typename T> unsigned int Oct<T>::getNB_OCTS() const {
	return m_NB_OCTS;
}

/*
 * Returns all the trees under, contained by this tree.
 */
template <typename T> std::unordered_set<Oct<T>*> Oct<T>::getPTrees() {
	std::unordered_set<Oct*> ptrees;
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

template <typename T> std::unordered_set<T*> Oct<T>::getPElements() const {
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

template <typename T> std::unordered_set<T*> Oct<T>::getPNeighbors(T* pelement) const {
	static std::unordered_set<T*> neighbors;

	printf("AB\n");

	if (m_a/getDistance(*m_ppoint, *pelement)<=(long double)m_ALPHA){
		printf("AC\n");
		if (m_pT!=NULL){
			neighbors.insert(m_pT);
		}else{
			neighbors.insert(new T(m_ppoint->getX(), m_ppoint->getY(), m_ppoint->getZ()));
		}
	}else{
		printf("AD\n");
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

template <typename T> bool Oct<T>::insert(T* pT) {
	if (pT!=NULL){
		Point3D p={pT->x, pT->y, pT->z};
		Point3D dp={pT->x-m_ppoint->x, pT->y-m_ppoint->y, pT->z-m_ppoint->z};

		if (abs(dp.x)<=m_a/2 && abs(dp.y)<=m_a/2 && abs(dp.z)<=m_a/2){// If in the cube centered on the point.
			if (m_pT==NULL){		// If empty
				//printf("Empty\n");
				if (m_pTLFTree==NULL and m_pTRFTree==NULL and m_pBLFTree==NULL and m_pBRFTree==NULL
						and m_pTRBTree==NULL and m_pTLBTree==NULL and m_pBLBTree==NULL and m_pBRBTree==NULL){	// If the cube has no Octs under (external branch)
					m_pT=pT;//We add in
					m_tot_weight=1.;//Set the tot_weight
					*m_pbarycenter=p;//Set the barycenter
				}else{																				// Else it means it is an internal branch
					m_tot_weight+=1.;//Add to tot_weight
					*m_pbarycenter+=p*(1./m_tot_weight);//Add to the barycenter

					if (dp.x<=0. && dp.y<=0. && dp.z<=0.){//If cube 1
						//printf("Square1\n");
						if (m_pBLBTree==NULL){//If there is not yet a tree we create it
							LSN a=m_a/4;
							Point3D np{a*-1,a*-1,a*-1};
							m_pBLBTree=new Oct<T>(m_a/2, *m_ppoint+np);
						}
						m_pBLBTree->insert(pT);
					}else if (dp.x>=0. && dp.y<=0. && dp.z<=0.){//If cube 2
						//printf("Square2\n");
						if (m_pBRBTree==NULL){//If there is not yet a tree we create it
							LSN a=m_a/4;
							Point3D np{a,a*-1,a*-1};
							m_pBRBTree=new Oct<T>(m_a/2, *m_ppoint+np);
						}
						m_pBRBTree->insert(pT);
					}else if (dp.x>=0. && dp.y>=0. && dp.z<=0.){//If cube 3
						//printf("Square3\n");
						if (m_pBRFTree==NULL){//If there is not yet a tree we create it
							LSN a=m_a/4;
							Point3D np{a,a,a*-1};
							m_pBRFTree=new Oct<T>(m_a/2, *m_ppoint+np);
						}
						m_pBRFTree->insert(pT);
					}else if (dp.x<=0. && dp.y>=0. && dp.z<=0.){//If cube 4
						//printf("Square4\n");
						if (m_pBLFTree==NULL){//If there is not yet a tree we create it
							LSN a=m_a/4;
							Point3D np{a*-1,a,a*-1};
							m_pBLFTree=new Oct<T>(m_a/2, *m_ppoint+np);
						}
						m_pBLFTree->insert(pT);
					}else if (dp.x<=0. && dp.y<=0. && dp.z>=0.){//If cube 5
						//printf("Square1\n");
						if (m_pTLBTree==NULL){//If there is not yet a tree we create it
							LSN a=m_a/4;
							Point3D np{a*-1,a*-1,a};
							m_pTLBTree=new Oct<T>(m_a/2, *m_ppoint+np);
						}
						m_pTLBTree->insert(pT);
					}else if (dp.x>=0. && dp.y<=0. && dp.z>=0.){//If cube 6
						//printf("Square2\n");
						if (m_pTRBTree==NULL){//If there is not yet a tree we create it
							LSN a=m_a/4;
							Point3D np{a,a*-1,a};
							m_pTRBTree=new Oct<T>(m_a/2, *m_ppoint+np);
						}
						m_pTRBTree->insert(pT);
					}else if (dp.x>=0. && dp.y>=0. && dp.z>=0.){//If cube 7
						//printf("Square3\n");
						if (m_pTRFTree==NULL){//If there is not yet a tree we create it
							LSN a=m_a/4;
							Point3D np{a,a,a};
							m_pTRFTree=new Oct<T>(m_a/2, *m_ppoint+np);
						}
						m_pTRFTree->insert(pT);
					}else if (dp.x<=0. && dp.y>=0. && dp.z>=0.){//If cube 8
						//printf("Square4\n");
						if (m_pTLFTree==NULL){//If there is not yet a tree we create it
							LSN a=m_a/4;
							Point3D np{a*-1,a,a};
							m_pTLFTree=new Oct<T>(m_a/2, *m_ppoint+np);
						}
						m_pTLFTree->insert(pT);
					}
				}
			}else{					// Else if full

				m_tot_weight=1.;//Set the tot_weight
				*m_pbarycenter=p;//Set the barycenter

				//printf("Full\n");

				if (dp.x<=0. && dp.y<=0. && dp.z<=0.){//If cube 1
					//printf("Square1\n");
					if (m_pBLBTree==NULL){//If there is not yet a tree we create it
						LSN a=m_a/4;
						Point3D np{a*-1,a*-1,a*-1};
						m_pBLBTree=new Oct<T>(m_a/2, *m_ppoint+np);
					}
					m_pBLBTree->insert(pT);
				}else if (dp.x>=0. && dp.y<=0. && dp.z<=0.){//If cube 2
					//printf("Square2\n");
					if (m_pBRBTree==NULL){//If there is not yet a tree we create it
						LSN a=m_a/4;
						Point3D np{a,a*-1,a*-1};
						m_pBRBTree=new Oct<T>(m_a/2, *m_ppoint+np);
					}
					m_pBRBTree->insert(pT);
				}else if (dp.x>=0. && dp.y>=0. && dp.z<=0.){//If cube 3
					//printf("Square3\n");
					if (m_pBRFTree==NULL){//If there is not yet a tree we create it
						LSN a=m_a/4;
						Point3D np{a,a,a*-1};
						m_pBRFTree=new Oct<T>(m_a/2, *m_ppoint+np);
					}
					m_pBRFTree->insert(pT);
				}else if (dp.x<=0. && dp.y>=0. && dp.z<=0.){//If cube 4
					//printf("Square4\n");
					if (m_pBLFTree==NULL){//If there is not yet a tree we create it
						LSN a=m_a/4;
						Point3D np{a*-1,a,a*-1};
						m_pBLFTree=new Oct<T>(m_a/2, *m_ppoint+np);
					}
					m_pBLFTree->insert(pT);
				}else if (dp.x<=0. && dp.y<=0. && dp.z>=0.){//If cube 5
					//printf("Square1\n");
					if (m_pTLBTree==NULL){//If there is not yet a tree we create it
						LSN a=m_a/4;
						Point3D np{a*-1,a*-1,a};
						m_pTLBTree=new Oct<T>(m_a/2, *m_ppoint+np);
					}
					m_pTLBTree->insert(pT);
				}else if (dp.x>=0. && dp.y<=0. && dp.z>=0.){//If cube 6
					//printf("Square2\n");
					if (m_pTRBTree==NULL){//If there is not yet a tree we create it
						LSN a=m_a/4;
						Point3D np{a,a*-1,a};
						m_pTRBTree=new Oct<T>(m_a/2, *m_ppoint+np);
					}
					m_pTRBTree->insert(pT);
				}else if (dp.x>=0. && dp.y>=0. && dp.z>=0.){//If cube 7
					//printf("Square3\n");
					if (m_pTRFTree==NULL){//If there is not yet a tree we create it
						LSN a=m_a/4;
						Point3D np{a,a,a};
						m_pTRFTree=new Oct<T>(m_a/2, *m_ppoint+np);
					}
					m_pTRFTree->insert(pT);
				}else if (dp.x<=0. && dp.y>=0. && dp.z>=0.){//If cube 8
					//printf("Square4\n");
					if (m_pTLFTree==NULL){//If there is not yet a tree we create it
						LSN a=m_a/4;
						Point3D np{a*-1,a,a};
						m_pTLFTree=new Oct<T>(m_a/2, *m_ppoint+np);
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

template <typename T> void Oct<T>::recalculate() {
	std::unordered_set<T*> pelements=this->getPElements();

	this->empty();

	for (Oct<T>* pelement : pelements){
		this->insert(pelement);
	}
}

template <typename T> bool Oct<T>::empty() {
	for (Oct<T>* ptree : this->getPTrees()){
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
	m_tot_weight=0.;
	m_pT=NULL;

	return true;
}

/*template<> bool Oct<Particle3D>::insert(Particle3D* ppart){//Doesn't work for some reason.
	if (ppart!=NULL){
		Point3D p={ppart->x, ppart->y, ppart->z};
		Point3D dp={ppart->x-m_ppoint->x, ppart->y-m_ppoint->y, ppart->z-m_ppoint->z};

		if (abs(dp.x)<=m_a/2 && abs(dp.y)<=m_a/2 && abs(dp.z)<=m_a/2){// If in the cube centered on the point.
			if (m_pT==NULL){		// If empty
				printf("Empty\n");
				if (m_pBLFTree==NULL and m_pBRFTree==NULL and m_pTRFTree==NULL and m_pTLFTree==NULL
						and m_pBLBTree==NULL and m_pBRBTree==NULL and m_pTRBTree==NULL and m_pTLBTree==NULL){	// If the square has no Quads under (external branch)
					m_pT=ppart;//We add in
					m_tot_weight=ppart->w;//Set the tot_weight
					*m_pbarycenter=p;//Set the barycenter
				}else{																				// Else it means it is an internal branch

					m_tot_weight+=ppart->w;//Add to tot_weight
					//LSN k=ppart->w/m_tot_weight;
					if (m_tot_weight!=LSN{0,0}){
						*m_pbarycenter+=p*(ppart->w/m_tot_weight);//Add to the barycenter
					}else{
						*m_pbarycenter=*m_ppoint;//Set the barycenter to the geometric center
					}


					if (dp.x<=0. && dp.y<=0. && dp.z<=0.){//If cube 1
						//printf("Square1\n");
						if (m_pBLBTree==NULL){//If there is not yet a tree we create it
							LSN a=m_a/4;
							Point3D np{m_a*(-1/4),m_a*(-1/4),m_a*(-1/4)};
							m_pBLBTree=new Oct<Particle3D>(m_a/2, *m_ppoint+np);
						}
						m_pBLBTree->insert(ppart);
					}else if (dp.x>0. && dp.y<0. && dp.z<0.){//If cube 2
						//printf("Square2\n");
						if (m_pBRBTree==NULL){//If there is not yet a tree we create it
							LSN a=m_a/4;
							Point3D np{m_a/4,m_a*(-1/4),m_a*(-1/4)};
							m_pBRBTree=new Oct<Particle3D>(m_a/2, *m_ppoint+np);
						}
						m_pBRBTree->insert(ppart);
					}else if (dp.x>0. && dp.y>0. && dp.z<0.){//If cube 3
						//printf("Square3\n");
						if (m_pBRFTree==NULL){//If there is not yet a tree we create it
							LSN a=m_a/4;
							Point3D np{m_a/4,m_a/4,m_a*(-1/4)};
							m_pBRFTree=new Oct<Particle3D>(m_a/2, *m_ppoint+np);
						}
						m_pBRFTree->insert(ppart);
					}else if (dp.x<0. && dp.y>0. && dp.z<0.){//If cube 4
						//printf("Square4\n");
						if (m_pBLFTree==NULL){//If there is not yet a tree we create it
							LSN a=m_a/4;
							Point3D np{m_a*(-1/4),m_a/4,m_a*(-1/4)};
							m_pBLFTree=new Oct<Particle3D>(m_a/2, *m_ppoint+np);
						}
						m_pBLFTree->insert(ppart);
					}else if (dp.x<0. && dp.y<0. && dp.z>0.){//If cube 5
						//printf("Square1\n");
						if (m_pTLBTree==NULL){//If there is not yet a tree we create it
							LSN a=m_a/4;
							Point3D np{m_a*(-1/4),m_a*(-1/4),m_a/4};
							m_pTLBTree=new Oct<Particle3D>(m_a/2, *m_ppoint+np);
						}
						m_pTLBTree->insert(ppart);
					}else if (dp.x>0. && dp.y<0. && dp.z>0.){//If cube 6
						//printf("Square2\n");
						if (m_pTRBTree==NULL){//If there is not yet a tree we create it
							LSN a=m_a/4;
							Point3D np{m_a/4,m_a*(-1/4),m_a/4};
							m_pTRBTree=new Oct<Particle3D>(m_a/2, *m_ppoint+np);
						}
						m_pTRBTree->insert(ppart);
					}else if (dp.x>0. && dp.y>0. && dp.z>0.){//If cube 7
						//printf("Square3\n");
						if (m_pTRFTree==NULL){//If there is not yet a tree we create it
							LSN a=m_a/4;
							Point3D np{m_a/4,m_a/4,m_a/4};
							m_pTRFTree=new Oct<Particle3D>(m_a/2, *m_ppoint+np);
						}
						m_pTRFTree->insert(ppart);
					}else if (dp.x<0. && dp.y>0. && dp.z>0.){//If cube 8
						//printf("Square4\n");
						if (m_pTLFTree==NULL){//If there is not yet a tree we create it
							LSN a=m_a/4;
							Point3D np{m_a*(-1/4),m_a/4,m_a/4};
							m_pTLFTree=new Oct<Particle3D>(m_a/2, *m_ppoint+np);
						}
						m_pTLFTree->insert(ppart);
					}
				}
			}else{					// Else if full

				m_tot_weight=ppart->w;//+m_pT->w//Set the tot_weight
				*m_pbarycenter=p;//Set the barycenter

				printf("Full\n");

				if (dp.x<=0. && dp.y<=0. && dp.z<=0.){//If cube 1
					//printf("Square1\n");
					if (m_pBLBTree==NULL){//If there is not yet a tree we create it
							LSN a=m_a/4;
						Point3D np{m_a*(-1/4),m_a*(-1/4),{0, 0}};
						m_pBLBTree=new Oct<Particle3D>(m_a/2, *m_ppoint+np);
					}
					m_pBLBTree->insert(ppart);
				}else if (dp.x>0. && dp.y<0. && dp.z<0.){//If cube 2
					//printf("Square2\n");
					if (m_pBRBTree==NULL){//If there is not yet a tree we create it
							LSN a=m_a/4;
						Point3D np{m_a/4,m_a*(-1/4),{0, 0}};
						m_pBRBTree=new Oct<Particle3D>(m_a/2, *m_ppoint+np);
					}
					m_pBRBTree->insert(ppart);
				}else if (dp.x>0. && dp.y>0. && dp.z<0.){//If cube 3
					//printf("Square3\n");
					if (m_pBRFTree==NULL){//If there is not yet a tree we create it
							LSN a=m_a/4;
						Point3D np{m_a/4,m_a/4,{0, 0}};
						m_pBRFTree=new Oct<Particle3D>(m_a/2, *m_ppoint+np);
					}
					m_pBRFTree->insert(ppart);
				}else if (dp.x<0. && dp.y>0. && dp.z<0.){//If cube 4
					//printf("Square4\n");
					if (m_pBLFTree==NULL){//If there is not yet a tree we create it
							LSN a=m_a/4;
						Point3D np{m_a*(-1/4),m_a/4,{0, 0}};
						m_pBLFTree=new Oct<Particle3D>(m_a/2, *m_ppoint+np);
					}
					m_pBLFTree->insert(ppart);
				}else if (dp.x<0. && dp.y<0. && dp.z>0.){//If cube 5
					//printf("Square1\n");
					if (m_pTLBTree==NULL){//If there is not yet a tree we create it
							LSN a=m_a/4;
						Point3D np{m_a*(-1/4),m_a*(-1/4),m_a/4};
						m_pTLBTree=new Oct<Particle3D>(m_a/2, *m_ppoint+np);
					}
					m_pTLBTree->insert(ppart);
				}else if (dp.x>0. && dp.y<0. && dp.z>0.){//If cube 6
					//printf("Square2\n");
					if (m_pTRBTree==NULL){//If there is not yet a tree we create it
							LSN a=m_a/4;
						Point3D np{m_a/4,m_a*(-1/4),m_a/4};
						m_pTRBTree=new Oct<Particle3D>(m_a/2, *m_ppoint+np);
					}
					m_pTRBTree->insert(ppart);
				}else if (dp.x>0. && dp.y>0. && dp.z>0.){//If cube 7
					//printf("Square3\n");
					if (m_pTRFTree==NULL){//If there is not yet a tree we create it
							LSN a=m_a/4;
						Point3D np{m_a/4,m_a/4,m_a/4};
						m_pTRFTree=new Oct<Particle3D>(m_a/2, *m_ppoint+np);
					}
					m_pTRFTree->insert(ppart);
				}else if (dp.x<0. && dp.y>0. && dp.z>0.){//If cube 8
					//printf("Square4\n");
					if (m_pTLFTree==NULL){//If there is not yet a tree we create it
							LSN a=m_a/4;
						Point3D np{m_a*(-1/4),m_a/4,m_a/4};
						m_pTLFTree=new Oct<Particle3D>(m_a/2, *m_ppoint+np);
					}
					m_pTLFTree->insert(ppart);
				}
				// We redistribute the object already present in the Quad.
				Particle3D* pT2=m_pT;
				m_pT=NULL;
				this->insert(pT2);
			}
		}
	}
	return true;
}*/

template <typename T> void Oct<T>::find(const T& t, std::unordered_set<Oct<T>*>& pquads) {
	Point3D p={t.x, t.y, {0, 0}};

	LSN s=this->m_a;
	LSN d=getDistance(p, *m_pbarycenter);
	LSN alpha=s/d;
	//std::cout<<"\n"<<alpha.to_string()<<"\n";

	if (alpha>=m_ALPHA){
		pquads.insert(this);
	}else{
		if (m_pTLBTree!=NULL){
			m_pTLBTree->find(t, pquads);
		}
		if (m_pTRBTree!=NULL){
			m_pTRBTree->find(t, pquads);
		}
		if (m_pBLBTree!=NULL){
			m_pBLBTree->find(t, pquads);
		}
		if (m_pBRBTree!=NULL){
			m_pBRBTree->find(t, pquads);
		}
		if (m_pTLFTree!=NULL){
			m_pTLFTree->find(t, pquads);
		}
		if (m_pTRFTree!=NULL){
			m_pTRFTree->find(t, pquads);
		}
		if (m_pBLFTree!=NULL){
			m_pBLFTree->find(t, pquads);
		}
		if (m_pBRFTree!=NULL){
			m_pBRFTree->find(t, pquads);
		}
	}
}

template <typename T> void Oct<T>::computeInverseSquareLawResultant(const T& t, Vector3D& v) const {
	if (&t!=m_pT){
		Point3D p={t.x, t.y, t.z};

		LSN s=this->m_a;

		LSN d=getDistance(p, *m_pbarycenter);
		LSN alpha=s/d;
		//std::cout<<"\n"<<alpha.to_string()<<"\n";

		if (alpha>=m_ALPHA){
			Vector3D* pdv=new Vector3D(p, *m_pbarycenter);//ERROR
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
}

/*
 * Stores the octs that are to be considered given alpha.
 */
/*template <typename T> std::unordered_set<T*> Oct<T>::find(const Point3D& point) {
	;
}*/

template <typename T> T* Oct<T>::search(Point3D* ppoint) const {
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



template <typename T> std::string Oct<T>::to_string(const bool& spread, const bool& full_info, const unsigned int& indent) const {
	std::string mes=((spread)?"\n" : "");
	mes+=((spread)?to_stringTabs(indent) : "");
	//mes+="QUAD";

	if (full_info){
		mes+="OCT[";
		std::stringstream ss;
		ss << this;
		mes+=ss.str();
		mes+="]:";
		mes+=m_a.to_string();						//a
		mes+=", ";
		mes+=m_ppoint->to_string(false, false);		//Point
		mes+=", ";
		mes+=m_pbarycenter->to_string(false, false);		//Barycenter
		mes+=", ";
		mes+=(m_pT==NULL) ? "NULL" : std::to_string((unsigned long long)(void**)m_pT);
		mes+=", ";
		mes+="w:" + std::to_string(m_tot_weight.to_long_double());
		mes+="]";
		mes+=((spread)?"\n" : "");
	}

	mes+=((spread)?to_stringTabs(indent+1) : "");
	//mes+=(m_pT==NULL) ? "NULL" : std::to_string((unsigned long long)(void**)m_pT);
	//mes+=", ";
	//mes+=std::to_string(m_tot_weight.to_long_double());
	//mes+=", ";
	if (full_info){
		mes+="(";
		//std::string nulll=to_stringTabs(indent+1);
		std::string nulll=((spread)?"\n" : "");
		nulll+=((spread)?to_stringTabs(indent+1) : "");
		nulll+="NULL";
		nulll+=", ";
		//nulll+=((spread)?"\n" : "");

		mes+=(m_pBLBTree==NULL)?nulll : m_pBLBTree->to_string(spread, full_info, indent+1);
		mes+=((spread)?to_stringTabs(indent+1) : "");
		mes+=(m_pBRBTree==NULL)?nulll : m_pBRBTree->to_string(spread, full_info, indent+1);
		mes+=((spread)?to_stringTabs(indent+1) : "");
		mes+=(m_pBRFTree==NULL)?nulll : m_pBRFTree->to_string(spread, full_info, indent+1);
		mes+=((spread)?to_stringTabs(indent+1) : "");
		mes+=(m_pBLFTree==NULL)?nulll : m_pBLFTree->to_string(spread, full_info, indent+1);
		mes+=((spread)?to_stringTabs(indent+1) : "");
		mes+=(m_pTLBTree==NULL)?nulll : m_pTLBTree->to_string(spread, full_info, indent+1);
		mes+=((spread)?to_stringTabs(indent+1) : "");
		mes+=(m_pTRBTree==NULL)?nulll : m_pTRBTree->to_string(spread, full_info, indent+1);
		mes+=((spread)?to_stringTabs(indent+1) : "");
		mes+=(m_pTRFTree==NULL)?nulll : m_pTRFTree->to_string(spread, full_info, indent+1);
		mes+=((spread)?to_stringTabs(indent+1) : "");
		mes+=(m_pTLFTree==NULL)?nulll : m_pTLFTree->to_string(spread, full_info, indent+1);
		//mes+=((spread)?to_stringTabs(indent+1) : "");


		mes.erase(mes.length()-2);
		mes+=((spread)?"\n" : "");
		mes+=((spread)?to_stringTabs(indent+1) : "");
		mes+=")";
	}

	return mes;
}

template <typename T> void Oct<T>::print(const bool& spread, const bool& full_info, const unsigned int& indent) const {
	printTabs(indent);
	std::cout << this->to_string(spread, full_info, indent);
}


#endif /* OCT_H_ */
