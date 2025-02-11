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
#include "Point3D.hpp"
#include "../utilities/Printable.hpp"


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
template<typename U, typename T> class Quad : public Printable {
protected:
	std::shared_ptr<Point3D<U>> m_ppoint;		// The center of the zone.
	std::shared_ptr<Point3D<U>> m_pbarycenter;	// The center of mass given the repartition of the WeightedPoints in the zone.

	T m_a;										// Length of the zone's border.
	T m_tot_weight;								// Total weight contained in this Quad.

	std::shared_ptr<U> m_pU;					// The content of this square (NULL if nothing).

	Quad<U, T>* m_ptrees[8];					// Contains the trees.

	static unsigned int m_NB_QUADS;				// Keeps track of the number of Quad created.

	void insertTLTree(std::shared_ptr<U> pU);//:)
	void insertTRTree(std::shared_ptr<U> pU);//:)
	void insertBRTree(std::shared_ptr<U> pU);//:)
	void insertBLTree(std::shared_ptr<U> pU);//:)

public:
	static T m_LIM_A;							// This indicates the limit at which we stop subdividing (useless)
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

	bool insert(std::shared_ptr<U> pU);
	//void insert(Particle3D* ppart);
	//void find(const T& t, std::unordered_set<Quad<U, T>*>& pquads);// It adds to the list of Quads in parameter accordingly to the ratio m_ALPHA
	//void computeInverseSquareLawResultant(const T& t, Vector3D& v) const;
	//std::set<T*> find(const Point3D<T>& point);
	std::shared_ptr<U> search(const std::shared_ptr<Point3D<T>> ppoint) const;
	void recalculate();
	void empty();

	bool isLeaf() const;
	bool isEmpty() const;

	// From Printable
	std::string to_string(const bool& spread=false, const bool& full_info=false, const unsigned char& indent=0) const;// :)
	void print(const bool& spread=false, const bool& full_info=false, const unsigned char& indent=0) const;// :)
};
template<typename U, typename T> unsigned int Quad<U, T>::m_NB_QUADS=0;
template<typename U, typename T> T Quad<U, T>::m_LIM_A=(T)1;
template<typename U, typename T> float Quad<U, T>::m_ALPHA=0.5;


/*
 * Constructor0
 */
