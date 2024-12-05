/*
 * main4.cpp
 *
 *  Created on: 27 avr. 2024
 *      Author: esn
 */

#ifndef MAIN4_CPP_
#define MAIN4_CPP_

#include "core/SN.h"
#include "core/WeightedPoint3D.h"
#include "core/Particle3D.h"
#include "core/Quad.h"
#include "core/Oct.h"


/*
 * Main core (Particle3D, Quads, Octs)
 */
int main(int argc, char* argv[]){
	printf("%lu\n", sizeof(Point3D<float, char>));
	printf("%lu\n", sizeof(WeightedPoint3D<float, char>));
	printf("%lu\n", sizeof(Particle3D));

	//
	// Tests Particles
	//
	std::cout<< "\n" << "####Tests Particles####" << "\n" << "\n";

	Particle3D par1({{-1.,0},{1.,0},{0.,0},{5.,1}});
	Particle3D par2({{1.5,0},{1.87006,0},{0.,0},{-3.,1}});
	Particle3D par3({{-1.75,0},{-1.9,0},{0.,0},{-2.,1}});
	Particle3D par4({{-1.,1},{2.,1},{0.,0},{7.,1}});
	par1.print(true, true, 0);
	par2.print(true, true, 0);
	par3.print(true, true, 0);
	par4.print(true, true, 0);


	//
	// Tests Quads
	//
	std::cout<< "\n" << "\n" << "####Tests Quads####" << "\n" << "\n";
	SN<float, char> a(1., 2);
	Point3D<float, char> p{{0.,0},{0.,0},{0.,0}};
	Quad<Particle3D, float, char> q1(a, p);
	//q1.m_ALPHA=0.1;

	q1.insert(&par1);
	q1.insert(&par2);
	q1.insert(&par3);
	q1.insert(&par4);
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
	std::cout<< "\n" << "####Tests Octs####" << "\n" << "\n";
	Oct<Particle3D, float, char> o1;

	o1.insert(&par1);
	o1.insert(&par2);
	o1.insert(&par3);
	o1.insert(&par4);
	//o1.recalculate();
	o1.print(true, true, 0);

	printf("\n\nBye bye\n");

	return 0;
}



#endif /* MAIN4_CPP_ */
