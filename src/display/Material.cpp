/*
 * Material.cpp
 *
 *  Created on: 8 jan. 2025
 *      Author: esn
 */

#ifndef MATERIAL_CPP_

#define MATERIAL_CPP_


#include "Material.h"


/**
 * Constructor 1
 */
Material::Material(std::shared_ptr<SDL_Color> pcolor){
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




#endif
