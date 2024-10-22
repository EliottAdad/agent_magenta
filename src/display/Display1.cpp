/*
 * Display1.cpp
 *
 *  Created on: 4 juin 2024
 *      Author: esn
 */

#include "Display1.h"

Display1::Display1() {
	m_pwindow=NULL;//SDL_CreateWindow("Fama", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 200, 200, SDL_WINDOW_SHOWN);
	m_prenderer=NULL;//SDL_CreateRenderer(m_pwindow, 0, SDL_RENDERER_TARGETTEXTURE);
	m_fclear=true;
}

Display1::~Display1() {
	if (m_pwindow!=NULL){
		//SDL_DestroyWindow(m_pwindow);
	}
	if (m_prenderer!=NULL){
		//SDL_DestroyRenderer(m_prenderer);
	}
}

/*
Display1::Display1(const Display1 &other) {
	m_pwindow=;
}*/



void Display1::renderPoints(std::set<Point3D*> ppoints){//:)
	for (Point3D* ppoint : ppoints){
		this->renderPoint(ppoint);
	}
}

void Display1::renderPoint(Point3D* ppoint){//:)
	;
}
