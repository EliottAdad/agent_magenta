/*
 * main0.cpp
 *
 *  Created on: 27 avr. 2024
 *      Author: esn
 */

#ifndef MAIN0_CPP_

#define MAIN0_CPP_

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



//#include <qt6/QtWidgets/QApplication>

//#include <qt6/QtWidgets/QGraphicsView>
//#include <qt5/QtWidgets/QGraphicsScene>
//#include <qt5/QtCore/QPointF>
//#include <qt5/QtGui/QVector2D>






/*
 * Main SDL
 */
int main(int argc, char* argv[]){

    printf("Hello %ld, %ld, %ld, %ld, %ld\n", sizeof(long int), sizeof(uint32_t), sizeof(int32_t), sizeof(int64_t), sizeof(SN<float, char>));
    std::unordered_set<std::shared_ptr<Particle3D<SN<float, char>>>> pparts;
    pparts=generate2DGridParticle3D(Point3D<SN<float, char>>{{2,1},{0,0},{0,0}}, SN<float, char>{1,3}, 5, SN<float, char>{1, 15});

    // Init SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0){
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[DEBUG] > %s", SDL_GetError());
        return EXIT_FAILURE;
    }

    // Sys
    std::shared_ptr<System3D<Particle3D<SN<float, char>>, float, char>> psys=std::make_shared<System3D<Particle3D<SN<float, char>>, float, char>>();
    psys->setA(SN<float, char>{1, 5});
    psys->setAlpha(5);
    for (std::shared_ptr<Particle3D<SN<float, char>>> ppart : pparts){
    	psys->addPElement(ppart);
    }
    psys->ptrLaw=rrr2;

    // Game
    Game g1;
    g1.pdisplay->setScale(0.2);
    //g1.pdisplay->ppoint=pparts[0];

    for (std::shared_ptr<Particle3D<SN<float, char>>> ppart : pparts){
        g1.pscene->addPDisplayable(ppart);
    }

    printf("\n%b\n", g1.pphysics->addPTimeSensitive(psys));

    g1.setFPS(40);
    g1.pphysics->setPPS(100);
    g1.setFPause(false);
    //g1.print(true, true, 0);

    g1.run(10000);

    printf("\nMain2\n");

    SDL_Delay(1000);

    SDL_Quit();

    printf("\nBye(main0)\n");

    return EXIT_SUCCESS;
}


#endif /* MAIN0_CPP_ */
