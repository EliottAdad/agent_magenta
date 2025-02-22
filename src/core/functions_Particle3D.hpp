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



template<typename T> std::unordered_set<std::shared_ptr<Particle3D<T>>> generate2DGridParticle3D(Point3D<T> p, T a, unsigned char n, T mass);
template<typename T> std::unordered_set<std::shared_ptr<Particle3D<T>>> generate3DGridParticle3D(Point3D<T> p, T a, unsigned char n, T mass);

template<typename T> T getMass(Particle3D<T> p);
template<typename T> T getCharge(Particle3D<T> p);



/*
 * Functions
 */



/**
 * Generates a grid in the x-y plane centered on p.
 */
template<typename T> inline std::unordered_set<std::shared_ptr<Particle3D<T>>> generate2DGridParticle3D(Point3D<T> p, T a, unsigned char n, T mass){
	std::unordered_set<std::shared_ptr<Particle3D<T>>> pparts;
	//printf("generate2DGridParticle3DA\n");
	for (unsigned char i(0) ; i<n ; i++){
		for (unsigned char j(0) ; j<n ; j++){
			//printf("generate2DGridParticle3DB\n");

			//printf("generate2DGridParticle3DC\n");
			//std::shared_ptr<Particle3D<T>> ppart=std::make_shared<Particle3D<T>>();
			std::shared_ptr<Particle3D<T>> ppart=std::make_shared<Particle3D<T>>(
					(T)(-1)*a/(T)2+(T)i*a/(T)(n-1)+p.x,
					(T)(-1)*a/(T)2+(T)j*a/(T)(n-1)+p.y,
					(T)0+p.z,
					mass);
			//printf("generate2DGridParticle3DD\n");
			ppart->ps=std::make_shared<Vector3D<T>>(Point3D<T>{(T)0,(T)0,(T)0});
			//printf("generate2DGridParticle3DE\n");
			//std::shared_ptr<Particle3D<T>> ppart=std::make_shared<Particle3D<T>>((M)i*a/(M)n, (M)j*a/(M)n, T{0, 0}, w);
			pparts.insert(ppart);
			//printf("generate2DGridParticle3DF\n");
		}
	}
	return pparts;
}

/**
 * Generates a grid in a cubic volume of side a centered on p.
 */
template<typename T> inline std::unordered_set<std::shared_ptr<Particle3D<T>>> generate3DGridParticle3D(Point3D<T> p, T a, unsigned char n, T mass){
	std::unordered_set<std::shared_ptr<Particle3D<T>>> pparts;
	for (unsigned char i(0) ; i<n ; i++){
		for (unsigned char j(0) ; j<n ; j++){
			for (unsigned char k(0) ; k<n ; k++){
				std::shared_ptr<Particle3D<T>> ppart=std::make_shared<Particle3D<T>>(
						(T)(-1)*a/(T)2+(T)i*a/(T)(n-1)+p.x,
						(T)(-1)*a/(T)2+(T)j*a/(T)(n-1)+p.y,
						(T)(-1)*a/(T)2+(T)k*a/(T)(n-1)+p.z,
						mass);
				ppart->ps=std::make_shared<Vector3D<T>>(Point3D<T>{(T)0,(T)0,(T)0});
				pparts.insert(ppart);
			}
		}
	}
	return pparts;
}



/* 
 * Mass, charge,...
 */

/**
 * j
 */
/*template<typename T> inline T getMass(const Particle3D<T>& p) {
	T w=(T)0;

	//if (pfields!=NULL){
		w=(T)(*(p.properties.get("mass")));
	//}

	return w;
}

template<typename T> inline T getCharge(const Particle3D<T>& p) {
	T w=(T)0;

	//if (pfields!=NULL){
		w=(T)(*(p.properties.get("charge")));
	//}

	return w;
}*/

template<typename T> inline T getMass(const Particle3D<T>& p) {// Pas la le probleme, avant
	//T w=(T)0;
	T w={1, 19};

	//if (pfields!=NULL){
		//w=(T)(*(std::static_pointer_cast<T>(p.properties.get("mass"))));
	//}

	return w;
}

template<typename T> inline T getCharge(const Particle3D<T>& p) {
	T w=(T)0;

	//if (pfields!=NULL){
	//*(p.properties.get("charge"));
		w=(T)(*(std::static_pointer_cast<T>(p.properties.get("charge"))));
	//}

	return w;
}

#endif /* FUNCTIONS_PARTICLE3D_HPP_ */
