/*
 * Displayable3D.hpp
 *
 *  Created on: 8 nov. 2024
 *      Author: esn
 */

#ifndef DISPLAYABLE3D_HPP_

#define DISPLAYABLE3D_HPP_

#include <memory>
#include <unordered_set>

#include "Point3D.hpp"
#include "Triangle3D.hpp"
#include "CoordinateSystem3D.hpp"
#include "../display/Material.hpp"
#include "../display/Animation.hpp"
#include "../display/functions_display.hpp"

/*
 * ####################
 *  Displayable3D<T> :)
 * ####################
 * @brief
 * Abstract class
 * Contains objects that can be rendered by a Camera.
 * Color + Mat + getPPoints(pcoord_system_caller)
 * Stores the color, and a shape to use when rendering
 * Depreciated:
 * If shape=NULL draws a point, if SDL_Color=NULL draws in white
 */
template<typename T> class Displayable3D {
public:
	//std::shared_ptr<COLOR> pcolor;					// Drawing color
	std::shared_ptr<Material> pmaterial;					// Drawing material
	std::shared_ptr<Animation> panimation;					// Drawn sprites
	//std::shared_ptr<Shape3D<T>> pshape;			// Pointer to the shape to be drawn(NULL if none)
	bool finvisible;

	Displayable3D();
	virtual ~Displayable3D();
	Displayable3D(const Displayable3D<T>& displayable);

	virtual std::unordered_set<Point3D<T>*> getPPoints(const CoordinateSystem3D<T>& coord_system_caller) const = 0;
	//virtual std::unordered_set<Line3D<T>*> getPLines() const = 0;
	//virtual std::unordered_set<Triangle3D<T>*> getPTriangles() const = 0;
	//virtual Image getSticker() const;
};


template<typename T> inline Displayable3D<T>::Displayable3D() {
	this->pmaterial=std::make_shared<Material>();
	this->panimation=std::make_shared<Animation>();
	//pcolor=NULL;//std::make_shared<SDL_Color>(255, 255, 255, 255);		// Will be interprated as white by the cameras and displays
	//m_pmesh=NULL;			//
	finvisible=false;
}

template<typename T> inline Displayable3D<T>::~Displayable3D() {
	;
}

template<typename T> inline Displayable3D<T>::Displayable3D(const Displayable3D& displayable) {
	//pcolor=displayable.pcolor;
	this->pmaterial=displayable.pmaterial;
	this->panimation=displayable.panimation;
	this->finvisible=displayable.finvisible;
}



/**
 * Points projected from the point of view of the caller.
 */
template<typename T> inline std::unordered_set<Point3D<T>*> Displayable3D<T>::getPPoints(const CoordinateSystem3D<T>& coord_system_caller) const {
	std::unordered_set<Point3D<T>*> ppoints;
	return ppoints;
}

/*template<typename T> std::unordered_set<std::shared_ptr<Line3D<T>>> Displayable3D<T>::getPLines() const {
	std::unordered_set<std::shared_ptr<Line3D<T>>> plines;
	return plines;
}

template<typename T> std::unordered_set<std::shared_ptr<Triangle3D<T>>> Displayable3D<T>::getPTriangles() const {
	std::unordered_set<std::shared_ptr<Triangle3D<T>>> ptriangles;
	return ptriangles;
}*/





#endif /* DISPLAYABLE_HPP_ */
