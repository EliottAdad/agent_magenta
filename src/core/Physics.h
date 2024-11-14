/*
 * Physics.h
 *
 *  Created on: 4 juin 2024
 *      Author: esn
 */

#ifndef PHYSICS_H_
#define PHYSICS_H_

//#include <ctime>
#include <chrono>
#include <unordered_set>

#include "TimeLoop.h"
//#include "Particle3DSet.h"
#include "VectorField.h"
#include "../utilities/Printable.h"

/*
 * ###########
 *  Physics :)
 * ###########
 * Physics must be kept independent from Game (it should be self sufficient)
 * Gère le temps (à la place de TimeLoop, tout transvaser)
 * Exemples of objects it can drive: System<T>, Particle3D, ...
 */
class Physics : public Printable {
private:
	float m_speed;					//Ratio between simulation_speed/real_world_speed
	unsigned int m_pps;				//Physics per second

	bool m_fcollide;
	bool m_fpause;
	std::unordered_set<TimeSensitive*> m_ptime_sensitives;			//List of time sensitive objects
	//std::unordered_set<Moveable*> m_pmoveables;			//List of moveable objects

public:
	Physics();
	virtual ~Physics();
	Physics(const Physics& phys);

	float getSpeed() const;
	void setSpeed(const float& speed);
	unsigned int getPPS() const;
	void setPPS(const unsigned int& pps);

	std::unordered_set<TimeSensitive*> getPTimeSensitives();
	bool addPTimeSensitive(TimeSensitive* ptime_sensitive);
	//std::unordered_set<Moveable*> getPMoveables();
	//bool addPMoveable(Moveable* pmoveabele);

	unsigned int getFCollide() const;
	void setFCollide(const bool& bcollide);
	unsigned int getFPause() const;
	void setFPause(const bool& bpause);

	//bool loop();
	bool run(const unsigned int& steps=1);
	bool iterate(const long double& dt);

	virtual std::string to_string(const bool& spread=false, const bool& full_info=false, const unsigned int& indent=0) const;// :)
	virtual void print(const bool& spread=false, const bool& full_info=false, const unsigned int& indent=0) const;// :)
};

#endif /* PHYSICS_H_ */
