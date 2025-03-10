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
	std::cout<< "\n\n" << "####Tests Vectors####" << "\n\n";

	Point3D<SN<float, char>> p0{{0,0},{0,0},{0,0}};
	Point3D<SN<float, char>> p1{{0,0},{2,0},{1,0}};
	Point3D<SN<float, char>> p2{{2,0},{2,0},{1,0}};
	Point3D<SN<float, char>> p3{{1,0},{-2,0},{1,0}};

	Vector3D<SN<float, char>> v1(p0, p1);
	v1.print(true, true, 0);
	Vector3D<SN<float, char>> v2(p0, p2);
	v2.print(true, true, 0);
	Vector3D<SN<float, char>> v3(p0, p3);
	v3.print(true, true, 0);


	printf("\n Test + start \n");
	Vector3D<SN<float, char>> rv1; rv1=v1+v2;			//{{2,0},{4,0},{2,0}}
	rv1.print();
	printf("\n Test + end \n");

	printf("\n Test - start \n");
	Vector3D<SN<float, char>> rv2=v1-v2;
	rv2.print();
	printf("\n Test - end \n");

	printf("\n Test * start \n");
	Vector3D<SN<float, char>> rv3=v1*2;
	rv3.print();
	printf("\n Test * end \n");

	printf("\n Test / start \n");
	Vector3D<SN<float, char>> rv4=v1/2;
	rv4.print();
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
	//std::shared_ptr<Vector3D> rv5=*(*rv1+*rv2)+*rv3;
	Vector3D rv5=rv1+rv2+rv3+rv4;
	//std::shared_ptr<Vector3D> rv5=*(*(*rv1-*rv2)+*rv3)*2.;// Now we can chain operators like Points3D
	rv5.print();
	std::cout<< "\n" << "Vectors : chain operations test end" << "\n";

	printf("\n\nBye bye\n");
}*/


#endif /* MAIN3_CPP_ */
