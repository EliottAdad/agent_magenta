/*
 * Display1.h
 *
 *  Created on: 4 juin 2024
 *      Author: esn
 */

#ifndef DISPLAY1_H_
#define DISPLAY1_H_

#include <set>
#include <SDL2/SDL.h>
#include "../core/Point3D.h"
#include "../core/Line3D.h"


/*
 * ############
 *  Display1 :)
 * ############
 * Orthographic projection
 * Choices between (x-y), (y-z), (z-x).
 * Display any object having x, y, z.
 */
template <typename T> class Display1 {
private:
	SDL_Window* m_pwindow;				// Pointeur to the window.
	SDL_Renderer* m_prenderer;			// Pointeur to the renderer.
	bool m_delw;
	bool m_delr;
	bool m_fclear;
public:
	Display1();
	virtual ~Display1();
	//Display1(const Display1 &other);

	bool render(T* pelement);
	void renderPoints(std::set<Point3D*> ppoints);//:)
	void renderPoint(Point3D* ppoint);//:)
	void renderLines(std::set<Line3D*> plines);//:)
	void renderLine(Line3D* pline);//:)
};


template <typename T> Display1<T>::Display1() {
	m_pwindow=SDL_CreateWindow("Fama", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 200, 200, SDL_WINDOW_SHOWN);
	m_prenderer=SDL_CreateRenderer(m_pwindow, 0, SDL_RENDERER_TARGETTEXTURE);
	m_delw=true;
	m_delr=true;
	m_fclear=true;
}

template <typename T> Display1<T>::~Display1() {
	if (m_pwindow!=NULL){
		SDL_DestroyWindow(m_pwindow);
	}
	if (m_prenderer!=NULL){
		SDL_DestroyRenderer(m_prenderer);
	}
}

/*
template <typename T> Display1::Display1(const Display1 &other) {
	m_pwindow=;
}*/



template <typename T> void Display1<T>::renderPoints(std::set<Point3D*> ppoints){//:)
	for (Point3D* ppoint : ppoints){
		this->renderPoint(ppoint);
	}
}

template <typename T> void Display1<T>::renderPoint(Point3D* ppoint){//:)
	;
}

/*
 * T needs to have x, y, z
 */
template <typename T> bool Display1<T>::render(T* pelement) {
	bool success=false;
	if (pelement!=NULL) {
		pelement->x, pelement->y, pelement->z;
	}
	return success;
}

#endif /* DISPLAY1_H_ */
