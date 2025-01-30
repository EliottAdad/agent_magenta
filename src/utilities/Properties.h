/*
 * Properties.h
 *
 *  Created on: 29 janv. 2025
 *      Author: esn
 */

#ifndef PROPERTIES_H_

#define PROPERTIES_H_

#include <memory>
#include <unordered_map>

struct Properties {
	std::unordered_map<std::string, std::shared_ptr<void>> pproperties[10];

	//Properties();
	//virtual ~Properties();
	//Properties(const Properties& properties);
};

#endif /* PROPERTIES_H_ */
