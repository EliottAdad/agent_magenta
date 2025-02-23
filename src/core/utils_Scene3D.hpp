/*
 * utils_Scene3D.hpp
 *
 *  Created on: 22 decembre 2024
 *      Author: esn
 */

#ifndef UTILS_SCENE3D_HPP_

#define UTILS_SCENE3D_HPP_

#include <memory>

#include "Scene3D.hpp"


template<typename U, typename T> std::string to_string(const Scene3D<T>& scene, const unsigned char& indent) {
	std::string mes="";
	
	mes+=to_stringTabs(indent);
	mes+="SCENE3D[";
	std::stringstream ss;
	ss << &scene;
	mes+=ss.str();
	mes+="]:";
	
	for (std::shared_ptr<Displayable3D<T>> pdisplayable : scene.pdisplayables){
		mes+=to_string(*pdisplayable);//:)
	}

	return mes;
}

template<typename U, typename T> void print(const Scene3D<T>& scene) {
	std::cout << to_string(scene);
}




#endif /* FUNCTIONS_SCENE3D_HPP_ */
