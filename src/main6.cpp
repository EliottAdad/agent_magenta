/*
 * main.cpp
 *
 *  Created on: 27 avr. 2024
 *      Author: esn
 */

#ifndef MAIN6_CPP_

#define MAIN6_CPP_

#include <chrono>
#include <iostream>
#include "unistd.h"
//#include <eigen3/Eigen/Dense>
#include <SDL2/SDL.h>

//#include "core/SN.h"
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
//#include "utilities/functionsParticle3D.h"



//#include <qt6/QtWidgets/QApplication>

//#include <qt6/QtWidgets/QGraphicsView>
//#include <qt5/QtWidgets/QGraphicsScene>
//#include <qt5/QtCore/QPointF>
//#include <qt5/QtGui/QVector2D>






/*
 * Main SDL (Game, )
 */
/*int main(int argc, char* argv[]){

    printf("Hello\n");
    Particle3D<float, char> p1;
    p1.x={1,1};
    p1.y={1,0};
    p1.z={0,0};
    p1.w={1,11};
    Point3D<float, char> point1{{0,0},{0,0},{0,0}};
    Point3D<float, char> point2{{1,-3},{0,0},{0,0}};
    std::shared_ptr<Vector3D<float, char>> pv(new Vector3D<float, char>(point2));
    *p1.ps=*pv;

    Particle3D<float, char> p2;
    p2.x={-3,1};
    p2.y={-2,1};
    p2.z={2,1};
    p2.w={1,10};
    Point3D<float, char> point3{{0,0},{0,0},{0,0}};
    Point3D<float, char> point4{{0,0},{-3,-1},{0,0}};
    std::shared_ptr<Vector3D<float, char>> pv2(new Vector3D<float, char>(point4));
    *p2.ps=*pv2;

//    Particle3D<float, char> p3;
//    p3.x={-3,1};
//    p3.y={1,0};
//    p3.z={0,0};
//    p3.w={1,13};
//    Point3D<float, char> point5{{0,0},{0,0},{0,0}};
//    Point3D<float, char> point6{{0,0},{-1,10},{0,0}};
//    std::shared_ptr<Vector3D<float, char>> pv3(new Vector3D<float, char>(point6));
//    *p3.ps=*pv3;

    std::shared_ptr<Particle3D<float, char>> pp1(new Particle3D<float, char>(p1));
    std::shared_ptr<Particle3D<float, char>> pp2(new Particle3D<float, char>(p2));
    //std::shared_ptr<Particle3D<float, char>> pp3(new Particle3D<float, char>(p3));

    p1.print(true, true, 0);
    p2.print(true, true, 0);
    //p3.print(true, true, 0);

    //SN<float, char> result=rrr2(&p, &p2);
    //result.print(true, true, 0);

    // Init SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0){
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[DEBUG] > %s", SDL_GetError());
        return EXIT_FAILURE;
    }

    // Sys
    std::shared_ptr<System3D<Particle3D<float, char>, float, char>> psys=std::make_shared<System3D<Particle3D<float, char>, float, char>>();
    psys->addPElement(pp1);
    psys->addPElement(pp2);
    //psys->addPElement(pp3);
    psys->ptrLaw=rrr2;
    psys->setAlpha(10);

    // Game
    Game g1;
    g1.pdisplay->setScale(1.5);


//    SDL_Window* pwindow=SDL_CreateWindow("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 600, 600, SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN_DESKTOP);
//    SDL_Renderer* prenderer=SDL_CreateRenderer(pwindow, 0, SDL_RENDERER_TARGETTEXTURE);
//    g1.pwindow=pwindow;
//    g1.prenderer=prenderer;

    g1.pscene->addPDisplayable(pp1);
    g1.pscene->addPDisplayable(pp2);
    //g1.pscene->addPDisplayable(pp3);
    //printf("\n%b\n", g1.pphysics->addPTimeSensitive(pp1));
    //printf("\n%b\n", g1.pphysics->addPTimeSensitive(pp2));
    printf("\n%b\n", g1.pphysics->addPTimeSensitive(psys));

    //printf("\naddPTimeSensitive was successful ?: %b\n", ans2);
    //for (TimeSensitive* ptime_sensitive : g1.getPPhysics()->getPTimeSensitives()){
    //	//printf("\n###2\n");
    //	ptime_sensitive->print(true);
    //	//printf("\n###2\n");
    //}//OK

    g1.setFPS(40);
    g1.pphysics->setPPS(100);
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
    g1.run(3000);

    //Quad<Particle3D> q({1, 3}, {{0,0}, {0,0}, {0,0}});
    //q.insert(&p);

    printf("\nMain2\n");

    p1.print(true, true, 0);
    p2.print(true, true, 0);
    //p3.print(true, true, 0);

    SDL_Delay(1000);

    SDL_Quit();

    printf("\nBye(main0)\n");

    return EXIT_SUCCESS;
}*/


#endif /* MAIN0_CPP_ */
