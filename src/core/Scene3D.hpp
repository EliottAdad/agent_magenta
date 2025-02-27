//:)
#ifndef SCENE3D_H

#define SCENE3D_H

#include <memory>
#include <unordered_set>

#include "Displayable3D.hpp"



/*
 * ##############
 *  Scene3D<T> :)
 * ##############
 * @brief
 * Scene3D contains Displayables
 * Containent une liste de tt ce qui va etre display
 */
template<typename T> class Scene3D {
public:
	std::unordered_set<std::shared_ptr<Displayable3D<T>>> pdisplayables;//:)
	
	Scene3D();//:)
	Scene3D(const Scene3D<T>& scene);//:/
	~Scene3D();//:)

	//std::unordered_set<std::shared_ptr<Displayable3D<T>>> getPDisplayables() const;//:)
	bool add(std::shared_ptr<Displayable3D<T>> pdisplayable);//:)
	bool remove(std::shared_ptr<Displayable3D<T>> pdisplayable);//:)
	unsigned int getNbElements() const;//:)
};



template<typename T> inline Scene3D<T>::Scene3D(){//:)
	;
}

template<typename T> inline Scene3D<T>::Scene3D(const Scene3D& scene){//:/
	;
}

template<typename T> inline Scene3D<T>::~Scene3D(){//:)
	;
}




/*template<typename T> std::unordered_set<std::shared_ptr<Displayable3D<T>>> Scene3D<T>::getPDisplayables() const {//:)
	return m_pdisplayables;
}*/

template<typename T> inline bool Scene3D<T>::add(std::shared_ptr<Displayable3D<T>> pdisplayable) {//:)
	bool success=false;
	if (pdisplayable!=NULL){
		success=pdisplayables.insert(pdisplayable).second;
	}
	return success;
}

template<typename T> inline bool Scene3D<T>::remove(std::shared_ptr<Displayable3D<T>> pdisplayable) {//:)
	bool success=false;
	for (std::shared_ptr<Displayable3D<T>> pelement : pdisplayables){
		if (pelement==pdisplayable){
			pdisplayables.remove(pelement);
			success=true;
			break;
		}
	}
	return success;
}

template<typename T> inline unsigned int Scene3D<T>::getNbElements() const {//:)
	return pdisplayables.size();
}





#endif /* SCENE_HPP_ */
