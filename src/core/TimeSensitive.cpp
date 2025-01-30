/*
 * TimeSensitive.cpp
 *
 *  Created on: 24 août 2024
 *      Author: esn
 */

#include "TimeSensitive.h"

TimeSensitive::TimeSensitive() {
	// TODO Auto-generated constructor stub
	m_dt=0;
}

TimeSensitive::~TimeSensitive() {
	// TODO Auto-generated destructor stub
}

/*TimeSensitive::TimeSensitive(const TimeSensitive &other) {
	// TODO Auto-generated constructor stub
}*/




float TimeSensitive::getT() {
	return m_dt;
}

void TimeSensitive::setT(const float& dt) {
	m_dt=dt;
}

void TimeSensitive::apply() {//Useless
	m_dt=0;
}



std::string TimeSensitive::to_string(const bool& spread, const bool& full_info, const unsigned char& indent) const {// :)
	std::string mes=(spread)?"\n":"";

	mes+="TIME_SENSITIVE";

	return mes;
}

void TimeSensitive::print(const bool& spread, const bool& full_info, const unsigned char& indent) const {// :)
	printTabs(indent);
	std::cout << this->to_string(spread, full_info, indent);
}


