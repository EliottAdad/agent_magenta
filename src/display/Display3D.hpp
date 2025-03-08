/*
 * Display3D.hpp
 *
 *  Created on: 4 juin 2024
 *      Author: esn
 */

#ifndef DISPLAY3D_HPP_

#define DISPLAY3D_HPP_

#include <memory>
#include <unordered_set>
#include <chrono>

#include "../core/Point3D.hpp"
#include "../core/Line3D.hpp"
#include "../core/Displayable3D.hpp"
//#include "../utilities/Printable.hpp"
#include "../utilities/functions.hpp"
#include "../core/Scene3D.hpp"
#include "../core/Mobile3D.hpp"
#include "../core/CoordinateSystem3D.hpp"
#include "../display/functions_display.hpp"


/*
 * ################
 *  Display3D<T> :)
 * ################
 * @brief
 * Orthographic projection along axis
 * Choices between (x-y), (y-z), (z-x).
 * Display any Displayable using getPoints(), getLines().
 */
template<typename T> class Display3D : public Mobile3D<T> {
public:
	char display;											// The point of view from which it is projected (1, 2, 3).
	unsigned char fps;										// Frames per second
	float scale;											// Ratio d_pixels/d_meters
	
	std::shared_ptr<CoordinateSystem3D<T>> pcoord_system;
	std::unordered_set<Scene3D<T>*> pscenes;				// Pointeurs to the scenes that are rendered in the display.

	std::shared_ptr<COLOR> pbkgd_color;						// Pointeur to the background color.
	std::shared_ptr<COLOR> pdraw_color;						// Pointeur to the render color.
	std::shared_ptr<WINDOW> pwindow;						// Pointeur to the window.
	std::shared_ptr<RENDERER> prenderer;					// Pointeur to the renderer.
	bool fclear;

	Display3D();
	Display3D(std::shared_ptr<Point3D<T>> ppoint);
	Display3D(std::shared_ptr<WINDOW> pwindow, std::shared_ptr<RENDERER> prenderer);
	virtual ~Display3D();
	Display3D(const Display3D<T>& display);

	virtual void addPScene(Scene3D<T>* pscene);
	
	virtual void run(const unsigned int frames) const;
	virtual bool render() const;
	virtual bool renderScene(const Scene3D<T>& scene) const;
	virtual bool renderDisplayable(const Displayable3D<T>& pdisplayable) const;
	virtual bool renderPoint(const Point3D<T>& point) const;
	virtual bool renderPoints(const std::unordered_set<Point3D<T>*> ppoints) const;

	// From TimeSensitive
	virtual float getT() const {return TimeSensitive::getT();}
	virtual void setT(const float& dt) {TimeSensitive::setT(dt);}
	virtual void apply() {TimeSensitive::apply();}

	// From Static3D
	virtual T getX() const {return Static3D<T>::getX();}
	virtual T getY() const {return Static3D<T>::getY();}
	virtual T getZ() const {return Static3D<T>::getZ();}
	virtual Point3D<T> getPosition() const {return Static3D<T>::getPosition();}
	
	// From Mobile3D
	virtual Vector3D<T> getSpeed() const {return Mobile3D<T>::getSpeed();}
	virtual Vector3D<T> getRotSpeed() const {return Mobile3D<T>::getRotSpeed();}
};




template<typename T> inline Display3D<T>::Display3D() : Mobile3D<T>() {
	this->display=1;
	this->fps=25;
	this->scale=2;
	
	this->pbkgd_color=createColor(0, 0, 0, 255);
	this->pdraw_color=createColor(255, 255, 255, 255);
	this->pwindow=createWindow();
	this->prenderer=createRenderer(this->pwindow);

	this->fclear=true;
}

template<typename T> inline Display3D<T>::Display3D(std::shared_ptr<Point3D<T>> ppoint) : Mobile3D<T>() {
	this->display=1;
	this->fps=25;
	this->scale=2;

	this->pbkgd_color=createColor(0, 0, 0, 255);
	this->pdraw_color=createColor(255, 255, 255, 255);
	this->pwindow=createWindow();
	this->prenderer=createRenderer(this->pwindow);

	this->fclear=true;
	
	// 
	this->ppoint=ppoint;
	
}

