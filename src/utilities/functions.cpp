/*
 * functions.cpp
 *
 *  Created on: 7 mai 2024
 *      Author: esn
 */

#include "functions.hpp"



/*
 * Functions
 */

/**
 * Returns the chained tabs as a string.
 */
std::string to_stringTabs(const unsigned char& nb) {
	std::string mes="";
	for (unsigned int i(0) ; i<nb ; i++){
		mes+="\t";
	}
	return mes;
}

/**
 * Renders the tabs.
 */
void printTabs(const unsigned char& nb) {
	for (unsigned int i(0) ; i<nb ; i++){
		std::cout<<"\t";
	}
}





/**
 * Returns the factorial of n.
 */
/*unsigned long long int factorial(unsigned int n) {
	unsigned long long int result(1);

	for (unsigned int i(1) ; i<n ; ++i){
		result*=i;
	}
	return result;
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



/**
 * Rounding helper, simplified version of the function I use (not mine).
 */
int roundUpToMultipleOfEight(int v){
    return (v+(8-1)) & -8;
}

/**
 * Draws a circle in the renderer (not mine)
 */
void drawCircle(SDL_Renderer* renderer, SDL_Point center, int radius){
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
std::vector<SDL_Point> pixelizeCircle(SDL_Point center, int radius){
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


