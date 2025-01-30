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
//#include "../geometry/Particle3D.h"
#include "Point3D.h"
#include "../utilities/Printable.h"


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
 *  Oct<T, U> :)
 * #############
 * T is the class for the objects stored.
 * U is the unit used for distance.
 * Can contain any object that has x, y, z, w, getW()
 */
template<typename T, typename U> class Oct : public Printable {
protected:
	std::shared_ptr<Point3D<U>> m_ppoint;					// The center of the zone.
	std::shared_ptr<Point3D<U>> m_pbarycenter;				// The center of mass given the repartition of the WeightedPoints in the zone.

	U m_a;												// Length of the zone's border.
	U m_tot_weight;										// Total weight contained in this Oct.

	std::shared_ptr<T> m_pT;					// The content of this square (NULL if nothing).

	std::shared_ptr<Oct<T, U>> m_ptrees[8];					// Contains the trees.

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
	static U m_LIT_A;					// This indicates the limit at which we stop subdividing (useless)
	static float m_ALPHA;						// The threshold m_ALPHA=a/d (with a being the width of the zone and d the distance from the center of the quad) indicates at which point we can consider an agglomeration of bodies as one.
												// Plus alpha est petit plus on est precis

	Oct();
	Oct(const U& a, const Point3D<U>& p={(U)0,(U)0,(U)0});
	virtual ~Oct();
	Oct(const Oct<T, U>& oct);

	Point3D<U> getPoint() const;
	void setPoint(const Point3D<U>& point);
	Point3D<U> getBarycenter() const;
	U getA() const;
	void setA(const U& a);
	unsigned int getNB_OCTS() const;
	//std::unordered_set<Oct<T, U>*> getPTrees();						//Returns all the trees under, contained by this tree.
	std::unordered_set<std::shared_ptr<T>> getPElements(const bool& mem=false) const;					//:) Returns all the elements contained in the tree.
	std::unordered_set<std::shared_ptr<T>> getPNeighbors(const std::shared_ptr<T> pelement, const bool& mem=false) const;		//:) Returns all the neighbors.

	 std::shared_ptr<T> insert(std::shared_ptr<T> pT);//:)
	//bool insert(Particle3D* ppart);
	//void find(const T& t, std::unordered_set<Oct<T, U>*>& pocts);// It adds to the list of Octs in parameter accordingly to the ratio m_ALPHA
	//void computeInverseSquareLawResultant(const T& t, Vector3D& v) const;// Useless
	//std::unordered_set<T*> find(const Point3D& point);
	std::shared_ptr<T> search(const std::shared_ptr<Point3D<U>> ppoint) const;
	std::unordered_set<std::shared_ptr<T>> recalculate();
	void empty();

	bool isLeaf() const;
	bool isEmpty() const;

	std::string to_string(const bool& spread=false, const bool& full_info=false, const unsigned char& indent=0) const;// :)
	void print(const bool& spread=false, const bool& full_info=false, const unsigned char& indent=0) const;// :)
};
template<typename T, typename U> unsigned int Oct<T, U>::m_NB_OCTS=0;
template<typename T, typename U> U Oct<T, U>::m_LIT_A=(U)1;
template<typename T, typename U> float Oct<T, U>::m_ALPHA=0.5;


/*
 * Constructor0
 */
