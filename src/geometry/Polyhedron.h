/*
 * Polyhedron.h
 *
 *  Created on: 20 mai 2024
 *      Author: esn
 */

#ifndef POLYHEDRON_H_

#define POLYHEDRON_H_

#include <memory>
#include <unordered_set>

#include "Shape3D.h"
#include "Triangle3D.h"

/*
 * ####################
 *  Polyhedron<M, E> :)
 * ####################
 */
template<typename M, typename E> class Polyhedron : public Shape3D {
protected:
	std::unordered_set<std::shared_ptr<Triangle3D<M, E>>> m_ptriangles;

public:
	Polyhedron();
	virtual ~Polyhedron();
	Polyhedron(const Polyhedron<M, E> &other);

	std::unordered_set<std::shared_ptr<Triangle3D<M, E>>> getPFaces();
	void setFace(std::shared_ptr<Triangle3D<M, E>> pface);

	virtual std::string to_string(const bool& spread=false, const bool& full_info=false, const unsigned char& indent=0) const;
	virtual void print(const bool& spread=false, const bool& full_info=false, const unsigned char& indent=0) const;
};

#endif /* POLYHEDRON_H_ */
