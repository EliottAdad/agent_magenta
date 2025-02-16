/*
 * Display2.hpp
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
#include "../utilities/functions_display.hpp"
#include "../utilities/functions_Point3D.hpp"


/*
 * ###############
 *  Display2<T> :)
 * ###############
 * Orthographic projection
 * Choices between (x-y), (y-z), (z-x).
 * Display any object having x, y, z.
 */
template<typename T> class Display2 : public Display3D<T> {
public:
	char display;									// The point of view from which it is projected (1, 2, 3).
	std::shared_ptr<Point3D<T>> ppoint;				// Pointeur to the center of display.

	Display2();
	Display2(std::shared_ptr<Point3D<T>> ppoint);
	Display2(std::shared_ptr<WINDOW> pwindow, std::shared_ptr<RENDERER> prenderer);
	virtual ~Display2();
	Display2(const Display2<T>& display);

	virtual void addPScene(std::shared_ptr<Scene3D<T>> pscene) {Display3D<T>::addPScene(pscene);};
	
	virtual bool renderDisplayable(const std::shared_ptr<Displayable3D<T>> pdisplayable) const;
	virtual bool renderPoint(const std::shared_ptr<Point3D<T>> ppoint) const;
	virtual bool renderPoints(const std::unordered_set<std::shared_ptr<Point3D<T>>> ppoints) const;
	
	// From Display3D
	virtual void run(const unsigned int frames) const {Display3D<T>::run(frames);};
	virtual bool render() const {return Display3D<T>::render();};
	virtual bool renderScene(const std::shared_ptr<Scene3D<T>> pscene) const;
	
	// From TimeSensitive
	virtual float getT() const {return TimeSensitive::getT();};
	virtual void setT(const float& dt) {TimeSensitive::setT(dt);};
	virtual void apply() {TimeSensitive::apply();};
	
	// From Mobile3D
	virtual T getX() const {return Mobile3D<T>::getX();};
	virtual T getY() const {return Mobile3D<T>::getY();};
	virtual T getZ() const {return Mobile3D<T>::getZ();};
	virtual Point3D<T> getPosition() const {return Mobile3D<T>::getPosition();};
};




template<typename T> inline Display2<T>::Display2() : Display3D<T>() {
	this->ppoint=std::make_shared<Point3D<T>>();
	this->fps=25;
	this->display=1;
	this->scale=2;

	this->pbkgd_color=createColor(0, 0, 0, 255);
	this->pdraw_color=createColor(255, 255, 255, 255);
	this->pwindow=NULL;//SDL_CreateWindow("Fama", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 600, 600, SDL_WINDOW_SHOWN);
	this->prenderer=NULL;

	this->fclear=true;
}

template<typename T> inline Display2<T>::Display2(std::shared_ptr<Point3D<T>> ppoint) : Display3D<T>() {
	this->ppoint=ppoint;
	this->fps=25;
	this->display=1;
	this->scale=2;

	this->pbkgd_color=createColor(0, 0, 0, 255);
	this->pdraw_color=createColor(255, 255, 255, 255);
	this->pwindow=NULL;
	this->prenderer=NULL;

	this->fclear=true;
}

template<typename T> inline Display2<T>::Display2(std::shared_ptr<SDL_Window> pwindow, std::shared_ptr<SDL_Renderer> prenderer) : Display3D<T>() {
	this->ppoint=std::make_shared<Point3D<T>>();
	this->fps=25;
	this->display=1;
	this->scale=2;

	this->pbkgd_color=createColor(0, 0, 0, 255);
	this->pdraw_color=createColor(255, 255, 255, 255);
	this->pwindow=pwindow;
	this->prenderer=prenderer;

	this->fclear=true;
}

template<typename T> inline Display2<T>::~Display2() {
	;
}

/*
Display2::Display2(const Display2 &other) {
	m_pwindow=;
}*/







/*
 * From Display3D
 */
 
/**
 * f
 */
template<typename T> inline bool Display2<T>::renderScene(const std::shared_ptr<Scene3D<T>> pscene) const {
	bool success=false;
	
	printf("Display2: renderScene1\n");
	if (pscene!=NULL){
		for (std::shared_ptr<Displayable3D<T>> pdisplayable : pscene->pdisplayables){
			success=success | renderDisplayable(pdisplayable);
		}
	}
	printf("Display2: renderScene2\n");

	return success;
}

/**
 * g
 */
template<typename T> inline bool Display2<T>::renderDisplayable(const std::shared_ptr<Displayable3D<T>> pdisplayable) const {
	bool success=true;

	if (pdisplayable!=NULL) {
		printf("Display2: renderDisplayable1\n");
		// For the points
		Eigen::Matrix<T, 3, 3> P=(this->pcoord_system->getM().inverse())*pdisplayable->pcoord_system->getM();		// (x'', y'', z'')=Id_2^-1*Id_1*(x', y', z')
		printf("Display2: renderDisplayable2\n");
		std::unordered_set<std::shared_ptr<Point3D<T>>> ppoints=pdisplayable->getPPoints();
		for (std::shared_ptr<Point3D<T>> ppoint : ppoints){
			Eigen::Matrix<T, 3, 1> m=P*toEigen(*ppoint);
			success=success & renderPoint(toPoint(m));//couper le z dans render(Point)
		}

		printf("Display2: renderDisplayable3\n");
		// For the lines
		/*std::unordered_set<std::shared_ptr<Point3D<T>>> ppoints=pdisplayable->pshape->getPoints();
		for (std::shared_ptr<Point3D<T>> ppoint : ppoints){
			success=success & render(ppoint);
		}*/
	}
	return success;
}

template<typename T> inline bool Display2<T>::renderPoint(const std::shared_ptr<Point3D<T>> ppoint) const {
	bool success=false;
	
	printf("Display2: renderPoint1\n");
	if (this->ppoint!=NULL){
		Point3D<T> d_point=*ppoint-*(this->ppoint);

		printf("Display2: renderPoint2\n");
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
						//printf("AAAAA\n");
						//printf("\nx=%i\n", (int)(d_point.x*(M)scale + centerx).to_m_type());
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
			printf("Display2: renderPoint3\n");
			success=true;
		}
	}
	return success;
}

template<typename T> inline bool Display2<T>::renderPoints(const std::unordered_set<std::shared_ptr<Point3D<T>>> ppoints) const {
	bool success=false;
	//printf("Rendering point\n");
	for (std::shared_ptr<Point3D<T>> ppoint : ppoints){
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
						//printf("\nx=%i\n", (int)(d_point.x*(M)scale + centerx).to_m_type());
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



#endif /* DISPLAY1_HPP_ */
