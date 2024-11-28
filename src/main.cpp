/*
 * main.cpp
 *
 *  Created on: 27 avr. 2024
 *      Author: esn
 */

#ifndef MAIN_CPP_
#define MAIN_CPP_

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
#include "core/VectorFieldUnidirectional.h"
#include "core/Physics.h"
#include "utilities/Game.h"
//#include "utilities/functions.h"



//#include <qt6/QtWidgets/QApplication>

//#include <qt6/QtWidgets/QGraphicsView>
//#include <qt5/QtWidgets/QGraphicsScene>
//#include <qt5/QtCore/QPointF>
//#include <qt5/QtGui/QVector2D>



/*
 * Test Eigen
 */
//int main(){
//
//	std::cout<< "Hello\n" << "\n";
//
//	Eigen::MatrixXd m(3,3);
//	m << 1, 2, 3,
//	     4, 5, 6,
//	     7, 8, 9;
//	std::cout << m << std::endl;
//	return 0;
//}


/*
 * Main core (LSN, Point3D, WeightedPoint3D)
 */
/*int main(int argc, char* argv[]){
	//
	// Tests LSN
	//
	std::cout<< "\n" << "####Tests LSN####" << "\n";

	LSN nb0{2,20};			//{2,20}
	LSN nb1=nb0*-1;			//{-2,20}
	LSN nb2{1,20};			//{1,20}
	LSN nb3=nb1+nb2;		//{-1,20}
	LSN nb4=nb2;			//{-1,20}
	//nb4+=nb0;				//{3,20}
	nb4-=nb0;				//{-1,20}
	printf("\nnb0:\n");
	nb0.print(true, 0, true);
	printf("\nnb1:\n");
	nb1.print(true, 0, true);
	printf("\nnb2:\n");
	nb2.print(true, 0, true);
	printf("\nnb3:\n");
	nb3.print(true, 0, true);
	printf("\nnb4:\n");
	nb4.print(true, 0, true);

	//nb3*=2.;

	bool answ=(nb3<1.);
	printf("\n\nansw:\n %b\n", answ);

	printf("\nnb3:\n");
	nb3.print(true, 0, true);

	std::cout<< "\n";

	//
	// Tests Points
	//
	std::cout<< "\n" << "####Tests Points####" << "\n";

	Point3D<float, char> p1{{0,0},{2,0},{1,0}};
	Point3D<float, char> p2{{2,8},{2,0},{1,0}};
	p1-=p2;											// {{-2,8},{0,0},{0,0}} Doesn't work.
	//p1+=p2;										// {{2,8},{4,0},{2,0}}
	Point3D<float, char> p3{{18,7},{2,0},{5,0}};
	Point3D<float, char> p4=p1+p2-p3;				// {{-1.8,8},{0,0},{-4,0}}
	//p4-=p4;
	printf("\np1:\n");
	p1.print(true, 0, false);
	printf("\np2:\n");
	p2.print(true, 0, false);
	printf("\np3:\n");
	p3.print(true, 0, false);
	printf("\np4:\n");
	p4.print(true, 0, false);

//	Quad<Point3D> q2(LSN{50, 0});
//	q2.insert(new Point3D{{0,0},{0,0},{0,0}});
//	q2.print(true, 0, true);
//
//	std::cout<< "\n";

	//
	// Tests Weighted Points
	//
	std::cout<< "\n" << "####Tests Weighted Points####" << "\n";

	WeightedPoint3D<float, char> wp1{{0,0},{2,0},{1,0},{1,0}};
	WeightedPoint3D<float, char> wp2{{20,7},{2,0},{1,0},{1,0}};
	WeightedPoint3D<float, char> wp3{{18,7},{2,0},{5,0},{1,0}};
	WeightedPoint3D<float, char> wp4=wp1+wp2-wp3;

	wp1.print(true, 0, false);
	wp2.print(true, 0, false);
	wp3.print(true, 0, false);
	wp4.print(true, 0, false);
}*/








/*
 * Main SDL
 */
/*int main(int argc, char* argv[]){

    printf("Hello\n");
    Particle3D p;
    p.x={1, 1};
    p.y={1, 1};
    p.z={0, 0};
    p.w={1, 12};
    Vector3D v({{0, 0}, {0, 0}, {0, 0}}, {{0, 0}, {0, 0}, {0, 0}});
    p.setSpeed(v);

    Particle3D p2;
    p2.x={-3, 1};
    p2.y={-2, 1};
    p2.z={2, 1};
    p2.w={1, 12};

    p.print(true, true, 0);
    p2.print(true, true, 0);

    LSN result=rrr2(&p, &p2);
    result.print(true, true, 0);

    // Init SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0){
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[DEBUG] > %s", SDL_GetError());
        return EXIT_FAILURE;
    }


    Game g1;

    g1.getPScene()->addPDisplayable(&p);
    g1.getPScene()->addPDisplayable(&p2);*/
    /*for (Displayable* pdisplayable : g1.getPScene()->getPDisplayables()){
    	printf("\n###1\n");
    	pdisplayable->print(true);
    	printf("\n###1\n");
    }*///OK
    /*bool ans2=g1.getPPhysics()->addPTimeSensitive(&p);
    g1.getPPhysics()->addPTimeSensitive(&p2);
    printf("\naddPTimeSensitive was successful ?: %b\n", ans2);*/
    /*for (TimeSensitive* ptime_sensitive : g1.getPPhysics()->getPTimeSensitives()){
    	//printf("\n###2\n");
    	ptime_sensitive->print(true);
    	//printf("\n###2\n");
    }*///OK


    // Creation of a particle system (System3D)
    /*System3D<Particle3D> sys;
    sys.setPFunc(rrr2);
    sys.setA({1, 3});
    sys.addPElement(&p);
    sys.addPElement(&p2);
    //sys.empty();
    sys.recalculate();
    printf("\nprint system1\n");
    sys.print(true, true, 1);
    printf("\nprint system2\n");

    g1.getPPhysics()->addPTimeSensitive(&sys);
    printf("\nprint physics1\n");
    g1.getPPhysics()->print(true, true, 0);
    printf("\nprint physics2\n");

    // Launch the simulation
    //g1.getPPhysics()->iterate(10);
    g1.run(100);

    //Quad<Particle3D> q({1, 3}, {{0,0}, {0,0}, {0,0}});
    //q.insert(&p);

    printf("\nMain2\n");

    SDL_Delay(1000);

    SDL_Quit();

    printf("\nBye\n");

    return EXIT_SUCCESS;
}*/


/*
 * Main QT
 */

//int main(int argc, char *argv[])
//{
//    QApplication a(argc, argv);
//    QVector2D <QPointF> points;
//
//    // Fill in points with n number of points
//    for(int i = 0; i< 100; i++)
//       points.append(QPointF(i*5, i*5));
//
//    // Create a view, put a scene in it and add tiny circles
//    // in the scene
//    QGraphicsView * view = new QGraphicsView();
//    QGraphicsScene * scene = new QGraphicsScene();
//    view->setScene(scene);
//
//    for(int i = 0; i< points.size(); i++)
//        scene->addEllipse(points[i].x(), points[i].y(), 1, 1);
//
//    // Show the view
//    view->show();
//
//    // or add the view to the layout inside another widget
//
//    return a.exec();
//}

#endif /* MAIN_CPP_ */
