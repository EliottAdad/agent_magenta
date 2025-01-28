/*
 * Sphere.h
 *
 *  Created on: 22 oct. 2024
 *      Author: esn
 */

#ifndef SPHERE_H_

#define SPHERE_H_

#include "Shape3D.h"
#include "../core/SN.h"
#include "../utilities/functions.h"

/*
 * ################
 *  Sphere<T> :)
 * ################
 */
template<typename T> class Sphere : public Shape3D<T> {
public:
	T r;

	Sphere();
	virtual ~Sphere();
	Sphere(const Sphere<T>& sphere);

	virtual std::unordered_set<std::shared_ptr<Point3D<T>>> getPoints() const;//To render the shape
	virtual std::unordered_set<std::shared_ptr<Line3D<T>>> getLines() const;//To render the shape

	virtual std::string to_string(const bool& spread=false, const bool& full_info=false, const unsigned char& indent=0) const;
	virtual void print(const bool& spread=false, const bool& full_info=false, const unsigned char& indent=0) const;

};

template<typename T> Sphere<T>::Sphere() {
	r=T{0,0};
}

template<typename T> Sphere<T>::~Sphere() {
	;
}

template<typename T> Sphere<T>::Sphere(const Sphere<T>& sphere) {
	r=sphere.r;
}



template<typename T> virtual std::unordered_set<std::shared_ptr<Point3D<T>>> Sphere<T>::getPoints() const{
	std::unordered_set<std::shared_ptr<Point3D<T>>> ppoints=pixelizeCircle(ppoint, (int)(r.to_m_type()), 8);
	return ppoints;
}

template<typename T> virtual std::unordered_set<std::shared_ptr<Line3D<T>>> Sphere<T>::getLines() const{
	;
}


template<typename T> std::string Sphere<T>::to_string(const bool& spread, const bool& full_info, const unsigned char& indent) const {
	std::string mes=((spread)?"\n" : "");

	if (full_info){
		mes+="SPHERE[";
		std::stringstream ss;
		ss << this;
		mes+=ss.str();
		mes+="]:";
		mes+=((spread)?"\n" : "");
	}
	return mes;
}

template<typename T> void Sphere<T>::print(const bool& spread, const bool& full_info, const unsigned char& indent) const {
	printTabs(indent);
	std::cout << this->to_string(spread, full_info, indent);
}


#endif /* SPHERE_H_ */
