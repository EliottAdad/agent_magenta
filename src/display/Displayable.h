/*
 * Displayable.h
 *
 *  Created on: 8 nov. 2024
 *      Author: esn
 */

#ifndef DISPLAYABLE_H_

#define DISPLAYABLE_H_

#include <memory>
#include <unordered_set>
#include <SDL2/SDL.h>

#include "../core/Point3D.h"
#include "../core/Triangle3D.h"
#include "../utilities/Printable.h"
#include "../core/CoordinateSystem3D.h"
#include "../utilities/functions_display.h"

/*
 * ##################
 *  Displayable<T> :)
 * ##################
 * Stores the color, and a shape to use when rendering
 * If shape=NULL draws a point, if SDL_Color=NULL draws in white
 */
template<typename T> struct Displayable : public Printable {
public:
	std::shared_ptr<CoordinateSystem3D<T>> psys;								// The coords system in wich it is expressed
	std::shared_ptr<COLOR> pcolor;		// Drawing color
	//std::shared_ptr<Shape3D<T>> pshape;			// Pointer to the shape to be drawn(NULL if none)

	Displayable();
	virtual ~Displayable();
	Displayable(const Displayable &other);

	virtual T getX() const;				//Gets the coords (changer plus tard en getPoints
	virtual T getY() const;
	virtual T getZ() const;
	virtual Point3D<T> getPosition() const;
	virtual std::unordered_set<std::shared_ptr<Point3D<T>>> getPPoints() const;
	/*virtual std::unordered_set<std::shared_ptr<Line3D<T>>> getPLines() const;
	virtual std::unordered_set<std::shared_ptr<Triangle3D<T>>> getPTriangles() const;*/
	//virtual Image getSticker() const;

	virtual std::string to_string(const bool& spread=false, const bool& full_info=false, const unsigned char& indent=0) const;// :)
	virtual void print(const bool& spread=false, const bool& full_info=false, const unsigned char& indent=0) const;// :)
};


template<typename T> Displayable<T>::Displayable() {
	pcolor=NULL;//std::make_shared<SDL_Color>(255, 255, 255, 255);		// Will be interprated as white by the cameras and displays
	//m_pmesh=NULL;			//
	//m_delc=true;
}

template<typename T> Displayable<T>::~Displayable() {
	;
}

template<typename T> Displayable<T>::Displayable(const Displayable &other) {
	pcolor=other.pcolor;
}


template<typename T> T Displayable<T>::getX() const {
	return (T)0;
}

template<typename T> T Displayable<T>::getY() const {
	return (T)0;
}

template<typename T> T Displayable<T>::getZ() const {
	return (T)0;
}

template<typename T> Point3D<T> Displayable<T>::getPosition() const {
	return Point3D<T>{this->getX(), this->getY(), this->getZ()};
}



template<typename T> std::unordered_set<std::shared_ptr<Point3D<T>>> Displayable<T>::getPPoints() const {
	std::unordered_set<std::shared_ptr<Point3D<T>>> ppoints;
	return ppoints;
}

/*template<typename T> std::unordered_set<std::shared_ptr<Line3D<T>>> Displayable<T>::getPLines() const {
	std::unordered_set<std::shared_ptr<Line3D<T>>> plines;
	return plines;
}

template<typename T> std::unordered_set<std::shared_ptr<Triangle3D<T>>> Displayable<T>::getPTriangles() const {
	std::unordered_set<std::shared_ptr<Triangle3D<T>>> ptriangles;
	return ptriangles;
}*/



template<typename T> std::string Displayable<T>::to_string(const bool& spread, const bool& full_info, const unsigned char& indent) const {// :)
	std::string mes=(spread)?"\n":"";

	mes+="DISPLAYABLE";

	return mes;
}

template<typename T> void Displayable<T>::print(const bool& spread, const bool& full_info, const unsigned char& indent) const {// :)
	printTabs(indent);
	std::cout << this->to_string(spread, full_info, indent);
}


#endif /* DISPLAYABLE_H_ */
