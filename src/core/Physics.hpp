/*
 * Physics.hpp
 *
 *  Created on: 4 juin 2024
 *      Author: esn
 */

#ifndef PHYSICS_HPP_

#define PHYSICS_HPP_

//#include <ctime>
#include <memory>
#include <chrono>
#include <unordered_set>

#include "TimeSensitive.hpp"
#include "VectorField.hpp"
//#include "../utilities/Printable.hpp"

/*
 * ###########
 *  Physics :)
 * ###########
 * Physics must be kept independent from Game (it should be self sufficient)
 * Gère le temps (à la place de TimeLoop, tout transvaser)
 * Exemples of objects it can drive: System<T>, Particle3D, ...
 */
class Physics {
public:
	float speed;					// Ratio between simulation_speed/real_world_speed
	unsigned char pps;				// Physics per second

	bool fcollide;
	bool fpause;
	std::unordered_set<std::shared_ptr<TimeSensitive>> ptime_sensitives;			//List of time sensitive objects

	Physics();
	Physics(const float& speed, const unsigned char& pps);
	virtual ~Physics();
	Physics(const Physics& phys);

	std::unordered_set<std::shared_ptr<TimeSensitive>> get();
	bool add(std::shared_ptr<TimeSensitive> ptime_sensitive);

	bool run(const unsigned int& steps=1);
	bool iterate(const float& dt);
};







inline Physics::Physics() {
	pps=40;//Computations per second
	speed=1;//Speed of the simulation

	fcollide=false;
	fpause=true;
}

inline Physics::Physics(const float& speed, const unsigned char& pps) {
	this->pps=pps;//Computations per second
	this->speed=speed;//Speed of the simulation

	fcollide=false;
	fpause=true;
}

inline Physics::~Physics() {
	ptime_sensitives.clear();
}

inline Physics::Physics(const Physics& phys) {
	pps=phys.pps;
	speed=phys.speed;

	fcollide=phys.fcollide;
	fpause=true;
}



inline std::unordered_set<std::shared_ptr<TimeSensitive>> Physics::get() {
	return ptime_sensitives;
}

inline bool Physics::add(std::shared_ptr<TimeSensitive> ptime_sensitive) {
	bool success=false;

	if (ptime_sensitive!=NULL){
		success=ptime_sensitives.insert(ptime_sensitive).second;
		//printf("Shush\n");
	}
	return success;
}




/*
 * If 0: infinite loop
 */
inline bool Physics::run(const unsigned int& steps) {
	std::chrono::time_point t1=std::chrono::system_clock::now();
	
	if (!fpause){
		unsigned int i(0);
		while (i<=steps){
			std::chrono::time_point t2=std::chrono::system_clock::now();
			std::chrono::duration dt=t2-t1;

			if (dt.count()>=1/(long double)pps*1000000000.){
				this->iterate(dt.count()/1000000000.);//The duration given by dt is in ns.
				
				printf("PPS %f\n", 1/(dt.count()/1000000000.));
				t1=t2;
				if (steps!=0){//If steps is not null
					i++;
				}
			}
		}
	}
	return fpause;
}

inline bool Physics::iterate(const float& dt) {
	//printf("Physics: iterate\n");
	for (std::shared_ptr<TimeSensitive> ptime_sensitive : ptime_sensitives){
		ptime_sensitive->setT(dt*speed);
		
		ptime_sensitive->apply();
	}
	return fpause;
}




#endif /* PHYSICS_HPP_ */
