/*
 * main3.cpp
 *
 *  Created on: 27 avr. 2024
 *      Author: esn
 */

#ifndef MAIN3_CPP_
#define MAIN3_CPP_

#include "core/Vector3D.h"


/*
 * Main core (Vector3D)
 */
/*int main(int argc, char* argv[]){
	//
	// Tests Vectors
	//
	std::cout<< "\n" << "####Tests Vectors####" << "\n" << "\n";

	Vector3D v1;
	v1.print(true, true, 0);
	Vector3D v2;
	v2.print(true, true, 0);
	Vector3D v3;
	v3.print(true, true, 0);


	printf("\n Test + start \n");
	std::unique_ptr<Vector3D> rv1=v1+v2;
	rv1->print();
	printf("\n Test + end \n");

	printf("\n Test - start \n");
	std::unique_ptr<Vector3D> rv2=v1-v2;
	rv2->print();
	printf("\n Test - end \n");

	printf("\n Test * start \n");
	std::unique_ptr<Vector3D> rv3=v1*2.;
	rv3->print();
	printf("\n Test * end \n");

	printf("\n Test / start \n");
	std::unique_ptr<Vector3D> rv4=v1/2.;
	rv4->print();
	printf("\n Test / end \n");

	printf("\n Test += start \n");
	v3+=v1;
	v3.print();
	printf("\n Test += end \n");

	printf("\n Test -= start \n");
	v3-=v1;
	v3.print();
	printf("\n Test -= end \n");

	printf("\n Test *= start \n");
	v3*=-2.;
	v3.print();
	printf("\n Test *= end \n");

	printf("\n Test /= start \n");
	v3/=-2.;
	v3.print();
	printf("\n Test /= end \n");

	// Still cannot chain operators
	std::cout<< "\n" << "Vectors : chain operations test start" << "\n";
	std::unique_ptr<Vector3D> rv5(*rv1+*rv2);
	//Vector3D rv5=((v1-v2)+v3)*2;// Cannot chain operators like Points3D//N'appelle pas l'égalisation des Vectors
	rv5->print(true, true, 1);
	std::cout<< "\n" << "Vectors : chain operations test end" << "\n";
}*/


#endif /* MAIN3_CPP_ */
