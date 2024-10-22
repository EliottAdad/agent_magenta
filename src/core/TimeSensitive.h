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

class TimeSensitive : public Printable {
public:
	TimeSensitive();
	virtual ~TimeSensitive();
	//TimeSensitive(const TimeSensitive &other);

	virtual void setT(const long double& dt);

	virtual std::string to_string(const bool& spread=false, const bool& full_info=false, const unsigned int& indent=0) const;// :)
	virtual void print(const bool& spread=false, const bool& full_info=false, const unsigned int& indent=0) const;// :)
};

#endif /* TIMESENSITIVE_H_ */
