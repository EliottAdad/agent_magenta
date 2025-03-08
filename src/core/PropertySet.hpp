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
template<typename U, typename T> class PropertySet {
public:
	U* ptarget;					// Object to which are attached the properties
	std::map<std::string, std::shared_ptr<T>> pproperties;
	std::map<std::string, T> properties;
	
	PropertySet();
	PropertySet(U* ptarget);
	virtual ~PropertySet();
	PropertySet(const PropertySet<U, T>& property_set);

	bool add(const std::string& name, std::shared_ptr<T> pprop);
	bool add(const std::string& name, const T& prop);
	//void remove(const std::string& name);
	std::shared_ptr<T> getP(const std::string& name) const;
	T get(const std::string& name) const;
	
	void operator=(const PropertySet<U, T>& property_set);
	void operator+=(const PropertySet<U, T>& property_set);
};

template<typename U, typename T> PropertySet<U, T> operator+(const PropertySet<U, T>& property_set1, const PropertySet<U, T>& property_set2);


/**
 * Constructor0
 */
template<typename U, typename T> inline PropertySet<U, T>::PropertySet() {
	this->ptarget=NULL;
}

/**
 * Constructor1
 */
template<typename U, typename T> inline PropertySet<U, T>::PropertySet(U* ptarget) {
	this->ptarget=ptarget;
}

/**
 * Destructor
 */
template<typename U, typename T> inline PropertySet<U, T>::~PropertySet() {
	this->ptarget=NULL;
}

/**
 * Copy constructor
 */
template<typename U, typename T> inline PropertySet<U, T>::PropertySet(const PropertySet<U, T>& property_set) {
	this->ptarget=property_set.ptarget;
}




/**
 * Inserts a new property (name of the property paired with a pointer to the said property)
 */
template<typename U, typename T> inline bool PropertySet<U, T>::add(const std::string& name, std::shared_ptr<T> pprop) {
	return this->pproperties.insert({name, pprop}).second;
}

/**
 * Inserts a new property (name of the property paired with a reference to the property)
 */
template<typename U, typename T> inline bool PropertySet<U, T>::add(const std::string& name, const T& prop) {
	return this->properties.insert({name, prop}).second;
}

/**
 * Returns the pointer to the requested property corresponding to the name.
 * NULL if not found.
 */
template<typename U, typename T> inline std::shared_ptr<T> PropertySet<U, T>::getP(const std::string& name) const {
	/*auto pairr=this->pproperties.find(name);
	if (pairr!=this->pproperties.end()){
		return pairr.second;
	}
	return NULL;*/
	//return this->pproperties.find(name).second;
	
	if (auto search = this->pproperties.find(name); search != this->pproperties.end()){
		return (*search).second;
	}
	return NULL;
}

/**
 * Returns the property corresponding to the name. Priority on pointers.
 * Return default T from default constructor if not found.
 */
template<typename U, typename T> inline T PropertySet<U, T>::get(const std::string& name) const {
	std::shared_ptr<T> pproperty=NULL;
	
	pproperty=this->getP(name);
	if (pproperty!=NULL){
		return *pproperty;
	}
	/*if (this->properties.contains(name)){
		return this->properties.find(name).second;
	}
	return T();*/
	//return this->properties.find(name).second;
	if (auto search = this->properties.find(name); search != this->properties.end()){
		return (*search).second;
	}
	return T();
}

/*
 * Operators
 */

/**
 * h
 */
template<typename U, typename T> inline void PropertySet<U, T>::operator=(const PropertySet<U, T>& property_set) {
	this->pproperties=property_set.pproperties;
	this->properties=property_set.properties;
}

/**
 * @brief
 * Add to the properties that are already present in this PropertySet
 */
template<typename U, typename T> inline void PropertySet<U, T>::operator+=(const PropertySet<U, T>& property_set) {
	//std::map<std::string, std::shared_ptr<T>> pproperties;
	//std::map<std::string, T> properties;

	for (auto property : this->properties){
		property.second+=property_set.get(property.first);
	}
}


/**
 * TODO
 */
template<typename U, typename T> inline PropertySet<U, T> operator+(const PropertySet<U, T>& property_set1, const PropertySet<U, T>& property_set2) {
	//this->properties;
	
	//=property_set.properties;
	std::shared_ptr<PropertySet<U, T>> pproperty_set=std::make_shared<PropertySet<U, T>>();
	return *pproperty_set;
}


#endif /* PROPERTYSET_HPP_ */
