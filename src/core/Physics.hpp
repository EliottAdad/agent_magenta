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

//#include "TimeLoop.hpp"
//#include "Particle3DSet.hpp"
#include "VectorField.hpp"
#include "../utilities/Printable.hpp"

/*
 * ###########
 *  Physics :)
 * ###########
 * Physics must be kept independent from Game (it should be self sufficient)
 * Gère le temps (à la place de TimeLoop, tout transvaser)
 * Exemples of objects it can drive: System<T>, Particle3D, ...
 */
class Physics : public Printable {
public:
	float speed;					//Ratio between simulation_speed/real_world_speed
	unsigned char pps;			//Physics per second

	bool fcollide;
	bool fpause;
	std::unordered_set<std::shared_ptr<TimeSensitive>> ptime_sensitives;			//List of time sensitive objects

	Physics();
	Physics(const float& speed, const unsigned char& pps);
	virtual ~Physics();
	Physics(const Physics& phys);

	std::unordered_set<std::shared_ptr<TimeSensitive>> get();
	bool add(std::shared_ptr<TimeSensitive> ptime_sensitive);
	//std::unordered_set<Moveable*> getPMoveables();
	//bool addPMoveable(Moveable* pmoveabele);

	//bool loop();
	bool run(const unsigned int& steps=1);
	bool iterate(const float& dt);

	// From Printable
	virtual std::string to_string(const bool& spread=false, const bool& full_info=false, const unsigned char& indent=0) const;// :)
	virtual void print(const bool& spread=false, const bool& full_info=false, const unsigned char& indent=0) const;// :)
};

#endif /* PHYSICS_HPP_ */
