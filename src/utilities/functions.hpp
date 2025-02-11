/*
 * functions.hpp
 *
 *  Created on: 7 mai 2024
 *      Author: esn
 */

#ifndef FUNCTIONS_HPP_

#define FUNCTIONS_HPP_

#include <memory>
#include <vector>
#include <unordered_set>
#include <iostream>
#include <stdio.h>
#include <SDL2/SDL.h>


/*
 * Functions
 */

std::string to_stringTabs(const unsigned char& nb);
void printTabs(const unsigned char& nb);

//unsigned long long int factorial(unsigned int n);
/*unsigned long long int binomialCoef(unsigned int n, unsigned int k);*/

/*
 * Graphic functions
 */

//void print(SDL_Color* pcolor, unsigned int indent=0);

//void init();
//void free();

//void setWindowColor(SDL_Renderer* prenderer, SDL_Color* pcolor=new SDL_Color{0, 0, 0, 255});

/*float getDistance(Point2D* ppoint1, Point2D* ppoint2);*/



//void initSoftwareNecessery(std::string sft_name, unsigned int wd_w, unsigned int wd_h);

int roundUpToMultipleOfEight(int v);
void drawCircle(SDL_Renderer* renderer, SDL_Point center, int radius);
std::vector<SDL_Point> pixelizeCircle(SDL_Point center, int radius);



#endif /* FUNCTIONS_HPP_ */
