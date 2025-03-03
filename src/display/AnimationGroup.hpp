/*
 * AnimationGroup.hpp
 */


#ifndef ANIMATIONGROUP_HPP_

#define ANIMATIONGROUP_HPP_


#include <string.h>

#include "Animation.hpp"

#define MAX_NB_ANIMATIONS 10			// Max nb of animations for an animation group


/**
 * ##################
 *  AnimationGroup :)
 * ##################
 * struct AnimationGroup
 * @brief
 * Link to a file. Cycles through the 
 * corresponding sprites in the image.
 * Accept multiple animation with different 
 * durations.
 * Animations are supposed to be stacked on 
 * top of each other in the file provided.
 */
class AnimationGroup {
protected:
    unsigned char id_active;
public:
    char* filename;								// Name of the file where to find the image.
    std::vector<std::shared_ptr<Animation>> panimations;
    unsigned char nb_animations;
	
	AnimationGroup();
	AnimationGroup(char* filename, float data[][6], unsigned char nb_animations);
	~AnimationGroup();
	AnimationGroup(const AnimationGroup& animation_group);
	
	unsigned char getIdActive();
	void setIdActive(unsigned char id_active);
	
	void next();
	void previous(AnimationGroup* panimation_group);
	
	// From TimeSensitive
	virtual float getT() const = 0;
	virtual void setT(const float& dt) = 0;			//Used to prepare the logic behind the scenes
	virtual void apply() = 0;
};



/*
 * Constructors/Destructors
 */
 
/**
 * Constructor0
 */
inline AnimationGroup::AnimationGroup(){
	AnimationGroup* panimation_group=(AnimationGroup*)malloc(sizeof(AnimationGroup));
	panimation_group->filename="";
	panimation_group->sz_panimations=0;
	return panimation_group;
}

/**
 * {{w, h, nb_sprites, duration, offsetx, offsety}, ...}
 * offsetx is an offset in reference to the left border of the image
 * offsety is an offset in reference to the precedent line
 * Exemple: {{16, 16, 4, 1, 0, 0}} is a single animation AnimationGroup with no offset
 */
inline AnimationGroup::AnimationGroup(char* filename, float data[][6], unsigned char nb_animations){
	AnimationGroup* panimation_group=(AnimationGroup*)malloc(sizeof(AnimationGroup));
	
	panimation_group->filename=filename;
	Animation** panimations=calloc(sizeof(Animation*), nb_animations);// Reserves the memory space for Animation*
	unsigned int y=0;
	for (unsigned char i(0) ; i<nb_animations ; i++){
		y+=data[i][5];		// Adding the y-offset
		float data_an[6]={data[i][4], (float)y, data[i][0], data[i][1], data[i][2], data[i][3]};
		panimations[i]=new_animation(filename, data_an);
		y+=data[i][1];		// Adding the image height for the next animation
	}
    panimation_group->nb_animations=nb_animations;
    panimation_group->id_active=0;
	
	return panimation_group;
}

inline AnimationGroup::~AnimationGroup(){
	for (int i(0) ; i<panimation_group->nb_animations ; i++){
		free(panimations[i]);
	}
	free(panimation_group);
}





inline unsigned char AnimationGroup::getIdActive(){
	return panimation_group->id_active;
}

inline void AnimationGroup::setIdActive(unsigned char id_active){
	if (id_active<this->nb_animations){
		this->id_active=id_active;
	}else{
		this->id_active=nb_animations;
	}
}


// Methods
/**
 * @brief
 * Switch to the next frame
 */
inline void AnimationGroup::next() {
	panimation_group->panimations[panimation_group->id_active]->next();
}

/**
 * @brief
 * Switch to the previous frame
 */
inline void AnimationGroup::previous(){
	panimation_group->panimations[panimation_group->id_active]->previous();
}


#endif /* ANIMATIONGROUP_HPP_ */
