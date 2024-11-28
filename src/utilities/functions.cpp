/*
 * functions.cpp
 *
 *  Created on: 7 mai 2024
 *      Author: esn
 */

#include "functions.h"



/*
 * Functions
 */

std::string to_stringTabs(const unsigned char& nb) {
	std::string mes="";
	for (unsigned int i(0) ; i<nb ; i++){
		mes+="\t";
	}
	return mes;
}

void printTabs(const unsigned char& nb) {
	for (unsigned int i(0) ; i<nb ; i++){
		std::cout<<"\t";
	}
}





/*float getDistance(Point2D* ppoint1, Point2D* ppoint2) {//:)
	// d=square root( (xA-xB)²+(yA-yB)² )
	return sqrt( pow(ppoint1->x-ppoint2->x, 2) + pow(ppoint1->y-ppoint2->y, 2) );
}*/

unsigned long long int factorial(unsigned int n) {
	unsigned long long int result(1);

	for (unsigned int i(1) ; i<n ; ++i)
	{
		result*=i;
	}
	return result;
}
/*
unsigned long long int binomialCoef(unsigned int n, unsigned int k) {
	return factorial(n)/(factorial(k)*factorial(n-k));
}*/




/*
 * Graphic functions
 */


/*void initSoftwareNecessary(std::string sft_name, unsigned int wd_w, unsigned int wd_h)
{
	SDL_Init(SDL_INIT_VIDEO);// Imports the moduls used.

	pwindow = SDL_CreateWindow(software_name, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, wd_w, wd_h, SDL_WINDOW_SHOWN);

	SDL_DestroyWindow(pwindow);
}*/

/*void init()
{
	SDL_Init(SDL_INIT_VIDEO);// Initialise SDL

	srand(time(NULL));
}*/

/*void free()
{
	SDL_Quit();// Quit SDL
}*/

/*void setWindowColor(SDL_Renderer* prenderer, SDL_Color* pcolor)
{
	SDL_SetRenderDrawColor(prenderer, pcolor->r, pcolor->g, pcolor->b, pcolor->a);// Set the renderer color to the one choosed.
	SDL_RenderClear(prenderer);// Clear the renderer.
}*/


/*void print(SDL_Color* pcolor, unsigned int indent)
{
	if (pcolor!=NULL)
	{
		printTabs(indent);
		printf("%i, %i, %i, %i", pcolor->r, pcolor->g, pcolor->b, pcolor->a);
	}
}*/



