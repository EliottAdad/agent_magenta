/*
 * Polyhedron.hpp
 *
 *  Created on: 20 mai 2024
 *      Author: esn
 */

#ifndef POLYHEDRON_HPP_

#define POLYHEDRON_HPP_

#include <memory>
#include <unordered_set>

#include "Shape3D.hpp"
#include "Triangle3D.hpp"

/*
 * #################
 *  Polyhedron<T> :)
 * #################
 */
template<typename T> class Polyhedron : public Shape3D<T> {
protected:
	std::unordered_set<std::shared_ptr<Triangle3D<T>>> m_ptriangles;

public:
	Polyhedron();
	virtual ~Polyhedron();
	Polyhedron(const Polyhedron<T> &other);

	std::unordered_set<std::shared_ptr<Triangle3D<T>>> getPFaces();
	void setFace(std::shared_ptr<Triangle3D<T>> pface);
};

template<typename T> inline Polyhedron<T>::Polyhedron() {
	// TODO Auto-generated constructor stub

}

template<typename T> inline Polyhedron<T>::~Polyhedron() {
	// TODO Auto-generated destructor stub
}

template<typename T> inline Polyhedron<T>::Polyhedron(const Polyhedron<T> &other) {
	// TODO Auto-generated constructor stub

}



#endif /* POLYHEDRON_HPP_ */