template<typename U, typename T> Quad<U, T>::Quad() {
	m_ppoint=std::make_shared<Point3D<T>>();
	m_pbarycenter=std::make_shared<Point3D<T>>(*m_ppoint);

	m_a=(T)100;
	m_tot_weight=(T)0;

	m_pU=NULL;

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
template<typename U, typename T> Quad<U, T>::Quad(const T& a, const Point3D<T>& point) {
	m_ppoint=std::make_shared<Point3D<T>>(point);
	m_pbarycenter=std::make_shared<Point3D<T>>(*m_ppoint);

	m_a=a;
	m_tot_weight=(T)0;

	m_pU=NULL;

	for (int i(0) ; i<8 ; i++){
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

template<typename U, typename T> Quad<U, T>::~Quad() {
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
template<typename U, typename T> Quad<U, T>::Quad(const Quad<U, T>& quad) {
	m_ppoint=std::make_shared<Point3D<T>>(quad.getPoint());
	m_pbarycenter=std::make_shared<Point3D<T>>(*m_ppoint);

	m_a=quad.getA();
	m_tot_weight=(T)0;

	m_pU=NULL;

	for (int i(0) ; i<8 ; i++){
		m_ptrees[i]=NULL;
	}

	m_NB_QUADS++;
}

template<typename U, typename T> Point3D<T> Quad<U, T>::getPoint() const {
	return *m_ppoint;
}

template<typename U, typename T> void Quad<U, T>::setPoint(const Point3D<T>& point) {
	if (m_ppoint!=NULL){
		*m_ppoint=point;
	}else{
		m_ppoint=std::make_shared<Point3D<T>>(point);
		// Et le barycentre ?
	}
	this->recalculate();
}

template<typename U, typename T> Point3D<T> Quad<U, T>::getBarycenter() const {
	return *m_pbarycenter;
}

template<typename U, typename T> T Quad<U, T>::getA() const {
	return m_a;
}

template<typename U, typename T> void Quad<U, T>::setA(const T& a) {
	m_a=a;
	this->recalculate();
}

template<typename U, typename T> unsigned int Quad<U, T>::getNB_QUADS() const {
	return m_NB_QUADS;
}

template<typename U, typename T> std::unordered_set<std::shared_ptr<U>> Quad<U, T>::getPElements(const bool& mem) const {
	static std::unordered_set<std::shared_ptr<U>> elmts;

	if (mem==false){
		elmts.clear();
	}

	if (m_pU!=NULL && mem==true){
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
template<typename U, typename T> std::unordered_set<std::shared_ptr<U>> Quad<U, T>::getPNeighbors(const std::shared_ptr<U> pelement, const bool& mem) const {//////LOOOOK HERE !
	static std::unordered_set<std::shared_ptr<U>> pneighbors;

	if (mem==false){
		pneighbors.clear();
	}

	if (pelement!=NULL){
		//printf("God0\n");
		//getDistance(/**m_pbarycenter*/*m_ppoint, *pelement).print();
		//printf("\n");
		//(getDistance(/**m_pbarycenter*/*m_ppoint, *pelement)/m_a).print();
		//printf("\n");
		if (m_pU==NULL && (T)(m_ALPHA)/**abs(m_tot_weight)*/>=getDistance(*m_pbarycenter/**m_ppoint*/, *pelement)/m_a){//SN<T>{1., 0}/getDistance(*m_ppoint, *pelement)<=SN<T>{m_ALPHA, 0}
			//printf("God3\n");
			for (int i(0) ; i<8 ; i++) {
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
				//printf("God1\n");
			}else{			// Else if the place is empty
				std::shared_ptr<U> new_pU(new U(m_pbarycenter->x, m_pbarycenter->y, m_pbarycenter->z, m_tot_weight));
				pneighbors.insert(new_pU);
				//printf("God2\n");
			}
		}
	}

	return pneighbors;
}

template<typename U, typename T> bool Quad<U, T>::insert(std::shared_ptr<U> pU) {
	//printf("A0\n");
	if (pU!=NULL){
		Point3D<T> p={pU->x, pU->y, pU->z};
		Point3D<T> dp=p-*m_ppoint;//{pT->x-m_ppoint->x, pT->y-m_ppoint->y, pT->z-m_ppoint->z};
		//printf("A0_2: ");
		//m_ppoint->print();
		//p.print();
		//abs(dp).print();
		//printf("\n");

		if (abs(dp.x)<=m_a/(T)2 && abs(dp.y)<=m_a/(T)2 && abs(dp.z)<=m_a/(T)2){// If in the cube centered on the point.

			//printf("A1\n");
			// Manage the barycenter
			m_tot_weight+=pU->getW();//Add to tot_weight
			if (m_tot_weight!=(T)0){
				*m_pbarycenter+=p*(pU->getW()/m_tot_weight);//Add to the barycenter
			}else{
				*m_pbarycenter=*m_ppoint;
			}

			if (this->isEmpty() && this->isLeaf()){		// If empty and the cube has no Octs under (if it's a leaf)
				printf("A3\n");
				m_pU=pU;//We add in
			}else{																				// Else it means it is an internal branch
				if (dp.x>=(T)0 && dp.y<=(T)0 && dp.z>=(T)0){//If cube 1
					//printf("E\n");
					insertTLTree(pU);
				}else if (dp.x>=(T)0 && dp.y<=(T)0 && dp.z<=(T)0){//If cube 2
					//printf("F\n");
					insertTRTree(pU);
				}else if (dp.x<=(T)0 && dp.y<=(T)0 && dp.z<=(T)0){//If cube 3
					//printf("G\n");
					insertBRTree(pU);
				}else if (dp.x<=(T)0 && dp.y>=(T)0 && dp.z>=(T)0){//If cube 4
					//printf("H\n");
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
		}
	}
	return true;
}

template<typename U, typename T> void Quad<U, T>::insertTLTree(std::shared_ptr<U> pU) {//En private
	if (TLTree==NULL){//If there is not yet a tree we create it
		T a=m_a/(T)4;
		Point3D<T> np{(T)(-1)*a, (T)(-1)*a, (T)(1)*a};
		TLTree=new Quad<U, T>(m_a/(T)2, *m_ppoint+np);
	}
	TLTree->insert(pU);
}

template<typename U, typename T> void Quad<U, T>::insertTRTree(std::shared_ptr<U> pU) {//En private
	if (TRTree==NULL){//If there is not yet a tree we create it
		T a=m_a/(T)4;
		Point3D<T> np{(T)(1)*a, (T)(-1)*a, (T)(1)*a};
		TRTree=new Quad<U, T>(m_a/(T)2, *m_ppoint+np);
	}
	TRTree->insert(pU);
}

template<typename U, typename T> void Quad<U, T>::insertBRTree(std::shared_ptr<U> pU) {//En private
	if (BLTree==NULL){//If there is not yet a tree we create it
		T a=m_a/(T)4;
		Point3D<T> np{(T)(1)*a, (T)(-1)*a, (T)(-1)*a};
		BLTree=new Quad<U, T>(m_a/(T)2, *m_ppoint+np);
	}
	BLTree->insert(pU);
}

template<typename U, typename T> void Quad<U, T>::insertBLTree(std::shared_ptr<U> pU) {//En private
	if (BLTree==NULL){//If there is not yet a tree we create it
		T a=m_a/(T)4;
		Point3D<T> np{(T)(-1)*a, (T)(-1)*a, (T)(-1)*a};
		BLTree=new Quad<U, T>(m_a/(T)2, *m_ppoint+np);
	}
	BLTree->insert(pU);
}

template<typename U, typename T> void Quad<U, T>::recalculate() {
	std::unordered_set<std::shared_ptr<U>> pelements=this->getPElements();

	this->empty();

	for (std::shared_ptr<U> pelement : pelements){
		this->insert(pelement);//:)
	}
}

template<typename U, typename T> void Quad<U, T>::empty() {
	for (int i(0) ; i<8 ; i++){
		if (m_ptrees[i]!=NULL){
			delete m_ptrees[i];
		}
	}

	*m_pbarycenter=*m_ppoint;
	m_tot_weight=(T)0;
	m_pU=NULL;
}

template<typename U, typename T> bool Quad<U, T>::isLeaf() const {
	bool test=false;

	if (m_pU==NULL){
		test=true;
	}

	return test;
}

template<typename U, typename T> bool Quad<U, T>::isEmpty() const {
	bool test=true;

	for (int i(0) ; i<8 ; i++){
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



template<typename U, typename T> std::string Quad<U, T>::to_string(const bool& spread, const bool& full_info, const unsigned char& indent) const {
	//printf("AAAAAA12\n");
	std::string mes=((spread)?"\n" : "");
	mes+=to_stringTabs(indent);

	mes+="QUAD[";
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
	ss2 << m_pU;
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

template<typename U, typename T> void Quad<U, T>::print(const bool& spread, const bool& full_info, const unsigned char& indent) const {
	printTabs(indent);
	std::cout << this->to_string(spread, full_info, indent);
}



#endif /* QUAD_HPP_ */
