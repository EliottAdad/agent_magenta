/*
 * main4.cpp
 *
 *  Created on: 27 avr. 2024
 *      Author: esn
 */

#ifndef MAIN4_CPP_

#define MAIN4_CPP_

#include <memory>

#include "core/SN.h"
#include "core/WeightedPoint3D.h"
#include "core/Particle3D.h"
#include "core/Quad.h"
#include "core/Oct.h"


/*
 * Main core (Particle3D, Quads, Octs)
 */
/*int main(int argc, char* argv[]){
	printf("%lu\n", sizeof(Point3D<float, char>));
	printf("%lu\n", sizeof(Point3D<float, char>));
	printf("%lu\n", sizeof(WeightedPoint3D<float, char>));
	printf("%lu\n", sizeof(Particle3D<float, char>));

	//
	// Tests Particles
	//
	std::cout<< "\n" << "####Tests Particles####" << "\n" << "\n";
	WeightedPoint3D<float, char> w1{{-1,0},{1,0},{0,0},{5,1}};
	WeightedPoint3D<float, char> w2{{1.5,0},{1.87006,0},{0,0},{-3,1}};
	WeightedPoint3D<float, char> w3{{-1.75,0},{-1.9,0},{0,0},{-2,1}};
	WeightedPoint3D<float, char> w4{{-1,1},{2,1},{0,0},{7,1}};
	Particle3D par1(w1);
	Particle3D par2(w2);
	Particle3D par3(w3);
	Particle3D par4(w4);
//	std::shared_ptr<Particle3D> ppar1(new Particle3D(w1));
//	std::shared_ptr<Particle3D> ppar2(new Particle3D(w2));
//	std::shared_ptr<Particle3D> ppar3(new Particle3D(w3));
//	std::shared_ptr<Particle3D> ppar4(new Particle3D(w4));
	par1.print(true, true, 1);
	par2.print(true, true, 1);
	par3.print(true, true, 1);
	par4.print(true, true, 1);


	//
	// Tests Quads
	//
	std::cout<< "\n\n" << "####Tests Quads####" << "\n\n";
	SN<float, char> a{1,2};
	Point3D<float, char> p{{0,0},{0,0},{0,0}};
	Quad<Particle3D<float, char>, float, char> q1(a, p);
//	//q1.m_ALPHA=0.1;

	std::shared_ptr<Particle3D<float, char>> ppar1(new Particle3D<float, char>(par1));
	std::shared_ptr<Particle3D<float, char>> ppar2(new Particle3D<float, char>(par2));
	std::shared_ptr<Particle3D<float, char>> ppar3(new Particle3D<float, char>(par3));
	std::shared_ptr<Particle3D<float, char>> ppar4(new Particle3D<float, char>(par4));
	ppar1->print(true, true, 1);
	ppar2->print(true, true, 1);
	ppar3->print(true, true, 1);
	ppar4->print(true, true, 1);
	q1.insert(ppar1);
	q1.insert(ppar2);
	//q1.insert(ppar3);
	//q1.insert(ppar4);
	q1.recalculate();
	q1.print(true, true, 0);

//	std::cout << "\nArobase\n";
//
//	std::unordered_set<Quad<Particle3D>*> pquads;
//	q1.find(par4, pquads);
//	for (Quad<Particle3D>* pquad : pquads){
//		pquad->print(true, false, 0);
//	}

	//Vector3D v(Point3D{{0,0},{0,0},{0,0}}, Point3D{{0,0},{0,0},{0,0}});
	//q1.computeInverseSquareLawResultant(par4, v);
	//std::cout << "\n" << v.to_string() << "\n";


	//
	// Tests Octs
	//
	std::cout<< "\n\n" << "####Tests Octs####" << "\n\n";
	//Oct<Particle3D<float, char>, float, char> o1(a, p);
	Oct<Particle3D<float, char>, float, char> o1;
	o1.setA(a);
	o1.setPoint(p);

	o1.insert(ppar1);//Not sure it works properly
	o1.insert(ppar2);
	o1.insert(ppar3);
	o1.insert(ppar4);
	o1.recalculate();
	o1.print(true, true, 0);

	printf("\n\nBye bye\n");

	return 0;
}*/



#endif /* MAIN4_CPP_ */
