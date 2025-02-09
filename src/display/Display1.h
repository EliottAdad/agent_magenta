/*
 * Display1.h
 *
 *  Created on: 4 juin 2024
 *      Author: esn
 */

#ifndef DISPLAY1_H_

#define DISPLAY1_H_

#include <memory>
#include <unordered_set>
//#include <SDL2/SDL.h>

#include "../core/Point3D.h"
#include "../core/Line3D.h"
#include "../display/Displayable.h"
#include "../utilities/Printable.h"
#include "../utilities/functions.h"
#include "../core/Scene.h"
#include "../utilities/functions_display.h"


/*
 * ###############
 *  Display1<T> :)
 * ###############
 * Orthographic projection
 * Choices between (x-y), (y-z), (z-x).
 * Display any object having x, y, z.
 */
template<typename T> class Display1 : public Printable {
public:
	unsigned char fps;					// Frames per second
	char display;						// The point of view from which it is projected (1, 2, 3).
	float scale;						// Ratio d_pixels/d_meters
	std::unordered_set<std::shared_ptr<Scene<T>>> pscenes;			// Pointeurs to the scenes that are rendered in the display.

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

	void addPScene(std::shared_ptr<Scene<T>> pscene);

	bool render() const;
	bool render(const std::shared_ptr<Scene<T>> pscene) const;
	bool render(const std::shared_ptr<Displayable<T>> pdisplayable) const;
	bool render(const std::shared_ptr<Point3D<T>> ppoint) const;

	virtual std::string to_string(const bool& spread=false, const bool& full_info=false, const unsigned char& indent=0) const;// :)
	virtual void print(const bool& spread=false, const bool& full_info=false, const unsigned char& indent=0) const;// :)
};


