/*
 * Line3DS.h
 *
 *  Created on: 20 août 2024
 *      Author: esn
 */

#ifndef LINE3DS_H_

#define LINE3DS_H_

#include <memory>

#include "../core/Point3DS.h"
#include "../utilities/functions.h"
#include "../utilities/Printable.h"

/*
 * #################
 *  Line3DS<T> :)
 * #################
 * A line is represented by two points.
 * This class present a few useful methods
 * to compute the geometry of the objects.
 */
template<typename T> class Line3DS : public Printable {
public:
	std::shared_ptr<Point3DS<T>> pp1;
	std::shared_ptr<Point3DS<T>> pp2;

	Line3DS();
	Line3DS(const Point3DS<T>& p1, const Point3DS<T>& p2);
	Line3DS(std::shared_ptr<Point3DS<T>> pp1, std::shared_ptr<Point3DS<T>> pp2);
	virtual ~Line3DS();												//:)
	Line3DS(const Line3DS<T>& line);

	virtual std::string to_string(const bool& spread=false, const bool& full_info=false, const unsigned char& indent=0) const;
	virtual void print(const bool& spread=false, const bool& full_info=false, const unsigned char& indent=0) const;
};



template<typename T> Line3DS<T>::Line3DS(){
	this->pp1=std::make_shared<Point3DS<T>>();
	this->pp2=std::make_shared<Point3DS<T>>((T)1,(T)1,(T)1);
}

template<typename T> Line3DS<T>::Line3DS(const Point3DS<T>& p1, const Point3DS<T>& p2){//:)
	this->pp1=std::make_shared<Point3DS<T>>(p1);// Copy the point
	this->pp2=std::make_shared<Point3DS<T>>(p2);// Copy the point
}

template<typename T> Line3DS<T>::Line3DS(std::shared_ptr<Point3DS<T>> pp1, std::shared_ptr<Point3DS<T>> pp2){//:)
	this->pp1=pp1;
	this->pp2=pp2;
}

template<typename T> Line3DS<T>::~Line3DS() {
	;
}

/*
 * Copy constructor
 */
template<typename T> Line3DS<T>::Line3DS(const Line3DS<T>& line){
	this->pp1=line.pp1;
	this->pp2=line.pp2;
}

template<typename T> std::string Line3DS<T>::to_string(const bool& spread, const bool& full_info, const unsigned char& indent) const {
	std::string mes=((spread)?"\n" : "");
	mes+=to_stringTabs(indent);

	if (full_info){
		mes+="LINE3DS[";
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

template<typename T> void Line3DS<T>::print(const bool& spread, const bool& full_info, const unsigned char& indent) const {
	printTabs(indent);
	std::cout << this->to_string(spread, full_info, indent);
}


#endif /* LINE3D_H_ */
