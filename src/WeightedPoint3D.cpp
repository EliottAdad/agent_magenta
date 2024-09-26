/*
 * WeightedPoint3D.cpp
 *
 *  Created on: 14 mai 2024
 *      Author: esn
 */

#include "WeightedPoint3D.h"

WeightedPoint3D::WeightedPoint3D() {
	this->x=LSN{0,0};
	this->y=LSN{0,0};
	this->z=LSN{0,0};
	this->w=LSN{1,0};
}

WeightedPoint3D::WeightedPoint3D(const Point3D& p, const LSN& w) {
	this->x=p.x;
	this->y=p.y;
	this->z=p.z;
	this->w=w;
}

WeightedPoint3D::WeightedPoint3D(const LSN& x, const LSN& y, const LSN& z, const LSN& w) {
	this->x=x;
	this->y=y;
	this->z=z;
	this->w=w;
}

/*
WeightedPoint3D::WeightedPoint3D(const LSN& x, const LSN& y, const LSN& z, const LSN& w) {
	this->x=x;
	this->y=y;
	this->z=z;
	this->w=w;
}*/

WeightedPoint3D::~WeightedPoint3D() {
	// TODO Auto-generated destructor stub
}



void WeightedPoint3D::operator=(const WeightedPoint3D& wp) {
	x=wp.x;
	y=wp.y;
	z=wp.z;
	w=wp.w;
}
/*
void WeightedPoint3D::operator+=(const Point3D& p) {
	x+=p.x;
	y+=p.y;
	z+=p.z;
}

void WeightedPoint3D::operator-=(const Point3D& p) {
	x-=p.x;
	y-=p.y;
	z-=p.z;
}*/


std::string WeightedPoint3D::to_string(const bool& spread, const bool& full_info, const unsigned int& indent) const {
	std::string mes=((spread)?"\n" : "");

	if (full_info){
		mes+="WEIGHTED POINT ():";
		mes+=((spread)?"\n" : "");
	}

	mes+="(" + x.to_string() + ", " + y.to_string() + ", " + z.to_string() + ", " + w.to_string()+")";

	return mes;
}

void WeightedPoint3D::print(const bool& spread, const bool& full_info, const unsigned int& indent) const {
	printTabs(indent);
	std::cout<<this->to_string(spread, full_info);
}
