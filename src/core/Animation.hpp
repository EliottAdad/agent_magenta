/*
 * Animation.hpp
 */


#ifndef ANIMATION_HPP_

#define ANIMATION_HPP_

#include <stdlib.h>


/**
 * #############
 *  Animation :)
 * #############
 * @brief
 * Link to a file. Cycles through 
 * the corresponding sprites in the image
 */
struct Animation {
    char* filename;						// Name of the file were to find the image.
    unsigned int w, h;					// Width and height of one frame in pixels
    unsigned int start_x, start_y;		// Positon of the top left corner of the first frame
    unsigned char nb_sprites;			// The number of different sprites contained by the AnimationGroup.
    //FILE* pfile;						// Pointer to the open file.
    unsigned char id;					// Id of the active sprite. Between [0, nb_sprites-1]
    //std::duration dt;					// Duration
    float duration;						// Duration of the animation in seconds
};


// Constructors/Destructors
/*Animation* new_animation();*/
Animation* new_animation(char* filename, float data[6]);
void free_animation(Animation* panimation);
Animation* copy_animation(Animation* panimation);

//Getters/Setters
char* get_filename(Animation* panimation);
void set_filename(Animation* panimation, char* filename);
unsigned char get_id(Animation* panimation);
void set_id(Animation* panimation, unsigned char id);
unsigned char get_nb_sprites(Animation* panimation);
void set_nb_sprites(Animation* panimation, unsigned char nb_sprites);
float get_duration(Animation* panimation);
void set_duration(Animation* panimation, float duration);
unsigned int get_width(Animation* panimation);
void set_width(Animation* panimation, unsigned int width);
unsigned int get_height(Animation* panimation);
void set_height(Animation* panimation, unsigned int height);
unsigned int get_start_x(Animation* panimation);
void set_start_x(Animation* panimation, unsigned int start_x);
unsigned int get_start_y(Animation* panimation);
void set_start_y(Animation* panimation, unsigned int start_y);

// Methods
void next(Animation* panimation);
void previous(Animation* panimation);
void first(Animation* panimation);




// Constructors/Destructors
/**
 * @brief
 * Creates a new instance of Animation with 
 * default arguments
 */
/*Animation* new_animation(){
	Animation* panimation=(Animation*) malloc(sizeof(Animation));
	
	panimation->filename="";
	panimation->w=64;
	panimation->h=64;
	panimation->start_x=0;
	panimation->start_y=0;
	panimation->nb_sprites=0;
	panimation->id=0;
	panimation->duration=1;
	
	return panimation;
}*/

/**
 * @brief
 * Creates a new instance of Animation given
 * (in order) :
 * the width and heigth of a single frame, the 
 * start_x, start_y, the nb of sprites and 
 * duration of the animation.
 * Ex: ={16, 16, 0, 0, 4, 1} creates a 
 */
Animation* new_animation(char* filename, float data[6]){
	Animation* panimation=(Animation*) malloc(sizeof(Animation));
	
	panimation->filename=filename;
	panimation->w=(unsigned int)data[0];
	panimation->h=(unsigned int)data[1];
	panimation->start_x=(unsigned int)data[2];
	panimation->start_y=(unsigned int)data[3];
	panimation->nb_sprites=(unsigned char)data[4];
	panimation->id=0;
	panimation->duration=data[5];
	
	return panimation;
}

/**
 * l
 */
void free_animation(Animation* panimation){
	free(panimation);
}

/**
 * Creates a copy from another Animation
 */
Animation* copy_animation(Animation* panimation){
	float info[6]={panimation->w, panimation->h, panimation->start_x, panimation->start_y, panimation->nb_sprites, panimation->duration};
	return new_animation(panimation->filename, info);
}


//Getters/Setters
char* get_filename(Animation* panimation){
	return panimation->filename;
}

void set_filename(Animation* panimation, char* filename){
	panimation->filename=filename;
}

unsigned char get_id(Animation* panimation){
	return panimation->id;
}

void set_id(Animation* panimation, unsigned char id){
	panimation->id=id%panimation->nb_sprites;
}

unsigned char get_nb_sprites(Animation* panimation){
	return panimation->nb_sprites;
}

void set_nb_sprites(Animation* panimation, unsigned char nb_sprites){
	panimation->nb_sprites=nb_sprites;
}

float get_duration(Animation* panimation){
	return panimation->duration;
}

void set_duration(Animation* panimation, float duration){
	panimation->duration=duration;
}

unsigned int get_width(Animation* panimation){
	return panimation->w;
}

void set_width(Animation* panimation, unsigned int width){
	panimation->w=width;
}

unsigned int get_height(Animation* panimation){
	return panimation->h;
}

void set_height(Animation* panimation, unsigned int height){
	panimation->h=height;
}

unsigned int get_start_x(Animation* panimation){
	return panimation->start_x;
}

void set_start_x(Animation* panimation, unsigned int start_x){
	panimation->start_x=start_x;
}

unsigned int get_start_y(Animation* panimation){
	return panimation->start_y;
}

void set_start_y(Animation* panimation, unsigned int start_y){
	panimation->start_y=start_y;
}


// Methods
/**
 * @brief
 * Switches to the next frame.
 */
void next(Animation* panimation){
	if (panimation!=NULL){
		panimation->id=(panimation->id+1)%panimation->nb_sprites;
	}
}

/**
 * @brief
 * Switches to the previous frame.
 */
void previous(Animation* panimation){
	if (panimation!=NULL){
		panimation->id=(panimation->id-1)%panimation->nb_sprites;
	}
}

/**
 * @brief
 * Reset to the first frame.
 */
void first(Animation* panimation){
	if (panimation!=NULL){
		panimation->id=0;
	}
}

/**
 * @brief
 * Reset to the first frame.
 */
void last(Animation* panimation){
	if (panimation!=NULL){
		panimation->id=panimation->nb_sprites-1;
	}
}

/**
 * @brief
 * Point p: where to be rendered.
 * WINDOW pwindow: window to be rendered.
 */
/*void render_to_window(Animation* panimation, Point p, WINDOW* pwindow){
	if (panimation!=NULL){
		panimation->id=0;
	}
}*/



#endif /* ANIMATION_HPP_ */
