/*
 * main.cpp
 *
 *  Created on: 27 avr. 2024
 *      Author: esn
 */

#ifndef MAIN_CPP_
#define MAIN_CPP_

#include "core/SN.h"
#include "core/LSN.h"


/*
 * Main core (SN)
 */
int main(int argc, char* argv[]){
	printf("%lu\n", sizeof(LSN));
	printf("%lu\n", sizeof(SN<float, char>));
	//
	// Tests SN
	//
	std::cout<< "\n" << "####Tests SN####" << "\n";

	SN<float, char> nb0{2.,20};			//{2,20}
	SN<float, char> nb1=nb0*(float)(-1.);			//{-2,20}
	SN<float, char> nb2{1.,20};			//{1,20}
	SN<float, char> nb3=nb1+nb2;		//{-1,20}
	SN<float, char> nb4=nb2;			//{1,20}
	nb0.print(true, true, 1);
	nb1.print(true, true, 1);
	nb2.print(true, true, 1);
	nb3.print(true, true, 1);
	nb4.print(true, true, 1);
}
	//nb4+=nb0;				//{3,20}
//	nb4-=nb0;				//{-1,20}
//	printf("\nnb0:\n");
//	nb0.print(true, 0, true);
//	printf("\nnb1:\n");
//	nb1.print(true, 0, true);
//	printf("\nnb2:\n");
//	nb2.print(true, 0, true);
//	printf("\nnb3:\n");
//	nb3.print(true, 0, true);
//	printf("\nnb4:\n");
//	nb4.print(true, 0, true);
//
//	//nb3*=2.;
//
//	bool answ=(nb3>1.);
//	printf("\nansw:\n %b", answ);
//	printf("\nnb3:\n");
//	nb3.print(true, 0, true);
//
//	std::cout<< "\n";
//}


#endif /* MAIN_CPP_ */
