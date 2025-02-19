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

#define PROPERTYSETSN std::map<std::string, SN<float, char>>
#define PROPERTYSETF std::map<std::string, float>
#define PROPERTYSETD std::map<std::string, int>
//#define PROPERTYSETF<T> PropertySet<T, float>



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
	PROPERTYSETSN properties_sn;
	//std::map<std::string, std::shared_ptr<SN<float, char>>> psn;
	PROPERTYSETF properties_f;
	PROPERTYSETD properties_d;
	
	PropertySet();
	//PropertySet(std::shared_ptr<U> ptarget);
	virtual ~PropertySet();
	PropertySet(const PropertySet<U>& property_set);

	void add(const std::string& name, const SN<float, char>& nb);
	void add(const std::string& name, const float& f);
	void add(const std::string& name, const int& d);
	SN<float, char> getSN(const std::string& name) const;
	float getF(const std::string& name) const;
	int getD(const std::string& name) const;
	
	void operator=(const PropertySet& properties);
};



template<typename U> PropertySet<U>::PropertySet() {
	//this->ptarget=NULL;
	this->properties_sn={};
	this->properties_f={};
	this->properties_d={};
}

/*template<typename U> PropertySet<U>::PropertySet(std::shared_ptr<U> ptarget) {
	//this->ptarget=ptarget;
}*/

template<typename U> PropertySet<U>::~PropertySet() {
	;
}

template<typename U> PropertySet<U>::PropertySet(const PropertySet<U>& property_set) {
	//this->ptarget=property_set.ptarget;
}




/**
 * Inserts a SN
 */
template<typename U> void PropertySet<U>::add(const std::string& name, const SN<float, char>& nb) {
	this->properties_sn.insert({name, nb});
}

/**
 * Inserts a float
 */
template<typename U> void PropertySet<U>::add(const std::string& name, const float& f) {
	this->properties_f.insert({name, f});
}

/**
 * Inserts an int
 */
template<typename U> void PropertySet<U>::add(const std::string& name, const int& d) {
	this->properties_d.insert({name, d});
}

/**
 * Returns the corresponding SN.
 */
template<typename U> SN<float, char> PropertySet<U>::getSN(const std::string& name) const {
	return this->properties_sn.at(name);
}

/**
 * Returns the corresponding float.
 */
template<typename U> float PropertySet<U>::getF(const std::string& name) const {
	return this->properties_f.at(name);
}

/**
 * Returns the corresponding int.
 */
template<typename U> int PropertySet<U>::getD(const std::string& name) const {
	return this->properties_d.at(name);
}

/**
 * Copy
 */
template<typename U> void PropertySet<U>::operator=(const PropertySet& property_set) {
	this->properties_sn=property_set.properties_sn;
	this->properties_f=property_set.properties_f;
	this->properties_d=property_set.properties_d;
}
	


#endif /* PROPERTYSET_HPP_ */
