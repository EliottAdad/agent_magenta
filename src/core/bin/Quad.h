/*
 * Quad.h
 *
 *  Created on: 18 mai 2024
 *      Author: esn
 */

#ifndef QUAD_H_

#define QUAD_H_

#include <memory>
#include <cstdio>
#include <unordered_set>

//#include "Particle3D.h"
#include "Point3D.h"
#include "../utilities/Printable.h"


#define TLTree m_ptrees[0] 		// Top Left corner : is NULL if nothing
#define TRTree m_ptrees[1]		// Top Right corner : is NULL if nothing
#define BRTree m_ptrees[2]		// Bottom Right corner : is NULL if nothing
#define BLTree m_ptrees[3]		// Bottom Left corner : is NULL if nothing


/*
 * #################
 *  Quad<T, M, E> :X
 * #################
 * Todo: Copy from Oct
 */
template<typename T, typename M, typename E> class Quad : public Printable {
protected:
	std::shared_ptr<Point3D<M, E>> m_ppoint;		// The center of the zone.
	std::shared_ptr<Point3D<M, E>> m_pbarycenter;	// The center of mass given the repartition of the WeightedPoints in the zone.

	SN<M, E> m_a;									// Length of the zone's border.
	SN<M, E> m_tot_weight;							// Total weight contained in this Quad.

	std::shared_ptr<T> m_pT;						// The content of this square (NULL if nothing).

	Quad<T, M, E>* m_ptrees[8];					// Contains the trees.

	static unsigned int m_NB_QUADS;					// Keeps track of the number of Quad created.

	void insertTLTree(std::shared_ptr<T> pT);//:)
	void insertTRTree(std::shared_ptr<T> pT);//:)
	void insertBRTree(std::shared_ptr<T> pT);//:)
	void insertBLTree(std::shared_ptr<T> pT);//:)

public:
	static SN<M, E> m_LIM_A;						// This indicates the limit at which we stop subdividing (useless)
	static float m_ALPHA;							// The threshold m_ALPHA=a/d (with a being the width of the zone and d the distance from the center of the quad) indicates at which point we can consider

	Quad();
	Quad(const SN<M, E>& a, const Point3D<M, E>& p={{0,0},{0,0},{0,0}});
	virtual ~Quad();
	Quad(const Quad<T, M, E>& quad);

	Point3D<M, E> getPoint() const;
	void setPoint(const Point3D<M, E>& point);
	Point3D<M, E> getBarycenter() const;
	SN<M, E> getA() const;
	void setA(const SN<M, E>& a);
	unsigned int getNB_QUADS() const;
	//std::unordered_set<Quad<T, M, E>*> getPTrees();						//Returns all the trees under, contained by this tree.
	std::unordered_set<std::shared_ptr<T>> getPElements(const bool& mem=false) const;					//Returns all the elements contained in the tree.
	std::unordered_set<std::shared_ptr<T>> getPNeighbors(const std::shared_ptr<T> pelement, const bool& mem=false) const;		//Returns all the neighbors.

	bool insert(std::shared_ptr<T> pT);
	//void insert(Particle3D* ppart);
	//void find(const T& t, std::unordered_set<Quad<T, M, E>*>& pquads);// It adds to the list of Quads in parameter accordingly to the ratio m_ALPHA
	//void computeInverseSquareLawResultant(const T& t, Vector3D& v) const;
	//std::set<T*> find(const Point3D<M, E>& point);
	std::shared_ptr<T> search(const std::shared_ptr<Point3D<M, E>> ppoint) const;
	void recalculate();
	void empty();

	bool isLeaf() const;
	bool isEmpty() const;

	std::string to_string(const bool& spread=false, const bool& full_info=false, const unsigned char& indent=0) const;// :)
	void print(const bool& spread=false, const bool& full_info=false, const unsigned char& indent=0) const;// :)
};
template<typename T, typename M, typename E> unsigned int Quad<T, M, E>::m_NB_QUADS=0;
template<typename T, typename M, typename E> SN<M, E> Quad<T, M, E>::m_LIM_A={1,0};
template<typename T, typename M, typename E> float Quad<T, M, E>::m_ALPHA=0.5;


