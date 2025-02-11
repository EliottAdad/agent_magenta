/*
 * Mobile.test.cpp
 *
 *  Created on: 7 mai 2024
 *      Author: esn
 */

#ifndef MOBILE_TEST_CPP_

#define MOBILE_TEST_CPP_

#include <string.h>
#include "../src/core/Mobile.hpp"

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE (Mobile_test) // le nom de la série de test est Mobile_test


BOOST_AUTO_TEST_CASE (test_constructor) { // 
	Mobile<SN<float, char>> m1;
	BOOST_CHECK(m1.pcoord_system==NULL);
	BOOST_CHECK(m1.ps==NULL);
	BOOST_CHECK(m1.getX()==(float)0.);
	BOOST_CHECK(m1.getY()==(float)0.);
	BOOST_CHECK(m1.getZ()==(float)0.);
	Point3D<SN<float, char>> p{0,0,0};
	BOOST_CHECK(m1.getPosition()==p);
}

BOOST_AUTO_TEST_CASE (test_getters) { // 
	Mobile<SN<float, char>> m1;
	BOOST_CHECK(m1.getX()==(float)0.);
	BOOST_CHECK(m1.getY()==(float)0.);
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


BOOST_AUTO_TEST_SUITE_END( )




#endif /* MOBILE_TEST_CPP_ */
