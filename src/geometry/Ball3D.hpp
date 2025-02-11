/*
 * Ball3D.hpp
 *
 *  Created on: 22 oct. 2024
 *      Author: esn
 */

#ifndef BALL3D_HPP_

#define BALL3D_HPP_

#include "../core/SN.hpp"
#include "Particle3D.hpp"

/*
 * #############
 *  Ball3D<T> :)
 * #############
 * Particle3D with radius (useless)
 */
template<typename T> class Ball3D : public Particle3D<T> {
public:
	T r;

	Ball3D();
	virtual ~Ball3D();
	Ball3D(const Ball3D<T>& ball);

	virtual std::string to_string(const bool& spread=false, const bool& full_info=false, const unsigned char& indent=0) const;
	virtual void print(const bool& spread=false, const bool& full_info=false, const unsigned char& indent=0) const;

};

template<typename T> Ball3D<T>::Ball3D() {
	r=(T)1;
}

template<typename T> Ball3D<T>::~Ball3D() {
	;
}

template<typename T> Ball3D<T>::Ball3D(const Ball3D<T>& ball) {
	r=ball.r;
}


template<typename T> std::string Ball3D<T>::to_string(const bool& spread, const bool& full_info, const unsigned char& indent) const {
	std::string mes=((spread)?"\n" : "");

	if (full_info){
		mes+="BALL3D[";
		std::stringstream ss;
		ss << this;
		mes+=ss.str();
		mes+="]:";
		mes+=((spread)?"\n" : "");
	}
	return mes;
}

template<typename T> void Ball3D<T>::print(const bool& spread, const bool& full_info, const unsigned char& indent) const {
	printTabs(indent);
	std::cout << this->to_string(spread, full_info, indent);
}

#endif /* BALL3D_HPP_ */
