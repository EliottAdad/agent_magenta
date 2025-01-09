/*
 * Line3D.h
 *
 *  Created on: 20 août 2024
 *      Author: esn
 */

#ifndef LINE3D_H_

#define LINE3D_H_

#include <memory>

#include "Point3D.h"
#include "../utilities/functions.h"
#include "../utilities/Printable.h"

/*
 * ################
 *  Line3D<M, E> :)
 * ################
 * A line is represented by two points.
 * This class present a few useful methods
 * to compute the geometry of the objects.
 */
template<typename M, typename E> class Line3D : public Printable {
public:
	std::shared_ptr<Point3D<M, E>> pp1;
	std::shared_ptr<Point3D<M, E>> pp2;

	Line3D();
	Line3D(const Point3D<M, E>& p1, const Point3D<M, E>& p2);
	Line3D(std::shared_ptr<Point3D<M, E>> pp1, std::shared_ptr<Point3D<M, E>> pp2);
	virtual ~Line3D();												//:)
	Line3D(const Line3D<M, E>& line);

	virtual std::string to_string(const bool& spread=false, const bool& full_info=false, const unsigned char& indent=0) const;
	virtual void print(const bool& spread=false, const bool& full_info=false, const unsigned char& indent=0) const;
};



template<typename M, typename E> Line3D<M, E>::Line3D(){
	this->pp1=std::make_shared<Point3D<M, E>>();
	this->pp2=std::make_shared<Point3D<M, E>>(SN<M, E>{1,0},SN<M, E>{1,0},SN<M, E>{1,0});
}

template<typename M, typename E> Line3D<M, E>::Line3D(const Point3D<M, E>& p1, const Point3D<M, E>& p2){//:)
	this->pp1=std::make_shared<Point3D<M, E>>(p1);// Copy the point
	this->pp2=std::make_shared<Point3D<M, E>>(p2);// Copy the point
}

template<typename M, typename E> Line3D<M, E>::Line3D(std::shared_ptr<Point3D<M, E>> pp1, std::shared_ptr<Point3D<M, E>> pp2){//:)
	this->pp1=pp1;
	this->pp2=pp2;
}

template<typename M, typename E> Line3D<M, E>::~Line3D() {
	;
}

/*
 * Copy constructor
 */
template<typename M, typename E> Line3D<M, E>::Line3D(const Line3D<M, E>& line){
	this->pp1=line.pp1;
	this->pp2=line.pp2;
}



/*Point3D<float, char> Line3D::getP1() const {
	//return Point3D{*(this->m_pp1)};
	return *m_pp1;
}*/

/**
 * Returns the pointer to p1 (if p1 has been
 * defined externally) or NULL in the other case
 */
/*Point3D<float, char>* Line3D::getPP1() const {
	Point3D<float, char>* pp1=NULL;
	// If it hasn't been created locally...
	if (!m_delp1){
		pp1=this->m_pp1;
	}
	return pp1;
}

void Line3D::setP1(Point3D<float, char>& p1, const bool& delp) {
	if (m_delp1){
		delete m_pp1;
	}
	if (delp){
		m_pp1=new Point3D<float, char>(p1);
	}else{
		m_pp1=&p1;
	}
	m_delp1=delp;
}

void Line3D::setPP1(Point3D<float, char>* pp1, const bool& delp) {
	if (pp1!=NULL){
		if (m_delp1){
			delete m_pp1;
		}
		if (delp){
			m_pp1=new Point3D<float, char>(*pp1);
		}else{
			m_pp1=pp1;
		}
		m_delp1=delp;
	}
}

Point3D<float, char> Line3D::getP2() const {
	//return Point3D{*(this->m_pp2)};
	return *m_pp2;
}*/

/**
 * Returns the pointer to p2 (if p2 has been
 * defined externally) or NULL in the other case
 */
/*Point3D<float, char>* Line3D::getPP2() const {
	Point3D<float, char>* pp2=nullptr;
	// If it hasn't been created locally...
	if (!m_delp2){
		pp2=this->m_pp2;
	}
	return pp2;
}

void Line3D::setP2(Point3D<float, char>& p2, const bool& delp) {
	if (m_delp2){
		delete m_pp2;
	}
	if (delp){
		m_pp1=new Point3D<float, char>(p2);
	}else{
		m_pp2=&p2;
	}
	m_delp2=delp;
}

void Line3D::setPP2(Point3D<float, char>* pp2, const bool& delp) {
	if (pp2!=NULL){
		if (m_delp2){
			delete m_pp2;
		}
		if (delp){
			m_pp2=new Point3D<float, char>(*pp2);
		}else{
			m_pp2=pp2;
		}
		m_delp2=delp;
	}
}

bool Line3D::getDelP1() const {
	return this->m_delp1;
}

bool Line3D::getDelP2() const {
	return this->m_delp2;
}*/


template<typename M, typename E> std::string Line3D<M, E>::to_string(const bool& spread, const bool& full_info, const unsigned char& indent) const {
	std::string mes=((spread)?"\n" : "");
	mes+=to_stringTabs(indent);

	if (full_info){
		mes+="LINE3D[";
		std::stringstream ss;
		ss << this;
		mes+=ss.str();
		mes+="]:";
		mes+=((spread)?"\n" + to_stringTabs(1) : "");
		//mes+=((spread)?"\n" : "");
	}
	mes+=to_stringTabs(indent);
	mes+="(";
	if (full_info){
		mes+="P1" + (pp1==NULL)?:" NULL", pp1->to_string() + "|*|";
	}
	mes+="P2" + (pp2==NULL)?:" NULL", pp2->to_string() + ")";

	return mes;
}

template<typename M, typename E> void Line3D<M, E>::print(const bool& spread, const bool& full_info, const unsigned char& indent) const {
	printTabs(indent);
	std::cout << this->to_string(spread, full_info, indent);
}


#endif /* LINE3D_H_ */
