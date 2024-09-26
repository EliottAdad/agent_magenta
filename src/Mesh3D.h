/*
 * Mesh3D.h
 *
 *  Created on: 26 sept. 2024
 *      Author: esn
 */

#ifndef MESH3D_H_
#define MESH3D_H_

#include <unordered_set>
#include "Triangle.h"


class Mesh3D {
private:
	std::unordered_set<Triangle*> m_ptriangles;
public:
	Mesh3D();
	virtual ~Mesh3D();
	//Mesh3D(const Mesh3D &other);

};

#endif /* MESH3D_H_ */
