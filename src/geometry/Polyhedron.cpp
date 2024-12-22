/*
 * Polyhedron.cpp
 *
 *  Created on: 20 mai 2024
 *      Author: esn
 */

#include "Polyhedron.h"

template<typename M, typename E> Polyhedron<M, E>::Polyhedron() {
	// TODO Auto-generated constructor stub

}

template<typename M, typename E> Polyhedron<M, E>::~Polyhedron() {
	// TODO Auto-generated destructor stub
}

template<typename M, typename E> Polyhedron<M, E>::Polyhedron(const Polyhedron<M, E> &other) {
	// TODO Auto-generated constructor stub

}


template<typename M, typename E> std::string Polyhedron<M, E>::to_string(const bool& spread, const bool& full_info, const unsigned char& indent) const {
	std::string mes=((spread)?"\n" : "");

	if (full_info){
		mes+="POLYHEDRON ():";
		mes+=((spread)?"\n" : "");
	}
	/*for (Particle3D* ppart : m_poctree->getPElements()){
		mes+="	- ( ";
		mes+=ppart->to_string(false, false);
		mes+=" )";
		mes+="\n";
	}*/
	return mes;
}

template<typename M, typename E> void Polyhedron<M, E>::print(const bool& spread, const bool& full_info, const unsigned char& indent) const {
	printTabs(indent);
	std::cout << this->to_string(spread, full_info, indent);
}


