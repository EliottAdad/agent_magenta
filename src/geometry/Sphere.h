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
 *  Sphere<M, E> :)
 * ################
 */
template<typename M, typename E> class Sphere : public Shape3D<M, E> {
public:
	SN<M, E> r;

	Sphere();
	virtual ~Sphere();
	Sphere(const Sphere<M, E>& sphere);

	virtual std::unordered_set<std::shared_ptr<Point3D<M, E>>> getPoints() const;//To render the shape
	virtual std::unordered_set<std::shared_ptr<Line3D<M, E>>> getLines() const;//To render the shape

	virtual std::string to_string(const bool& spread=false, const bool& full_info=false, const unsigned char& indent=0) const;
	virtual void print(const bool& spread=false, const bool& full_info=false, const unsigned char& indent=0) const;

};

template<typename M, typename E> Sphere<M, E>::Sphere() {
	r=SN<M, E>{0,0};
}

template<typename M, typename E> Sphere<M, E>::~Sphere() {
	;
}

template<typename M, typename E> Sphere<M, E>::Sphere(const Sphere<M, E>& sphere) {
	r=sphere.r;
}



template<typename M, typename E> virtual std::unordered_set<std::shared_ptr<Point3D<M, E>>> Sphere<M, E>::getPoints() const{
	std::unordered_set<std::shared_ptr<Point3D<M, E>>> ppoints=pixelizeCircle(ppoint, (int)(r.to_m_type()), 8);
	return ppoints;
}

template<typename M, typename E> virtual std::unordered_set<std::shared_ptr<Line3D<M, E>>> Sphere<M, E>::getLines() const{
	;
}


template<typename M, typename E> std::string Sphere<M, E>::to_string(const bool& spread, const bool& full_info, const unsigned char& indent) const {
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

template<typename M, typename E> void Sphere<M, E>::print(const bool& spread, const bool& full_info, const unsigned char& indent) const {
	printTabs(indent);
	std::cout << this->to_string(spread, full_info, indent);
}


#endif /* SPHERE_H_ */
