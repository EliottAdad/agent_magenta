/*
 * main5.cpp
 *
 *  Created on: 27 avr. 2024
 *      Author: esn
 */

#ifndef MAIN5_CPP_
#define MAIN5_CPP_

#include "core/Particle3D.h"
//#include "core/ParticleSystem3D.h"
#include "core/System3D.h"
//#include "core/Vector3D.h"
//#include "core/WeightedPoint3D.h"
//#include "core/Particle3D.h"
//#include "core/Quad.h"
//#include "core/Oct.h"


/*
 * Main core (Particle3D, Quads, Octs)
 */
int main(int argc, char* argv[]){

	Particle3D par1({{-1,0},{1,0},{0,0},{5,1}});
	Particle3D par2({{1.5,0},{1.87006,0},{0,0},{-3,1}});
	Particle3D par3({{-1.75,0},{-1.9,0},{0,0},{-2,1}});

	//
	// Tests Particle Sets
	//
	/*std::cout<< "\n" << "####Tests Particle Sets####" << "\n";
	ParticleSystem3D ps;
	ps.addPParticle(&par1);
	ps.addPParticle(&par2);
	ps.print(true, true, 0);*/

	//
	// Tests Systems
	//
	std::cout<< "\n" << "####Tests System3Ds####" << "\n";
	System3D<Particle3D, float, char> ps2;
//	bool test=ps2.addPElement(&par1);
//	printf("%b\n", test);
//	test=ps2.addPElement(&par2);
//	printf("%b\n", test);
//	test=ps2.addPElement(&par3);
//	printf("%b\n", test);
	ps2.print(true, true, 1);

	//
	// Tests Vector Fields
	//
	/*VectorFieldUnidirectional vf1;
	//vf1.addPMoveable(&ps);
	vf1.print(true, true, 0);*/


	//
	// Tests Physics
	//
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
	printf("\nBye bye\n");

	return 0;
}



#endif /* MAIN5_CPP_ */
