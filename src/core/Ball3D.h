/*
 * Ball3D.h
 *
 *  Created on: 22 oct. 2024
 *      Author: esn
 */

#ifndef BALL3D_H_

#define BALL3D_H_

#include "../core/SN.h"
#include "Particle3D.h"

/*
 * ################
 *  Ball3D<M, E> :)
 * ################
 * Particle3D with radius.
 */
template<typename M, typename E> class Ball3D : public Particle3D<M, E> {
public:
	SN<M, E> r;

	Ball3D();
	virtual ~Ball3D();
	Ball3D(const Ball3D<M, E>& ball);

	virtual std::string to_string(const bool& spread=false, const bool& full_info=false, const unsigned char& indent=0) const;
	virtual void print(const bool& spread=false, const bool& full_info=false, const unsigned char& indent=0) const;

};

template<typename M, typename E> Ball3D<M, E>::Ball3D() {
	r=SN<M, E>{1,0};
}

template<typename M, typename E> Ball3D<M, E>::~Ball3D() {
	;
}

template<typename M, typename E> Ball3D<M, E>::Ball3D(const Ball3D<M, E>& ball) {
	r=ball.r;
}


template<typename M, typename E> std::string Ball3D<M, E>::to_string(const bool& spread, const bool& full_info, const unsigned char& indent) const {
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

template<typename M, typename E> void Ball3D<M, E>::print(const bool& spread, const bool& full_info, const unsigned char& indent) const {
	printTabs(indent);
	std::cout << this->to_string(spread, full_info, indent);
}

#endif /* BALL3D_H_ */
