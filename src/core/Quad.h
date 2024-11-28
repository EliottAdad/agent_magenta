/*
 * Quad.h
 *
 *  Created on: 18 mai 2024
 *      Author: esn
 */

#ifndef QUAD_H_
#define QUAD_H_

#include <cstdio>
//#include <cmath>
#include <unordered_set>
#include "Particle3D.h"
#include "Point3D.h"
#include "../utilities/Printable.h"

/*
 * ########
 *  Quad :)
 * ########
 */
template <typename T, typename M, typename E> class Quad : public Printable {
protected:
	Point3D<M, E>* m_ppoint;					// The center of the zone.
	Point3D<M, E>* m_pbarycenter;				// The center of mass given the repartition of the WeightedPoints in the zone.
	bool m_delp;					// If the point should be deleted.

	SN<M, E> m_a;							// Length of the zone's border.
	SN<M, E> m_tot_weight;					// Total weight contained in this Quad.

	T* m_pT;							// The content of this square (NULL if nothing).
	//Particle3D* m_pparticle;			// The content of this node.

	Quad<T, M, E>* m_pTLTree;					// Top Left corner : is NULL if nothing
	Quad<T, M, E>* m_pTRTree;					// Top Right corner : is NULL if nothing
	Quad<T, M, E>* m_pBLTree;					// Bottom Left corner : is NULL if nothing
	Quad<T, M, E>* m_pBRTree;					// Bottom Right corner : is NULL if nothing

	static unsigned int m_NB_QUADS;		// Keeps track of the number of Quad created.

public:
	static SN<M, E> m_LIM_A;					// This indicates the limit at which we stop subdividing (useless)
	static float m_ALPHA;				// The threshold m_ALPHA=a/d (with a being the width of the zone and d the distance from the center of the quad) indicates at which point we can consider

	Quad(const SN<M, E>& a, const Point3D<M, E>& p={{0,0},{0,0},{0,0}});
	Quad(const SN<M, E>& a, Point3D<M, E>* ppoint);
	Quad(const Quad<T, M, E>* pquad);
	virtual ~Quad();

	Point3D<M, E> getPoint() const;
	Point3D<M, E>* getPPoint() const;
	Point3D<M, E> getBarycenter() const;
	//Point3D<M, E><M, E>* getPBarycenter() const;
	bool getDelP() const;
	SN<M, E> getA() const;
	void setA(const SN<M, E>& a);
	unsigned int getNB_QUADS() const;
	//float getAlpha();
	//void setAlpha(float& alpha=0.5);
	std::unordered_set<Quad<T, M, E>*> getPTrees();						//Returns all the trees under, contained by this tree.
	std::unordered_set<T*> getPElements() const;					//Returns all the elements contained in the tree.
	std::unordered_set<T*> getPNeighbors(T* pelement) const;		//Returns all the neighbors.

	bool insert(T* pT);
	//void insert(Particle3D* ppart);
	void find(const T& t, std::unordered_set<Quad<T, M, E>*>& pquads);// It adds to the list of Quads in parameter accordingly to the ratio m_ALPHA
	//void computeInverseSquareLawResultant(const T& t, Vector3D& v) const;
	//std::set<T*> find(const Point3D<M, E>& point);
	T* search(const Point3D<M, E>* ppoint) const;
	void recalculate();
	bool empty();

	std::string to_string(const bool& spread=false, const bool& full_info=false, const unsigned char& indent=0) const;// :)
	void print(const bool& spread=false, const bool& full_info=false, const unsigned char& indent=0) const;// :)
};
template <typename T, typename M, typename E> unsigned int Quad<T, M, E>::m_NB_QUADS=0;
template <typename T, typename M, typename E> SN<M, E> Quad<T, M, E>::m_LIM_A={1, 0};
template <typename T, typename M, typename E> float Quad<T, M, E>::m_ALPHA=0.5;


/*
 * Constructor1
 */