/*
 * Constructor0
 */
template<typename T, typename M, typename E> Quad<T, M, E>::Quad() {
	m_ppoint=std::make_shared<Point3D<M, E>>();
	m_pbarycenter=std::make_shared<Point3D<M, E>>(*m_ppoint);

	m_a={1,2};
	m_tot_weight=0.;

	m_pT=NULL;

	for (int i(0) ; i<4 ; i++){
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
template<typename T, typename M, typename E> Quad<T, M, E>::Quad(const SN<M, E>& a, const Point3D<M, E>& point) {
	m_ppoint=std::make_shared<Point3D<M, E>>(point);
	m_pbarycenter=std::make_shared<Point3D<M, E>>(*m_ppoint);

	m_a=a;
	m_tot_weight=(M)0.;

	m_pT=NULL;

	for (int i(0) ; i<8 ; i++){
		m_ptrees[i]=NULL;
	}
	// There is one more Quad
	m_NB_QUADS++;
}

/*
 * Constructor2
 */
/*template <typename T, typename M, typename E> Quad<T, M, E>::Quad(const SN<M, E>& a, std::shared_ptr<Point3D<M, E>> ppoint) {
	m_ppoint=ppoint;
	m_pbarycenter=std::shared_ptr(new Point3D<M, E>(*m_ppoint));
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

template<typename T, typename M, typename E> Quad<T, M, E>::~Quad() {
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
template<typename T, typename M, typename E> Quad<T, M, E>::Quad(const Quad<T, M, E>& quad) {
	m_ppoint=std::make_shared<Point3D<M, E>>(quad.getPoint());
	m_pbarycenter=std::make_shared<Point3D<M, E>>(*m_ppoint);

	m_a=quad.getA();
	m_tot_weight=(M)0.;

	m_pT=NULL;

	for (int i(0) ; i<8 ; i++){
		m_ptrees[i]=NULL;
	}

	m_NB_QUADS++;
}

template<typename T, typename M, typename E> Point3D<M, E> Quad<T, M, E>::getPoint() const {
	return *m_ppoint;
}

template<typename T, typename M, typename E> void Quad<T, M, E>::setPoint(const Point3D<M, E>& point) {
	if (m_ppoint!=NULL){
		*m_ppoint=point;
	}else{
		m_ppoint=std::make_shared<Point3D<M, E>>(point);
		// Et le barycentre ?
	}
	this->recalculate();
}

template<typename T, typename M, typename E> Point3D<M, E> Quad<T, M, E>::getBarycenter() const {
	return *m_pbarycenter;
}

template<typename T, typename M, typename E> SN<M, E> Quad<T, M, E>::getA() const {
	return m_a;
}

template<typename T, typename M, typename E> void Quad<T, M, E>::setA(const SN<M, E>& a) {
	m_a=a;
	this->recalculate();
}

template<typename T, typename M, typename E> unsigned int Quad<T, M, E>::getNB_QUADS() const {
	return m_NB_QUADS;
}

template<typename T, typename M, typename E> std::unordered_set<std::shared_ptr<T>> Quad<T, M, E>::getPElements(const bool& mem) const {
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
template<typename T, typename M, typename E> std::unordered_set<std::shared_ptr<T>> Quad<T, M, E>::getPNeighbors(const std::shared_ptr<T> pelement, const bool& mem) const {//////LOOOOK HERE !
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

template<typename T, typename M, typename E> bool Quad<T, M, E>::insert(std::shared_ptr<T> pT) {
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

template<typename T, typename M, typename E> void Quad<T, M, E>::insertTLTree(std::shared_ptr<T> pT) {//En private
	if (TLTree==NULL){//If there is not yet a tree we create it
		SN<M, E> a=m_a/(M)4.;
		Point3D<M, E> np{(M)(-1.)*a, (M)(-1.)*a, (M)(1.)*a};
		TLTree=new Quad<T, M, E>(m_a/(M)2., *m_ppoint+np);
	}
	TLTree->insert(pT);
}

template<typename T, typename M, typename E> void Quad<T, M, E>::insertTRTree(std::shared_ptr<T> pT) {//En private
	if (TRTree==NULL){//If there is not yet a tree we create it
		SN<M, E> a=m_a/(M)4.;
		Point3D<M, E> np{(M)(1.)*a, (M)(-1.)*a, (M)(1.)*a};
		TRTree=new Quad<T, M, E>(m_a/(M)2., *m_ppoint+np);
	}
	TRTree->insert(pT);
}

template<typename T, typename M, typename E> void Quad<T, M, E>::insertBRTree(std::shared_ptr<T> pT) {//En private
	if (BLTree==NULL){//If there is not yet a tree we create it
		SN<M, E> a=m_a/(M)4.;
		Point3D<M, E> np{(M)(1.)*a, (M)(-1.)*a, (M)(-1.)*a};
		BLTree=new Quad<T, M, E>(m_a/(M)2., *m_ppoint+np);
	}
	BLTree->insert(pT);
}

template<typename T, typename M, typename E> void Quad<T, M, E>::insertBLTree(std::shared_ptr<T> pT) {//En private
	if (BLTree==NULL){//If there is not yet a tree we create it
		SN<M, E> a=m_a/(M)4.;
		Point3D<M, E> np{(M)(-1.)*a, (M)(-1.)*a, (M)(-1.)*a};
		BLTree=new Quad<T, M, E>(m_a/(M)2., *m_ppoint+np);
	}
	BLTree->insert(pT);
}
template<typename T, typename M, typename E> void Quad<T, M, E>::recalculate() {
	std::unordered_set<std::shared_ptr<T>> pelements=this->getPElements();

	this->empty();

	for (std::shared_ptr<T> pelement : pelements){
		this->insert(pelement);//:)
	}
}

template<typename T, typename M, typename E> void Quad<T, M, E>::empty() {
	for (int i(0) ; i<8 ; i++){
		if (m_ptrees[i]!=NULL){
			delete m_ptrees[i];
		}
	}

	*m_pbarycenter=*m_ppoint;
	m_tot_weight={(M)0,(E)0};
	m_pT=NULL;
}

template<typename T, typename M, typename E> bool Quad<T, M, E>::isLeaf() const {
	bool test=false;

	if (m_pT==NULL){
		test=true;
	}

	return test;
}

template<typename T, typename M, typename E> bool Quad<T, M, E>::isEmpty() const {
	bool test=true;

	for (int i(0) ; i<8 ; i++){
		if (m_ptrees[i]!=NULL){
			test=false;
			break;
		}
	}

	return test;
}

/*template<typename T, typename M, typename E> std::shared_ptr<T> Quad<T, M, E>::search(const std::shared_ptr<Point3D<M, E>> ppoint) const {
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



template<typename T, typename M, typename E> std::string Quad<T, M, E>::to_string(const bool& spread, const bool& full_info, const unsigned char& indent) const {
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
		mes+=(BLTree==NULL)?nulll : BLTree->to_string(spread, full_info, indent+1);
		mes+=to_stringTabs(indent+1);
		//printf("AAAAAA14\n");
		mes+=(BRTree==NULL)?nulll : BRTree->to_string(spread, full_info, indent+1);
		mes+=to_stringTabs(indent+1);
		//printf("AAAAAA15\n");
		mes+=(BRTree==NULL)?nulll : BRTree->to_string(spread, full_info, indent+1);
		mes+=to_stringTabs(indent+1);
		//printf("AAAAAA16\n");
		mes+=(BLTree==NULL)?nulll : BLTree->to_string(spread, full_info, indent+1);
		mes+=to_stringTabs(indent+1);
		//printf("AAAAAA17\n");


		mes.erase(mes.length()-2);
		mes+=((spread)?"\n" : "");
		mes+=((spread)?to_stringTabs(indent+1) : "");
		mes+=")";
	}

	return mes;
}

template<typename T, typename M, typename E> void Quad<T, M, E>::print(const bool& spread, const bool& full_info, const unsigned char& indent) const {
	printTabs(indent);
	std::cout << this->to_string(spread, full_info, indent);
}



#endif /* QUAD_H_ */
