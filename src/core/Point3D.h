/*
 * Point3D.h
 *
 *  Created on: 14 mai 2024
 *      Author: esn
 */

#ifndef POINT3D_H_
#define POINT3D_H_

#include "SN.h"
#include "../utilities/Printable.h"
#include <memory>





/*
 * #################
 *  Point3D<M, E> :)
 * #################
 */
template<typename M, typename E> struct Point3D : public Printable {
public:
	SN<M, E> x;
	SN<M, E> y;
	SN<M, E> z;

	Point3D();
	Point3D(const SN<M, E>& x, const SN<M, E>& y, const SN<M, E>& z);
	virtual ~Point3D();
	Point3D(const Point3D<M, E>& point);//Copy constructor

	virtual SN<M, E> getX() const;							// :)
	virtual SN<M, E> getY() const;							// :)
	virtual SN<M, E> getZ() const;							// :)
	virtual Point3D<M, E> getPosition() const;				// :)

	virtual void operator=(const Point3D<M, E>& p);			// :)
	virtual void operator=(const SN<M, E>& nb);				// :)
	virtual void operator+=(const Point3D<M, E>& p);			// :)
	virtual void operator+=(const SN<M, E>& nb);				// :)
	virtual void operator+=(const M& nb);		// :)
	virtual void operator-=(const Point3D<M, E>& p);			// :)
	virtual void operator-=(const SN<M, E>& nb);				// :)
	virtual void operator-=(const M& nb);		// :)
	virtual void operator*=(const SN<M, E>& k);				// :)
	virtual void operator*=(const M& k);		// :)
	virtual void operator/=(const SN<M, E>& k);				// :)
	virtual void operator/=(const M& k);		// :)

	virtual std::string to_string(const bool& spread=false, const bool& full_info=false, const unsigned char& indent=0) const;// :)
	virtual void print(const bool& spread=false, const bool& full_info=false, const unsigned char& indent=0) const;// :)
};

template<typename M, typename E> bool operator==(const Point3D<M, E>& p1, const Point3D<M, E>& p2);		// :)
template<typename M, typename E> bool operator!=(const Point3D<M, E>& p1, const Point3D<M, E>& p2);		// :)
template<typename M, typename E> bool operator<=(const Point3D<M, E>& p1, const Point3D<M, E>& p2);		// :)
template<typename M, typename E> bool operator>=(const Point3D<M, E>& p1, const Point3D<M, E>& p2);		// :)
template<typename M, typename E> Point3D<M, E> operator+(const Point3D<M, E>& p1, const Point3D<M, E>& p2);	// :)
template<typename M, typename E> Point3D<M, E> operator-(const Point3D<M, E>& p1, const Point3D<M, E>& p2);	// :)
template<typename M, typename E> Point3D<M, E> operator*(const Point3D<M, E>& p, const SN<M, E>& k);			// :)
template<typename M, typename E> Point3D<M, E> operator*(const SN<M, E>& k, const Point3D<M, E>& p);			// :)
template<typename M, typename E> Point3D<M, E> operator*(const Point3D<M, E>& p, const long double& k);	// :)
template<typename M, typename E> Point3D<M, E> operator*(const long double& k, const Point3D<M, E>& p);	// :)
template<typename M, typename E> Point3D<M, E> operator/(const Point3D<M, E>& p, const SN<M, E>& k);			// :)
//template<typename M, typename E> Point3D operator/(const SN& k, const Point3D& p);			// :)
template<typename M, typename E> Point3D<M, E> operator/(const Point3D<M, E>& p, const long double& k);	// :)
//template<typename M, typename E> Point3D operator/(const long double& k, const Point3D& p);	// :)




template<typename M, typename E> Point3D<M, E>::Point3D() {
	this->x=SN<M, E>{0,0};
	this->y=SN<M, E>{0,0};
	this->z=SN<M, E>{0,0};
}