template<typename T> inline Display3D<T>::Display3D(std::shared_ptr<SDL_Window> pwindow, std::shared_ptr<SDL_Renderer> prenderer) : Mobile3D<T>() {
	this->display=1;
	this->fps=25;
	this->scale=2;

	this->ppoint=std::make_shared<Point3D<T>>();
	
	this->pbkgd_color=createColor(0, 0, 0, 255);
	this->pdraw_color=createColor(255, 255, 255, 255);
	this->pwindow=pwindow;
	this->prenderer=prenderer;

	this->fclear=true;
}

template<typename T> inline Display3D<T>::~Display3D() {
	;
}


template<typename T> inline Display3D<T>::Display3D(const Display3D<T>& display) : Mobile3D<T>(display) {
	this->display=display.display;
	this->fps=display.fps;
	this->scale=display.scale;
	this->pscenes=display.pscenes;

	this->pbkgd_color=display.pbkgd_color;
	this->pdraw_color=display.pdraw_color;
	this->pwindow=display.pwindow;
	this->prenderer=display.prenderer;

	this->fclear=display.fclear;
}





template<typename T> inline void Display3D<T>::addPScene(Scene3D<T>* pscene) {
	if (pscene!=NULL){
		this->pscenes.insert(pscene);
	}
}

/**
 * @brief
 * If 0: infinite loop
 */
template<typename T> inline void Display3D<T>::run(const unsigned int frames) const {
	//printf("Display3D : run\n");
	std::chrono::time_point t1=std::chrono::system_clock::now();
	//if (!fpause){
		unsigned int i(0);
		while (i<=frames){
			std::chrono::time_point t2=std::chrono::system_clock::now();
			std::chrono::duration dt=t2-t1;

			if (dt.count()>=1/(long double)fps*1000000000.){
				//printf("dt: %f\n", (float)(dt.count()/1000000000.));
				this->render();

				//printf("Display3D: FPS %f\n", 1/(dt.count()/1000000000.));
				
				t1=t2;
				if (frames!=0){//If steps is not null
					i++;
				}
			}
		}
	//}
}

/*
 *
 */
template<typename T> inline bool Display3D<T>::render() const {
	bool success=false;
	
	//printf("Display3D : render1\n");
	if (prenderer!=NULL){
		if (fclear){
			fillRendererWithColor(prenderer, pbkgd_color);// Fill the canvas with the background color
		}

		//printf("Display3D : render2\n");
		//printf("\nRendering 1: %ld\n", pscenes.size());
		for (Scene3D<T>* pscene : pscenes){
			success=success | renderScene(*pscene);
		}
		//drawCircle(prenderer.get(), {0, 0}, 100);

		/*std::unordered_set<std::shared_ptr<Point3D<T>>> ppoints=pixelizeCircle(ppoint, 200, 8);
		for (std::shared_ptr<Point3D<T>> ppoint : ppoints){
			success=success & render(ppoint);
		}*/
		//printf("Display3D : render3\n");

		displayChangesRenderer(prenderer);
		//printf("Display3D : render4\n");
	}

	return success;
}

/**
 * @brief
 * f
 */
template<typename T> inline bool Display3D<T>::renderScene(const Scene3D<T>& scene) const {
	bool success=false;

	for (std::shared_ptr<Displayable3D<T>> pdisplayable : scene.pdisplayables){
		success=success | renderDisplayable(*pdisplayable);
	}

	return success;
}

/**
 * @brief
 * g
 */
template<typename T> inline bool Display3D<T>::renderDisplayable(const Displayable3D<T>& displayable) const {
	bool success=true;

	// For the points
	success=success & this->renderPoints(displayable.getPPoints(*this->pcoord_system));

	// For the lines
	
	return success;
}

template<typename T> inline bool Display3D<T>::renderPoint(const Point3D<T>& point) const {
	bool success=false;
	
	if (this->ppoint!=NULL){
		Point3D<T> d_point=point-*(this->ppoint);

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

template<typename T> inline bool Display3D<T>::renderPoints(const std::unordered_set<Point3D<T>*> ppoints) const {
	bool success=false;
	//printf("Display1: renderPoints1\n");
	if (this->ppoint!=NULL){
		for (Point3D<T>* ppoint : ppoints){
			if (ppoint!=NULL){
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
		}
	}
	return success;
}



#endif /* DISPLAY3D_HPP_ */
