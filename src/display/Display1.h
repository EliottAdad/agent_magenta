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
#include <SDL2/SDL.h>

#include "../core/LSN.h"
#include "../core/Point3D.h"
#include "../core/Line3D.h"
#include "../display/Displayable.h"
#include "../utilities/Printable.h"
#include "../core/Scene.h"


/*
 * ##################
 *  Display1<M, E> :)
 * ##################
 * Orthographic projection
 * Choices between (x-y), (y-z), (z-x).
 * Display any object having x, y, z.
 */
template<typename M, typename E> class Display1 : public Printable {
private:
	char m_display;						// The point of view from which it is projected (1, 2, 3).
	float m_scale;						// Ratio d_pixels/d_meters
	std::unordered_set<std::shared_ptr<Scene<M, E>>> m_pscenes;			// Pointeurs to the scenes that are rendered in the display.

	bool m_fclear;

public:
	std::shared_ptr<Point3D<M, E>> ppoint;				// Pointeur to the center of display.

	std::shared_ptr<SDL_Color> pbkgd_color;				// Pointeur to the background color.
	std::shared_ptr<SDL_Color> pdraw_color;				// Pointeur to the render color.
	std::shared_ptr<SDL_Window> pwindow;				// Pointeur to the window.
	std::shared_ptr<SDL_Renderer> prenderer;			// Pointeur to the renderer.

	Display1();
	Display1(std::shared_ptr<Point3D<M, E>> ppoint);
	Display1(std::shared_ptr<SDL_Window> pwindow, std::shared_ptr<SDL_Renderer> prenderer);
	virtual ~Display1();
	//Display1(const Display1 &other);

	char getDisplay() const;
	void setDisplay(const char& display);
	float getScale() const;
	void setScale(const float& scale);
	bool getFClear() const;
	void setFClear(const bool& fclear);

	std::unordered_set<std::shared_ptr<Scene<M, E>>> getPScenes() const;
	void addPScene(std::shared_ptr<Scene<M, E>> pscene);

	bool render() const;
	bool render(const std::shared_ptr<Scene<M, E>> pscene) const;
	bool render(const std::shared_ptr<Displayable<M, E>> pdisplayable) const;
	bool render(const std::shared_ptr<Point3D<M, E>> ppoint) const;

	virtual std::string to_string(const bool& spread=false, const bool& full_info=false, const unsigned char& indent=0) const;// :)
	virtual void print(const bool& spread=false, const bool& full_info=false, const unsigned char& indent=0) const;// :)
};


template<typename M, typename E> Display1<M, E>::Display1() {
	ppoint=std::make_shared<Point3D<M, E>>();
	m_display=1;
	m_scale=5;

	pbkgd_color=std::make_shared<SDL_Color>(SDL_Color{0, 0, 0, 255});
	pdraw_color=std::make_shared<SDL_Color>(SDL_Color{255, 255, 255, 255});
	pwindow=NULL;//SDL_CreateWindow("Fama", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 600, 600, SDL_WINDOW_SHOWN);
//	if (pwindow!=NULL){
//		prenderer=SDL_CreateRenderer(pwindow, 0, SDL_RENDERER_TARGETTEXTURE);
//	}
	prenderer=NULL;

	m_fclear=true;
}

template<typename M, typename E> Display1<M, E>::Display1(std::shared_ptr<Point3D<M, E>> ppoint) {
	this->ppoint=ppoint;
	m_display=1;
	m_scale=5;

	pbkgd_color=std::make_shared<SDL_Color>(SDL_Color{0, 0, 0, 255});
	pdraw_color=std::make_shared<SDL_Color>(SDL_Color{255, 255, 255, 255});
	pwindow=NULL;//SDL_CreateWindow("Fama", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 600, 600, SDL_WINDOW_SHOWN);
//	if (pwindow!=NULL){
//		prenderer=SDL_CreateRenderer(pwindow, 0, SDL_RENDERER_TARGETTEXTURE);
//	}
	prenderer=NULL;

	m_fclear=true;
}

template<typename M, typename E> Display1<M, E>::Display1(std::shared_ptr<SDL_Window> pwindow, std::shared_ptr<SDL_Renderer> prenderer) {
	ppoint=std::make_shared<Point3D<M, E>>();
	m_display=1;
	m_scale=5;

	pbkgd_color=std::make_shared<SDL_Color>(SDL_Color{0, 0, 0, 255});
	pdraw_color=std::make_shared<SDL_Color>(SDL_Color{255, 255, 255, 255});
	this->pwindow=pwindow;
	this->prenderer=prenderer;

	m_fclear=true;
}

