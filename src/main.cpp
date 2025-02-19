/*
 * main.cpp
 *
 *  Created on: 4 fevrier 2025
 *      Author: esn
 */

#ifndef MAIN_CPP_

#define MAIN_CPP_


#include <chrono>
#include <iostream>
#include "unistd.h"
//#include <eigen3/Eigen/Dense>
#include <SDL2/SDL.h>

#include "core_includes.hpp"
#include "utilities_includes.hpp"



/*
 * Main SDL
 */
int main(int argc, char* argv[]){
    printf("Hello %ld, %ld, %ld, %ld, %ld\n", sizeof(long int), sizeof(uint32_t), sizeof(int32_t), sizeof(int64_t), sizeof(SN<float, char>));
    std::unordered_set<std::shared_ptr<Particle3D<SN<float, char>>>> pparts;
	printf("main : generate2DGridParticle3D\n");
    pparts=generate2DGridParticle3D(Point3D<SN<float, char>>{{2,1},{0,0},{0,0}}, SN<float, char>{2,3}, 5, SN<float, char>{1, 18});
    
    // Init SDL
	printf("main : SDL\n");
    initSDL();

    // Sys
	printf("main : sys\n");
    std::shared_ptr<System3D<Particle3D<SN<float, char>>, SN<float, char>>> psys=std::make_shared<System3D<Particle3D<SN<float, char>>, SN<float, char>>>();
    psys->setA(SN<float, char>{1,4});
    psys->setAlpha(0.1);
    for (std::shared_ptr<Particle3D<SN<float, char>>> ppart : pparts){
    	psys->insert(ppart);
    }
    psys->ptrLaw=gravitOptimised;

    // Game
	printf("main : game\n");
    Game3D<SN<float, char>> g1;
    //g1.pdisplay->fclear=false;
    g1.fpause=false;//useless
    g1.pdisplay->scale=0.15;
    g1.pdisplay->fps=40;
    g1.pphysics->pps=200;
    g1.pphysics->speed=0.1;
    g1.pphysics->fpause=false;

	// Adding to the scene
	printf("main : adding to scene\n");
    //g1.pscene->addPDisplayable(psys);// Not sure it works properly.
    for (std::shared_ptr<Particle3D<SN<float, char>>> ppart : pparts){
        g1.pscene->add(ppart);
    }
    // Adding to physics
	printf("main : adding to physics\n");
    /*for (std::shared_ptr<Particle3D<SN<float, char>>> ppart : pparts){
        g1.pphysics->add(ppart);
    }*/
    g1.pphysics->add(psys);

    g1.run(10000);

	printf("main : run\n");

    SDL_Delay(1000);

    quitSDL();

	printf("main : quitSDL\n");

    return EXIT_SUCCESS;
}


#endif /* MAIN_CPP_ */