template<typename M, typename E> Point3D<M, E>::Point3D(const SN<M, E>& x, const SN<M, E>& y, const SN<M, E>& z) {
	this->x=x;
	this->y=y;
	this->z=z;
}

template<typename M, typename E> Point3D<M, E>::~Point3D() {
	// TODO Auto-generated destructor stub
}

template<typename M, typename E> Point3D<M, E>::Point3D(const Point3D<M, E>& point) {
	this->x=point.x;
	this->y=point.y;
	this->z=point.z;
}



template<typename M, typename E> SN<M, E> Point3D<M, E>::getX() const {
	return x;
}

template<typename M, typename E> SN<M, E> Point3D<M, E>::getY() const {
	return y;
}

template<typename M, typename E> SN<M, E> Point3D<M, E>::getZ() const {
	return z;
}

template<typename M, typename E> Point3D<M, E> Point3D<M, E>::getPosition() const {
	return {x, y, z};
}

template<typename M, typename E> void Point3D<M, E>::operator=(const Point3D<M, E>& p) {
	this->x=p.x;
	this->y=p.y;
	this->z=p.z;
}

template<typename M, typename E> void Point3D<M, E>::operator=(const SN<M, E>& nb) {
	this->x=nb;
	this->y=nb;
	this->z=nb;
}

template<typename M, typename E> void Point3D<M, E>::operator+=(const Point3D<M, E>& p) {
	this->x+=p.x;
	this->y+=p.y;
	this->z+=p.z;
}

template<typename M, typename E> void Point3D<M, E>::operator+=(const SN<M, E>& nb) {
	this->x+=nb;
	this->y+=nb;
	this->z+=nb;
}

template<typename M, typename E> void Point3D<M, E>::operator+=(const M& nb) {
	this->x+=nb;
	this->y+=nb;
	this->z+=nb;
}

template<typename M, typename E> void Point3D<M, E>::operator-=(const Point3D<M, E>& p) {
	this->x-=p.x;
	this->y-=p.y;
	this->z-=p.z;
}

template<typename M, typename E> void Point3D<M, E>::operator-=(const SN<M, E>& nb) {
	this->x-=nb;
	this->y-=nb;
	this->z-=nb;
}

template<typename M, typename E> void Point3D<M, E>::operator-=(const M& nb) {
	this->x-=nb;
	this->y-=nb;
	this->z-=nb;
}

template<typename M, typename E> void Point3D<M, E>::operator*=(const SN<M, E>& k) {
	this->x*=k;
	this->y*=k;
	this->z*=k;
}

template<typename M, typename E> void Point3D<M, E>::operator*=(const M& k) {
	this->x*=k;
	this->y*=k;
	this->z*=k;
}

template<typename M, typename E> void Point3D<M, E>::operator/=(const SN<M, E>& k) {
	this->x/=k;
	this->y/=k;
	this->z/=k;
}

template<typename M, typename E> void Point3D<M, E>::operator/=(const M& k) {
	this->x/=k;
	this->y/=k;
	this->z/=k;
}





