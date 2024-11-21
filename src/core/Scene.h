//:)
#ifndef SCENE_H

#define SCENE_H


#include <set>
#include "../display/Displayable.h"


/*
 * #########
 *  Scene :)
 * #########
 * Scene contains Displayables
 */
class Scene{
public:
	Scene();//:)
	//Scene(std::string name, std::vector<SDL_Color*> pcolors={});//:)
	Scene(const Scene& scene);//:/
	~Scene();//:)

	std::set<Displayable*> getPDisplayables();//:)
	//void addDisplayables(std::vector<Displayable*> pdisplayables);//:)
	void addPDisplayable(Displayable* pdisplayable);//:)

private:
	std::set<Displayable*> m_pdisplayables;//:)
};




#endif
