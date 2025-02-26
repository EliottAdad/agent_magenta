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
	virtual void setT(const float& dt){TimeSensitive::setT(dt);}
	virtual void apply();
};


// Methods




// Constructors/Destructors
/**
 * @brief
 * Creates a new instance of Animation with 
 * default arguments
 */
Animation::Animation() {
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
Animation::Animation(char* filename, float data[6]) {
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
Animation::~Animation() {
	;
}

/**
 * Creates a copy from another Animation
 */
Animation::Animation(const Animation& animation) {
	this->filename=filename;
	this->w=animation.w;
	this->h=animation.h;
	this->start_x=animation.start_x;
	this->start_y=animation.start_y;
	this->nb_sprites=animation.nb_sprites;
	this->id=0;
	this->duration=animation.duration;
}


//Getters/Setters
char* get_filename(Animation* panimation) {
	return panimation->filename;
}

void set_filename(Animation* panimation, char* filename) {
	panimation->filename=filename;
}

unsigned char get_id(Animation* panimation) {
	return panimation->id;
}

void set_id(Animation* panimation, unsigned char id) {
	panimation->id=id%panimation->nb_sprites;
}

unsigned char get_nb_sprites(Animation* panimation) {
	return panimation->nb_sprites;
}

void set_nb_sprites(Animation* panimation, unsigned char nb_sprites) {
	panimation->nb_sprites=nb_sprites;
}

float get_duration(Animation* panimation) {
	return panimation->duration;
}

void set_duration(Animation* panimation, float duration) {
	panimation->duration=duration;
}

unsigned int get_width(Animation* panimation) {
	return panimation->w;
}

void set_width(Animation* panimation, unsigned int width) {
	panimation->w=width;
}

unsigned int get_height(Animation* panimation) {
	return panimation->h;
}

void set_height(Animation* panimation, unsigned int height) {
	panimation->h=height;
}

unsigned int get_start_x(Animation* panimation) {
	return panimation->start_x;
}

void set_start_x(Animation* panimation, unsigned int start_x){
	panimation->start_x=start_x;
}

unsigned int get_start_y(Animation* panimation) {
	return panimation->start_y;
}

void set_start_y(Animation* panimation, unsigned int start_y) {
	panimation->start_y=start_y;
}


// Methods
/**
 * @brief
 * Switches to the next frame.
 */
void next(Animation* panimation) {
	if (panimation!=NULL){
		panimation->id=(panimation->id+1)%panimation->nb_sprites;
	}
}

/**
 * @brief
 * Switches to the previous frame.
 */
void previous(Animation* panimation) {
	if (panimation!=NULL){
		panimation->id=(panimation->id-1)%panimation->nb_sprites;
	}
}

/**
 * @brief
 * Reset to the first frame.
 */
void first(Animation* panimation) {
	if (panimation!=NULL){
		panimation->id=0;
	}
}

/**
 * @brief
 * Reset to the first frame.
 */
void last(Animation* panimation) {
	if (panimation!=NULL){
		panimation->id=panimation->nb_sprites-1;
	}
}




/*
 * From TimeSensitive
 */



#endif /* ANIMATION_HPP_ */