template<typename M, typename E> std::string Point3D<M, E>::to_string(const bool& spread, const bool& full_info, const unsigned char& indent) const {
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

template<typename M, typename E> void Point3D<M, E>::print(const bool& spread, const bool& full_info, const unsigned char& indent) const {
	printTabs(indent);
	std::cout << this->to_string(spread, full_info, indent);
}



template<typename M, typename E> bool operator==(const Point3D<M, E>& p1, const Point3D<M, E>& p2) {
	if (p1.x==p2.x && p1.y==p2.y && p1.z==p2.z){
		return true;
	}
	return false;
}

template<typename M, typename E> bool operator!=(const Point3D<M, E>& p1, const Point3D<M, E>& p2) {
	if (p1.x!=p2.x && p1.y!=p2.y && p1.z!=p2.z){
		return true;
	}
	return false;
}

template<typename M, typename E> bool operator<=(const Point3D<M, E>& p1, const Point3D<M, E>& p2) {
	if (p1.x<=p2.x && p1.y<=p2.y && p1.z<=p2.z){
		return true;
	}
	return false;
}

template<typename M, typename E> bool operator>=(const Point3D<M, E>& p1, const Point3D<M, E>& p2) {
	if (p1.x>=p2.x && p1.y>=p2.y && p1.z>=p2.z){
		return true;
	}
	return false;
}

template<typename M, typename E> Point3D<M, E> operator+(const Point3D<M, E>& p1, const Point3D<M, E>& p2) {
	return Point3D<M, E>{p1.x+p2.x, p1.y+p2.y, p1.z+p2.z};
}

template<typename M, typename E> Point3D<M, E> operator-(const Point3D<M, E>& p1, const Point3D<M, E>& p2) {
	return Point3D<M, E>{p1.x-p2.x, p1.y-p2.y, p1.z-p2.z};
}

template<typename M, typename E> Point3D<M, E> operator*(const Point3D<M, E>& p, const SN<M, E>& k) {
	return Point3D<M, E>{p.x*k, p.y*k, p.z*k};
}

template<typename M, typename E> Point3D<M, E> operator*(const SN<M, E>& k, const Point3D<M, E>& p) {
	return Point3D<M, E>{k*p.x, k*p.y, k*p.z};
}

template<typename M, typename E> Point3D<M, E> operator*(const Point3D<M, E>& p, const M& k) {
	return Point3D<M, E>{p.x*k, p.y*k, p.z*k};
}

template<typename M, typename E> Point3D<M, E> operator*(const M& k, const Point3D<M, E>& p) {
	return Point3D<M, E>{k*p.x, k*p.y, k*p.z};
}

template<typename M, typename E> Point3D<M, E> operator/(const Point3D<M, E>& p, const SN<M, E>& k) {
	return Point3D<M, E>{p.x/k, p.y/k, p.z/k};
}

/*Point3D operator/(const SN& k, const Point3D& p) {
	//Point3D* pnp=new Point3D{this->x/k, this->y/k, this->z/k};
	return {p.x/k, p.y/k, p.z/k};
}*/

template<typename M, typename E> Point3D<M, E> operator/(const Point3D<M, E>& p, const M& k) {
	return Point3D<M, E>{p.x/k, p.y/k, p.z/k};
}

/*Point3D operator/(const long double& k, const Point3D& p) {
	//Point3D* pnp=new Point3D{this->x/k, this->y/k, this->z/k};
	return {p.x/k, p.y/k, p.z/k};
}*/






/*
 * Functions
 */

//template <typename U> SN<S, T> getDistance(const U& p1, const U& p2);
/*
 * The type T needs: .to_long_double(), .getX(), .getY(), .getZ() that return SNs
 */
/*template <typename T> SN getDistance(const T& p1, const T& p2) {
	return {sqrt(pow((p1.getX()-p2.getX()).to_long_double(), (long int)2) + pow((p1.getY()-p2.getY()).to_long_double(), (long int)2) + pow((p1.getZ()-p2.getZ()).to_long_double(), (long int)2)), 0};// d=sqrt( (xA-xB)²+(yA-yB)² );
}*/

//template<typename M, typename E> SN<M, E> getDistance(const Point3D<M, E>& p1, const Point3D<M, E>& p2);

template<typename M, typename E> SN<M, E> getDistance(const Point3D<M, E>& p1, const Point3D<M, E>& p2) {
	M nm=sqrt(pow((p1.x-p2.x).to_m_type(), (long int)2) + pow((p1.y-p2.y).to_m_type(), (long int)2) + pow((p1.z-p2.z).to_m_type(), (long int)2));// d=sqrt( (xA-xB)²+(yA-yB)² )
	SN<M, E> nnb{nm, 0};
	nnb.recal();
	return nnb;
}




#endif /* POINT3D_H_ */
