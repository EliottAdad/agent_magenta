/*
 * Particle3D.test.cpp
 *
 *  Created on: 7 mai 2024
 *      Author: esn
 */

#ifndef PARTICLE3D_TEST_CPP_

#define PARTICLE3D_TEST_CPP_

#include <boost/test/unit_test.hpp>
#include <string.h>

#include "../src/core/utils_Particle3D.hpp"


struct FParticle3D {
	Particle3D<SN<float, char>>* pp;

	FParticle3D() {
		BOOST_TEST_MESSAGE("setup fixture");
		pp=new Particle3D<SN<float, char>>();
	}
	~FParticle3D() {
		BOOST_TEST_MESSAGE("teardown fixture");
		delete pp;
	}
};




BOOST_FIXTURE_TEST_SUITE (Particle3D_test, FParticle3D) // The name of this serie is Particle3D_test


	BOOST_AUTO_TEST_CASE (test_constructor) { //
		pp;
		/*Vector3D<SN<float, char>> v1;
		Vector3D<SN<double, char>> v2;
		Vector3D<SN<int, char>> v3;
		Vector3D<SN<float, float>> v4;
		Vector3D<SN<int, int>> v5;
		BOOST_CHECK(p1.x == (SN<float, char>)0 && p1.y == (SN<float, char>)0 && p1.z == (SN<float, char>)0);
		BOOST_CHECK(p2.x == (SN<double, char>)0 && p2.y == (SN<double, char>)0 && p2.z == (SN<double, char>)0);
		BOOST_CHECK(p3.x == (SN<int, char>)0 && p3.y == (SN<int, char>)0 && p3.z == (SN<int, char>)0);
		BOOST_CHECK(p4.x == (SN<float, float>)0 && p4.y == (SN<float, float>)0 && p4.z == (SN<float, float>)0);
		BOOST_CHECK(p5.x == (SN<int, int>)0 && p5.y == (SN<int, int>)0 && p5.z == (SN<int, int>)0);*/
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

	/*BOOST_AUTO_TEST_CASE (test_operator_equal) { //
		Point3D<SN<float, char>> p1={{1,2},{1,2},{1,2}};
		Point3D<SN<float, char>> p2={{1,2},{1,2},{1,2}};
		BOOST_CHECK(p1 == p2);
	}

	BOOST_AUTO_TEST_CASE (test_operator_not_equal) { //
		Point3D<SN<float, char>> p1={{1,2},{1,2},{1,2}};
		Point3D<SN<float, char>> p2={{-1,2},{2,2},{3,2}};
		BOOST_CHECK(p1 != p2);
	}*/


BOOST_AUTO_TEST_SUITE_END()




#endif /* TIMESENSITIVE_TEST_CPP_ */
