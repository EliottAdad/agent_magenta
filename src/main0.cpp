/*
 * main.cpp
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
#include "core/LSN.h"
#include "core/Point3D.h"
#include "core/WeightedPoint3D.h"
#include "core/Quad.h"
#include "core/Oct.h"
#include "core/Particle3D.h"
//#include "core/ParticleSystem3D.h"
#include "core/System3D.h"
#include "core/Vector3D.h"
#include "core/VectorField.h"
//#include "core/VectorFieldUnidirectional.h"
#include "core/Physics.h"
#include "utilities/Game.h"
//#include "utilities/functions.h"



//#include <qt6/QtWidgets/QApplication>

//#include <qt6/QtWidgets/QGraphicsView>
//#include <qt5/QtWidgets/QGraphicsScene>
//#include <qt5/QtCore/QPointF>
//#include <qt5/QtGui/QVector2D>






/*
 * Main SDL
 */
/*int main(int argc, char* argv[]){

    printf("Hello\n");
    Particle3D p1;
    p1.x={1.,0};
    p1.y={1.,0};
    p1.z={0.,0};
    p1.w={1.,12};
    Vector3D v({{0.,0},{0.,0},{0.,0}}, {{1.,0},{0.,0},{0.,0}});
    p1.setSpeed(v);

    Particle3D p2;
    p2.x={-3.,1};
    p2.y={-2.,1};
    p2.z={2.,1};
    p2.w={1.,1};

    p1.print(true, true, 0);
    p2.print(true, true, 0);

    //SN<float, char> result=rrr2(&p, &p2);
    //result.print(true, true, 0);

    // Init SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0){
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[DEBUG] > %s", SDL_GetError());
        return EXIT_FAILURE;
    }


    Game g1;

    g1.addPDisplayable(&p1);
    g1.addPDisplayable(&p2);
//    for (Displayable* pdisplayable : g1.getPScene()->getPDisplayables()){
//    	printf("\n###1\n");
//    	pdisplayable->print(true);
//    	printf("\n###1\n");
//    }//OK
    printf("\n%b\n", g1.addPTimeSensitive(&p1));
    printf("\n%b\n", g1.addPTimeSensitive(&p2));
    //g1.addPTimeSensitive(&p2);
    //printf("\naddPTimeSensitive was successful ?: %b\n", ans2);
    //for (TimeSensitive* ptime_sensitive : g1.getPPhysics()->getPTimeSensitives()){
    //	//printf("\n###2\n");
    //	ptime_sensitive->print(true);
    //	//printf("\n###2\n");
    //}//OK

    g1.setFPS(99);
    g1.setPPS(100);
    g1.setFPause(false);

    // Creation of a particle system (System3D)
//    System3D<Particle3D, float, char> sys;
//    sys.setPFunc(rrr2);
//    sys.setA({1, 3});
//    sys.addPElement(&p);
//    sys.addPElement(&p2);
//    //sys.empty();
//    sys.recalculate();
//    printf("\nprint system1\n");
//    sys.print(true, true, 1);
//    printf("\nprint system2\n");

    //g1.getPPhysics()->addPTimeSensitive(&sys);
    //printf("\nprint physics1\n");
    //g1.getPPhysics()->print(true, true, 0);
    //printf("\nprint physics2\n");

    // Launch the simulation
    //g1.getPPhysics()->iterate(10);
    g1.run(1);

    //Quad<Particle3D> q({1, 3}, {{0,0}, {0,0}, {0,0}});
    //q.insert(&p);

    printf("\nMain2\n");

    p1.print(true, true, 0);
    p2.print(true, true, 0);

    SDL_Delay(1000);

    SDL_Quit();

    printf("\nBye(main0)\n");

    return EXIT_SUCCESS;
}*/


#endif /* MAIN0_CPP_ */
