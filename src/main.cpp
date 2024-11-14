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

#include "core/LSN.h"
#include "core/Point3D.h"
#include "core/WeightedPoint3D.h"
#include "core/Quad.h"
#include "core/Oct.h"
#include "core/Particle3D.h"
#include "core/ParticleSystem3D.h"
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
 * Main core
 */
//int main(){
//	/*
//	 * Tests LSN
//	 */
//	std::cout<< "\n" << "####Tests LSN####" << "\n";
//
//	LSN nb1{-2000.53,20};
//	LSN nb2{1,20};
//	LSN nb3=nb1+nb2;
//	nb1.print(true, 0, true);
//	nb2.print(true, 0, true);
//	nb3.print(true, 0, true);
//	nb3*=2;
//	nb3*=LSN{5,-1};
//	nb3.print(true, 0, true);
//
//	std::cout<< "\n";
//
//	/*
//	 * Tests Points
//	 */
//	std::cout<< "\n" << "####Tests Points####" << "\n";
//
//	Point3D p1{{0,0},{2,0},{1,0}};
//	Point3D p2{{20,7},{2,0},{1,0}};
//	p1-=p2;
//	Point3D p3{{18,7},{2,0},{5,0}};
//	Point3D p4=p1+p2-p3;
//	p1.print(true, 0, false);
//	p2.print(true, 0, false);
//	p3.print(true, 0, false);
//	p4.print(true, 0, false);
//
//	Quad<Point3D> q2(LSN{50, 0});
//	q2.insert(new Point3D{{0,0},{0,0},{0,0}});
//	q2.print(true, 0, true);
//
//	std::cout<< "\n";
//
//	/*
//	 * Tests Weighted Points
//	 */
//	std::cout<< "\n" << "####Tests Weighted Points####" << "\n";
//
//	WeightedPoint3D wp1{{0,0},{2,0},{1,0},{1,0}};
//	WeightedPoint3D wp2{{20,7},{2,0},{1,0},{1,0}};
//	WeightedPoint3D wp3{{18,7},{2,0},{5,0},{1,0}};
//	WeightedPoint3D wp4=wp1+wp2-wp3;
//
//	wp1.print(true, 0, false);
//	wp2.print(true, 0, false);
//	wp3.print(true, 0, false);
//	wp4.print(true, 0, false);
//
//
//	/*
//	 * Tests Time
//	 */
//	std::cout<< "\n" << "####Tests Time####" << "\n";
//
//	std::chrono::time_point t1=std::chrono::system_clock::now();
//	//std::cout "t1=" << t1.count() << "\n";
//	sleep(1);
//	std::chrono::time_point t2=std::chrono::system_clock::now();
//	std::chrono::duration dt=t2-t1;
//	std::cout << "\n delta t = " << dt.count() << "ns\n";
//
//	/*
//	 * Tests Vectors
//	 */
//	std::cout<< "\n" << "####Tests Vectors####" << "\n" << "\n";
//
//	Vector3D v1;
//	v1.print();
//	Vector3D v2;
//	v2.print();
//	Vector3D v3;
//	v3.print();
//
//
//	printf("\n Test + start \n");
//	Vector3D rv1=v1+v2;
//	rv1.print();
//	printf("\n Test + end \n");
//
//	printf("\n Test - start \n");
//	Vector3D rv2=v1-v2;
//	rv2.print();
//	printf("\n Test - end \n");
//
//	printf("\n Test * start \n");
//	Vector3D rv3=v1*2.;
//	rv3.print();
//	printf("\n Test * end \n");
//
//	printf("\n Test / start \n");
//	Vector3D rv4=v1/2.;
//	rv4.print();
//	printf("\n Test / end \n");
//
//	std::cout<< "\n" << "Vectors : chain operations test start" << "\n";
//	//Vector3D rv5=((rv1+rv2)-rv4)+rv3;
//	//Vector3D rv5=((v1-v2)+v3)*2;// Cannot chain operators like Points3D//N'appelle pas l'égalisation des Vectors
//	//rv5.print();
//	std::cout<< "\n" << "Vectors : chain operations test end" << "\n";
//

	/*
	 * Tests Particles
	 */
//	std::cout<< "\n" << "####Tests Particles####" << "\n" << "\n";
//
//	Particle3D par1({{-1,0},{1,0},{0,0},{5,1}});
//	Particle3D par2({{1.5,0},{1.87006,0},{0,0},{-3,1}});
//	Particle3D par3({{-1.75,0},{-1.9,0},{0,0},{-2,1}});
//	Particle3D par4({{-1,1},{2,1},{0,0},{7,1}});
//	par1.print(true, true, 0);
//	par2.print(true, true, 0);
//	par3.print(true, true, 0);
//	par4.print(true, true, 0);

