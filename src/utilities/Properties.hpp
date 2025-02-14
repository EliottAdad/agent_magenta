/*
 * Properties.hpp
 *
 *  Created on: 29 janv. 2025
 *      Author: esn
 */

#ifndef PROPERTIES_HPP_

#define PROPERTIES_HPP_

#include <memory>
#include <unordered_map>

struct Properties {
	std::unordered_map<std::string, std::shared_ptr<void>> pproperties[10];

	//Properties();
	//virtual ~Properties();
	//Properties(const Properties& properties);
};






/*Properties::Properties() {
	// TODO Auto-generated constructor stub

}

Properties::~Properties() {
	// TODO Auto-generated destructor stub
}

Properties::Properties(const Properties &other) {
	// TODO Auto-generated constructor stub

}*/



#endif /* PROPERTIES_HPP_ */
