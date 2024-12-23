/*
 * Sphere.h
 *
 *  Created on: 22 oct. 2024
 *      Author: esn
 */

#ifndef SPHERE_H_

#define SPHERE_H_

#include "Shape3D.h"
#include "../core/LSN.h"

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


#endif /* SPHERE_H_ */