template<typename T, typename U> Oct<T, U>::Oct() {
	m_ppoint=std::make_shared<Point3D<U>>();
	m_pbarycenter=std::make_shared<Point3D<U>>(*m_ppoint);
	//printf("\nHein1 ? (Oct)\n");
	//m_pbarycenter->print();

	m_a=(U)100;
	m_tot_weight=(U)0;

	m_pT=NULL;

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
template<typename T, typename U> Oct<T, U>::Oct(const U& a, const Point3D<U>& p) {
	m_ppoint=std::make_shared<Point3D<U>>(p);
	m_pbarycenter=std::make_shared<Point3D<U>>(*m_ppoint);

	m_a=a;
	m_tot_weight=(U)0.;

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
/*template<typename T, typename U> Oct<T, U>::Oct(const U& a, std::shared_ptr<Point3D<T>> ppoint) {
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
/*template<typename T, typename U> Oct<T, U>::Oct(const U& a, Point3D<T>* ppoint) {
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

template<typename T, typename U> Oct<T, U>::~Oct() {
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
template<typename T, typename U> Oct<T, U>::Oct(const Oct<T, U>& oct) {
	m_ppoint=std::make_shared<Point3D<U>>(oct.getPoint());
	m_pbarycenter=std::make_shared<Point3D<U>>(*m_ppoint);

	m_a=oct.getA();
	m_tot_weight=(U)0.;

	m_pT=NULL;

	for (int i(0) ; i<8 ; i++){
		m_ptrees[i]=NULL;
	}
	// There is one more Oct
	m_NB_OCTS++;
}

template<typename T, typename U> Point3D<U> Oct<T, U>::getPoint() const {// Because it can be NULL
	return *m_ppoint;
}

template<typename T, typename U> void Oct<T, U>::setPoint(const Point3D<U>& point) {
	if (m_ppoint!=NULL){
		*m_ppoint=point;
	}else{
		m_ppoint=std::make_shared<Point3D<U>>(point);
		// Et le barycentre ?
	}
	this->recalculate();
}

template<typename T, typename U> Point3D<U> Oct<T, U>::getBarycenter() const {
	return *m_pbarycenter;
}

template<typename T, typename U> U Oct<T, U>::getA() const {
	return m_a;
}

template<typename T, typename U> void Oct<T, U>::setA(const U& a){
	m_a=a;
	this->recalculate();
}

template<typename T, typename U> unsigned int Oct<T, U>::getNB_OCTS() const {
	return m_NB_OCTS;
}

/**
 * mem: flag memorise
 */
template<typename T, typename U> std::unordered_set<std::shared_ptr<T>> Oct<T, U>::getPElements(const bool& mem) const {
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
template<typename T, typename U> std::unordered_set<std::shared_ptr<T>> Oct<T, U>::getPNeighbors(const std::shared_ptr<T> pelement, const bool& mem) const {//////LOOOOK HERE !
	static std::unordered_set<std::shared_ptr<T>> pneighbors;

	if (mem==false){
		pneighbors.clear();
	}

	if (pelement!=NULL){
		if (m_pT==NULL && (U)(m_ALPHA)/**abs(m_tot_weight)*/<=m_a/getDistance(*m_pbarycenter/**m_ppoint*/, *pelement)){//U{1., 0}/getDistance(*m_ppoint, *pelement)<=U{m_ALPHA, 0}
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

/**
 * returns
 * NULL if it was inserted successfully or if entered NULL pointer
 *  or the pointer that was passed in argument if it was enable.
 */
template<typename T, typename U> std::shared_ptr<T> Oct<T, U>::insert(std::shared_ptr<T> pT) {
	if (pT!=NULL){
		Point3D<U> p={pT->x, pT->y, pT->z};
		Point3D<U> dp=p-*m_ppoint;

		if (abs(dp.x)<=m_a/(U)2 && abs(dp.y)<=m_a/(U)2 && abs(dp.z)<=m_a/(U)2){// If in the cube centered on the point.
			// Manages the barycenter
			m_tot_weight+=pT->getW();//Add to tot_weight
			if (m_tot_weight!=(U)0){
				*m_pbarycenter+=p*(pT->getW()/m_tot_weight);//Add to the barycenter
			}else{
				*m_pbarycenter=*m_ppoint;
			}

			if (this->isEmpty() && this->isLeaf()){		// If empty and the cube has no Octs under (if it's a leaf)
				m_pT=pT;//We add in
			}else{																				// Else it means it is an internal branch
				if (dp.x<=(U)0 && dp.y<=(U)0 && dp.z>=(U)0){//If cube 1
					insertTLFTree(pT);
				}else if (dp.x>=(U)0 && dp.y<=(U)0 && dp.z>=(U)0){//If cube 2
					insertTRFTree(pT);
				}else if (dp.x>=(U)0 && dp.y<=(U)0 && dp.z<=(U)0){//If cube 3
					insertBRFTree(pT);
				}else if (dp.x<=(U)0 && dp.y<=(U)0 && dp.z<=(U)0){//If cube 4
					insertBLFTree(pT);
				}else if (dp.x<=(U)0 && dp.y>=(U)0 && dp.z>=(U)0){//If cube 5
					insertTLBTree(pT);
				}else if (dp.x>=(U)0 && dp.y>=(U)0 && dp.z>=(U)0){//If cube 6
					insertTRBTree(pT);
				}else if (dp.x>=(U)0 && dp.y>=(U)0 && dp.z<=(U)0){//If cube 7
					insertBRBTree(pT);
				}else if (dp.x<=(U)0 && dp.y>=(U)0 && dp.z<=(U)0){//If cube 8
					insertBLBTree(pT);
				}

				// We reinsert the object already present(can be null if it wasn't a leaf).
				if (m_pT!=NULL){
					m_tot_weight-=m_pT->getW();//Subtract the w of the already present obj to tot_weight
					std::shared_ptr<T> pT2;//Init to null
					pT2.swap(m_pT);// Set m_pT to NULL and pT2 to m_pT
					this->insert(pT2);
				}
			}
		}else{
			return pT;
		}
	}else{
		return NULL;
	}
	return NULL;
}

template<typename T, typename U> void Oct<T, U>::insertTLFTree(std::shared_ptr<T> pT) {//En private
	if (TLFTree==NULL){//If there is not yet a tree we create it
		U a=m_a/(U)4;
		Point3D<U> np{(U)(-1)*a, (U)(-1)*a, (U)(1)*a};
		TLFTree=std::make_shared<Oct<T, U>>(m_a/(U)2, *m_ppoint+np);
	}
	TLFTree->insert(pT);
}

template<typename T, typename U> void Oct<T, U>::insertTRFTree(std::shared_ptr<T> pT) {//En private
	if (TRFTree==NULL){//If there is not yet a tree we create it
		U a=m_a/(U)4;
		Point3D<U> np{(U)(1)*a, (U)(-1)*a, (U)(1)*a};
		TRFTree=std::make_shared<Oct<T, U>>(m_a/(U)2, *m_ppoint+np);
	}
	TRFTree->insert(pT);
}

template<typename T, typename U> void Oct<T, U>::insertBRFTree(std::shared_ptr<T> pT) {//En private
	if (BLBTree==NULL){//If there is not yet a tree we create it
		U a=m_a/(U)4;
		Point3D<U> np{(U)(1)*a, (U)(-1)*a, (U)(-1)*a};
		BLBTree=std::make_shared<Oct<T, U>>(m_a/(U)2, *m_ppoint+np);
	}
	BLBTree->insert(pT);
}

template<typename T, typename U> void Oct<T, U>::insertBLFTree(std::shared_ptr<T> pT) {//En private
	if (BLFTree==NULL){//If there is not yet a tree we create it
		U a=m_a/(U)4.;
		Point3D<U> np{(U)(-1)*a, (U)(-1)*a, (U)(-1)*a};
		BLFTree=std::make_shared<Oct<T, U>>(m_a/(U)2, *m_ppoint+np);
	}
	BLFTree->insert(pT);
}

template<typename T, typename U> void Oct<T, U>::insertTLBTree(std::shared_ptr<T> pT) {//En private
	if (TLBTree==NULL){//If there is not yet a tree we create it
		U a=m_a/(U)4;
		Point3D<U> np{(U)(-1)*a, (U)(1)*a, (U)(1)*a};
		TLBTree=std::make_shared<Oct<T, U>>(m_a/(U)2, *m_ppoint+np);
	}
	TLBTree->insert(pT);
}

template<typename T, typename U> void Oct<T, U>::insertTRBTree(std::shared_ptr<T> pT) {//En private
	if (TRBTree==NULL){//If there is not yet a tree we create it
		U a=m_a/(U)4;
		Point3D<U> np{(U)(1)*a, (U)(1)*a, (U)(1)*a};
		TRBTree=std::make_shared<Oct<T, U>>(m_a/(U)2, *m_ppoint+np);
	}
	TRBTree->insert(pT);
}

template<typename T, typename U> void Oct<T, U>::insertBRBTree(std::shared_ptr<T> pT) {//En private
	if (BRBTree==NULL){//If there is not yet a tree we create it
		U a=m_a/(U)4;
		Point3D<U> np{(U)(1)*a, (U)(1)*a, (U)(-1)*a};
		BRBTree=std::make_shared<Oct<T, U>>(m_a/(U)2, *m_ppoint+np);
	}
	BRBTree->insert(pT);
}

template<typename T, typename U> void Oct<T, U>::insertBLBTree(std::shared_ptr<T> pT) {//En private
	if (BLBTree==NULL){//If there is not yet a tree we create it
		U a=m_a/(U)4.;
		Point3D<U> np{(U)(-1)*a, (U)(1)*a, (U)(-1)*a};
		BLBTree=std::make_shared<Oct<T, U>>(m_a/(U)2, *m_ppoint+np);
	}
	BLBTree->insert(pT);
}

/**
 * Gives up objects that are outside of the range.
 */
template<typename T, typename U> std::unordered_set<std::shared_ptr<T>> Oct<T, U>::recalculate() {
	std::unordered_set<std::shared_ptr<T>> pelements=this->getPElements();
	std::unordered_set<std::shared_ptr<T>> perrored_elements;

	this->empty();

	for (std::shared_ptr<T> pelement : pelements){
		std::shared_ptr<T> perrored=this->insert(pelement);//:)
		if (perrored!=NULL){
			perrored_elements.insert(perrored);
		}
	}
	return perrored_elements;
}

template<typename T, typename U> void Oct<T, U>::empty() {
	// No more under Octs
	for (int i(0) ; i<8 ; i++){
		if (m_ptrees[i]!=NULL){
			m_ptrees[i]=NULL;
		}
	}

	*m_pbarycenter=*m_ppoint;
	m_tot_weight=(U)0;
	m_pT=NULL;
}

template<typename T, typename U> bool Oct<T, U>::isLeaf() const {
	bool test=false;

	if (m_pT==NULL){
		test=true;
	}

	return test;
}

template<typename T, typename U> bool Oct<T, U>::isEmpty() const {
	bool test=true;

	for (int i(0) ; i<8 ; i++){
		if (m_ptrees[i]!=NULL){
			test=false;
			break;
		}
	}

	return test;
}

/*template<typename T, typename U> std::shared_ptr<T> Oct<T, U>::search(const std::shared_ptr<Point3D<T>> ppoint) const {
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



template<typename T, typename U> std::string Oct<T, U>::to_string(const bool& spread, const bool& full_info, const unsigned char& indent) const {
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

template<typename T, typename U> void Oct<T, U>::print(const bool& spread, const bool& full_info, const unsigned char& indent) const {
	printTabs(indent);
	std::cout << this->to_string(spread, full_info, indent);
}


#endif /* OCT_H_ */
