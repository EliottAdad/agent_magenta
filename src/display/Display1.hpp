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
#include "../core/Line3D.hpp"
#include "../display/Displayable3D.hpp"
//#include "../utilities/Printable.hpp"
#include "../utilities/functions.hpp"
#include "../core/Scene3D.hpp"
#include "../utilities/functions_display.hpp"


/*
 * ###############
 *  Display1<T> :)
 * ###############
 * Orthographic projection
 * Choices between (x-y), (y-z), (z-x).
 * Display any object having x, y, z.
 */
template<typename T> class Display1 {
public:
	unsigned char fps;					// Frames per second
	char display;						// The point of view from which it is projected (1, 2, 3).
	float scale;						// Ratio d_pixels/d_meters
	std::unordered_set<std::shared_ptr<Scene3D<T>>> pscenes;			// Pointeurs to the scenes that are rendered in the display.

	std::shared_ptr<Point3D<T>> ppoint;				// Pointeur to the center of display.

	std::shared_ptr<COLOR> pbkgd_color;				// Pointeur to the background color.
	std::shared_ptr<COLOR> pdraw_color;				// Pointeur to the render color.
	std::shared_ptr<WINDOW> pwindow;				// Pointeur to the window.
	std::shared_ptr<RENDERER> prenderer;			// Pointeur to the renderer.
	bool fclear;

	Display1();
	Display1(std::shared_ptr<Point3D<T>> ppoint);
	Display1(std::shared_ptr<WINDOW> pwindow, std::shared_ptr<RENDERER> prenderer);
	virtual ~Display1();
	//Display1(const Display1 &other);

	void addPScene(std::shared_ptr<Scene3D<T>> pscene);
	
	void run(const unsigned int frames) const;
	bool render() const;
	bool renderScene(const std::shared_ptr<Scene3D<T>> pscene) const;
	bool renderDisplayable(const std::shared_ptr<Displayable3D<T>> pdisplayable) const;
	bool renderPoint(const std::shared_ptr<Point3D<T>> ppoint) const;
	bool renderPoints(const std::unordered_set<std::shared_ptr<Point3D<T>>> ppoints) const;
};




template<typename T> inline Display1<T>::Display1() {
	ppoint=std::make_shared<Point3D<T>>();
	fps=25;
	display=1;
	scale=2;

	pbkgd_color=createColor(0, 0, 0, 255);
	pdraw_color=createColor(255, 255, 255, 255);
	pwindow=NULL;//SDL_CreateWindow("Fama", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 600, 600, SDL_WINDOW_SHOWN);
//	if (pwindow!=NULL){
//		prenderer=SDL_CreateRenderer(pwindow, 0, SDL_RENDERER_TARGETTEXTURE);
//	}
	prenderer=NULL;

	fclear=true;
}

template<typename T> inline Display1<T>::Display1(std::shared_ptr<Point3D<T>> ppoint) {
	this->ppoint=ppoint;
	fps=25;
	display=1;
	scale=2;

	pbkgd_color=createColor(0, 0, 0, 255);
	pdraw_color=createColor(255, 255, 255, 255);
	pwindow=NULL;
	prenderer=NULL;

	fclear=true;
}

template<typename T> inline Display1<T>::Display1(std::shared_ptr<SDL_Window> pwindow, std::shared_ptr<SDL_Renderer> prenderer) {
	ppoint=std::make_shared<Point3D<T>>();
	fps=25;
	display=1;
	scale=2;

	pbkgd_color=createColor(0, 0, 0, 255);
	pdraw_color=createColor(255, 255, 255, 255);
	this->pwindow=pwindow;
	this->prenderer=prenderer;

	fclear=true;
}

template<typename T> inline Display1<T>::~Display1() {
	;
}

/*
Display1::Display1(const Display1 &other) {
	m_pwindow=;
}*/





template<typename T> inline void Display1<T>::addPScene(std::shared_ptr<Scene3D<T>> pscene){
	if (pscene!=NULL){
		pscenes.insert(pscene);
	}
}

/*
 * If 0: infinite loop
 */
template<typename T> inline void Display1<T>::run(const unsigned int frames) const {
	std::chrono::time_point t1=std::chrono::system_clock::now();
	//if (!fpause){
		unsigned int i(0);
		while (i<=frames){
			std::chrono::time_point t2=std::chrono::system_clock::now();
			std::chrono::duration dt=t2-t1;

			if (dt.count()>=1/(long double)fps*1000000000.){
				//printf("dt: %f\n", (float)(dt.count()/1000000000.));
				this->render();

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
template<typename T> inline bool Display1<T>::render() const {
	bool success=false;

	if (prenderer!=NULL){
		if (fclear){
			fillRendererWithColor(prenderer, pbkgd_color);// Fill the canvas with the background color
		}

		//printf("\nRendering 1: %ld\n", pscenes.size());
		for (std::shared_ptr<Scene3D<T>> pscene : pscenes){
			success=success | renderScene(pscene);
		}
		//drawCircle(prenderer.get(), {0, 0}, 100);

		/*std::unordered_set<std::shared_ptr<Point3D<T>>> ppoints=pixelizeCircle(ppoint, 200, 8);
		for (std::shared_ptr<Point3D<T>> ppoint : ppoints){
			success=success & render(ppoint);
		}*/

		displayChangesRenderer(prenderer);
	}

	return success;
}

/*
 *
 */
template<typename T> inline bool Display1<T>::renderScene(const std::shared_ptr<Scene3D<T>> pscene) const {
	bool success=false;

	if (pscene!=NULL){
		for (std::shared_ptr<Displayable3D<T>> pdisplayable : pscene->pdisplayables){
			success=success | renderDisplayable(pdisplayable);
		}
	}

	return success;
}

/*
 *
 */
template<typename T> inline bool Display1<T>::renderDisplayable(const std::shared_ptr<Displayable3D<T>> pdisplayable) const {
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
		/*std::unordered_set<std::shared_ptr<Point3D<T>>> ppoints=pdisplayable->pshape->getPoints();
		for (std::shared_ptr<Point3D<T>> ppoint : ppoints){
			success=success & render(ppoint);
		}*/
	}
	return success;
}

template<typename T> inline bool Display1<T>::renderPoint(const std::shared_ptr<Point3D<T>> ppoint) const {
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

template<typename T> inline bool Display1<T>::renderPoints(const std::unordered_set<std::shared_ptr<Point3D<T>>> ppoints) const {
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
}



#endif /* DISPLAY1_HPP_ */
