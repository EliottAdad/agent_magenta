/*
 * Sphere.h
 *
 *  Created on: 22 oct. 2024
 *      Author: esn
 */

#ifndef SPHERE_H_
#define SPHERE_H_

#include "Shape3D.h"
#include "../core/LSN.h"

/*
 * Sphere
 */
class Sphere: public Shape3D {
private:
	LSN m_r;

public:
	Sphere();
	virtual ~Sphere();
	Sphere(const Sphere &other);

	LSN getR() const;
	void setR(const LSN& r);
};

#endif /* SPHERE_H_ */
