//:)
#ifndef SCENE_H

#define SCENE_H


#include <unordered_set>
#include "../display/Displayable.h"


/*
 * #########
 *  Scene :)
 * #########
 * Scene contains Displayables
 */
template<typename M, typename E> class Scene : public Printable {
public:
	Scene();//:)
	//Scene(std::string name, std::vector<SDL_Color*> pcolors={});//:)
	Scene(const Scene& scene);//:/
	~Scene();//:)

	std::unordered_set<Displayable<M, E>*> getPDisplayables() const;//:)
	//void addDisplayables(std::vector<Displayable*> pdisplayables);//:)
	bool addPDisplayable(Displayable<M, E>* pdisplayable);//:)

private:
	std::unordered_set<Displayable<M, E>*> m_pdisplayables;//:)
};



template<typename M, typename E> Scene<M, E>::Scene(){//:)
	;
}

template<typename M, typename E> Scene<M, E>::Scene(const Scene& scene){//:/
	;
}

template<typename M, typename E> Scene<M, E>::~Scene(){//:)
	;
}

template<typename M, typename E> std::unordered_set<Displayable<M, E>*> Scene<M, E>::getPDisplayables() const {//:)
	return m_pdisplayables;
}

template<typename M, typename E> bool Scene<M, E>::addPDisplayable(Displayable<M, E>* pdisplayable){//:)
	//m_pdisplayables.insert(pdisplayable);

	bool success=false;
	if (pdisplayable!=NULL){
		success=m_pdisplayables.insert(pdisplayable).second;
	}
	return success;
}




#endif
