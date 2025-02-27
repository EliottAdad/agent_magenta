/*
 * Physics.hpp
 *
 *  Created on: 4 juin 2024
 *      Author: esn
 */

#ifndef TIME_MANAGER_HPP_

#define TIME_MANAGER_HPP_

//#include <ctime>
#include <memory>
#include <chrono>
#include <unordered_set>

#include "TimeSensitive.hpp"
//#include "VectorField3D.hpp"
//#include "../utilities/Printable.hpp"

/**
 * ###############
 *  TimeManager :)
 * ###############
 * @brief
 * TimeManager must be kept independent from Game (it should be self sufficient)
 * Gère le temps
 * Exemples of objects it can drive: System<T>, Particle3D, ...
 * TODO : change to TimeManager
 */
class TimeManager {
public:
	float speed;					// Ratio between simulation_speed/real_world_speed
	unsigned char pps;				// Pulse Per Second

	bool fcollide;
	bool fpause;
	std::unordered_set<std::shared_ptr<TimeSensitive>> ptime_sensitives;			//List of time sensitive objects

	TimeManager();
	TimeManager(const float& speed, const unsigned char& pps);
	virtual ~TimeManager();
	TimeManager(const TimeManager& phys);

	std::unordered_set<std::shared_ptr<TimeSensitive>> get();
	bool add(std::shared_ptr<TimeSensitive> ptime_sensitive);

	bool run(const unsigned int& steps=1);
	bool iterate(const float& dt);
};







inline TimeManager::TimeManager() {
	pps=40;//Computations per second
	speed=1;//Speed of the simulation

	fcollide=false;
	fpause=true;
}

inline TimeManager::TimeManager(const float& speed, const unsigned char& pps) {
	this->pps=pps;//Computations per second
	this->speed=speed;//Speed of the simulation

	fcollide=false;
	fpause=true;
}

inline TimeManager::~TimeManager() {
	ptime_sensitives.clear();
}

inline TimeManager::TimeManager(const TimeManager& phys) {
	pps=phys.pps;
	speed=phys.speed;

	fcollide=phys.fcollide;
	fpause=true;
}



inline std::unordered_set<std::shared_ptr<TimeSensitive>> TimeManager::get() {
	return ptime_sensitives;
}

inline bool TimeManager::add(std::shared_ptr<TimeSensitive> ptime_sensitive) {
	bool success=false;

	if (ptime_sensitive!=NULL){
		success=this->ptime_sensitives.insert(ptime_sensitive).second;
	}
	return success;
}




/*
 * If 0: infinite loop
 */
inline bool TimeManager::run(const unsigned int& steps) {
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

inline bool TimeManager::iterate(const float& dt) {
	//printf("Physics: iterate\n");
	for (std::shared_ptr<TimeSensitive> ptime_sensitive : ptime_sensitives){
		ptime_sensitive->setT(dt*speed);
		
		ptime_sensitive->apply();
	}
	return fpause;
}




#endif /* TIME_MANAGER_HPP_ */
