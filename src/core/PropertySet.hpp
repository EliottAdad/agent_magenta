/*
 * PropertySet.hpp
 *
 *  Created on: 4 juin 2024
 *      Author: esn
 */

#ifndef PROPERTYSET_HPP_

#define PROPERTYSET_HPP_

#include <memory>
#include <string>
#include <map>

#include "SN.hpp"

#define PROPERTYSET std::map<std::string, std::shared_ptr<void>>



/*
 * ##################
 *  PropertySet<U> :)
 * ##################
 * U: Unit of the target
 * P: Type of the property (SN<float, char>, float, bool, ...)
 * Not properly designed yet.
 */
template<typename U> struct PropertySet {
public:
	//U* ptarget;					// Object to which are attached the properties
	//std::shared_ptr<std::map<std::string, std::shared_ptr<P>>> pproperties;		// Properties
	PROPERTYSET properties;
	
	PropertySet();
	//PropertySet(std::shared_ptr<U> ptarget);
	virtual ~PropertySet();
	PropertySet(const PropertySet<U>& property_set);

	void add(const std::string& name, std::shared_ptr<void> pprop);
	std::shared_ptr<void> get(const std::string& name) const;
	
	void operator=(const PropertySet<U>& properties);
};

template<typename U> PropertySet<U>::PropertySet() {
	//this->ptarget=NULL;
	//this->properties={};
}

/*template<typename U> PropertySet<U>::PropertySet(std::shared_ptr<U> ptarget) {
	//this->ptarget=ptarget;
}*/

template<typename U> PropertySet<U>::~PropertySet() {
	//this->ptarget=NULL;
}

template<typename U> PropertySet<U>::PropertySet(const PropertySet<U>& property_set) {
	//this->ptarget=property_set.ptarget;
}




/**
 * Inserts
 */
template<typename U> void PropertySet<U>::add(const std::string& name, std::shared_ptr<void> pprop) {
	this->properties.insert({name, pprop});
}

/**
 * Returns the corresponding.
 */
template<typename U> std::shared_ptr<void> PropertySet<U>::get(const std::string& name) const {
	return this->properties.at(name);
}

/**
 * Copy
 */
template<typename U> void PropertySet<U>::operator=(const PropertySet<U>& property_set) {
	this->properties=property_set.properties;
}
	


#endif /* PROPERTYSET_HPP_ */
