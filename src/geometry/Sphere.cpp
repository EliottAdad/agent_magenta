/*
 * Sphere.cpp
 *
 *  Created on: 22 oct. 2024
 *      Author: esn
 */

#include "Sphere.h"

Sphere::Sphere() {
	// TODO Auto-generated constructor stub

}

Sphere::~Sphere() {
	// TODO Auto-generated destructor stub
}

Sphere::Sphere(const Sphere &other) {
	// TODO Auto-generated constructor stub

}

LSN Sphere::getR() const {
	return m_r;
}

void Sphere::setR(const LSN& r) {
	m_r=r;
}
