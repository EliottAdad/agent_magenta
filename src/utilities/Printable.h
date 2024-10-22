/*
 * Printable.h
 *
 *  Created on: 24 août 2024
 *      Author: esn
 */

#ifndef PRINTABLE_H_
#define PRINTABLE_H_

#include <iostream>
#include <string>
#include "functions.h"

class Printable {
public:
	Printable();
	virtual ~Printable();
	Printable(const Printable &other);

	virtual std::string to_string(const bool& spread=false, const bool& full_info=false, const unsigned int& indent=0) const;// :)
	virtual void print(const bool& spread=false, const bool& full_info=false, const unsigned int& indent=0) const;// :)
};

#endif /* PRINTABLE_H_ */
