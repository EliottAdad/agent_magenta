/*
 * functions.hpp
 *
 *  Created on: 7 mai 2024
 *      Author: esn
 */

#ifndef FUNCTIONS_HPP_

#define FUNCTIONS_HPP_

#include <memory>
#include <string.h>
#include <vector>
#include <unordered_set>
#include <iostream>
#include <stdio.h>
#include <SDL2/SDL.h>

#include "macros.hpp"



template<typename T> bool equal(const T& nb1, const T& nb2);

std::string to_stringTabs(const unsigned char& nb);
void printTabs(const unsigned char& nb);





int roundUpToMultipleOfEight(int v);
void drawCircle(SDL_Renderer* renderer, SDL_Point center, int radius);
std::vector<SDL_Point> pixelizeCircle(SDL_Point center, int radius);




/*
 * Functions
 */

/**
 * Test out if number are sufficiently close to be considered equal
 * Can be used on float, double, SN.
 */
template<typename T> bool equal(const T& nb1, const T& nb2){
	if ((T)abs(nb1-nb2)<=(T)LIM_EQUAL){
		true;
	}else{
		return false;
	}
}

/**
 * Returns the chained tabs as a string.
 */
inline std::string to_stringTabs(const unsigned char& nb) {
	std::string mes="";
	for (unsigned int i(0) ; i<nb ; i++){
		mes+="\t";
	}
	return mes;
}

/**
 * Renders the tabs.
 */
inline void printTabs(const unsigned char& nb) {
	for (unsigned int i(0) ; i<nb ; i++){
		std::cout<<"\t";
	}
}






/**
 * Rounding helper, simplified version of the function I use (not mine).
 */
inline int roundUpToMultipleOfEight(int v){
    return (v+(8-1)) & -8;
}

/**
 * Draws a circle in the renderer (not mine)
 */
inline void drawCircle(SDL_Renderer* renderer, SDL_Point center, int radius){
    // 35 / 49 is a slightly biased approximation of 1/sqrt(2)
    const int arrSize = roundUpToMultipleOfEight(radius*8*35/49);
    SDL_Point points[arrSize];
    int drawCount=0;

    const int32_t diameter=radius*2;

    int32_t x=radius-1;
    int32_t y=0;
    int32_t tx=1;
    int32_t ty=1;
    int32_t error=tx-diameter;

    while( x >= y )
    {
        // Each of the following renders an octant of the circle
        points[drawCount+0] = { center.x+x, center.y-y };
        points[drawCount+1] = { center.x+x, center.y+y };
        points[drawCount+2] = { center.x-x, center.y-y };
        points[drawCount+3] = { center.x-x, center.y+y };
        points[drawCount+4] = { center.x+y, center.y-x };
        points[drawCount+5] = { center.x+y, center.y+x };
        points[drawCount+6] = { center.x-y, center.y-x };
        points[drawCount+7] = { center.x-y, center.y+x };

        drawCount+=8;

        if(error<=0){
            y++;
            error+=ty;
            ty+=2;
        }

        if(error>0){
            x--;
            tx+=2;
            error+=tx-diameter;
        }
    }

    SDL_RenderDrawPoints(renderer, points, drawCount);
}

/**
 * Returns the Points that are to be rendered.
 */
inline std::vector<SDL_Point> pixelizeCircle(SDL_Point center, int radius){
    std::vector<SDL_Point> points;

    // 35 / 49 is a slightly biased approximation of 1/sqrt(2)
    const int arrSize=roundUpToMultipleOfEight(radius*8*35/49);
    points.reserve(arrSize);

    const int32_t diameter=radius*2;

    int32_t x=radius-1;
    int32_t y=0;
    int32_t tx=1;
    int32_t ty=1;
    int32_t error=tx-diameter;

    while(x>=y){
        // Each of the following renders an octant of the circle
        points.push_back( { center.x+x, center.y-y } );
        points.push_back( { center.x+x, center.y+y } );
        points.push_back( { center.x-x, center.y-y } );
        points.push_back( { center.x-x, center.y+y } );
        points.push_back( { center.x+y, center.y-x } );
        points.push_back( { center.x+y, center.y+x } );
        points.push_back( { center.x-y, center.y-x } );
        points.push_back( { center.x-y, center.y+x } );

        if(error<=0){
            y++;
            error+=ty;
            ty+=2;
        }

        if(error>0){
            x--;
            tx+=2;
            error+=tx-diameter;
        }
    }

    return points; // RVO FTW
}



#endif /* FUNCTIONS_HPP_ */
