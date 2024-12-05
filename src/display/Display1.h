/*
 * Display1.h
 *
 *  Created on: 4 juin 2024
 *      Author: esn
 */

#ifndef DISPLAY1_H_

#define DISPLAY1_H_

#include <unordered_set>
#include <SDL2/SDL.h>
#include "../core/LSN.h"
#include "../core/Point3D.h"
#include "../core/Line3D.h"
#include "../display/Displayable.h"
#include "../utilities/Printable.h"
#include "../core/Scene.h"


/*
 * ############
 *  Display1 :)
 * ############
 * Orthographic projection
 * Choices between (x-y), (y-z), (z-x).
 * Display any object having x, y, z.
 */
template<typename M, typename E> class Display1 : public Printable {
private:
	Point3D<M, E>* m_ppoint;			// Pointeur to the center of display.
	char m_display;						// The point of view from which it is projected (1, 2, 3).
	float m_scale;						// Ratio d_pixels/d_meters
	std::unordered_set<Scene<M, E>*> m_pscenes;			// Pointeurs to the scenes that are rendered in the display.

	SDL_Color* m_pbkgd_color;			// Pointeur to the background color.
	SDL_Color* m_pdraw_color;			// Pointeur to the render color.
	SDL_Window* m_pwindow;				// Pointeur to the window.
	SDL_Renderer* m_prenderer;			// Pointeur to the renderer.

	bool m_delp;
	bool m_delw;
	bool m_delr;
	bool m_fclear;

public:
	Display1();
	Display1(Point3D<M, E>* ppoint);
	Display1(SDL_Window* pwindow, SDL_Renderer* prenderer);
	virtual ~Display1();
	//Display1(const Display1 &other);

	//Point3D<M, E> getPoint() const;
	Point3D<M, E>* getPPoint() const;
	void setPPoint(Point3D<M, E>* ppoint, const bool& delp=false);
	void setPoint(Point3D<M, E>& point, const bool& delp=true);
	char getDisplay() const;
	void setDisplay(const char& display);
	float getScale() const;
	void setScale(const float& scale);
	SDL_Color getBkgdColor() const;
	void setBkrdColor(const SDL_Color& color);
	void setBkrdColor(const unsigned char& r, const unsigned char& g, const unsigned char& b, const unsigned char& a);
	SDL_Color getDrawColor() const;
	void setDrawColor(const SDL_Color& color);
	void setDrawColor(const unsigned char& r, const unsigned char& g, const unsigned char& b, const unsigned char& a);

	SDL_Window* getPWindow() const ;
	void setPWindow(SDL_Window* pwindow, const bool& delw=false);
	SDL_Renderer* getPRenderer() const ;
	void setPRenderer(SDL_Renderer* prenderer, const bool& delr=false);
	std::unordered_set<Scene<M, E>*> getPScenes() const;
	void addPScene(Scene<M, E>* pscene);

	bool render() const;
	bool render(const Scene<M, E>* pscene) const;
	bool render(const Displayable<M, E>* pdisplayable) const;
	bool render(const Point3D<M, E>* ppoint) const;

	virtual std::string to_string(const bool& spread=false, const bool& full_info=false, const unsigned char& indent=0) const;// :)
	virtual void print(const bool& spread=false, const bool& full_info=false, const unsigned char& indent=0) const;// :)
};


