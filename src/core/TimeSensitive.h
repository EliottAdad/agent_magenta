/*
 * TimeSensitive.h
 *
 *  Created on: 24 août 2024
 *      Author: esn
 */

#ifndef TIMESENSITIVE_H_

#define TIMESENSITIVE_H_

#include <string>

#include "../utilities/functions.h"
#include "../utilities/Printable.h"

/*
 * #################
 *  TimeSensitive :)
 * #################
 */
class TimeSensitive : public Printable {
protected:
	float m_dt;

public:
	TimeSensitive();
	virtual ~TimeSensitive();
	//TimeSensitive(const TimeSensitive &other);

	virtual void setT(const float& dt);	//Used to prepare the logic behind the scenes
	virtual void apply();						//Can used to execute an action (Ex: For the grav rule, move...)

	virtual std::string to_string(const bool& spread=false, const bool& full_info=false, const unsigned char& indent=0) const;// :)
	virtual void print(const bool& spread=false, const bool& full_info=false, const unsigned char& indent=0) const;// :)
};

#endif /* TIMESENSITIVE_H_ */
