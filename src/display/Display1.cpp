/*
 * Display1.cpp
 *
 *  Created on: 8 nov. 2024
 *      Author: esn
 */

//#include "Display1.h"

#ifdef D

#define E

template<typename M, typename E> Display1<M, E>::Display1() {
	m_ppoint=new Point3D<M, E>();
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

template<typename M, typename E> Display1<M, E>::Display1(Point3D<float, char>* ppoint) {
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

template<typename M, typename E> Display1<M, E>::Display1(SDL_Window* pwindow, SDL_Renderer* prenderer) {
	m_ppoint=new Point3D<float, char>();
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

template<typename M, typename E> Display1<M, E>::~Display1() {
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



template<typename M, typename E> Point3D<float, char> Display1<M, E>::getPoint() const {
	return *m_ppoint;
}

template<typename M, typename E> Point3D<float, char>* Display1<M, E>::getPPoint() const {
	return m_ppoint;
}

/*
 * If you give a pointer, the point will be automatically considered
 * as instanciated somewhere else outside of the class.
 */
template<typename M, typename E> void Display1<M, E>::setPPoint(Point3D<float, char>* ppoint, const bool& delp){
	if (delp){
		if (m_delp){
			delete m_ppoint;
		}
		m_ppoint=new Point3D<float, char>{*ppoint};
	}else{
		m_ppoint=ppoint;
	}
	m_delp=delp;
}

template<typename M, typename E> void Display1<M, E>::setPoint(Point3D<float, char>& point, const bool& delp){
	if (delp){
		if (m_delp){
			delete m_ppoint;
		}
		m_ppoint=new Point3D<float, char>(point);
	}else{
		m_ppoint=&point;
	}
	m_delp=delp;
}

template<typename M, typename E> char Display1<M, E>::getDisplay() const {
	return m_display;
}

template<typename M, typename E> void Display1<M, E>::setDisplay(const char& display){
	m_display=display;
}

template<typename M, typename E> float Display1<M, E>::getScale() const {
	return m_scale;
}

template<typename M, typename E> void Display1<M, E>::setScale(const float& scale){
	m_scale=scale;
}

template<typename M, typename E> SDL_Color Display1<M, E>::getBkgdColor() const {
	return *m_pbkgd_color;
}

template<typename M, typename E> void Display1<M, E>::setBkrdColor(unsigned char b, unsigned char g, unsigned char r, unsigned char a){
	m_pdraw_color->b=r;
	m_pdraw_color->g=g;
	m_pdraw_color->r=r;
	m_pdraw_color->a=a;
}

template<typename M, typename E> SDL_Color Display1<M, E>::getDrawColor() const {
	return *m_pdraw_color;
}

template<typename M, typename E> void Display1<M, E>::setDrawColor(unsigned char b, unsigned char g, unsigned char r, unsigned char a){
	m_pdraw_color->b=r;
	m_pdraw_color->g=g;
	m_pdraw_color->r=r;
	m_pdraw_color->a=a;
}

template<typename M, typename E> SDL_Window* Display1<M, E>::getPWindow() const {
	SDL_Window* pwindow=NULL;
	if (!m_delw){
		pwindow=m_pwindow;
	}
	return pwindow;
}

template<typename M, typename E> void Display1<M, E>::setPWindow(SDL_Window* pwindow, const bool& delw){
	;
}

template<typename M, typename E> SDL_Renderer* Display1<M, E>::getPRenderer() const {
	SDL_Renderer* prenderer=NULL;
	if (!m_delr){
		prenderer=m_prenderer;
	}
	return prenderer;
}

template<typename M, typename E> void Display1<M, E>::setPRenderer(SDL_Renderer* prenderer, const bool& delr){
	;
}


template<typename M, typename E> std::unordered_set<Scene*> Display1<M, E>::getPScenes() const {
	return m_pscenes;
}

template<typename M, typename E> void Display1<M, E>::addPScene(Scene* pscene){
	if (pscene!=NULL){
		m_pscenes.insert(pscene);
	}
}

/*
 *
 */
template<typename M, typename E> bool Display1<M, E>::render() const {
	bool success=false;
	for (Scene* pscene : m_pscenes){
		render(pscene);
	}
	return success;
}

/*
 *
 */
template<typename M, typename E> bool Display1<M, E>::render(const Scene* pscene) const {
	bool success=true;
	if (pscene!=NULL){
		for (Displayable* pdisplayable : pscene->getPDisplayables()){
			//printf("pdisplayable2\n");
			//pdisplayable->print(true);
			success=success & render(pdisplayable);
		}
	}
	return success;
}

/*
 *
 */
template<typename M, typename E> bool Display1<M, E>::render(const Displayable* pdisplayable) const {
	bool success=false;
	if (pdisplayable!=NULL) {
		//printf("pdisplayable1\n");
		//pdisplayable->getX().print(true);
		//pdisplayable->getY().print(true);
		//pdisplayable->getZ().print(true);
		Point3D<float, char> p(pdisplayable->getX(), pdisplayable->getY(), pdisplayable->getZ());
		//render(&p);
	}
	return success;
}





template<typename M, typename E> std::string Display1<M, E>::to_string(const bool& spread, const bool& full_info, const unsigned char& indent) const {// :)
	std::string mes=(spread)?"\n":"";

	mes+="DISPLAY1";

	return mes;
}

template<typename M, typename E> void Display1<M, E>::print(const bool& spread, const bool& full_info, const unsigned char& indent) const {// :)
	printTabs(indent);
	std::cout << this->to_string(spread, full_info, indent);
}


// Functions
#endif

