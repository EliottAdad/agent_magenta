/*
 * functions_Particle3D.hpp
 *
 *  Created on: 22 decembre 2024
 *      Author: esn
 */

#ifndef FUNCTIONS_PARTICLE3D_HPP_

#define FUNCTIONS_PARTICLE3D_HPP_

#include <memory>

#include "Particle3D.hpp"

/*
 * Functions
 */

template<typename T> std::unordered_set<std::shared_ptr<Particle3D<T>>> generate2DGridParticle3D(Point3D<T> p, T a, unsigned char n, SN<float, char> mass);

/**
 * Generates a grid in the x-y plane centered on p.
 */
template<typename T> inline std::unordered_set<std::shared_ptr<Particle3D<T>>> generate2DGridParticle3D(Point3D<T> p, T a, unsigned char n, SN<float, char> mass){
	std::unordered_set<std::shared_ptr<Particle3D<T>>> pparts;
	printf("generate2DGridParticle3DA\n");
	for (unsigned char i(0) ; i<n ; i++){
		for (unsigned char j(0) ; j<n ; j++){
			printf("generate2DGridParticle3DB\n");
			//((M)(-1)*a/(M)2+(M)i*a/(M)(n-1)+p.x).print(true, true, 2);

			(T)(-1)*a/(T)2+(T)i*a/(T)(n-1)+p.x;
			(T)(-1)*a/(T)2+(T)j*a/(T)(n-1)+p.y;
			(T)0+p.z;
			mass;
			printf("generate2DGridParticle3DC\n");
			std::shared_ptr<Particle3D<T>> ppart=std::make_shared<Particle3D<T>>();
			/*std::shared_ptr<Particle3D<T>> ppart=std::make_shared<Particle3D<T>>(
					(T)(-1)*a/(T)2+(T)i*a/(T)(n-1)+p.x,
					(T)(-1)*a/(T)2+(T)j*a/(T)(n-1)+p.y,
					(T)0+p.z,
					mass);*/
			printf("generate2DGridParticle3DD\n");
			ppart->ps=std::make_shared<Vector3D<T>>(Point3D<T>{(T)0,(T)0,(T)0});
			printf("generate2DGridParticle3DE\n");
			//std::shared_ptr<Particle3D<T>> ppart=std::make_shared<Particle3D<T>>((M)i*a/(M)n, (M)j*a/(M)n, T{0, 0}, w);
			pparts.insert(ppart);
			printf("generate2DGridParticle3DF\n");
		}
	}
	return pparts;
}

template<typename T> inline std::unordered_set<std::shared_ptr<Particle3D<T>>> generate3DGridParticle3D(Point3D<T> p, T a, unsigned char n, T w);

/**
 * Generates a grid in a cubic volume of side a centered on p.
 */
template<typename T> inline std::unordered_set<std::shared_ptr<Particle3D<T>>> generate3DGridParticle3D(Point3D<T> p, T a, unsigned char n, T w){
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


#endif /* FUNCTIONS_PARTICLE3D_HPP_ */
