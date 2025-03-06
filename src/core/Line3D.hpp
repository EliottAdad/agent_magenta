/*
 * Line3D.hpp
 *
 *  Created on: 20 août 2024
 *      Author: esn
 */

#ifndef LINE3D_HPP_

#define LINE3D_HPP_

#include <memory>
#include <eigen3/Eigen/Dense>

#include "../utilities/functions.hpp"
#include "utils_Point3D.hpp"

/**
 * #############
 *  Line3D<T> :)
 * #############
 * @brief
 * A line is represented by two points (pointers never NULL).
 * This class present a few useful methods
 * to compute the geometry of the objects.
 */
template<typename T> class Line3D {
protected:
	std::shared_ptr<Point3D<T>> m_pp1;
	std::shared_ptr<Point3D<T>> m_pp2;
public:

	Line3D();
	Line3D(const Point3D<T>& p2);
	Line3D(const Point3D<T>& p1, const Point3D<T>& p2);
	Line3D(std::shared_ptr<Point3D<T>> pp1, std::shared_ptr<Point3D<T>> pp2);
	Line3D(std::shared_ptr<Point3D<T>> pp1, const Point3D<T>& p2);
	Line3D(const Point3D<T>& p1, std::shared_ptr<Point3D<T>> pp2);
	virtual ~Line3D();												//:)
	Line3D(const Line3D<T>& line);
	
	// Getters/Setters
	Point3D<T> getP1() const {return *this->m_pp1;}
	std::shared_ptr<Point3D<T>> getPP1() const {return this->m_pp1;}
	void setP1(const Point3D<T>& p1) {*this->m_pp1=p1;}
	void setPP1(std::shared_ptr<Point3D<T>> pp1) {if (pp1!=NULL)this->m_pp1=pp1;}
	Point3D<T> getP2() const {return *this->m_pp2;}
	std::shared_ptr<Point3D<T>> getPP2() const {return this->m_pp2;}
	void setP2(const Point3D<T>& p2) {*this->m_pp2=p2;}
	void setPP2(std::shared_ptr<Point3D<T>> pp2) {if (pp2!=NULL)this->m_pp2=pp2;}
};

template<typename T> Point3D<T> getIntersection(const Line3D<T>& l1, const Line3D<T>& l2);
template<typename T> Point3D<T> getIntersectionSegments(const Line3D<T>& l1, const Line3D<T>& l2);


/**
 * Default constructor
 */
template<typename T> inline Line3D<T>::Line3D(){
	this->m_pp1=std::make_shared<Point3D<T>>();					// First point created at origin
	this->m_pp2=std::make_shared<Point3D<T>>((T)1,(T)1,(T)1);	// Second point at {1, 1, 1}
}

/**
 * @brief
 * Constructor2
 * A Vector3D is defined by two Point3D
 * @param p2 Second point
 * @param[in/out] p1 and p2 are copied
 */
template<typename T> inline Line3D<T>::Line3D(const Point3D<T>& p2) {
	this->m_pp1=std::make_shared<Point3D<T>>();
	this->m_pp2=std::make_shared<Point3D<T>>(p2);
}

/**
 * Constructor
 */
template<typename T> inline Line3D<T>::Line3D(const Point3D<T>& p1, const Point3D<T>& p2){//:)
	this->m_pp1=std::make_shared<Point3D<T>>(p1);// Copy the point
	this->m_pp2=std::make_shared<Point3D<T>>(p2);// Copy the point
}

/**
 * Constructor2
 */
template<typename T> inline Line3D<T>::Line3D(std::shared_ptr<Point3D<T>> pp1, std::shared_ptr<Point3D<T>> pp2){//:)
	if (pp1!=NULL){
		this->m_pp1=pp1;
	}else{
		this->m_pp1=std::make_shared<Point3D<T>>();
	}
	
	if (pp2!=NULL){
		this->m_pp2=pp2;
	}else{
		this->m_pp1=std::make_shared<Point3D<T>>((T)1,(T)1,(T)1);
	}
}

/**
 * @brief
 * Constructor5 TODO
 * Defined by two points
 * @param pp1 Pointer to the first point
 * (modifications outside of class definition will be passed onto p1)
 * @param p2 Second point
 */
template<typename T> inline Line3D<T>::Line3D(std::shared_ptr<Point3D<T>> pp1, const Point3D<T>& p2) {
	this->m_pp1=pp1;
	this->m_pp2=std::make_shared<Point3D<T>>(p2);
}

/**
 * @brief
 * Constructor6
 * Defined by two points
 * @param p1 First point
 * @param pp2 Pointer to the second point
 * (modifications outside of class definition will be passed onto p2)
 */
template<typename T> inline Line3D<T>::Line3D(const Point3D<T>& p1, std::shared_ptr<Point3D<T>> pp2) {
	this->m_pp1=std::make_shared<Point3D<T>>(p1);
	this->m_pp2=pp2;
}

/**
 * Destructor
 */
template<typename T> inline Line3D<T>::~Line3D() {
	;
}

/**
 * Copy constructor
 */
template<typename T> inline Line3D<T>::Line3D(const Line3D<T>& line){
	this->m_pp1=line.getPP1();
	this->m_pp2=line.getPP2();
}










/**
 * Returns NULL if no intersection or 
 * computes the point where they intersect.
 */
template<typename T> Point3D<T> getIntersection(const Line3D<T>& l1, const Line3D<T>& l2) {
	if (l1.getP2() - l1.getP1() == l2.getP2() - l2.getP1()){//if p2-p1 == p2'-p1' not intersction
		return Point3D<T>{(T)0, (T)0, (T)0};	// TODO
	}else{
		//Point3D<T> p;
		//t=(p1'-p1)(p2-p1-(p2'-p1'))
		Eigen::Matrix<T, 3, 1> t= toEigen(l1.getP2()-l1.getP1() - (l2.getP2()-l2.getP1())).inverse() * toEigen(l2.getP1()-l1.getP1());
		Eigen::Matrix<T, 3, 1> p= toEigen(l1.getP2()-l1.getP1()) * t + toEigen(l1.getP1());
		return toPoint(p);
	}
}

/**
 * Returns NULL if no intersection or 
 * computes the point where they intersect.
 */
template<typename T> Point3D<T> getIntersectionSegments(const Line3D<T>& l1, const Line3D<T>& l2) {
	if (l1.getP2() - l1.getP1() == l2.getP2() - l2.getP1()){//if p2-p1 == p2'-p1' not intersction
			return Point3D<T>{(T)0, (T)0, (T)0};	// TODO
	}else{
		//Point3D<T> p;
		//t=(p1'-p1)(p2-p1-(p2'-p1'))
		Eigen::Matrix<T, 3, 1> t= toEigen(l1.getP2()-l1.getP1() - (l2.getP2()-l2.getP1())).inverse() * toEigen(l2.getP1()-l1.getP1());
		//Eigen::Matrix<T, 3, 1> p= toEigen(*(l1.pp2)-*(l1.pp1)) * t + toEigen(*l1.pp1);
		if (Point3D<T>{(T)0,(T)0,(T)0}<=toPoint(t) && toPoint(t)<=Point3D<T>{(T)1,(T)1,(T)1}){
			Eigen::Matrix<T, 3, 1> p= toEigen(l1.getP2()-l1.getP1()) * t + toEigen(l1.getP1());
			return toPoint(p);
		}else{
			return Point3D<T>{(T)0, (T)0, (T)0};	// TODO
		}
	}
}


#endif /* LINE3D_HPP_ */
