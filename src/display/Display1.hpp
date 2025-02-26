/*
 * Display1.hpp
 *
 *  Created on: 4 juin 2024
 *      Author: esn
 */

#ifndef DISPLAY1_HPP_

#define DISPLAY1_HPP_

#include <memory>
#include <unordered_set>
#include <chrono>

#include "../core/Point3D.hpp"
#include "../core/Scene3D.hpp"
#include "../display/Display3D.hpp"
#include "functions_display.hpp"


/*
 * ###############
 *  Display1<T> :)
 * ###############
 * @brief
 * Orthographic projection
 * Choices between (x-y), (y-z), (z-x).
 * Display any Displayable.
 */
template<typename T> class Display1 : public Display3D<T> {
public:
	char display;									// The point of view from which it is projected (1, 2, 3).

	Display1();
	Display1(std::shared_ptr<Point3D<T>> ppoint);
	Display1(std::shared_ptr<WINDOW> pwindow, std::shared_ptr<RENDERER> prenderer);
	virtual ~Display1();
	Display1(const Display1<T>& display);

	virtual bool renderDisplayable(const std::shared_ptr<Displayable3D<T>> pdisplayable) const;
	virtual bool renderPoint(const Point3D<T>* ppoint) const;
	virtual bool renderPoints(const std::unordered_set<Point3D<T>*> ppoints) const;
	
	// From Display3D
	virtual void addPScene(std::shared_ptr<Scene3D<T>> pscene) {Display3D<T>::addPScene(pscene);}
	
	virtual void run(const unsigned int frames) const {Display3D<T>::run(frames);}
	virtual bool render() const {return Display3D<T>::render();}
	virtual bool renderScene(const std::shared_ptr<Scene3D<T>> pscene) const;

};





template<typename T> inline Display1<T>::Display1() : Display3D<T>() {
	this->display=1;
}

template<typename T> inline Display1<T>::Display1(std::shared_ptr<Point3D<T>> ppoint) : Display3D<T>(ppoint) {
	this->display=1;
}

template<typename T> inline Display1<T>::Display1(std::shared_ptr<SDL_Window> pwindow, std::shared_ptr<SDL_Renderer> prenderer) : Display3D<T>(pwindow, prenderer) {
	this->display=1;
}

template<typename T> inline Display1<T>::~Display1() {
	;
}

template<typename T> inline Display1<T>::Display1(const Display1<T>& display1) : Display3D<T>(display1) {
	this->display=display1.display;
}


/**
 * g
 */
template<typename T> inline bool Display1<T>::renderDisplayable(const std::shared_ptr<Displayable3D<T>> pdisplayable) const {
	bool success=true;

	if (pdisplayable!=NULL) {
		//std::shared_ptr<Point3D<T>> pp(new Point3D<T>(pdisplayable->getPosition()));
		//success=success & render(pp);

		// For the points
		/*std::unordered_set<std::shared_ptr<Point3D<T>>> ppoints=pdisplayable->getPPoints();
		for (std::shared_ptr<Point3D<T>> ppoint : ppoints){
			//printf("There is at least one Point to be displayed.");
			success=success & renderPoint(ppoint);
		}*/
		//printf("Display1: renderDisplayable\n");
		this->renderPoints(pdisplayable->getPPoints());

		// For the lines
		/*std::unordered_set<std::shared_ptr<Point3D<T>>> ppoints=pdisplayable->pshape->getPoints();
		for (std::shared_ptr<Point3D<T>> ppoint : ppoints){
			success=success & render(ppoint);
		}*/
	}
	return success;
}

template<typename T> inline bool Display1<T>::renderPoint(const Point3D<T>* ppoint) const {
	bool success=false;
	
	if (this->ppoint!=NULL){
		Point3D<T> d_point=*ppoint-*(this->ppoint);

		if (this->pwindow!=NULL && this->prenderer!=NULL && this->pdraw_color!=NULL){
			changeRenderDrawColor(this->prenderer, this->pdraw_color);
			//SDL_SetRenderDrawColor(prenderer.get(), pdraw_color->r, pdraw_color->g, pdraw_color->b, pdraw_color->a); // Chooses the draw color.

			// Get the dimensions of the window
			int sizex(0);
			int sizey(0);
			SDL_GetWindowSize(this->pwindow.get(), &sizex, &sizey);
			T centerx=(T)(sizex/2);
			T centery=(T)(sizey/2);

			if (this->prenderer!=NULL){
				switch (this->display){
					case 1://(x,y) plane
						drawPointRenderer(this->prenderer, (int)(d_point.x*this->scale + centerx).to_m_type(), (int)(d_point.y*this->scale + centery).to_m_type());
						break;
					case 2://(y,z) plane
						drawPointRenderer(this->prenderer, (int)(d_point.y*this->scale + centerx).to_m_type(), (int)(d_point.z*this->scale + centery).to_m_type());
						break;
					case 3://(x,z) plane
						drawPointRenderer(this->prenderer, (int)(d_point.x*this->scale + centerx).to_m_type(), (int)(d_point.z*this->scale + centery).to_m_type());
						break;
				}
			}
			success=true;
		}
	}
	return success;
}

template<typename T> inline bool Display1<T>::renderPoints(const std::unordered_set<Point3D<T>*> ppoints) const {
	bool success=false;
	//printf("Display1: renderPoints1\n");
	for (Point3D<T>* ppoint : ppoints){
		//printf("Display1: renderPoints2\n");
		Point3D<T> d_point=*ppoint-*(this->ppoint);

		if (this->pwindow!=NULL && this->prenderer!=NULL && this->pdraw_color!=NULL){
			changeRenderDrawColor(this->prenderer, this->pdraw_color);
			//SDL_SetRenderDrawColor(prenderer.get(), pdraw_color->r, pdraw_color->g, pdraw_color->b, pdraw_color->a); // Chooses the draw color.

			// Get the dimensions of the window
			int sizex(0);
			int sizey(0);
			SDL_GetWindowSize(this->pwindow.get(), &sizex, &sizey);
			T centerx=(T)(sizex/2);
			T centery=(T)(sizey/2);

			if (this->prenderer!=NULL){
				switch (display){
					case 1://(x,y) plane
						//printf("Display1: renderPoints3\n");
						drawPointRenderer(this->prenderer, (int)(d_point.x*this->scale + centerx).to_m_type(), (int)(d_point.y*this->scale + centery).to_m_type());
						break;
					case 2://(y,z) plane
						drawPointRenderer(this->prenderer, (int)(d_point.y*this->scale + centerx).to_m_type(), (int)(d_point.z*this->scale + centery).to_m_type());
						break;
					case 3://(x,z) plane
						drawPointRenderer(this->prenderer, (int)(d_point.x*this->scale + centerx).to_m_type(), (int)(d_point.z*this->scale + centery).to_m_type());
						break;
				}
			}
			success=true;
		}
	}
	return success;
}


/*
 * From Display3D
 */
 
/**
 * f
 */
template<typename T> inline bool Display1<T>::renderScene(const std::shared_ptr<Scene3D<T>> pscene) const {
	//printf("Display1 : renderScene\n");
	bool success=false;

	if (pscene!=NULL){
		for (std::shared_ptr<Displayable3D<T>> pdisplayable : pscene->pdisplayables){
			success=success | renderDisplayable(pdisplayable);
		}
	}

	return success;
}


#endif /* DISPLAY1_HPP_ */
