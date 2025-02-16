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
#include "../display/Displayable3D.hpp"
//#include "../utilities/Printable.hpp"
#include "../utilities/functions.hpp"
#include "../core/Scene3D.hpp"
#include "../core/Mobile3D.hpp"
#include "../utilities/functions_display.hpp"


/*
 * ################
 *  Display3D<T> :)
 * ################
 * Orthographic projection
 * Display any object having x, y, z.
 */
template<typename T> class Display3D : public Mobile3D<T>{
public:
	unsigned char fps;					// Frames per second
	float scale;						// Ratio d_pixels/d_meters
	std::unordered_set<std::shared_ptr<Scene3D<T>>> pscenes;			// Pointeurs to the scenes that are rendered in the display.

	std::shared_ptr<Point3D<T>> ppoint;				// Pointeur to the center of display.

	std::shared_ptr<COLOR> pbkgd_color;				// Pointeur to the background color.
	std::shared_ptr<COLOR> pdraw_color;				// Pointeur to the render color.
	std::shared_ptr<WINDOW> pwindow;				// Pointeur to the window.
	std::shared_ptr<RENDERER> prenderer;			// Pointeur to the renderer.
	bool fclear;

	Display3D();
	Display3D(std::shared_ptr<Point3D<T>> ppoint);
	Display3D(std::shared_ptr<WINDOW> pwindow, std::shared_ptr<RENDERER> prenderer);
	virtual ~Display3D();
	//Display3D(const Display3D &other);

	virtual void addPScene(std::shared_ptr<Scene3D<T>> pscene) = 0;
	
	virtual void run(const unsigned int frames) const = 0;
	virtual bool render() const = 0;
	virtual bool renderScene(const std::shared_ptr<Scene3D<T>> pscene) const = 0;
};




template<typename T> inline Display3D<T>::Display3D() : Mobile3D<T>() {
	this->fps=25;
	this->scale=2;
	this->pscenes={};
	
	this->ppoint=std::make_shared<Point3D<T>>();

	this->pbkgd_color=createColor(0, 0, 0, 255);
	this->pdraw_color=createColor(255, 255, 255, 255);
	this->pwindow=createWindow();
	this->prenderer=createRenderer();

	this->fclear=true;
}

template<typename T> inline Display3D<T>::Display3D(std::shared_ptr<Point3D<T>> ppoint) : Mobile3D<T>() {
	this->fps=25;
	this->scale=2;
	this->pscenes={};

	this->ppoint=ppoint;
	
	this->pbkgd_color=createColor(0, 0, 0, 255);
	this->pdraw_color=createColor(255, 255, 255, 255);
	this->pwindow=NULL;
	this->prenderer=NULL;

	this->fclear=true;
}

