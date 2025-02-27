/*
 * Material.hpp
 *
 *  Created on: 8 jan. 2025
 *      Author: esn
 */

#ifndef MATERIAL_HPP_

#define MATERIAL_HPP_


#include <memory>
#include <vector>
//#include <SDL2/SDL.h>

//#include "../utilities/Printable.hpp"
#include "functions_display.hpp"




/*
 * ############
 *  Material :)
 * ############
 * @brief
 * A material to apply on the objects.
 */
class Material {
public:
	std::shared_ptr<COLOR> pcolor;

	Material(std::shared_ptr<COLOR> pcolor);
	Material(const Material& material);
	~Material();
};





/**
 * Constructor 1
 */
inline Material::Material(std::shared_ptr<COLOR> pcolor){
	this->pcolor=pcolor;
}

/**
 * Constructor 2
 */
inline Material::Material(const Material& material){
	pcolor=material.pcolor;
}

/**
 * Destructor
 */
inline Material::~Material(){
	//pcolor=NULL;
}



#endif
