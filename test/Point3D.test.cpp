/*
 * Point3D.test.cpp
 *
 *  Created on: 7 mai 2024
 *      Author: esn
 */

#ifndef POINT3D_TEST_CPP_

#define POINT3D_TEST_CPP_

#include <boost/test/unit_test.hpp>
#include <string.h>

#include "../src/core/utils_Point3D.hpp"


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

BOOST_AUTO_TEST_CASE (test_getDistance) { // 
	Point3D<SN<float, char>> p1={{3,2},{4,2},{0,0}};
	Point3D<SN<float, char>> p2={{3,2},{0,0},{0,0}};
	Point3D<SN<float, char>> p3={{0,0},{4,2},{0,0}};
	SN<float, char> answ={5,2};
	BOOST_CHECK(getDistance(p1) == answ);
	BOOST_CHECK(getDistance(p2, p3) == answ);
}

BOOST_AUTO_TEST_CASE (test_toEigen) { // 
	Point3D<SN<float, char>> p1={{1,2},{-1,2},{2,2}};
	Eigen::Matrix<SN<float, char>, 3, 1> pimg=toEigen(p1);
	BOOST_CHECK(pimg[0] == p1.x);
	BOOST_CHECK(pimg[1] == p1.y);
	BOOST_CHECK(pimg[2] == p1.z);
}

BOOST_AUTO_TEST_CASE (test_toPoint) { // 
	Eigen::Matrix<SN<float, char>, 3, 1> p1={SN<float, char>{1,2},SN<float, char>{1,2},SN<float, char>{1,2}};
	Point3D<SN<float, char>> pimg=toPoint(p1);
	BOOST_CHECK(pimg.x == p1[0]);
	BOOST_CHECK(pimg.y == p1[1]);
	BOOST_CHECK(pimg.z == p1[2]);
}


BOOST_AUTO_TEST_SUITE_END( )




#endif /* POINT3D_TEST_CPP_ */