template <typename T, typename M, typename E> Quad<T, M, E>::Quad(const SN<M, E>& a, const Point3D<M, E>& point) {
	m_ppoint=new Point3D<M, E>(point);
	m_pbarycenter=new Point3D<M, E>(*m_ppoint);
	m_delp=true;

	m_a=a;
	m_tot_weight=0.;

	m_pT=NULL;

	m_pTLTree=NULL;
	m_pTRTree=NULL;
	m_pBLTree=NULL;
	m_pBRTree=NULL;

	m_NB_QUADS++;
}

/*
 * Constructor2
 */
template <typename T, typename M, typename E> Quad<T, M, E>::Quad(const SN<M, E>& a, Point3D<M, E>* ppoint) {
	m_ppoint=ppoint;
	m_pbarycenter=new Point3D<M, E>(*m_ppoint);
	m_delp=false;

	m_a=a;
	m_tot_weight=0.;

	m_pT=NULL;

	m_pTLTree=NULL;
	m_pTRTree=NULL;
	m_pBLTree=NULL;
	m_pBRTree=NULL;

	m_NB_QUADS++;
}

/*
 * Copy constructor
 */
template <typename T, typename M, typename E> Quad<T, M, E>::Quad(const Quad<T, M, E>* pquad) {
	m_ppoint=new Point3D<M, E>(pquad->getPoint());
	m_pbarycenter=new Point3D<M, E>(*m_ppoint);
	m_delp=false;

	m_a=pquad->getA();
	m_tot_weight=0.;

	m_pT=NULL;

	m_pTLTree=NULL;
	m_pTRTree=NULL;
	m_pBLTree=NULL;
	m_pBRTree=NULL;

	m_NB_QUADS++;
}

template <typename T, typename M, typename E> Quad<T, M, E>::~Quad() {
	if (m_delp){
		delete m_ppoint;
	}else{
		m_ppoint=NULL;
	}
	delete m_pbarycenter;

	m_pT=NULL;

	if (m_pTLTree!=NULL){
		delete m_pTLTree;
	}
	if (m_pTRTree!=NULL){
		delete m_pTRTree;
	}
	if (m_pBLTree!=NULL){
		delete m_pBLTree;
	}
	if (m_pBRTree!=NULL){
		delete m_pBRTree;
	}
	// There is one less Quad
	m_NB_QUADS--;
}

template <typename T, typename M, typename E> Point3D<M, E> Quad<T, M, E>::getPoint() const {
	return *m_ppoint;
}

template <typename T, typename M, typename E> Point3D<M, E>* Quad<T, M, E>::getPPoint() const {
	Point3D<M, E>* pp=NULL;
	// If it hasn't been created locally...
	if (!m_delp){
		pp=this->m_ppoint;
	}
	return pp;
}

template <typename T, typename M, typename E> Point3D<M, E> Quad<T, M, E>::getBarycenter() const {
	return *m_pbarycenter;
}

/*template <typename T, typename M, typename E> Point3D<M, E>* Quad<T, M, E>::getPBarycenter() const {
	Point3D<M, E>* pp=NULL;
	// If it hasn't been created locally...
	if (!m_delp){
		pp=this->m_pbarycenterpoint;
	}
	return pp;
}*/

template <typename T, typename M, typename E> bool Quad<T, M, E>::getDelP() const {
	return m_delp;
}

template <typename T, typename M, typename E> SN<M, E> Quad<T, M, E>::getA() const {
	return m_a;
}

template <typename T, typename M, typename E> void Quad<T, M, E>::setA(const SN<M, E>& a) {
	m_a=a;
	this->recalculate();
}

template <typename T, typename M, typename E> unsigned int Quad<T, M, E>::getNB_QUADS() const {
	return m_NB_QUADS;
}

template <typename T, typename M, typename E> std::unordered_set<T*> Quad<T, M, E>::getPElements() const {
	std::unordered_set<T*> elmts;

	if (m_pT!=NULL){
		elmts.insert(m_pT);
	}else{
		if (m_pTLTree==NULL){
			for (T* pt : m_pTLTree->getPElements()){
				elmts.insert(pt);
			}
		}
		if (m_pTRTree==NULL){
			for (T* pt : m_pTRTree->getPElements()){
				elmts.insert(pt);
			}
		}
		if (m_pBLTree==NULL){
			for (T* pt : m_pBLTree->getPElements()){
				elmts.insert(pt);
			}
		}
		if (m_pBRTree==NULL){
			for (T* pt : m_pBRTree->getPElements()){
				elmts.insert(pt);
			}
		}
	}


	return elmts;
}