template<typename M, typename E> Display1<M, E>::Display1() {
	m_ppoint=new Point3D<M, E>{{0.,0},{0.,0},{0.,0}};
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

template<typename M, typename E> Display1<M, E>::Display1(Point3D<M, E>* ppoint) {
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
	m_ppoint=new Point3D<M, E>{{0.,0},{0.,0},{0.,0}};
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
	if (m_delp){
		delete m_ppoint;
	}
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



/*template<typename M, typename E> Point3D<M, E> Display1<M, E>::getPoint() const {
	return *m_ppoint;
}*/

template<typename M, typename E> Point3D<M, E>* Display1<M, E>::getPPoint() const {
	Point3D<M, E>* ppoint;
	if (!m_delp){
		ppoint=m_ppoint;
	}
	return ppoint;
}

/*
 * If you give a pointer, the point will be automatically considered
 * as instanciated somewhere else outside of the class.
 */
template<typename M, typename E> void Display1<M, E>::setPPoint(Point3D<M, E>* ppoint, const bool& delp){
	if (m_delp){
		delete m_ppoint;
	}
	if (delp){
		m_ppoint=new Point3D<float, char>(*ppoint);
	}else{
		m_ppoint=ppoint;
	}
	m_delp=delp;
}

template<typename M, typename E> void Display1<M, E>::setPoint(Point3D<M, E>& point, const bool& delp){
	if (m_delp){
		delete m_ppoint;
	}
	if (delp){
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

template<typename M, typename E> void Display1<M, E>::setBkrdColor(const unsigned char& b, const unsigned char& g, const unsigned char& r, const unsigned char& a){
	m_pdraw_color->b=r;
	m_pdraw_color->g=g;
	m_pdraw_color->r=r;
	m_pdraw_color->a=a;
}

template<typename M, typename E> SDL_Color Display1<M, E>::getDrawColor() const {
	return *m_pdraw_color;
}

template<typename M, typename E> void Display1<M, E>::setDrawColor(const unsigned char& b, const unsigned char& g, const unsigned char& r, const unsigned char& a){
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


template<typename M, typename E> std::unordered_set<Scene<M, E>*> Display1<M, E>::getPScenes() const {
	return m_pscenes;
}

template<typename M, typename E> void Display1<M, E>::addPScene(Scene<M, E>* pscene){
	if (pscene!=NULL){
		m_pscenes.insert(pscene);
	}
}

/*
 *
 */
template<typename M, typename E> bool Display1<M, E>::render() const {
	bool success=false;

	SDL_SetRenderDrawColor(m_prenderer, m_pbkgd_color->r, m_pbkgd_color->g, m_pbkgd_color->b, m_pbkgd_color->a); // Chooses the background color.
	if (m_fclear){
		SDL_RenderClear(m_prenderer); // Fill the canvas with the background color
	}

	printf("\nRendering 1\n");
	for (Scene<M, E>* pscene : m_pscenes){
		render(pscene);
	}

	SDL_RenderPresent(m_prenderer);

	return success;
}

/*
 *
 */
template<typename M, typename E> bool Display1<M, E>::render(const Scene<M, E>* pscene) const {
	bool success=true;
	printf("\nRendering 2: %li\n", pscene->getPDisplayables().size());
	if (pscene!=NULL){
		for (Displayable<M, E>* pdisplayable : pscene->getPDisplayables()){
			//printf("pdisplayable2\n");
			//pdisplayable->print(true);
			//success=success & render(pdisplayable);
			success=success && render(pdisplayable);
		}
	}
	return success;
}

/*
 *
 */
template<typename M, typename E> bool Display1<M, E>::render(const Displayable<M, E>* pdisplayable) const {
	bool success=false;
	printf("\nRendering 3_1, next if: %b\n", pdisplayable!=NULL);
	if (pdisplayable!=NULL) {
		//printf("pdisplayable1\n");
		//pdisplayable->getX().print(true);
		//pdisplayable->getY().print(true);
		//pdisplayable->getZ().print(true);
		printf("\nRendering 3_2\n");
		SDL_SetRenderDrawColor(m_prenderer, pdisplayable->getColor().r, pdisplayable->getColor().g, pdisplayable->getColor().b, pdisplayable->getColor().a);
		printf("\nRendering 3_3\n");
		Point3D<M, E> p(pdisplayable->getX(), pdisplayable->getY(), pdisplayable->getZ());
		render(&p);
	}
	return success;
}

template<typename M, typename E> bool Display1<M, E>::render(const Point3D<M, E>* ppoint) const {
	Point3D<M, E> d_point=(*ppoint)-(*m_ppoint);
	printf("\nRendering 4\n");
	//ppoint->print(true);
	//m_ppoint->print(true);
	//d_point.print(true);
	//SDL_Renderer* prenderer=pdisplay->getPRenderer();
	//SDL_Window* pwindow=pdisplay->getPWindow();

	if (m_prenderer!=NULL){
		//SDL_SetRenderDrawColor(m_prenderer, m_pdraw_color->r, m_pdraw_color->g, m_pdraw_color->b, m_pdraw_color->a); // Chooses the draw color.
		//SDL_RenderClear(m_prenderer); // Fill the canvas with the background color

		if (m_pwindow!=NULL){
			// Get the dimensions of the window
			int sizex(0);
			int sizey(0);
			SDL_GetWindowSize(m_pwindow, &sizex, &sizey);
			SN<M, E> centerx={(M)(sizex/2), (E)0};
			SN<M, E> centery={(M)(sizey/2), (E)0};

			if (m_prenderer!=NULL){
				switch (m_display){
					case 1://(x,y) plane
						printf("\nx=%i\n", (int)(d_point.x*(M)m_scale + centerx).to_m_type());
						SDL_RenderDrawPoint(m_prenderer, (int)(d_point.x*(M)m_scale + centerx).to_m_type(), (int)(d_point.y*(M)m_scale + centery).to_m_type());
						break;
					case 2://(y,z) plane
						SDL_RenderDrawPoint(m_prenderer, (int)(d_point.y*(M)m_scale + centerx).to_m_type(), (int)(d_point.z*(M)m_scale + centery).to_m_type());
						break;
					case 3://(x,z) plane
						SDL_RenderDrawPoint(m_prenderer, (int)(d_point.x*(M)m_scale + centerx).to_m_type(), (int)(d_point.z*(M)m_scale + centery).to_m_type());
						break;
				}
			}
			return true;
		}
	}
	return false;
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


//template<typename M, typename E> bool render(const Display1<M, E>* pdisplay, const Point3D<M, E>* ppoint);
//template<typename T, typename M, typename E> bool render(const Display1<M, E>* pdisplay, const T* pt);
//template<typename M, typename E> void renderPoints(const Display1* pdisplay, std::unordered_set<Point3D<M, E>*> ppoints);//:)
//template<typename M, typename E> void renderPoint(const Display1* pdisplay, const Point3D<M, E>* ppoint);//:)
//void renderLines(const Display1* pdisplay, std::unordered_set<Line3D*> plines);//:)
//void renderLine(const Display1* pdisplay, Line3D* pline);//:)



/*
 *
 */
/*template<typename T, typename M, typename E> bool render(const Display1<M, E>* pdisplay, const T* pt) {
	bool success=false;
	if (pt!=NULL) {
		//printf("pdisplayable1\n");
		//pdisplayable->getX().print(true);
		//pdisplayable->getY().print(true);
		//pdisplayable->getZ().print(true);
		Point3D<M, E> p{pt->getX(), pt->getY(), pt->getZ()};
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
	Point3D<float, char> d_point=(*ppoint)-(*m_ppoint);
	//ppoint->print(true);
	//m_ppoint->print(true);
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
		switch (m_display){
			case 1://(x,y) plane
				SDL_RenderDrawPoint(m_prenderer, (int)(d_point.x*m_scale + centerx).to_m_type(), (int)(d_point.y*m_scale + centery).to_m_type());
				break;
			case 2://(y,z) plane
				SDL_RenderDrawPoint(m_prenderer, (int)(d_point.y*m_scale + centerx).to_m_type(), (int)(d_point.z*m_scale + centery).to_m_type());
				break;
			case 3://(x,z) plane
				SDL_RenderDrawPoint(m_prenderer, (int)(d_point.x*m_scale + centerx).to_m_type(), (int)(d_point.z*m_scale + centery).to_m_type());
				break;
		}
	}

}*/



#endif /* DISPLAY1_H_ */
