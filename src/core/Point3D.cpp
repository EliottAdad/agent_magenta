/*
 * Point3D.cpp
 *
 *  Created on: 14 mai 2024
 *      Author: esn
 */

#include "Point3D.h"

Point3D::Point3D() {
	this->x=LSN{0,0};
	this->y=LSN{0,0};
	this->z=LSN{0,0};
}

Point3D::Point3D(const LSN& x, const LSN& y, const LSN& z) {
	this->x=x;
	this->y=y;
	this->z=z;
}

Point3D::~Point3D() {
	// TODO Auto-generated destructor stub
}

Point3D::Point3D(const Point3D& point) {
	this->x=point.x;
	this->y=point.y;
	this->z=point.z;
}



LSN Point3D::getX() const {
	return x;
}

LSN Point3D::getY() const {
	return y;
}

LSN Point3D::getZ() const {
	return z;
}

Point3D Point3D::getPosition() const {
	return {x, y, z};
}

void Point3D::operator=(const Point3D& p) {
	this->x=p.x;
	this->y=p.y;
	this->z=p.z;
}

void Point3D::operator=(const LSN& nb) {
	this->x=nb;
	this->y=nb;
	this->z=nb;
}

void Point3D::operator+=(const Point3D& p) {
	this->x+=p.x;
	this->y+=p.y;
	this->z+=p.z;
}

void Point3D::operator+=(const LSN& nb) {
	this->x+=nb;
	this->y+=nb;
	this->z+=nb;
}

void Point3D::operator+=(const long double& nb) {
	this->x+=nb;
	this->y+=nb;
	this->z+=nb;
}

void Point3D::operator-=(const Point3D& p) {
	this->x-=p.x;
	this->y-=p.y;
	this->z-=p.z;
}

void Point3D::operator-=(const LSN& nb) {
	this->x-=nb;
	this->y-=nb;
	this->z-=nb;
}

void Point3D::operator-=(const long double& nb) {
	this->x-=nb;
	this->y-=nb;
	this->z-=nb;
}

void Point3D::operator*=(const LSN& k) {
	this->x*=k;
	this->y*=k;
	this->z*=k;
}

void Point3D::operator*=(const long double& k) {
	this->x*=k;
	this->y*=k;
	this->z*=k;
}

void Point3D::operator/=(const LSN& k) {
	this->x/=k;
	this->y/=k;
	this->z/=k;
}

void Point3D::operator/=(const long double& k) {
	this->x/=k;
	this->y/=k;
	this->z/=k;
}





std::string Point3D::to_string(const bool& spread, const bool& full_info, const unsigned char& indent) const {
	std::string mes=((spread)?"\n" : "");

	if (full_info){
		mes+="POINT[";
		std::stringstream ss;
		ss << this;
		mes+=ss.str();
		mes+="]:";
		mes+=((spread)?"\n" : "");
	}

	mes+="(x:" + x.to_string() + ", y:" + y.to_string() + ", z:" + z.to_string() + ")";

	return mes;
}

void Point3D::print(const bool& spread, const bool& full_info, const unsigned char& indent) const {
	printTabs(indent);
	std::cout << this->to_string(spread, full_info, indent);
}



bool operator==(const Point3D& p1, const Point3D& p2) {
	if (p1.x==p2.x && p1.y==p2.y && p1.z==p2.z){
		return true;
	}
	return false;
}

bool operator!=(const Point3D& p1, const Point3D& p2) {
	if (p1.x!=p2.x && p1.y!=p2.y && p1.z!=p2.z){
		return true;
	}
	return false;
}

bool operator<=(const Point3D& p1, const Point3D& p2) {
	if (p1.x<=p2.x && p1.y<=p2.y && p1.z<=p2.z){
		return true;
	}
	return false;
}

bool operator>=(const Point3D& p1, const Point3D& p2) {
	if (p1.x>=p2.x && p1.y>=p2.y && p1.z>=p2.z){
		return true;
	}
	return false;
}

Point3D operator+(const Point3D& p1, const Point3D& p2) {
	//Point3D* pnp=new Point3D;
	return {p1.x+p2.x, p1.y+p2.y, p1.z+p2.z};
}

Point3D operator-(const Point3D& p1, const Point3D& p2) {
	//Point3D* pnp=new Point3D{this->x-p.x, this->y-p.y, this->z-p.z};
	return {p1.x-p2.x, p1.y-p2.y, p1.z-p2.z};
}

Point3D operator*(const Point3D& p, const LSN& k) {
	//Point3D* pnp=new Point3D{this->x*k, this->y*k, this->z*k};
	return {p.x*k, p.y*k, p.z*k};
}

Point3D operator*(const LSN& k, const Point3D& p) {
	//Point3D* pnp=new Point3D{this->x*k, this->y*k, this->z*k};
	return {p.x*k, p.y*k, p.z*k};
}

Point3D operator*(const Point3D& p, const long double& k) {
	//Point3D* pnp=new Point3D
	return {p.x*k, p.y*k, p.z*k};
}

Point3D operator*(const long double& k, const Point3D& p) {
	//Point3D* pnp=new Point3D
	return {p.x*k, p.y*k, p.z*k};
}

Point3D operator/(const Point3D& p, const LSN& k) {
	//Point3D* pnp=new Point3D{this->x/k, this->y/k, this->z/k};
	return {p.x/k, p.y/k, p.z/k};
}

/*Point3D operator/(const LSN& k, const Point3D& p) {
	//Point3D* pnp=new Point3D{this->x/k, this->y/k, this->z/k};
	return {p.x/k, p.y/k, p.z/k};
}*/

Point3D operator/(const Point3D& p, const long double& k) {
	//Point3D* pnp=new Point3D{this->x/k, this->y/k, this->z/k};
	return {p.x/k, p.y/k, p.z/k};
}

/*Point3D operator/(const long double& k, const Point3D& p) {
	//Point3D* pnp=new Point3D{this->x/k, this->y/k, this->z/k};
	return {p.x/k, p.y/k, p.z/k};
}*/


/*
 * Functions
 */
LSN getDistance(const Point3D& p1, const Point3D& p2) {
	//LSN* pnlsn=new LSN{sqrt(pow((p1.x-p2.x).to_long_double(), (long int)2) + pow((p1.y-p2.y).to_long_double(), (long int)2) + pow((p1.z-p2.z).to_long_double(), (long int)2)), 0};// d=sqrt( (xA-xB)²+(yA-yB)² )
	return {sqrt(pow((p1.x-p2.x).to_long_double(), (long int)2) + pow((p1.y-p2.y).to_long_double(), (long int)2) + pow((p1.z-p2.z).to_long_double(), (long int)2)), 0};// d=sqrt( (xA-xB)²+(yA-yB)² );
}