template <typename T, typename M, typename E> bool Quad<T, M, E>::insert(T* pT) {
	if (pT!=NULL){
		Point3D<M, E> p={pT->x, pT->y, {0, 0}/*ppart->z*/};
		Point3D<M, E> dp={pT->x-m_ppoint->x, pT->y-m_ppoint->y, {0, 0}};

		if (abs(dp.x)<=m_a/(M)2. && abs(dp.y)<=m_a/(M)2.){// If in the square centered on the point.
			if (m_pT==NULL){		// If empty
				//printf("Empty\n");
				if (m_pBLTree==NULL and m_pBRTree==NULL and m_pTRTree==NULL and m_pTLTree==NULL){	// If the square has no Quads under (external branch)
					m_pT=pT;//We add in
					m_tot_weight=1.;//Set the tot_weight
					*m_pbarycenter=p;//Set the barycenter
				}else{																				// Else it means it is an internal branch

					m_tot_weight+=1.;//Add to tot_weight
					*m_pbarycenter+=p*((M)1./m_tot_weight);//Add to the barycenter

					if (dp.x<=(M)0. && dp.y<=(M)0.){//If square 1
						if (m_pBLTree==NULL){//If there is not yet a tree we create it
							SN<M, E> a=m_a/(M)4.;
							Point3D<M, E> np{(M)(-1.)*a, (M)(-1.)*a,{0, 0}};
							std::cout<<"1"<<np.to_string(true);
							m_pBLTree=new Quad<T, M, E>(m_a/(M)2., *m_ppoint+np);
						}
						m_pBLTree->insert(pT);
					}else if (dp.x>=(M)0. && dp.y<=(M)0.){//If square 2
						if (m_pBRTree==NULL){//If there is not yet a tree we create it
							SN<M, E> a=m_a/(M)4.;
							Point3D<M, E> np{a, (M)(-1.)*a,{0, 0}};
							std::cout<<"2"<<np.to_string(true);
							m_pBRTree=new Quad<T, M, E>(m_a/(M)2., *m_ppoint+np);
						}
						m_pBRTree->insert(pT);
					}else if (dp.x>=(M)0. && dp.y>=(M)0.){//If square 3
						if (m_pTRTree==NULL){//If there is not yet a tree we create it
							SN<M, E> a=m_a/(M)4.;
							Point3D<M, E> np{a, a, {0, 0}};
							std::cout<<"3"<<np.to_string(true);
							m_pTRTree=new Quad<T, M, E>(m_a/(M)2., *m_ppoint+np);
						}
						m_pTRTree->insert(pT);
					}else if (dp.x<=(M)0. && dp.y>=(M)0.){//If square 4
						if (m_pTLTree==NULL){//If there is not yet a tree we create it
							SN<M, E> a=m_a/(M)4.;
							Point3D<M, E> np{(M)(-1.)*a, a, {0, 0}};
							std::cout<<"4"<<np.to_string(true);
							m_pTLTree=new Quad<T, M, E>(m_a/(M)2., *m_ppoint+np);
						}
						m_pTLTree->insert(pT);
					}
				}
			}else{					// Else if full

				m_tot_weight=1.;//Set the tot_weight
				*m_pbarycenter=p;//Set the barycenter

				//printf("Full\n");
				if (dp.x<=(M)0. && dp.y<=(M)0.){//If square 1
					if (m_pBLTree==NULL){//If there is not yet a tree we create it
						SN<M, E> a=m_a/(M)4.;
						Point3D<M, E> np{(M)(-1.)*a, (M)(-1.)*a, {0, 0}};
						std::cout<<"5"<<np.to_string(true);
						m_pBLTree=new Quad<T, M, E>(m_a/(M)2., *m_ppoint+np);
					}
					m_pBLTree->insert(pT);
				}else if (dp.x>=(M)0. && dp.y<=(M)0.){//If square 2
					if (m_pBRTree==NULL){//If there is not yet a tree we create it
						SN<M, E> a=m_a/(M)4.;
						Point3D<M, E> np{a, (M)(-1.)*a, {0, 0}};
						std::cout<<"6"<<np.to_string(true);
						m_pBRTree=new Quad<T, M, E>(m_a/(M)2., *m_ppoint+np);
					}
					m_pBRTree->insert(pT);
				}else if (dp.x>=(M)0. && dp.y>=(M)0.){//If square 3
					if (m_pTRTree==NULL){//If there is not yet a tree we create it
						SN<M, E> a=m_a/(M)4.;
						Point3D<M, E> np{a, a, {0, 0}};
						std::cout<<"7"<<np.to_string(true);
						m_pTRTree=new Quad<T, M, E>(m_a/(M)2., *m_ppoint+np);
					}
					m_pTRTree->insert(pT);
				}else if (dp.x<=(M)0. && dp.y>=(M)0.){//If square 4
					if (m_pTLTree==NULL){//If there is not yet a tree we create it
						SN<M, E> a=m_a/(M)4.;
						Point3D<M, E> np{(M)(-1.)*a, a, {0, 0}};
						std::cout<<"8"<<np.to_string(true);
						m_pTLTree=new Quad<T, M, E>(m_a/(M)2., *m_ppoint+np);
					}
					m_pTLTree->insert(pT);
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

/*template<> bool Quad<Point3D<M, E>, M, E>::insert(Point3D<M, E>* ppart) {// WHy does it work for Quads but not Octs
	return true;
}*/

/*template<> bool Quad<Particle3D, M, E>::insert(Particle3D* ppart) {// WHy does it work for Quads but not Octs
	if (ppart!=NULL){
		Point3D<M, E> p={ppart->x, ppart->y, {0, 0}};//ppart->z
		Point3D<M, E> dp={ppart->x-m_ppoint->x, ppart->y-m_ppoint->y, {0, 0}};

		if (abs(dp.x)<=m_a/2 && abs(dp.y)<=m_a/2){// If in the square centered on the point.
			if (m_pT==NULL){		// If empty
				//printf("Empty\n");
				if (m_pBLTree==NULL and m_pBRTree==NULL and m_pTRTree==NULL and m_pTLTree==NULL){	// If the square has no Quads under (external branch)
					m_pT=ppart;//We add in
					m_tot_weight=ppart->w;//Set the tot_weight
					*m_pbarycenter=p;//Set the barycenter
				}else{																				// Else it means it is an internal branch

					m_tot_weight+=ppart->w;//Add to tot_weight
					*m_pbarycenter+=p*(ppart->w/m_tot_weight);//Add to the barycenter

					if (m_tot_weight!=LSN{0,0}){
						*m_pbarycenter+=p*(ppart->w/m_tot_weight);//Add to the barycenter
					}else{
						*m_pbarycenter=*m_ppoint;//Set the barycenter to the geometric center
					}


					if (dp.x<=0. && dp.y<=0.){//If square 1
						//printf("Square1\n");
						if (m_pBLTree==NULL){//If there is not yet a tree we create it
							LSN a=m_a/4;
							Point3D<M, E> np{a*-1,a*-1,{0, 0}};
							m_pBLTree=new Quad<Particle3D, M, E>(m_a/2, *m_ppoint+np);
						}
						m_pBLTree->insert(ppart);
					}else if (dp.x>=0. && dp.y<=0.){//If square 2
						if (m_pBRTree==NULL){//If there is not yet a tree we create it
							LSN a=m_a/4;
							Point3D<M, E> np{a,a*-1,{0, 0}};
							m_pBRTree=new Quad<Particle3D, M, E>(m_a/2, *m_ppoint+np);
						}
						m_pBRTree->insert(ppart);
					}else if (dp.x>=0. && dp.y>=0.){//If square 3
						if (m_pTRTree==NULL){//If there is not yet a tree we create it
							LSN a=m_a/4;
							Point3D<M, E> np{a,a,{0, 0}};
							m_pTRTree=new Quad<Particle3D, M, E>(m_a/2, *m_ppoint+np);
						}
						m_pTRTree->insert(ppart);
					}else if (dp.x<=0. && dp.y>=0.){//If square 4
						if (m_pTLTree==NULL){//If there is not yet a tree we create it
							LSN a=m_a/4;
							Point3D<M, E> np{a*-1,a,{0, 0}};
							m_pTLTree=new Quad<Particle3D, M, E>(m_a/2, *m_ppoint+np);
						}
						m_pTLTree->insert(ppart);
					}
				}
			}else{					// Else if full

				m_tot_weight=ppart->w;//+m_pT->w//Set the tot_weight
				*m_pbarycenter=p;//Set the barycenter

				//printf("Full\n");
				if (dp.x<=0. && dp.y<=0.){//If square 1
					if (m_pBLTree==NULL){//If there is not yet a tree we create it
						LSN a=m_a/4;
						Point3D<M, E> np{a*-1,a*-1,{0, 0}};
						m_pBLTree=new Quad<Particle3D, M, E>(m_a/2, *m_ppoint+np);
					}
					m_pBLTree->insert(ppart);
				}else if (dp.x>=0. && dp.y<=0.){//If square 2
					if (m_pBRTree==NULL){//If there is not yet a tree we create it
						LSN a=m_a/4;
						Point3D<M, E> np{a,a*-1,{0, 0}};
						m_pBRTree=new Quad<Particle3D, M, E>(m_a/2, *m_ppoint+np);
					}
					m_pBRTree->insert(ppart);
				}else if (dp.x>=0. && dp.y>=0.){//If square 3
					if (m_pTRTree==NULL){//If there is not yet a tree we create it
						LSN a=m_a/4;
						Point3D<M, E> np{a,a,{0, 0}};
						m_pTRTree=new Quad<Particle3D, M, E>(m_a/2, *m_ppoint+np);
					}
					m_pTRTree->insert(ppart);
				}else if (dp.x<=0. && dp.y>=0.){//If square 4
					if (m_pTLTree==NULL){//If there is not yet a tree we create it
						LSN a=m_a/4;
						Point3D<M, E> np{a*-1,a,{0, 0}};
						m_pTLTree=new Quad<Particle3D, M, E>(m_a/2, *m_ppoint+np);
					}
					m_pTLTree->insert(ppart);
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

/*
 * Stores the quads that are to be considered given alpha.
 */
template <typename T, typename M, typename E> void Quad<T, M, E>::find(const T& t, std::unordered_set<Quad<T, M, E>*>& pquads) {
	Point3D<M, E> p={t.x, t.y, {0, 0}};

	SN<M, E> s=this->m_a;
	SN<M, E> d=getDistance(p, *m_pbarycenter);
	SN<M, E> alpha=s/d;

	if (alpha>=m_ALPHA){
		pquads.insert(this);
	}else{
		if (m_pBLTree!=NULL){
			m_pBLTree->find(t, pquads);
		}
		if (m_pBRTree!=NULL){
			m_pBRTree->find(t, pquads);
		}
		if (m_pTRTree!=NULL){
			m_pTRTree->find(t, pquads);
		}
		if (m_pTLTree!=NULL){
			m_pTLTree->find(t, pquads);
		}
	}
}

/*
 * Usefull to simulate the effects of gravitation or electromagnetic interactions
 */
/*template <typename T, typename M, typename E> void Quad<T, M, E>::computeInverseSquareLawResultant(const T& t, Vector3D& v) const {
	if (&t!=m_pT){
		Point3D<M, E> p={t.x, t.y, {0, 0}};

		LSN s=this->m_a;
		LSN d=getDistance(p, *m_pbarycenter);
		LSN alpha=s/d;
		//std::cout<<"\n"<<alpha.to_string()<<"\n";

		if (alpha>=m_ALPHA){
			Vector3D* pdv=new Vector3D(p, *m_pbarycenter);//ERROR
			//Vector3D dv;//ERROR
			//Vector3D dv(p, *m_pbarycenter);//ERROR
			//std::cout << "\n" << dv.to_string(true, true) << "\n";
			//Line3D l;
			//std::cout<<"\n"<<l.to_string(true, true)<<"\n";

			//Vector3D dv;//ERROR
			//dv.setP2(Point3D<M, E>{{0,0},{0,0},{0,0}});
			LSN nb=t.w*this->m_tot_weight;
			LSN nb2=nb/pow(d, 2);
			pdv->setNorm(nb2);

			//std::cout<<"\n";
			//dv.print(true, 0, true);
			//std::cout<<"\n"<<dv.to_string()<<"\n";
			v+=*pdv;
			//std::cout<<"\n"<<v.to_string()<<"\n";
		}else{
			if (m_pBLTree!=NULL){
				m_pBLTree->computeInverseSquareLawResultant(t, v);
			}
			if (m_pBRTree!=NULL){
				m_pBRTree->computeInverseSquareLawResultant(t, v);
			}
			if (m_pTRTree!=NULL){
				m_pTRTree->computeInverseSquareLawResultant(t, v);
			}
			if (m_pTLTree!=NULL){
				m_pTLTree->computeInverseSquareLawResultant(t, v);
			}
		}
	}
}*/

/*template <typename T, typename M, typename E> std::set<T*> Quad<T, M, E>::find(const Point3D<M, E>& point) {
	;
}*/

template <typename T, typename M, typename E> T* Quad<T, M, E>::search(const Point3D<M, E>* ppoint) const {
	T* pT=NULL;

	if (ppoint!=NULL){
		long double delta_x=(long double)(ppoint->x-m_ppoint->x);
		long double delta_y=(long double)(ppoint->y-m_ppoint->y);

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
}

template<typename T, typename M, typename E> void Quad<T, M, E>::recalculate() {
	;
}

template <typename T, typename M, typename E> bool Quad<T, M, E>::empty() {
	for (Quad<T, M, E>* ptree : this->getPTrees()){
		delete ptree;
	}

	m_pTLTree=NULL;
	m_pTRTree=NULL;
	m_pBLTree=NULL;
	m_pBRTree=NULL;

	*m_pbarycenter=*m_ppoint;
	m_tot_weight=0.;
	m_pT=NULL;

	return true;
}


template <typename T, typename M, typename E> std::string Quad<T, M, E>::to_string(const bool& spread, const bool& full_info, const unsigned char& indent) const {
	std::string mes=((spread)?"\n" : "");
	mes+=((spread)?to_stringTabs(indent) : "");
	//mes+="QUAD";

	if (full_info){
		mes+="QUAD[";
		std::stringstream ss;
		ss << this;
		mes+=ss.str();
		mes+="]:";
		mes+=m_a.to_string();						//a
		mes+="|";
		mes+=m_ppoint->to_string(false, false);		//Point
		mes+="|";
		mes+=m_pbarycenter->to_string(false, false);		//Barycenter
		mes+="|";
		std::stringstream ss2;
		ss2 << m_pT;
		mes+=ss2.str();
		mes+="|";
		mes+="w:" + std::to_string(m_tot_weight.to_m_type());
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

		mes+=(m_pTLTree==NULL)?nulll : m_pTLTree->to_string(spread, full_info, indent+1);
		mes+=((spread)?to_stringTabs(indent+1) : "");
		mes+=(m_pTRTree==NULL)?nulll : m_pTRTree->to_string(spread, full_info, indent+1);
		mes+=((spread)?to_stringTabs(indent+1) : "");
		mes+=(m_pBLTree==NULL)?nulll : m_pBLTree->to_string(spread, full_info, indent+1);
		mes+=((spread)?to_stringTabs(indent+1) : "");
		mes+=(m_pBRTree==NULL)?nulll : m_pBRTree->to_string(spread, full_info, indent+1);
		//mes+=to_stringTabs(indent+1);


		mes.erase(mes.length()-2);
		mes+=((spread)?"\n" : "");
		mes+=((spread)?to_stringTabs(indent+1) : "");
		mes+=")";
	}

	return mes;
}

template <typename T, typename M, typename E> void Quad<T, M, E>::print(const bool& spread, const bool& full_info, const unsigned char& indent) const {
	printTabs(indent);
	std::cout << this->to_string(spread, full_info, indent);
}



#endif /* QUAD_H_ */
