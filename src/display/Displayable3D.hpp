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

#include "../core/Point3D.hpp"
#include "../core/Triangle3D.hpp"
#include "../core/Mobile3D.hpp"
#include "../core/CoordinateSystem3D.hpp"
#include "../display/functions_display.hpp"

/*
 * ####################
 *  Displayable3D<T> :)
 * ####################
 * @brief
 * Abstract class
 * Color + Mat + getX
 * Stores the color, and a shape to use when rendering
 * If shape=NULL draws a point, if SDL_Color=NULL draws in white
 */
template<typename T> class Displayable3D : public Mobile3D<T> {
public:
	std::shared_ptr<COLOR> pcolor;					// Drawing color
	//std::shared_ptr<Shape3D<T>> pshape;			// Pointer to the shape to be drawn(NULL if none)
	bool finvisible;

	Displayable3D();
	virtual ~Displayable3D();
	Displayable3D(const Displayable3D& displayable);

	virtual std::unordered_set<std::shared_ptr<Point3D<T>>> getPPoints() const = 0;
	/*virtual std::unordered_set<std::shared_ptr<Line3D<T>>> getPLines() const;
	virtual std::unordered_set<std::shared_ptr<Triangle3D<T>>> getPTriangles() const;*/
	//virtual Image getSticker() const;
};


template<typename T> inline Displayable3D<T>::Displayable3D() : Mobile3D<T>() {
	pcolor=NULL;//std::make_shared<SDL_Color>(255, 255, 255, 255);		// Will be interprated as white by the cameras and displays
	//m_pmesh=NULL;			//
	finvisible=false;
}

template<typename T> inline Displayable3D<T>::~Displayable3D() {
	;
}

template<typename T> inline Displayable3D<T>::Displayable3D(const Displayable3D& displayable) : Mobile3D<T>(displayable) {
	pcolor=displayable.pcolor;
	finvisible=displayable.finvisible;
}




template<typename T> inline std::unordered_set<std::shared_ptr<Point3D<T>>> Displayable3D<T>::getPPoints() const {
	std::unordered_set<std::shared_ptr<Point3D<T>>> ppoints;
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
