/*
 * Mesh3D.hpp
 *
 *  Created on: 26 sept. 2024
 *      Author: esn
 */

#ifndef MESH3D_HPP_

#define MESH3D_HPP_

#include <memory>
#include <unordered_set>

#include "../core/Line3D.hpp"
#include "../core/Point3D.hpp"
#include "Triangle3D.hpp"
#include "Shape3D.hpp"
//#include "../utilities/Printable.hpp"

/*
 * ###########
 *  Mesh<T> :)
 * ###########
 * Abstract class
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

template<typename T> inline Mesh3D<T>::Mesh3D() {
	;
}

template<typename T> inline Mesh3D<T>::~Mesh3D() {
	;
}

template<typename T> inline Mesh3D<T>::Mesh3D(const Mesh3D& mesh) {
	;
}


template<typename T> inline void Mesh3D<T>::addTriangle(std::shared_ptr<Triangle3D<T>> ptriangle){
	ptriangles.insert(ptriangle);
}

#endif /* MESH3D_HPP_ */