template<typename T> Display1<T>::Display1() {
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

template<typename T> Display1<T>::Display1(std::shared_ptr<Point3D<T>> ppoint) {
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

template<typename T> Display1<T>::Display1(std::shared_ptr<SDL_Window> pwindow, std::shared_ptr<SDL_Renderer> prenderer) {
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

template<typename T> Display1<T>::~Display1() {
	;
}

/*
Display1::Display1(const Display1 &other) {
	m_pwindow=;
}*/



template<typename T> void Display1<T>::addPScene(std::shared_ptr<Scene<T>> pscene){
	if (pscene!=NULL){
		pscenes.insert(pscene);
	}
}

/*
 *
 */
template<typename T> bool Display1<T>::render() const {
	bool success=false;

	if (prenderer!=NULL){
		if (fclear){
			fillRendererWithColor(prenderer, pbkgd_color);// Fill the canvas with the background color
		}

		//printf("\nRendering 1: %ld\n", pscenes.size());
		for (std::shared_ptr<Scene<T>> pscene : pscenes){
			success=success | render(pscene);
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
template<typename T> bool Display1<T>::render(const std::shared_ptr<Scene<T>> pscene) const {
	bool success=false;

	if (pscene!=NULL){
		for (std::shared_ptr<Displayable<T>> pdisplayable : pscene->getPDisplayables()){
			success=success | render(pdisplayable);
		}
	}

	return success;
}

/*
 *
 */
template<typename T> bool Display1<T>::render(const std::shared_ptr<Displayable<T>> pdisplayable) const {
	bool success=true;

	if (pdisplayable!=NULL) {
		//std::shared_ptr<Point3D<T>> pp(new Point3D<T>(pdisplayable->getPosition()));
		//success=success & render(pp);

		// For the points
		std::unordered_set<std::shared_ptr<Point3D<T>>> ppoints=pdisplayable->getPPoints();
		for (std::shared_ptr<Point3D<T>> ppoint : ppoints){
			//printf("There is at least one Point to be displayed.");
			success=success & render(ppoint);
		}

		// For the lines
		/*std::unordered_set<std::shared_ptr<Point3D<T>>> ppoints=pdisplayable->pshape->getPoints();
		for (std::shared_ptr<Point3D<T>> ppoint : ppoints){
			success=success & render(ppoint);
		}*/
	}
	return success;
}

template<typename T> bool Display1<T>::render(const std::shared_ptr<Point3D<T>> ppoint) const {
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

/*template<typename T> bool Display1<T>::renderPoints(const std::unordered_set<std::shared_ptr<Point3D<T>>> ppoints) const {
	bool success=false;

	//if (this->ppoint!=NULL){
		Point3D<T> d_point=*ppoint-*(this->ppoint);
		//printf("\nRendering 4\n");
		//ppoint->print(true);
		//ppoint->print(true);
		//d_point.print(true);
		//SDL_Renderer* prenderer=pdisplay->getPRenderer();
		//SDL_Window* pwindow=pdisplay->getPWindow();

		if (pwindow!=NULL && prenderer!=NULL && pdraw_color!=NULL){
			SDL_SetRenderDrawColor(prenderer.get(), pdraw_color->r, pdraw_color->g, pdraw_color->b, pdraw_color->a); // Chooses the draw color.

			//SDL_RenderClear(m_prenderer); // Fill the canvas with the background color

			// Get the dimensions of the window
			int sizex(0);
			int sizey(0);
			SDL_GetWindowSize(pwindow.get(), &sizex, &sizey);
			SN<T> centerx={(M)(sizex/2),(E)0};
			SN<T> centery={(M)(sizey/2),(E)0};

			if (prenderer!=NULL){
				switch (display){
					case 1://(x,y) plane
						//printf("\nx=%i\n", (int)(d_point.x*(M)scale + centerx).to_m_type());
						SDL_RenderDrawPoint(prenderer.get(), (int)(d_point.x*(M)scale + centerx).to_m_type(), (int)(d_point.y*(M)scale + centery).to_m_type());
						break;
					case 2://(y,z) plane
						SDL_RenderDrawPoint(prenderer.get(), (int)(d_point.y*(M)scale + centerx).to_m_type(), (int)(d_point.z*(M)scale + centery).to_m_type());
						break;
					case 3://(x,z) plane
						SDL_RenderDrawPoint(prenderer.get(), (int)(d_point.x*(M)scale + centerx).to_m_type(), (int)(d_point.z*(M)scale + centery).to_m_type());
						break;
				}
			}
			success=true;
		}
	//}
	return success;
}*/





template<typename T> std::string Display1<T>::to_string(const bool& spread, const bool& full_info, const unsigned char& indent) const {// :)
	std::string mes=(spread)?"\n":"";

	mes+="DISPLAY1\n";

	return mes;
}

template<typename T> void Display1<T>::print(const bool& spread, const bool& full_info, const unsigned char& indent) const {// :)
	printTabs(indent);
	std::cout << this->to_string(spread, full_info, indent);
}


// Functions


//template<typename T> bool render(const Display1<T>* pdisplay, const Point3D<T>* ppoint);
//template<typename T, typename M, typename E> bool render(const Display1<T>* pdisplay, const T* pt);
//template<typename T> void renderPoints(const Display1* pdisplay, std::unordered_set<Point3D<T>*> ppoints);//:)
//template<typename T> void renderPoint(const Display1* pdisplay, const Point3D<T>* ppoint);//:)
//void renderLines(const Display1* pdisplay, std::unordered_set<Line3D*> plines);//:)
//void renderLine(const Display1* pdisplay, Line3D* pline);//:)



/*
 *
 */
/*template<typename T, typename M, typename E> bool render(const Display1<T>* pdisplay, const T* pt) {
	bool success=false;
	if (pt!=NULL) {
		//printf("pdisplayable1\n");
		//pdisplayable->getX().print(true);
		//pdisplayable->getY().print(true);
		//pdisplayable->getZ().print(true);
		Point3D<T> p{pt->getX(), pt->getY(), pt->getZ()};
		render(pdisplay, &p);
	}
	return success;
}*/


/*void renderPoints(std::unordered_set<Point3D<float, char>*> ppoints) const {//:)
	for (Point3D<float, char>* ppoint : ppoints){
		this->renderPoint(ppoint);
	}
}

void Display1::renderPoint(Point3D<float, char>* ppoint) const {//:)
	Point3D<float, char> d_point=(*ppoint)-(*ppoint);
	//ppoint->print(true);
	//ppoint->print(true);
	//d_point.print(true);

	SDL_SetRenderDrawColor(m_prenderer, m_pdraw_color->r, m_pdraw_color->g, m_pdraw_color->b, m_pdraw_color->a); // Chooses the background color.
	//SDL_RenderClear(m_prenderer); // Fill the canvas with the background color

	// Get the dimensions of the window
	int sizex(0);
	int sizey(0);
	SDL_GetWindowSize(m_pwindow, &sizex, &sizey);
	SN<float, char> centerx={(float)sizex/2, 0};
	SN<float, char> centery={(float)sizey/2, 0};

	if (m_prenderer!=NULL){
		switch (display){
			case 1://(x,y) plane
				SDL_RenderDrawPoint(m_prenderer, (int)(d_point.x*scale + centerx).to_m_type(), (int)(d_point.y*scale + centery).to_m_type());
				break;
			case 2://(y,z) plane
				SDL_RenderDrawPoint(m_prenderer, (int)(d_point.y*scale + centerx).to_m_type(), (int)(d_point.z*scale + centery).to_m_type());
				break;
			case 3://(x,z) plane
				SDL_RenderDrawPoint(m_prenderer, (int)(d_point.x*scale + centerx).to_m_type(), (int)(d_point.z*scale + centery).to_m_type());
				break;
		}
	}

}*/



#endif /* DISPLAY1_H_ */
