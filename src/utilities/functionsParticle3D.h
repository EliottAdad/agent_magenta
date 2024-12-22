/*
 * functionsParticle3D.h
 *
 *  Created on: 22 decembre 2024
 *      Author: esn
 */

#ifndef FUNCTIONSPARTICLE3D_H_
#define FUNCTIONSPARTICLE3D_H_

#include <memory>

#include "../core/Particle3D.h"

/*
 * Functions
 */

template<typename M, typename E> std::unordered_set<std::shared_ptr<Particle3D<M, E>>> generate2DGridParticle3D(Point3D<M, E> p, SN<M, E> a, unsigned char n, SN<M, E> w);

/**
 * Generates a grid in the x-y plane centered on p.
 */
template<typename M, typename E> std::unordered_set<std::shared_ptr<Particle3D<M, E>>> generate2DGridParticle3D(Point3D<M, E> p, SN<M, E> a, unsigned char n, SN<M, E> w){
	std::unordered_set<std::shared_ptr<Particle3D<M, E>>> pparts;
	for (unsigned char i(0) ; i<n ; i++){
		for (unsigned char j(0) ; j<n ; j++){
			((M)(-1)*a/(M)2+(M)i*a/(M)(n-1)+p.x).print(true, true, 2);
			std::shared_ptr<Particle3D<M, E>> ppart=std::make_shared<Particle3D<M, E>>((M)(-1)*a/(M)2+(M)i*a/(M)(n-1)+p.x,
					(M)(-1)*a/(M)2+(M)j*a/(M)(n-1)+p.y,
					SN<M, E>{0, 0}+p.z,
					w);
			ppart->ps=std::make_shared<Vector3D<M, E>>(Point3D<M, E>{{0,0},{0,0},{0,0}});
			//std::shared_ptr<Particle3D<M, E>> ppart=std::make_shared<Particle3D<M, E>>((M)i*a/(M)n, (M)j*a/(M)n, SN<M, E>{0, 0}, w);
			pparts.insert(ppart);
		}
	}
	return pparts;
}

template<typename M, typename E> std::unordered_set<std::shared_ptr<Particle3D<M, E>>> generate3DGridParticle3D(Point3D<M, E> p, SN<M, E> a, unsigned char n, SN<M, E> w);

/**
 * Generates a grid in a cubic volume of side a centered on p.
 */
template<typename M, typename E> std::unordered_set<std::shared_ptr<Particle3D<M, E>>> generate3DGridParticle3D(Point3D<M, E> p, SN<M, E> a, unsigned char n, SN<M, E> w){
	std::unordered_set<std::shared_ptr<Particle3D<M, E>>> pparts;
	for (unsigned char i(0) ; i<n ; i++){
		for (unsigned char j(0) ; j<n ; j++){
			for (unsigned char k(0) ; k<n ; k++){
				pparts.insert(std::make_shared<Particle3D<M, E>>((M)(-1)*a/(M)2+(M)i*a/(M)(n-1)+p.x,
						(M)(-1)*a/(M)2+(M)j*a/(M)(n-1)+p.y,
						(M)(-1)*a/(M)2+(M)k*a/(M)(n-1)+p.z,
						w));
			}
		}
	}
	return pparts;
}


#endif /* FUNCTIONS_H_ */
