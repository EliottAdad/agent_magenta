/*
 * Displayable.h
 *
 *  Created on: 8 nov. 2024
 *      Author: esn
 */

#ifndef DISPLAYABLE_H_

#define DISPLAYABLE_H_

#include <memory>
#include <SDL2/SDL.h>

#include "../geometry/Mesh3D.h"
#include "../utilities/Printable.h"

/*
 * ###############
 *  Displayable :)
 * ###############
 * Stores the color, and a mesh to use when rendering
 * If mesh=NULL draws a point, if SDL_Color=NULL draws in white
 */
template<typename M, typename E> struct Displayable : public Printable {
protected:
	//Mesh3D* pmesh;			// Pointer to the mesh to be drawn

	//bool m_delc;

public:
	std::shared_ptr<SDL_Color> pcolor;		// Drawing color

	Displayable();
	virtual ~Displayable();
	Displayable(const Displayable &other);

	virtual SN<M, E> getX() const;				//Gets the coords (changer plus tard en getPoints
	virtual SN<M, E> getY() const;
	virtual SN<M, E> getZ() const;
	//virtual SDL_Color getColor() const;
	//virtual SDL_Color* getPColor() const;
	//virtual void setColor(SDL_Color& color, const bool& delc=true);
	//virtual void setPColor(SDL_Color* pcolor, const bool& delc=false);
	//render();

	//virtual Image getSticker() const;

	virtual std::string to_string(const bool& spread=false, const bool& full_info=false, const unsigned char& indent=0) const;// :)
	virtual void print(const bool& spread=false, const bool& full_info=false, const unsigned char& indent=0) const;// :)
};


template<typename M, typename E> Displayable<M, E>::Displayable() {
	pcolor=NULL;//std::make_shared<SDL_Color>(255, 255, 255, 255);		// Will be interprated as white by the cameras and displays
	//m_pmesh=NULL;			//
	//m_delc=true;
}

template<typename M, typename E> Displayable<M, E>::~Displayable() {
	;
}

template<typename M, typename E> Displayable<M, E>::Displayable(const Displayable &other) {
	pcolor=other.pcolor;
}



/*void Displayable::setColor(int r, int b, int g, int a){
	m_pcolor->r=r;
	m_pcolor->g=g;
	m_pcolor->b=b;
	m_pcolor->a=a;
}*/


template<typename M, typename E> SN<M, E> Displayable<M, E>::getX() const {
	return {0.,0};
}

template<typename M, typename E> SN<M, E> Displayable<M, E>::getY() const {
	return {0.,0};
}

template<typename M, typename E> SN<M, E> Displayable<M, E>::getZ() const {
	return {0.,0};
}

/*template<typename M, typename E> SDL_Color Displayable<M, E>::getColor() const {//Yes because it cannot be null
	return *pcolor;
}

template<typename M, typename E> SDL_Color* Displayable<M, E>::getPColor() const {
	SDL_Color* pcolor=NULL;
	if (!m_delc){
		pcolor=m_pcolor;
	}
	return pcolor;
}

template<typename M, typename E> void Displayable<M, E>::setColor(SDL_Color& color, const bool& delc) {
	if (m_delc){//Get rid of the last color
		delete m_pcolor;
	}
	if (delc){//Insert the new color
		m_pcolor=new SDL_Color(color);
	}else{
		m_pcolor=&color;
	}
	m_delc=delc;
}

template<typename M, typename E> void Displayable<M, E>::setPColor(SDL_Color* pcolor, const bool& delc) {
	if (m_delc){//Get rid of the last color
		delete m_pcolor;
	}
	if (delc){//Insert the new color
		m_pcolor=new SDL_Color(*pcolor);
	}else{
		m_pcolor=pcolor;
	}
	m_delc=delc;
}*/


template<typename M, typename E> std::string Displayable<M, E>::to_string(const bool& spread, const bool& full_info, const unsigned char& indent) const {// :)
	std::string mes=(spread)?"\n":"";

	mes+="DISPLAYABLE";

	return mes;
}

template<typename M, typename E> void Displayable<M, E>::print(const bool& spread, const bool& full_info, const unsigned char& indent) const {// :)
	printTabs(indent);
	std::cout << this->to_string(spread, full_info, indent);
}


#endif /* DISPLAYABLE_H_ */
