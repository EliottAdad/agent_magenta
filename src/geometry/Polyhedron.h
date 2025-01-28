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
 *  Polyhedron<T> :)
 * ####################
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

	virtual std::string to_string(const bool& spread=false, const bool& full_info=false, const unsigned char& indent=0) const;
	virtual void print(const bool& spread=false, const bool& full_info=false, const unsigned char& indent=0) const;
};

template<typename T> Polyhedron<T>::Polyhedron() {
	// TODO Auto-generated constructor stub

}

template<typename T> Polyhedron<T>::~Polyhedron() {
	// TODO Auto-generated destructor stub
}

template<typename T> Polyhedron<T>::Polyhedron(const Polyhedron<T> &other) {
	// TODO Auto-generated constructor stub

}


template<typename T> std::string Polyhedron<T>::to_string(const bool& spread, const bool& full_info, const unsigned char& indent) const {
	std::string mes=((spread)?"\n" : "");

	if (full_info){
		mes+="POLYHEDRON ():";
		mes+=((spread)?"\n" : "");
	}
	/*for (Particle3D* ppart : m_poctree->getPElements()){
		mes+="	- ( ";
		mes+=ppart->to_string(false, false);
		mes+=" )";
		mes+="\n";
	}*/
	return mes;
}

template<typename T> void Polyhedron<T>::print(const bool& spread, const bool& full_info, const unsigned char& indent) const {
	printTabs(indent);
	std::cout << this->to_string(spread, full_info, indent);
}


#endif /* POLYHEDRON_H_ */
