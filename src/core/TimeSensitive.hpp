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
#include "../utilities/Printable.hpp"

/*
 * #################
 *  TimeSensitive :)
 * #################
 * Squeleton for time management.
 */
class TimeSensitive : public Printable {
protected:
	float m_dt;

public:
	TimeSensitive();
	virtual ~TimeSensitive();
	TimeSensitive(const TimeSensitive& time_sensitive);

	virtual float getT() const;
	virtual void setT(const float& dt);			//Used to prepare the logic behind the scenes
	virtual void apply();						//Can be used to execute an action (Ex: For the grav rule, move...)

	// From Printable
	virtual std::string to_string(const bool& spread=false, const bool& full_info=false, const unsigned char& indent=0) const;// :)
	virtual void print(const bool& spread=false, const bool& full_info=false, const unsigned char& indent=0) const;// :)
};

#endif /* TIMESENSITIVE_HPP_ */
