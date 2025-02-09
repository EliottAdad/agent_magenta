/*
 * Material.cpp
 *
 *  Created on: 8 jan. 2025
 *      Author: esn
 */


#include "Material.h"


/**
 * Constructor 1
 */
Material::Material(std::shared_ptr<COLOR> pcolor){
	this->pcolor=pcolor;
}

/**
 * Constructor 2
 */
Material::Material(const Material& material){
	pcolor=material.pcolor;
}

/**
 * Destructor
 */
Material::~Material(){
	//pcolor=NULL;
}



