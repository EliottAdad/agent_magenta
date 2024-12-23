/*
 * Mesh3D.h
 *
 *  Created on: 26 sept. 2024
 *      Author: esn
 */

#ifndef MESH3D_H_

#define MESH3D_H_

#include <memory>
#include <unordered_set>

#include "../core/Point3D.h"
#include "../core/Line3D.h"
#include "Triangle3D.h"
#include "../utilities/Printable.h"

/*
 * ##############
 *  Mesh<M, E> :)
 * ##############
 * A mesh is a set of triangles.
 */
template<typename M, typename E> class Mesh3D: public Printable {
public:
	std::unordered_set<std::shared_ptr<Triangle3D<M, E>>> ptriangles;

	Mesh3D();
	virtual ~Mesh3D();
	Mesh3D(const Mesh3D& mesh);

	void addTriangle(std::shared_ptr<Triangle3D<M, E>> ptriangle);

	virtual std::unordered_set<std::shared_ptr<Point3D<M, E>>> getPoints() const;//To render the mesh
	virtual std::unordered_set<std::shared_ptr<Line3D<M, E>>> getLines() const;//To render the mesh
};

template<typename M, typename E> Mesh3D<M, E>::Mesh3D() {
	;
}

template<typename M, typename E> Mesh3D<M, E>::~Mesh3D() {
	;
}

template<typename M, typename E> Mesh3D<M, E>::Mesh3D(const Mesh3D& mesh) {
	;
}


template<typename M, typename E> void Mesh3D<M, E>::addTriangle(std::shared_ptr<Triangle3D<M, E>> ptriangle){
	ptriangles.insert(ptriangle);
}

template<typename M, typename E> std::unordered_set<std::shared_ptr<Point3D<M, E>>> Mesh3D<M, E>::getPoints() const {
	std::unordered_set<std::shared_ptr<Point3D<M, E>>> ppoints;
	return ppoints;
}

template<typename M, typename E> std::unordered_set<std::shared_ptr<Line3D<M, E>>> Mesh3D<M, E>::getLines() const {
	std::unordered_set<std::shared_ptr<Line3D<M, E>>> plines;
	return plines;
}

#endif /* MESH3D_H_ */
