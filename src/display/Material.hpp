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

#include "../utilities/Printable.hpp"
#include "../utilities/functions_display.hpp"




/*
 * ############
 *  Material :)
 * ############
 * A material to apply on the objects.
 */
class Material{
public:
	std::shared_ptr<COLOR> pcolor;

	Material(std::shared_ptr<COLOR> pcolor);
	Material(const Material& material);
	~Material();
};

#endif
