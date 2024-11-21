/*
 * Display1.cpp
 *
 *  Created on: 8 nov. 2024
 *      Author: esn
 */

#include "Display1.h"

Display1::Display1() {
	m_ppoint=new Point3D();
	m_display=1;
	m_scale=10;

	m_pbkgd_color=new SDL_Color{0, 0, 0, 255};
	m_pdraw_color=new SDL_Color{255, 255, 255, 255};
	m_pwindow=SDL_CreateWindow("Fama", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 600, 600, SDL_WINDOW_SHOWN);
	m_prenderer=SDL_CreateRenderer(m_pwindow, 0, SDL_RENDERER_TARGETTEXTURE);

	m_delp=true;
	m_delw=true;
	m_delr=true;
	m_fclear=true;
}

Display1::Display1(Point3D* ppoint) {
	m_ppoint=ppoint;
	m_display=1;
	m_scale=10;

	m_pbkgd_color=new SDL_Color{0, 0, 0, 255};
	m_pdraw_color=new SDL_Color{255, 255, 255, 255};
	m_pwindow=NULL;
	m_prenderer=NULL;

	m_delp=false;
	m_delw=false;
	m_delr=false;
	m_fclear=true;
}

Display1::Display1(SDL_Window* pwindow, SDL_Renderer* prenderer) {
	m_ppoint=new Point3D();
	m_display=1;
	m_scale=10;

	m_pbkgd_color=new SDL_Color{0, 0, 0, 255};
	m_pdraw_color=new SDL_Color{255, 255, 255, 255};
	m_pwindow=pwindow;
	m_prenderer=prenderer;

	m_delp=true;
	m_delw=false;
	m_delr=false;
	m_fclear=true;
}

Display1::~Display1() {
	delete m_ppoint;
	delete m_pbkgd_color;
	delete m_pdraw_color;

	if (m_pwindow!=NULL && m_delw){
		SDL_DestroyWindow(m_pwindow);
	}
	if (m_prenderer!=NULL && m_delr){
		SDL_DestroyRenderer(m_prenderer);
	}
}

/*
Display1::Display1(const Display1 &other) {
	m_pwindow=;
}*/



Point3D* Display1::getPPoint(){
	return m_ppoint;
}

/*
 * If you give a pointer, the point will be automatically considered
 * as instanciated somewhere else outside of the class.
 */
void Display1::setPPoint(Point3D* ppoint, const bool& delp){
	if (delp){
		if (m_delp){
			delete m_ppoint;
		}
		m_ppoint=new Point3D{*ppoint};
	}else{
		m_ppoint=ppoint;
	}
	m_delp=delp;
}

void Display1::setPoint(Point3D& point, const bool& delp){
	if (delp){
		if (m_delp){
			delete m_ppoint;
		}
		m_ppoint=new Point3D(point);
	}else{
		m_ppoint=&point;
	}
	m_delp=delp;
}

char Display1::getDisplay() const {
	return m_display;
}

void Display1::setDisplay(const char& display){
	m_display=display;
}

SDL_Window* Display1::getPWindow(){
	return m_pwindow;
}

SDL_Renderer* Display1::getPRenderer(){
	return m_prenderer;
}

std::set<Scene*> Display1::getPScenes() const {
	return m_pscenes;
}

void Display1::addPScene(Scene* pscene){
	if (pscene!=NULL){
		m_pscenes.insert(pscene);
	}
}

SDL_Color* Display1::getPBkgdColor(){
	return m_pbkgd_color;
}

void Display1::setBkrdColor(int b, int g, int r, int a){
	m_pdraw_color->b=r;
	m_pdraw_color->g=g;
	m_pdraw_color->r=r;
	m_pdraw_color->a=a;
}

SDL_Color* Display1::getPDrawColor(){
	return m_pdraw_color;
}


void Display1::setDrawColor(int b, int g, int r, int a){
	m_pdraw_color->b=r;
	m_pdraw_color->g=g;
	m_pdraw_color->r=r;
	m_pdraw_color->a=a;
}

void Display1::renderPoints(std::set<Point3D*> ppoints) const {//:)
	for (Point3D* ppoint : ppoints){
		this->renderPoint(ppoint);
	}
}

void Display1::renderPoint(Point3D* ppoint) const {//:)
	Point3D d_point=(*ppoint)-(*m_ppoint);
	ppoint->print(true);
	m_ppoint->print(true);
	d_point.print(true);

	SDL_SetRenderDrawColor(m_prenderer, m_pdraw_color->r, m_pdraw_color->g, m_pdraw_color->b, m_pdraw_color->a); // Chooses the background color.
	//SDL_RenderClear(m_prenderer); // Fill the canvas with the background color

	// Get the dimensions of the window
	int sizex(0);
	int sizey(0);
	SDL_GetWindowSize(m_pwindow, &sizex, &sizey);
	LSN centerx={(long double)sizex/2, 0};
	LSN centery={(long double)sizey/2, 0};

	if (m_prenderer!=NULL){
		switch (m_display){
			case 1://(x,y) plane
				SDL_RenderDrawPoint(m_prenderer, (int)(d_point.x*m_scale + centerx).to_long_double(), (int)(d_point.y*m_scale + centery).to_long_double());
				break;
			case 2://(y,z) plane
				SDL_RenderDrawPoint(m_prenderer, (int)(d_point.y*m_scale + centerx).to_long_double(), (int)(d_point.z*m_scale + centery).to_long_double());
				break;
			case 3://(x,z) plane
				SDL_RenderDrawPoint(m_prenderer, (int)(d_point.x*m_scale + centerx).to_long_double(), (int)(d_point.z*m_scale + centery).to_long_double());
				break;
		}
	}

}

/*
 *
 */
bool Display1::render() const {
	bool success=false;
	for (Scene* pscene : m_pscenes){
		render(pscene);
	}
	return success;
}

/*
 *
 */
bool Display1::render(Scene* pscene) const {
	bool success=false;
	for (Displayable* pdisplayable : pscene->getPDisplayables()){
		//printf("pdisplayable2\n");
		pdisplayable->print(true);
		render(pdisplayable);
	}
	return success;
}

/*
 *
 */
bool Display1::render(Displayable* pdisplayable) const {
	bool success=false;
	if (pdisplayable!=NULL) {
		//printf("pdisplayable1\n");
		pdisplayable->getX().print(true);
		pdisplayable->getY().print(true);
		pdisplayable->getZ().print(true);
		this->renderPoint(new Point3D{pdisplayable->getX(), pdisplayable->getY(), pdisplayable->getZ()});
	}
	return success;
}


std::string Display1::to_string(const bool& spread, const bool& full_info, const unsigned char& indent) const {// :)
	std::string mes=(spread)?"\n":"";

	mes+="DISPLAY1";

	return mes;
}

void Display1::print(const bool& spread, const bool& full_info, const unsigned char& indent) const {// :)
	printTabs(indent);
	std::cout << this->to_string(spread, full_info, indent);
}