//
//	/*
//	 * Tests Quads
//	 */
//	std::cout<< "\n" << "\n" << "####Tests Quads####" << "\n" << "\n";
//	Quad<Particle3D> q1(LSN{1, 2});
//	//q1.m_ALPHA=0.1;
//
//	q1.insert(&par1);
//	q1.insert(&par2);
//	q1.insert(&par3);
//	q1.insert(&par4);
//	q1.print(true, true, 0);
//
//	std::cout << "\nArobase\n";
//
//	std::unordered_set<Quad<Particle3D>*> pquads;
//	q1.find(par4, pquads);
//	for (Quad<Particle3D>* pquad : pquads){
//		pquad->print(true, false, 0);
//	}
//
//	Vector3D v(Point3D{{0,0},{0,0},{0,0}}, Point3D{{0,0},{0,0},{0,0}});
//	q1.computeInverseSquareLawResultant(par4, v);
//	std::cout << "\n" << v.to_string() << "\n";
//
//
//	/*
//	 * Tests Octs
//	 */
//	std::cout<< "\n" << "####Tests Octs####" << "\n" << "\n";
//	Oct<Particle3D> o1(LSN{1, 2});
//
//	o1.insert(&par1);
//	o1.insert(&par2);
//	o1.insert(&par3);
//	//o1.insert(&par4);
//	o1.print(true, true, 0);
//
//
//	/*
//	 * Tests Particle Sets
//	 */
//	std::cout<< "\n" << "####Tests Particle Sets####" << "\n";
//	ParticleSystem3D ps;
//	ps.addPParticle(&par1);
//	ps.addPParticle(&par2);
//	ps.print(true, true, 0);
//
	/*
	 * Tests Systems
	 */
//	std::cout<< "\n" << "####Tests System3Ds####" << "\n";
//	System3D<Particle3D> ps2;
//	ps2.addPElement(&par1);
//	ps2.addPElement(&par2);
//	ps2.print(true, true, 0);

//	/*
//	 * Tests Vector Fields
//	 */
//	VectorFieldUnidirectional vf1;
//	//vf1.addPMoveable(&ps);
//	vf1.print(true, true, 0);


	/*
	 * Tests Physics
	 */
	/*std::cout<< "\n" << "\n" << "####Tests Physics####" << "\n";
	Physics phys;
	phys.setCPS(100);
	phys.setFPause(false);
	printf("%b\n", phys.addPTimeSensitive(&par1));
	printf("%b\n", phys.addPTimeSensitive(&ps2));*/

	//phys.run(1);

	// Affichage du mouvement
	//vf1.print(true, 0, true);

	//phys.print(true, true, 0);

	/*
	 * Tests Physics
	 */

	//std::cout<< "\n" << "####Tests Physics2####" << "\n";
//	printf("\nBye bye\n");
//
//	return 0;
//}



/*
 * Main SDL
 */
int main(int argc, char* argv[]){

    printf("Hello\n");
    Particle3D p;
    p.x={1, 1};
    p.y={1, 1};
    p.z={0, 0};
    p.w={0, 0};

    Particle3D p2;
    p2.x={-3, 1};
    p2.y={-2, 1};
    p2.z={2, 1};
    p2.w={0, 0};

    printf("\nMain0\n");
    p.print(true);
    printf("\nMain1\n");

    // Init SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[DEBUG] > %s", SDL_GetError());
        return EXIT_FAILURE;
    }


    Game g1;

    g1.getPScene()->addPDisplayable(&p);
    g1.getPScene()->addPDisplayable(&p2);
    for (Displayable* pdisplayable : g1.getPScene()->getPDisplayables()){
    	printf("\n###1\n");
    	pdisplayable->print(true);
    	printf("\n###1\n");
    }//OK
    bool ans2=g1.getPPhysics()->addPTimeSensitive(&p);
    g1.getPPhysics()->addPTimeSensitive(&p2);
    printf("\naddPTimeSensitive was successful ?: %b\n", ans2);
    for (TimeSensitive* ptime_sensitive : g1.getPPhysics()->getPTimeSensitives()){
    	printf("\n###2\n");
    	ptime_sensitive->print(true);
    	printf("\n###2\n");
    }//OK
    //g1.getPPhysics()->iterate(10);
    g1.run(100);

    printf("\nMain2\n");

    SDL_Delay(1000);

    SDL_Quit();

    printf("\nBye\n");

    return EXIT_SUCCESS;
}


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
