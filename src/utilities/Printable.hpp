/*
 * Printable.hpp
 *
 *  Created on: 24 août 2024
 *      Author: esn
 */

#ifndef PRINTABLE_HPP_
#define PRINTABLE_HPP_

#include <iostream>
#include <string>
#include <sstream>

#include "functions.hpp"

class Printable {
public:
	Printable();
	virtual ~Printable();
	Printable(const Printable &other);

	virtual std::string to_string(const bool& spread=false, const bool& full_info=false, const unsigned char& indent=0) const;// :)
	virtual void print(const bool& spread=false, const bool& full_info=false, const unsigned char& indent=0) const;// :)
};

#endif /* PRINTABLE_HPP_ */
