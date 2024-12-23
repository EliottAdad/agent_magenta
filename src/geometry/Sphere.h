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
template<typename M, typename E> class Sphere : public Shape3D {
public:
	SN<M, E> r;

	Sphere();
	virtual ~Sphere();
	Sphere(const Sphere<M, E>& sphere);

	/*SN<> getR() const;
	void setR(const SN<M, E>& r);*/
};

template<typename M, typename E> Sphere<M, E>::Sphere() {
	r=SN<M, E>{0,0};
}

template<typename M, typename E> Sphere<M, E>::~Sphere() {
	r=SN<M, E>{0,0};
}

template<typename M, typename E> Sphere<M, E>::Sphere(const Sphere<M, E>& sphere) {
	r=sphere.r;
}


#endif /* SPHERE_H_ */
