/*
 * Animation.hpp
 */


#ifndef ANIMATION_HPP_

#define ANIMATION_HPP_

#include <string.h>

#include "../core/TimeSensitive.hpp"


/**
 * #############
 *  Animation :)
 * #############
 * @brief
 * Link to a file. Cycles through 
 * the corresponding sprites in the image
 */
struct Animation : public TimeSensitive {
    std::string filename;						// Name of the file were to find the image.
    unsigned int w, h;					// Width and height of one frame in pixels
    unsigned int start_x, start_y;		// Positon of the top left corner of the first frame
    unsigned char nb_sprites;			// The number of different sprites contained by the AnimationGroup.
    unsigned char id;					// Id of the active sprite. Between [0, nb_sprites-1]
    float duration;						// Duration of the animation in seconds
	
	// Constructors/Destructors
	Animation();
	Animation(char* filename, float data[6]);
	~Animation();
	Animation(const Animation& animation);

	void next();
	void previous();
	void first();
	void last();

	// From TimeSensitive
	virtual float getT() const {return TimeSensitive::getT();}
	virtual void setT(const float& dt);
	virtual void apply();
};


// Methods




// Constructors/Destructors
/**
 * @brief
 * Creates a new instance of Animation with 
 * default arguments
 */
inline Animation::Animation() : TimeSensitive() {
	this->filename="";
	this->w=64;
	this->h=64;
	this->start_x=0;
	this->start_y=0;
	this->nb_sprites=0;
	this->id=0;
	this->duration=1;
}

/**
 * @brief
 * Creates a new instance of Animation given
 * (in order) :
 * the width and heigth of a single frame, the 
 * start_x, start_y, the nb of sprites and 
 * duration of the animation.
 * Ex: ={16, 16, 0, 0, 4, 1} creates a 
 */
inline Animation::Animation(char* filename, float data[6]) : TimeSensitive() {
	this->filename=filename;
	this->w=(unsigned int)data[0];
	this->h=(unsigned int)data[1];
	this->start_x=(unsigned int)data[2];
	this->start_y=(unsigned int)data[3];
	this->nb_sprites=(unsigned char)data[4];
	this->id=0;
	this->duration=data[5];
}

/**
 * l
 */
inline Animation::~Animation() {
	;
}

/**
 * @brief
 * Creates a copy from another Animation
 */
inline Animation::Animation(const Animation& animation) : TimeSensitive(animation) {
	this->filename=filename;
	this->w=animation.w;
	this->h=animation.h;
	this->start_x=animation.start_x;
	this->start_y=animation.start_y;
	this->nb_sprites=animation.nb_sprites;
	this->id=0;
	this->duration=animation.duration;
}




// Methods
/**
 * @brief
 * Switches to the next frame.
 */
inline void Animation::next() {
	this->id=(this->id+1)%this->nb_sprites;
}

/**
 * @brief
 * Switches to the previous frame.
 */
inline void Animation::previous() {
	this->id=(this->id-1)%this->nb_sprites;
}

/**
 * @brief
 * Reset to the first frame.
 */
inline void Animation::first() {
	this->id=0;
}

/**
 * @brief
 * Reset to the first frame.
 */
inline void Animation::last() {
		this->id=this->nb_sprites-1;
}




/*
 * From TimeSensitive
 */

inline void Animation::setT(const float& dt) {
	this->m_dt+=dt;
}

inline void Animation::apply() {
	if (this->m_dt>=this->duration){
		this->next();
		this->m_dt=0;
	}
}


#endif /* ANIMATION_HPP_ */
