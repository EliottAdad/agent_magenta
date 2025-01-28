/*
 * Material.h
 *
 *  Created on: 8 jan. 2025
 *      Author: esn
 */

#ifndef MATERIAL_H_

#define MATERIAL_H_


#include <memory>
#include <vector>
#include <SDL2/SDL.h>

#include "../utilities/Printable.h"
#include "../utilities/functions_display.h"




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
