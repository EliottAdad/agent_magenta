/*
 * Mesh3D.h
 *
 *  Created on: 26 sept. 2024
 *      Author: esn
 */

#ifndef MESH3D_H_
#define MESH3D_H_

#include <unordered_set>

#include "Triangle3D.h"


class Mesh3D {
private:
	//std::unordered_set<std::pair<Point3D*, bool>> m_ppoints;

	//std::unordered_set<std::pair<Triangle3D*, bool>> m_ptriangles;
public:
	Mesh3D();
	virtual ~Mesh3D();
	//Mesh3D(const Mesh3D &other);

	//public ;
};

#endif /* MESH3D_H_ */
