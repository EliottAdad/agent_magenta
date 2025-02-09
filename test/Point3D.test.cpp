/*
 * Point3D.test.cpp
 *
 *  Created on: 7 mai 2024
 *      Author: esn
 */

#ifndef POINT3D_TEST_CPP_

#define POINT3D_TEST_CPP_

#include <string.h>
#include "../src/core/Point3D.h"

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE (Point3D_test) // le nom de la série de test est Point3D_test


BOOST_AUTO_TEST_CASE (test_constructor) { // 
	Point3D<SN<float, char>> p1;
	Point3D<SN<double, char>> p2;
	Point3D<SN<int, char>> p3;
	Point3D<SN<float, float>> p4;
	Point3D<SN<int, int>> p5;
	BOOST_CHECK(p1.x == (SN<float, char>)0 && p1.y == (SN<float, char>)0 && p1.z == (SN<float, char>)0);
	BOOST_CHECK(p2.x == (SN<double, char>)0 && p2.y == (SN<double, char>)0 && p2.z == (SN<double, char>)0);
	BOOST_CHECK(p3.x == (SN<int, char>)0 && p3.y == (SN<int, char>)0 && p3.z == (SN<int, char>)0);
	BOOST_CHECK(p4.x == (SN<float, float>)0 && p4.y == (SN<float, float>)0 && p4.z == (SN<float, float>)0);
	BOOST_CHECK(p5.x == (SN<int, int>)0 && p5.y == (SN<int, int>)0 && p5.z == (SN<int, int>)0);
}

/*BOOST_AUTO_TEST_CASE (test_recal) { // 
	SN<float, char> nb1={10, 2};
	nb1.recal();
	BOOST_CHECK(nb1.m == 1 && nb1.e == 3);
	
	nb1=SN<float, char>{-10, 2};
	nb1.recal();
	BOOST_CHECK(nb1.m == -1 && nb1.e == 3);
	
	nb1=SN<float, char>{-1000, -2};
	nb1.recal();
	BOOST_CHECK(nb1.m == -1 && nb1.e == 1);
}*/

BOOST_AUTO_TEST_CASE (test_operator_equal) { // 
	Point3D<SN<float, char>> p1={{1,2},{1,2},{1,2}};
	Point3D<SN<float, char>> p2={{1,2},{1,2},{1,2}};
	BOOST_CHECK(p1 == p2);
}

BOOST_AUTO_TEST_CASE (test_operator_not_equal) { // 
	Point3D<SN<float, char>> p1={{1,2},{1,2},{1,2}};
	Point3D<SN<float, char>> p2={{-1,2},{2,2},{3,2}};
	BOOST_CHECK(p1 != p2);
}


BOOST_AUTO_TEST_SUITE_END( )




#endif /* POINT3D_TEST_CPP_ */
