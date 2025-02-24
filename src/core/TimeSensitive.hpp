/*
 * TimeSensitive.hpp
 *
 *  Created on: 24 août 2024
 *      Author: esn
 */

#ifndef TIMESENSITIVE_HPP_

#define TIMESENSITIVE_HPP_

#include <string>

#include "../utilities/functions.hpp"
//#include "../utilities/Printable.hpp"

/*
 * #################
 *  TimeSensitive :)
 * #################
 * @brief
 * Abstract class
 * Skeleton for time management.
 */
class TimeSensitive {
protected:
	float m_dt;

public:
	TimeSensitive();
	virtual ~TimeSensitive();
	TimeSensitive(const TimeSensitive& time_sensitive);

	virtual float getT() const = 0;
	virtual void setT(const float& dt) = 0;			//Used to prepare the logic behind the scenes
	virtual void apply() = 0;						//Can be used to execute an action (Ex: For the grav rule, move...)
};





inline TimeSensitive::TimeSensitive() {
	this->m_dt=0;
}

inline TimeSensitive::~TimeSensitive() {
	;
}

inline TimeSensitive::TimeSensitive(const TimeSensitive& time_sensitive) {
	this->m_dt=time_sensitive.getT();
}




inline float TimeSensitive::getT() const {
	return this->m_dt;
}

inline void TimeSensitive::setT(const float& dt) {
	this->m_dt=dt;
}

inline void TimeSensitive::apply() {//Useless
	this->m_dt=0;
}




#endif /* TIMESENSITIVE_HPP_ */
