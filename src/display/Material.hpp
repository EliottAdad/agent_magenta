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

	Material();
	Material(std::shared_ptr<COLOR> pcolor);
	Material(const Material& material);
	~Material();
};





/**
 * @brief
 * Constructor 1
 */
inline Material::Material() {
	this->pcolor=createColor(255, 255, 255, 255);
}

/**
 * @brief
 * Constructor 1
 */
inline Material::Material(std::shared_ptr<COLOR> pcolor) {
	this->pcolor=pcolor;
}

/**
 * @brief
 * Constructor 2
 */
inline Material::Material(const Material& material){
	pcolor=material.pcolor;
}

/**
 * @brief
 * Destructor
 */
inline Material::~Material(){
	//pcolor=NULL;
}



#endif /* MATERIAL_HPP_ */
