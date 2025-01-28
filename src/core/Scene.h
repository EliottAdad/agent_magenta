//:)
#ifndef SCENE_H

#define SCENE_H

#include <memory>
#include <unordered_set>

#include "../display/Displayable.h"


/*
 * ############
 *  Scene<T> :)
 * ############
 * Scene contains Displayables
 */
template<typename T> class Scene : public Printable {
public:
	Scene();//:)
	//Scene(std::string name, std::vector<SDL_Color*> pcolors={});//:)
	Scene(const Scene& scene);//:/
	~Scene();//:)

	std::unordered_set<std::shared_ptr<Displayable<T>>> getPDisplayables() const;//:)
	//void addDisplayables(std::vector<Displayable*> pdisplayables);//:)
	bool addPDisplayable(std::shared_ptr<Displayable<T>> pdisplayable);//:)

private:
	std::unordered_set<std::shared_ptr<Displayable<T>>> m_pdisplayables;//:)
};



template<typename T> Scene<T>::Scene(){//:)
	;
}

template<typename T> Scene<T>::Scene(const Scene& scene){//:/
	;
}

template<typename T> Scene<T>::~Scene(){//:)
	;
}

template<typename T> std::unordered_set<std::shared_ptr<Displayable<T>>> Scene<T>::getPDisplayables() const {//:)
	return m_pdisplayables;
}

template<typename T> bool Scene<T>::addPDisplayable(std::shared_ptr<Displayable<T>> pdisplayable){//:)
	bool success=false;
	if (pdisplayable!=NULL){
		success=m_pdisplayables.insert(pdisplayable).second;
	}
	return success;
}




#endif