template<typename M, typename E> Display1<M, E>::~Display1() {
	;
}

/*
Display1::Display1(const Display1 &other) {
	m_pwindow=;
}*/



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

template<typename M, typename E> bool Display1<M, E>::getFClear() const {
	return m_fclear;
}

template<typename M, typename E> void Display1<M, E>::setFClear(const bool& fclear){
	m_fclear=fclear;
}

template<typename M, typename E> std::unordered_set<std::shared_ptr<Scene<M, E>>> Display1<M, E>::getPScenes() const {
	return m_pscenes;
}

template<typename M, typename E> void Display1<M, E>::addPScene(std::shared_ptr<Scene<M, E>> pscene){
	if (pscene!=NULL){
		m_pscenes.insert(pscene);
	}
}

/*
 *
 */
template<typename M, typename E> bool Display1<M, E>::render() const {
	bool success=false;

	if (prenderer!=NULL){
		if (m_fclear){
			SDL_SetRenderDrawColor(prenderer.get(), pbkgd_color->r, pbkgd_color->g, pbkgd_color->b, pbkgd_color->a); // Chooses the background color.
			SDL_RenderClear(prenderer.get()); // Fill the canvas with the background color
		}

		//printf("\nRendering 1: %ld\n", m_pscenes.size());
		for (std::shared_ptr<Scene<M, E>> pscene : m_pscenes){
			success=success | render(pscene);
		}

		SDL_RenderPresent(prenderer.get());
	}

	return success;
}

/*
 *
 */
template<typename M, typename E> bool Display1<M, E>::render(const std::shared_ptr<Scene<M, E>> pscene) const {
	bool success=false;
	//printf("\nRendering 2: %li\n", pscene->getPDisplayables().size());

	if (pscene!=NULL){
		for (std::shared_ptr<Displayable<M, E>> pdisplayable : pscene->getPDisplayables()){
			success=success | render(pdisplayable);
		}
	}
	return success;
}

/*
 *
 */
template<typename M, typename E> bool Display1<M, E>::render(const std::shared_ptr<Displayable<M, E>> pdisplayable) const {
	bool success=true;

	if (pdisplayable!=NULL) {
		std::shared_ptr<Point3D<M, E>> pp(new Point3D<M, E>(pdisplayable->getPosition()));
		//std::unordered_set<std::shared_ptr<Point3D<M, E>>> ppoints=pdisplayable->getPoints();
		success=success & render(pp);
		/*for (std::shared_ptr<Point3D<M, E>> ppoint : ppoints){
			success=success & render(ppoint);
		}*/
		if (pdisplayable->pmesh!=NULL){
			std::unordered_set<std::shared_ptr<Point3D<M, E>>> ppoints=pdisplayable->pmesh->getPoints();
			for (std::shared_ptr<Point3D<M, E>> ppoint : ppoints){
				success=success & render(ppoint);
			}
		}
	}
	return success;
}

template<typename M, typename E> bool Display1<M, E>::render(const std::shared_ptr<Point3D<M, E>> ppoint) const {
	bool success=false;

	if (this->ppoint!=NULL){
		Point3D<M, E> d_point=*ppoint-*(this->ppoint);
		//printf("\nRendering 4\n");
		//ppoint->print(true);
		//m_ppoint->print(true);
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
			SN<M, E> centerx={(M)(sizex/2),(E)0};
			SN<M, E> centery={(M)(sizey/2),(E)0};

			if (prenderer!=NULL){
				switch (m_display){
					case 1://(x,y) plane
						//printf("\nx=%i\n", (int)(d_point.x*(M)m_scale + centerx).to_m_type());
						SDL_RenderDrawPoint(prenderer.get(), (int)(d_point.x*(M)m_scale + centerx).to_m_type(), (int)(d_point.y*(M)m_scale + centery).to_m_type());
						break;
					case 2://(y,z) plane
						SDL_RenderDrawPoint(prenderer.get(), (int)(d_point.y*(M)m_scale + centerx).to_m_type(), (int)(d_point.z*(M)m_scale + centery).to_m_type());
						break;
					case 3://(x,z) plane
						SDL_RenderDrawPoint(prenderer.get(), (int)(d_point.x*(M)m_scale + centerx).to_m_type(), (int)(d_point.z*(M)m_scale + centery).to_m_type());
						break;
				}
			}
			success=true;
		}
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
