/*
 * main5.cpp
 *
 *  Created on: 27 avr. 2024
 *      Author: esn
 */

#ifndef MAIN5_CPP_

#define MAIN5_CPP_

#include <memory>

#include "core/Particle3D.h"
#include "core/System3D.h"
#include "core/Physics.h"


/*
 * Main core (Particle3D, System3D, Physics)
 */
int main(int argc, char* argv[]){

	WeightedPoint3D<float, char> w1{{-1,0},{1,0},{0,0},{5,1}};
	WeightedPoint3D<float, char> w2{{1.5,0},{1.87006,0},{0,0},{-3,1}};
	WeightedPoint3D<float, char> w3{{-1.75,0},{-1.9,0},{0,0},{-2,1}};
	WeightedPoint3D<float, char> w4{{-1,1},{2,1},{0,0},{7,1}};
	Particle3D par1(w1);
	Particle3D par2(w2);
	Particle3D par3(w3);
	Particle3D par4(w4);
	std::shared_ptr<Particle3D<float, char>> ppar1(new Particle3D<float, char>(par1));
	std::shared_ptr<Particle3D<float, char>> ppar2(new Particle3D<float, char>(par2));
	std::shared_ptr<Particle3D<float, char>> ppar3(new Particle3D<float, char>(par3));
	std::shared_ptr<Particle3D<float, char>> ppar4(new Particle3D<float, char>(par4));
	par1.print(true, true, 1);
	par2.print(true, true, 1);
	par3.print(true, true, 1);
	par4.print(true, true, 1);

	//
	// Tests Particle Sets
	//
//	std::cout<< "\n" << "####Tests Particle Sets####" << "\n";
//	ParticleSystem3D ps;
//	ps.addPParticle(&par1);
//	ps.addPParticle(&par2);
//	ps.print(true, true, 0);

	//
	// Tests Systems
	//
	std::cout<< "\n\n" << "####Tests System3Ds####" << "\n\n";
	System3D<Particle3D<float, char>, float, char> ps2;
	bool test=ps2.addPElement(ppar1);
	printf("%b\n", test);
	//test=ps2.addPElement(ppar2);
	//printf("%b\n", test);
	//test=ps2.addPElement(ppar3);
	//printf("%b\n", test);
	ps2.print(true, true, 0);

	//
	// Tests Vector Fields
	//
//	VectorFieldUnidirectional vf1;
//	//vf1.addPMoveable(&ps);
//	vf1.print(true, true, 0);


	//
	// Tests Physics
	//
	std::cout<< "\n\n" << "####Tests Physics####" << "\n\n";
	//std::shared_ptr<Particle3D> ppar4=std::make_shared<Particle3D>();//(new Particle3D());//(WeightedPoint3D<float, char>{{-1,0},{1,0},{0,0},{5,1}});

	Physics phys;
	phys.setPPS(200);
	phys.setFPause(false);
	//phys.addPTimeSensitive(std::shared_ptr<System3D<Particle3D, float, char>>(&ps2));//Doesn't work
	printf("%b\n", phys.addPTimeSensitive(ppar4));
	//printf("%b\n", phys.addPTimeSensitive(std::shared_ptr<Particle3D>(&par2)));
	//printf("%b\n", phys.addPTimeSensitive(std::shared_ptr<Particle3D>(&par3)));
	//printf("%b\n", phys.addPTimeSensitive(&ps2));

	//phys.run(1);

	// Affichage du mouvement
	//vf1.print(true, 0, true);

	phys.print(true, true, 2);

	//
	// Tests Physics
	//

	std::cout<< "\n" << "####Tests Physics2####" << "\n";
	printf("\nBye bye\n");

	return 0;
}


#endif /* MAIN5_CPP_ */
