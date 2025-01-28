/*
 * functionsParticle3D.h
 *
 *  Created on: 22 decembre 2024
 *      Author: esn
 */

#ifndef FUNCTIONSPARTICLE3D_H_
#define FUNCTIONSPARTICLE3D_H_

#include <memory>

#include "../geometry/Particle3D.h"

/*
 * Functions
 */

template<typename T> std::unordered_set<std::shared_ptr<Particle3D<T>>> generate2DGridParticle3D(Point3D<T> p, T a, unsigned char n, T w);

/**
 * Generates a grid in the x-y plane centered on p.
 */
template<typename T> std::unordered_set<std::shared_ptr<Particle3D<T>>> generate2DGridParticle3D(Point3D<T> p, T a, unsigned char n, T w){
	std::unordered_set<std::shared_ptr<Particle3D<T>>> pparts;
	for (unsigned char i(0) ; i<n ; i++){
		for (unsigned char j(0) ; j<n ; j++){
			//((M)(-1)*a/(M)2+(M)i*a/(M)(n-1)+p.x).print(true, true, 2);
			std::shared_ptr<Particle3D<T>> ppart=std::make_shared<Particle3D<T>>(
					(T)(-1)*a/(T)2+(T)i*a/(T)(n-1)+p.x,
					(T)(-1)*a/(T)2+(T)j*a/(T)(n-1)+p.y,
					(T)0+p.z,
					w);
			ppart->ps=std::make_shared<Vector3D<T>>(Point3D<T>{(T)0,(T)0,(T)0});
			//std::shared_ptr<Particle3D<T>> ppart=std::make_shared<Particle3D<T>>((M)i*a/(M)n, (M)j*a/(M)n, T{0, 0}, w);
			pparts.insert(ppart);
		}
	}
	return pparts;
}

template<typename T> std::unordered_set<std::shared_ptr<Particle3D<T>>> generate3DGridParticle3D(Point3D<T> p, T a, unsigned char n, T w);

/**
 * Generates a grid in a cubic volume of side a centered on p.
 */
template<typename T> std::unordered_set<std::shared_ptr<Particle3D<T>>> generate3DGridParticle3D(Point3D<T> p, T a, unsigned char n, T w){
	std::unordered_set<std::shared_ptr<Particle3D<T>>> pparts;
	for (unsigned char i(0) ; i<n ; i++){
		for (unsigned char j(0) ; j<n ; j++){
			for (unsigned char k(0) ; k<n ; k++){
				std::shared_ptr<Particle3D<T>> ppart=std::make_shared<Particle3D<T>>(
						(T)(-1)*a/(T)2+(T)i*a/(T)(n-1)+p.x,
						(T)(-1)*a/(T)2+(T)j*a/(T)(n-1)+p.y,
						(T)(-1)*a/(T)2+(T)k*a/(T)(n-1)+p.z,
						w);
				ppart->ps=std::make_shared<Vector3D<T>>(Point3D<T>{(T)0,(T)0,(T)0});
				pparts.insert(ppart);
			}
		}
	}
	return pparts;
}


#endif /* FUNCTIONSPARTICLE3D_H_ */
