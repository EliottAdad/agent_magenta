/*
 * Displayable.cpp
 *
 *  Created on: 8 nov. 2024
 *      Author: esn
 */

//#include "Displayable.h"
#ifdef D

#define E

template<typename M, typename E> Displayable<M, E>::Displayable() {
	pcolor=NULL;		// Will be interprated as white by the cameras and displays
	pmesh=NULL;			//
}

template<typename M, typename E> Displayable<M, E>::~Displayable() {
	pcolor=NULL;		// Will be interprated as white by the cameras
	pmesh=NULL;			//
}

template<typename M, typename E> Displayable<M, E>::Displayable(const Displayable &other) {
	pcolor=other.pcolor;		// Will be interprated as white by the cameras
	pmesh=other.pmesh;			//
}


/*SDL_Color* Displayable::getPColor(){
	return m_pcolor;
}*/

/*void Displayable::setColor(int r, int b, int g, int a){
	m_pcolor->r=r;
	m_pcolor->g=g;
	m_pcolor->b=b;
	m_pcolor->a=a;
}*/


template<typename M, typename E> SN<float, char> Displayable<M, E>::getX() const {
	return {0., 0};
}

template<typename M, typename E> SN<float, char> Displayable<M, E>::getY() const {
	return {0., 0};
}

template<typename M, typename E> SN<float, char> Displayable<M, E>::getZ() const {
	return {0., 0};
}


template<typename M, typename E> std::string Displayable<M, E>::to_string(const bool& spread, const bool& full_info, const unsigned char& indent) const {// :)
	std::string mes=(spread)?"\n":"";

	mes+="DISPLAYABLE";

	return mes;
}

template<typename M, typename E> void Displayable<M, E>::print(const bool& spread, const bool& full_info, const unsigned char& indent) const {// :)
	printTabs(indent);
	std::cout << this->to_string(spread, full_info, indent);
}

#endif