template<typename T> inline Display3D<T>::Display3D(std::shared_ptr<SDL_Window> pwindow, std::shared_ptr<SDL_Renderer> prenderer) : Mobile3D<T>() {
	this->fps=25;
	this->scale=2;
	this->pscenes={};

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


template<typename T> inline Display3D<T>::Display3D(const Display3D& display) : Mobile3D<T>(display) {
	this->fps=display.fps;
	this->scale=display.scale;
	this->pscenes=display.pscenes;

	this->ppoint=display.ppoint;

	this->pbkgd_color=display.pbkgd_color;
	this->pdraw_color=display.pdraw_color;
	this->pwindow=display.pwindow;
	this->prenderer=display.prenderer;

	this->fclear=display.fclear;
}





template<typename T> inline void Display3D<T>::addPScene(std::shared_ptr<Scene3D<T>> pscene) {
	if (pscene!=NULL){
		pscenes.insert(pscene);
	}
}

/*
 * If 0: infinite loop
 */
template<typename T> inline void Display3D<T>::run(const unsigned int frames) const {
	printf("Display3D : run\n");
	std::chrono::time_point t1=std::chrono::system_clock::now();
	//if (!fpause){
		unsigned int i(0);
		while (i<=frames){
			std::chrono::time_point t2=std::chrono::system_clock::now();
			std::chrono::duration dt=t2-t1;

			if (dt.count()>=1/(long double)fps*1000000000.){
				//printf("dt: %f\n", (float)(dt.count()/1000000000.));
				this->render();

				printf("FPS %f\n", 1/(dt.count()/1000000000.));
				
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
	
	printf("Display3D : render1\n");
	if (prenderer!=NULL){
		if (fclear){
			fillRendererWithColor(prenderer, pbkgd_color);// Fill the canvas with the background color
		}

		printf("Display3D : render2\n");
		//printf("\nRendering 1: %ld\n", pscenes.size());
		for (std::shared_ptr<Scene3D<T>> pscene : pscenes){
			success=success | renderScene(pscene);
		}
		//drawCircle(prenderer.get(), {0, 0}, 100);

		/*std::unordered_set<std::shared_ptr<Point3D<T>>> ppoints=pixelizeCircle(ppoint, 200, 8);
		for (std::shared_ptr<Point3D<T>> ppoint : ppoints){
			success=success & render(ppoint);
		}*/
		printf("Display3D : render3\n");

		displayChangesRenderer(prenderer);
		printf("Display3D : render4\n");
	}

	return success;
}

/*
 *
 */
template<typename T> inline bool Display3D<T>::renderScene(const std::shared_ptr<Scene3D<T>> pscene) const {
	printf("Display3D : renderScene\n");
	bool success=false;

	/*if (pscene!=NULL){
		for (std::shared_ptr<Displayable3D<T>> pdisplayable : pscene->pdisplayables){
			success=success | renderDisplayable(pdisplayable);
		}
	}*/
	
	return success;
}

/*
 *
 */
/*template<typename T> inline bool Display3D<T>::renderDisplayable(const std::shared_ptr<Displayable3D<T>> pdisplayable) const {
	bool success=true;

	if (pdisplayable!=NULL) {
		//std::shared_ptr<Point3D<T>> pp(new Point3D<T>(pdisplayable->getPosition()));
		//success=success & render(pp);

		// For the points
		std::unordered_set<std::shared_ptr<Point3D<T>>> ppoints=pdisplayable->getPPoints();
		for (std::shared_ptr<Point3D<T>> ppoint : ppoints){
			//printf("There is at least one Point to be displayed.");
			success=success & renderPoint(ppoint);
		}

		// For the lines
	}
	return success;
}

template<typename T> inline bool Display3D<T>::renderPoint(const std::shared_ptr<Point3D<T>> ppoint) const {
	bool success=false;
	//printf("Rendering point\n");
	if (this->ppoint!=NULL){
		Point3D<T> d_point=*ppoint-*(this->ppoint);

		if (pwindow!=NULL && prenderer!=NULL && pdraw_color!=NULL){
			changeRenderDrawColor(prenderer, pdraw_color);
			//SDL_SetRenderDrawColor(prenderer.get(), pdraw_color->r, pdraw_color->g, pdraw_color->b, pdraw_color->a); // Chooses the draw color.

			// Get the dimensions of the window
			int sizex(0);
			int sizey(0);
			SDL_GetWindowSize(pwindow.get(), &sizex, &sizey);
			T centerx=(T)(sizex/2);
			T centery=(T)(sizey/2);

			if (prenderer!=NULL){
				switch (display){
					case 1://(x,y) plane
						//printf("AAAAA\n");
						//printf("\nx=%i\n", (int)(d_point.x*(M)scale + centerx).to_m_type());
						drawPointRenderer(prenderer, (int)(d_point.x*scale + centerx).to_m_type(), (int)(d_point.y*scale + centery).to_m_type());
						break;
					case 2://(y,z) plane
						drawPointRenderer(prenderer, (int)(d_point.y*scale + centerx).to_m_type(), (int)(d_point.z*scale + centery).to_m_type());
						break;
					case 3://(x,z) plane
						drawPointRenderer(prenderer, (int)(d_point.x*scale + centerx).to_m_type(), (int)(d_point.z*scale + centery).to_m_type());
						break;
				}
			}
			success=true;
		}
	}
	return success;
}

template<typename T> inline bool Display3D<T>::renderPoints(const std::unordered_set<std::shared_ptr<Point3D<T>>> ppoints) const {
	bool success=false;
	//printf("Rendering point\n");
	for (std::shared_ptr<Point3D<T>> ppoint : ppoints){
		Point3D<T> d_point=*ppoint-*(this->ppoint);

		if (pwindow!=NULL && prenderer!=NULL && pdraw_color!=NULL){
			changeRenderDrawColor(prenderer, pdraw_color);
			//SDL_SetRenderDrawColor(prenderer.get(), pdraw_color->r, pdraw_color->g, pdraw_color->b, pdraw_color->a); // Chooses the draw color.

			// Get the dimensions of the window
			int sizex(0);
			int sizey(0);
			SDL_GetWindowSize(pwindow.get(), &sizex, &sizey);
			T centerx=(T)(sizex/2);
			T centery=(T)(sizey/2);

			if (prenderer!=NULL){
				switch (display){
					case 1://(x,y) plane
						//printf("\nx=%i\n", (int)(d_point.x*(M)scale + centerx).to_m_type());
						drawPointRenderer(prenderer, (int)(d_point.x*scale + centerx).to_m_type(), (int)(d_point.y*scale + centery).to_m_type());
						break;
					case 2://(y,z) plane
						drawPointRenderer(prenderer, (int)(d_point.y*scale + centerx).to_m_type(), (int)(d_point.z*scale + centery).to_m_type());
						break;
					case 3://(x,z) plane
						drawPointRenderer(prenderer, (int)(d_point.x*scale + centerx).to_m_type(), (int)(d_point.z*scale + centery).to_m_type());
						break;
				}
			}
			success=true;
		}
	}
	return success;
}*/



#endif /* DISPLAY3D_HPP_ */
