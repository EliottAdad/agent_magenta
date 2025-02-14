/*
 * Sphere.hpp
 *
 *  Created on: 22 oct. 2024
 *      Author: esn
 */

#ifndef SPHERE_HPP_

#define SPHERE_HPP_

#include "Shape3D.hpp"
#include "../core/SN.hpp"
#include "../utilities/functions.hpp"

/*
 * #############
 *  Sphere<T> :)
 * #############
 */
template<typename T> class Sphere : public Shape3D<T> {
public:
	T r;

	Sphere();
	virtual ~Sphere();
	Sphere(const Sphere<T>& sphere);

	virtual std::unordered_set<std::shared_ptr<Point3D<T>>> getPoints() const;//To render the shape
	virtual std::unordered_set<std::shared_ptr<Line3D<T>>> getLines() const;//To render the shape
};





template<typename T> inline Sphere<T>::Sphere() {
	r=(T)0;
}

template<typename T> inline Sphere<T>::~Sphere() {
	;
}

template<typename T> inline Sphere<T>::Sphere(const Sphere<T>& sphere) {
	r=sphere.r;
}



template<typename T> inline virtual std::unordered_set<std::shared_ptr<Point3D<T>>> Sphere<T>::getPoints() const{
	std::unordered_set<std::shared_ptr<Point3D<T>>> ppoints=pixelizeCircle(ppoint, (int)(r.to_m_type()), 8);
	return ppoints;
}

template<typename T> inline virtual std::unordered_set<std::shared_ptr<Line3D<T>>> Sphere<T>::getLines() const{
	;
}


#endif /* SPHERE_HPP_ */
