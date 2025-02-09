


#ifndef MAIN_CPP_
#define MAIN_CPP_


#include <chrono>
#include <iostream>
#include "unistd.h"
//#include <eigen3/Eigen/Dense>
#include <SDL2/SDL.h>

//#include "core/SN.h"
#include "geometry/WeightedPoint3D.h"
#include "core/Quad.h"
#include "core/Oct.h"
#include "geometry/Particle3D.h"
//#include "core/ParticleSystem3D.h"
#include "core/System3D.h"
#include "core/VectorField.h"
//#include "core/VectorFieldUnidirectional.h"
#include "core/Physics.h"
#include "core/Point3D.h"
#include "core/Vector3D.h"
#include "utilities/Game.h"
#include "utilities/functionsParticle3D.h"



/*
 * Main SDL
 */
int main(int argc, char* argv[]){
    printf("Hello %ld, %ld, %ld, %ld, %ld\n", sizeof(long int), sizeof(uint32_t), sizeof(int32_t), sizeof(int64_t), sizeof(SN<float, char>));
    std::unordered_set<std::shared_ptr<Particle3D<SN<float, char>>>> pparts;
    pparts=generate2DGridParticle3D(Point3D<SN<float, char>>{{2,1},{0,0},{0,0}}, SN<float, char>{2,3}, 5, SN<float, char>{1, 16});
    for (std::shared_ptr<Particle3D<SN<float, char>>> ppart : pparts) {
    	ppart->print(true, true, 0);
    }
    // Init SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0){
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[DEBUG] > %s", SDL_GetError());
        return EXIT_FAILURE;
    }

    // Sys
    std::shared_ptr<System3D<Particle3D<SN<float, char>>, SN<float, char>>> psys=std::make_shared<System3D<Particle3D<SN<float, char>>, SN<float, char>>>();
    psys->setA(SN<float, char>{1,4});
    psys->setAlpha(0.75);
    for (std::shared_ptr<Particle3D<SN<float, char>>> ppart : pparts){
    	psys->addPElement(ppart);
    }
    psys->ptrLaw=gravitOptimised;

    // Game
    Game g1;
    //g1.pdisplay->fclear=false;
    g1.pdisplay->scale=0.15;
    //g1.pdisplay->ppoint=pparts[0];

    //g1.pscene->addPDisplayable(psys);// Not sure it works properly.
    for (std::shared_ptr<Particle3D<SN<float, char>>> ppart : pparts){
        g1.pscene->addPDisplayable(ppart);
    }

    g1.pphysics->addPTimeSensitive(psys);

    g1.pdisplay->fps=40;
    g1.pphysics->pps=200;
    g1.fpause=false;
    //g1.print(true, true, 0);

    g1.run(10000);

    printf("\nMain2\n");

    SDL_Delay(1000);

    SDL_Quit();

    printf("\nBye(main0)\n");

    //return EXIT_SUCCESS;
}


#endif /* MAIN_CPP_ */
