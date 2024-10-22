/*
 * Polyhedron.h
 *
 *  Created on: 20 mai 2024
 *      Author: esn
 */

#ifndef POLYHEDRON_H_
#define POLYHEDRON_H_

#include <unordered_set>

#include "Shape3D.h"
#include "Triangle3D.h"

/*
 * ##############
 *  Polyhedron :)
 * ##############
 */
class Polyhedron : public Shape3D {
protected:
	std::unordered_set<Triangle3D*> m_ptriangs;
	//std::unordered_set<Point3D*> m_ppoints;

public:
	Polyhedron();
	virtual ~Polyhedron();
	Polyhedron(const Polyhedron &other);

	std::unordered_set<Triangle3D*> getPFaces();
	void setFace(Triangle3D* pface);

	virtual std::string to_string(const bool& spread=false, const bool& full_info=false, const unsigned int& indent=0) const;
	virtual void print(const bool& spread=false, const bool& full_info=false, const unsigned int& indent=0) const;
};

#endif /* POLYHEDRON_H_ */
