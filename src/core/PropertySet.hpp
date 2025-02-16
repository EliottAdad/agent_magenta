/*
 * PropertySet.hpp
 *
 *  Created on: 4 juin 2024
 *      Author: esn
 */

#ifndef PROPERTYSET_HPP_

#define PROPERTYSET_HPP_

#include <memory>
#include <map>

#include "SN.hpp"

#define PROPERTYSETSN std::map<std::string, std::shared_ptr<SN<float, char>>>
#define PROPERTYSETF std::map<std::string, std::shared_ptr<float>>
#define PROPERTYSETD std::map<std::string, std::shared_ptr<int>>
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
	std::shared_ptr<U> ptarget;					// Object to which are attached the properties
	//std::shared_ptr<std::map<std::string, std::shared_ptr<P>>> pproperties;		// Properties
	PROPERTYSETSN psn;
	PROPERTYSETF pf;
	PROPERTYSETD pd;
	
	PropertySet();
	PropertySet(std::shared_ptr<U> ptarget);
	virtual ~PropertySet();
	PropertySet(const PropertySet<U>& property_set);

	void add(std::string name, std::shared_ptr<SN<float, char>> pnb);
	void add(std::string name, std::shared_ptr<float> pf);
	void add(std::string name, std::shared_ptr<int> pd);
	//virtual void remove();
	
	void operator=(const PropertySet& properties);
};



template<typename U> PropertySet<U>::PropertySet() {
	;
}

template<typename U> PropertySet<U>::PropertySet(std::shared_ptr<U> ptarget) {
	this->ptarget=ptarget;
}

template<typename U> PropertySet<U>::~PropertySet() {
	;
}

template<typename U> PropertySet<U>::PropertySet(const PropertySet<U>& property_set) {
	this->ptarget=property_set.ptarget;
}




/**
 * Inserts a SN
 */
template<typename U> void PropertySet<U>::add(std::string name, std::shared_ptr<SN<float, char>> pnb) {
	PROPERTYSETSN.insert({name, pnb});
}

/**
 * Inserts a float
 */
template<typename U> void PropertySet<U>::add(const std::string& name, std::shared_ptr<float> pf) {
	PROPERTYSETF.insert({name, pf});
}

/**
 * Inserts an int
 */
template<typename U> void PropertySet<U>::add(const std::string& name, std::shared_ptr<int> pd) {
	PROPERTYSETD.insert({name, pd});
}

/**
 * Copy
 */
template<typename U> void PropertySet<U>::operator=(const PropertySet& properties) {
	this->psn=properties.psn;
	this->pf=properties.pf;
	this->pd=properties.pd;
}
	


#endif /* PROPERTYSET_HPP_ */
