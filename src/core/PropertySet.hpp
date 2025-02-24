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





/**
 * #####################
 *  PropertySet<U, T> :)
 * #####################
 * @brief
 * U: Unit of the target
 * T: Unit of distances target
 * P: Type of the property (SN<float, char>, float, bool, ...)
 * Not properly designed yet.
 */
template<typename U, typename T> struct PropertySet {
public:
	U* ptarget;					// Object to which are attached the properties
	std::map<std::string, std::shared_ptr<T>> properties;
	
	PropertySet();
	PropertySet(const U* ptarget);
	virtual ~PropertySet();
	PropertySet(const PropertySet<U, T>& property_set);

	void add(const std::string& name, std::shared_ptr<T> pprop);
	std::shared_ptr<T> get(const std::string& name) const;
	
	void operator=(const PropertySet<U, T>& property_set);
	void operator+=(const PropertySet<U, T>& property_set);
};

template<typename U, typename T> PropertySet<U, T>::PropertySet() {
	this->ptarget=NULL;
}

template<typename U, typename T> PropertySet<U, T>::PropertySet(const U* ptarget) {
	this->ptarget=ptarget;
}

template<typename U, typename T> PropertySet<U, T>::~PropertySet() {
	this->ptarget=NULL;
}

template<typename U, typename T> PropertySet<U, T>::PropertySet(const PropertySet<U, T>& property_set) {
	this->ptarget=property_set.ptarget;
}




/**
 * Inserts
 */
template<typename U, typename T> void PropertySet<U, T>::add(const std::string& name, std::shared_ptr<T> pprop) {
	this->properties.insert({name, pprop});
}

/**
 * Returns the corresponding.
 */
template<typename U, typename T> std::shared_ptr<T> PropertySet<U, T>::get(const std::string& name) const {
	return this->properties.at(name);
}

/*
 * Operators
 */

/**
 * h
 */
template<typename U, typename T> void PropertySet<U, T>::operator=(const PropertySet<U, T>& property_set) {
	this->properties=property_set.properties;
}

/**
 * TODO
 */
template<typename U, typename T> void PropertySet<U, T>::operator+=(const PropertySet<U, T>& property_set) {
	this->properties=property_set.properties;
}
	


#endif /* PROPERTYSET_HPP_ */
