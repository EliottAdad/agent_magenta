/*
 * TimeSensitive.cpp
 *
 *  Created on: 24 août 2024
 *      Author: esn
 */

#include "TimeSensitive.h"

TimeSensitive::TimeSensitive() {
	// TODO Auto-generated constructor stub
}

TimeSensitive::~TimeSensitive() {
	// TODO Auto-generated destructor stub
}

/*TimeSensitive::TimeSensitive(const TimeSensitive &other) {
	// TODO Auto-generated constructor stub
}*/



void TimeSensitive::setT(const long double& dt) {
	// TODO Auto-generated constructor stub

}

void TimeSensitive::apply() {//Useless
	;
}



std::string TimeSensitive::to_string(const bool& spread, const bool& full_info, const unsigned int& indent) const {// :)
	std::string mes=(spread)?"\n":"";

	mes+="TIME_SENSITIVE";

	return mes;
}

void TimeSensitive::print(const bool& spread, const bool& full_info, const unsigned int& indent) const {// :)
	printTabs(indent);
	printf((this->to_string(spread, indent, full_info)).c_str());
}


