/*
 * Map.hpp
 *
 *  Created on: 20 août 2024
 *      Author: esn
 */

#ifndef MAP_HPP_

#define MAP_HPP_

#include <memory>
#include <cstdio>
#include <unordered_set>

#include "SN.hpp"
#include "Point3D.hpp"


#define TLFTree m_ptrees[0] 	// Top Left Front corner : is NULL if nothing
#define TRFTree m_ptrees[1]		// Top Right Front corner : is NULL if nothing
#define BRFTree m_ptrees[2]		// Bottom Right Front corner : is NULL if nothing
#define BLFTree m_ptrees[3]		// Bottom Left Front corner : is NULL if nothing
#define TLBTree m_ptrees[4]		// Top Left Back corner : is NULL if nothing
#define TRBTree m_ptrees[5]		// Top Right Back corner : is NULL if nothing
#define BRBTree m_ptrees[6]		// Bottom Right Back corner : is NULL if nothing
#define BLBTree m_ptrees[7]		// Bottom Left Back corner : is NULL if nothing


struct Rule{
	;
}

/*
 * #############
 *  Map :)
 * #############
 * U is the class for the objects stored.
 * T is the unit used for distance.
 * Can contain any object that has x, y, z, w, getW()
 */
template<typename U, typename T> class Map : public Printable {
protected:
	std::shared_ptr<Point3D<T>> m_ppoint;					// The center of the zone.
	std::shared_ptr<Point3D<T>> m_pbarycenter;				// The center of mass given the repartition of the WeightedPoints in the zone.

	T m_ha;												// Half of the length of the zone's border (better to make calculations).
	T m_tot_weight;										// Total weight contained in this Oct.

	std::shared_ptr<U> m_pU;					// The content of this square (NULL if nothing).

	std::shared_ptr<Oct<U, T>> m_ptrees[8];					// Contains the trees.

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
	Matrix<int> map;
	Image references
	background image;
	Rules to smooth map/decor tileset
	Ordre de rendu/different planes
	
	
	
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

#endif /* MAP_HPP_ */
