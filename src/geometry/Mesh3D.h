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

#include "../core/Line3D.h"
#include "../core/Point3D.h"
#include "Triangle3D.h"
#include "Shape3D.h"
#include "../utilities/Printable.h"

/*
 * ###########
 *  Mesh<T> :)
 * ###########
 * A mesh is a set of triangles.
 */
template<typename T> class Mesh3D : public Shape3D<T> {
public:
	std::unordered_set<std::shared_ptr<Triangle3D<T>>> ptriangles;

	Mesh3D();
	virtual ~Mesh3D();
	Mesh3D(const Mesh3D& mesh);

	void addTriangle(std::shared_ptr<Triangle3D<T>> ptriangle);

	virtual std::unordered_set<std::shared_ptr<Point3D<T>>> getPoints() const;//To render the shape
	virtual std::unordered_set<std::shared_ptr<Line3D<T>>> getLines() const;//To render the shape

};

template<typename T> Mesh3D<T>::Mesh3D() {
	;
}

template<typename T> Mesh3D<T>::~Mesh3D() {
	;
}

template<typename T> Mesh3D<T>::Mesh3D(const Mesh3D& mesh) {
	;
}


template<typename T> void Mesh3D<T>::addTriangle(std::shared_ptr<Triangle3D<T>> ptriangle){
	ptriangles.insert(ptriangle);
}

#endif /* MESH3D_H_ */
