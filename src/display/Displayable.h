/*
 * Displayable.h
 *
 *  Created on: 8 nov. 2024
 *      Author: esn
 */

#ifndef DISPLAYABLE_H_
#define DISPLAYABLE_H_

#include <SDL2/SDL.h>
#include "../geometry/Mesh3D.h"
#include "../utilities/Printable.h"

/*
 * ###############
 *  Displayable :)
 * ###############
 * Stores the color, and a mesh to use when rendering
 * If mesh=NULL draws a point, if SDL_Color=NULL draws in white
 */
struct Displayable : public Printable {
	Displayable();
	virtual ~Displayable();
	Displayable(const Displayable &other);

	SDL_Color* pcolor;		// Drawing color
	Mesh3D* pmesh;			// Pointer to the mesh to be drawn

	virtual SN<float, char> getX() const;				//Gets the coords
	virtual SN<float, char> getY() const;
	virtual SN<float, char> getZ() const;

	virtual std::string to_string(const bool& spread=false, const bool& full_info=false, const unsigned char& indent=0) const;// :)
	virtual void print(const bool& spread=false, const bool& full_info=false, const unsigned char& indent=0) const;// :)
};



#endif /* DISPLAYABLE_H_ */
