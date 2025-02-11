/*
 * TimeSensitive.cpp
 *
 *  Created on: 24 août 2024
 *      Author: esn
 */

#include "TimeSensitive.hpp"

TimeSensitive::TimeSensitive() {
	m_dt=0;
}

TimeSensitive::~TimeSensitive() {
	;
}

TimeSensitive::TimeSensitive(const TimeSensitive& time_sensitive) {
	m_dt=time_sensitive.getT();
}




float TimeSensitive::getT() const {
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

	mes+="TIME_SENSITIVE\n";

	return mes;
}

void TimeSensitive::print(const bool& spread, const bool& full_info, const unsigned char& indent) const {// :)
	printTabs(indent);
	std::cout << this->to_string(spread, full_info, indent);
}


