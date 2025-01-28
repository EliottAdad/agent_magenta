/*
 * WeightedPoint3D.h
 *
 *  Created on: 14 mai 2024
 *      Author: esn
 */

#ifndef WEIGHTEDPOINT3D_H_

#define WEIGHTEDPOINT3D_H_

#include "../core/Point3D.h"

/*
 * ######################
 *  WeightedPoint3D<T> :)
 * ######################
 * A point with a weight (useless)
 */
template<typename T> struct WeightedPoint3D : public Point3D<T> {
	T w;

	WeightedPoint3D();
	WeightedPoint3D(const Point3D<T>& p, const T& w={1,0});
	WeightedPoint3D(const T& x, const T& y, const T& z, const T& w);
	virtual ~WeightedPoint3D();

	virtual void operator=(const WeightedPoint3D<T>& wp);// :)
	//virtual void operator+=(const Point3D& p);// :)Not necessary
	//virtual void operator-=(const Point3D& p);// :)Not necessary

	virtual T getW() const;

	virtual std::string to_string(const bool& spread=false, const bool& full_info=false, const unsigned char& indent=0) const;// :)
	virtual void print(const bool& spread=false, const bool& full_info=false, const unsigned char& indent=0) const;// :)
};


template<typename T> WeightedPoint3D<T>::WeightedPoint3D() {
	this->x=SN<float, char>{0,0};
	this->y=SN<float, char>{0,0};
	this->z=SN<float, char>{0,0};
	this->w=SN<float, char>{1,0};
}

template<typename T> WeightedPoint3D<T>::WeightedPoint3D(const Point3D<T>& p, const T& w) {
	this->x=p.x;
	this->y=p.y;
	this->z=p.z;
	this->w=w;
}

template<typename T> WeightedPoint3D<T>::WeightedPoint3D(const T& x, const T& y, const T& z, const T& w) {
	this->x=x;
	this->y=y;
	this->z=z;
	this->w=w;
}

/*
template<typename T> WeightedPoint3D::WeightedPoint3D(const LSN& x, const LSN& y, const LSN& z, const LSN& w) {
	this->x=x;
	this->y=y;
	this->z=z;
	this->w=w;
}*/

template<typename T> WeightedPoint3D<T>::~WeightedPoint3D() {
	// TODO Auto-generated destructor stub
}



template<typename T> void WeightedPoint3D<T>::operator=(const WeightedPoint3D<T>& wp) {
	this->x=wp.x;
	this->y=wp.y;
	this->z=wp.z;
	this->w=wp.w;
}
/*
template<typename T> void WeightedPoint3D::operator+=(const Point3D& p) {
	x+=p.x;
	y+=p.y;
	z+=p.z;
}

template<typename T> void WeightedPoint3D::operator-=(const Point3D& p) {
	x-=p.x;
	y-=p.y;
	z-=p.z;
}*/

template<typename T> T WeightedPoint3D<T>::getW() const {
	return w;
}

template<typename T> std::string WeightedPoint3D<T>::to_string(const bool& spread, const bool& full_info, const unsigned char& indent) const {
	std::string mes=((spread)?"\n" : "");

	if (full_info){
		mes+="WEIGHTEDPOINT3D[";
		std::stringstream ss;
		ss << this;
		mes+=ss.str();
		mes+="]:";
		mes+=((spread)?"\n" + to_stringTabs(1) : "");
	}

	mes+="(x:" + this->x.to_string() + " ; y:" + this->y.to_string() + " ; z:" + this->z.to_string() + " ; w:" + w.to_string()+")";

	return mes;
}

template<typename T> void WeightedPoint3D<T>::print(const bool& spread, const bool& full_info, const unsigned char& indent) const {
	printTabs(indent);
	std::cout << this->to_string(spread, full_info, indent);
}



#endif /* WEIGHTEDPOINT3D_H_ */
