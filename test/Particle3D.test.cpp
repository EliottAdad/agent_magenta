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
		// SN
		BOOST_TEST_MESSAGE("setup fixture");
		pp=new Particle3D<SN<float, char>>();
	}
	~FParticle3D() {
		BOOST_TEST_MESSAGE("teardown fixture");
		delete pp;
	}
};




BOOST_FIXTURE_TEST_SUITE (Particle3D_test, FParticle3D) // The name of this serie is Particle3D_test


	BOOST_AUTO_TEST_CASE (test_constructor_default) { //
		// Checking position
		SN<float, char> x{0, 0};
		SN<float, char> y{0, 0};
		SN<float, char> z{0, 0};
		Point3D<SN<float, char>> p{SN<float, char>{0, 0}, SN<float, char>{0, 0}, SN<float, char>{0, 0}};
		BOOST_CHECK(pp->getX()==x);
		BOOST_CHECK(pp->getY()==y);
		BOOST_CHECK(pp->getZ()==z);
		BOOST_CHECK(pp->getPosition()==p);
		// Checking speed
		Vector3D<SN<float, char>> v(Point3D<SN<float, char>>{{0,0}, {0,0}, {0,0}});//v={0, 0, 0}
		BOOST_CHECK(pp->getSpeed()==v);
		BOOST_CHECK(pp->getRotSpeed()==v);
		// Checking points to render
		CoordinateSystem3D<SN<float, char>> coord_system;
		BOOST_CHECK(pp->getPPoints(coord_system).size()==1);
		// Checking TimeSensitive methods
		BOOST_CHECK(pp->getT() == 0);
		pp->setT(1);
		pp->apply();
	}

	BOOST_AUTO_TEST_CASE (test_constructor2) { //
		Point3D<SN<float, char>> p{SN<float, char>{-1, 0}, SN<float, char>{1, 0}, SN<float, char>{-3, 0}};
		SN<float, char> w{1, 10};
		std::shared_ptr<Particle3D<SN<float, char>>> pp2=std::make_shared<Particle3D<SN<float, char>>>(p, w);

		// Checking position
		SN<float, char> x{-1, 0};
		SN<float, char> y{1, 0};
		SN<float, char> z{-3, 0};
		BOOST_CHECK(pp2->getX()==x);
		BOOST_CHECK(pp2->getY()==y);
		BOOST_CHECK(pp2->getZ()==z);
		BOOST_CHECK(pp2->getPosition()==p);
		// Checking speed
		Vector3D<SN<float, char>> v(Point3D<SN<float, char>>{{0,0}, {0,0}, {0,0}});//v={0, 0, 0}
		BOOST_CHECK(pp2->getSpeed()==v);
		BOOST_CHECK(pp2->getRotSpeed()==v);
		// Checking points to render
		CoordinateSystem3D<SN<float, char>> coord_system;
		BOOST_CHECK(pp2->getPPoints(coord_system).size()==1);
		// Checking TimeSensitive methods
		BOOST_CHECK(pp2->getT() == 0);
		pp2->setT(1);
		pp2->apply();
	}

	BOOST_AUTO_TEST_CASE (test_constructor3) { //
		SN<float, char> x{-1, 0};
		SN<float, char> y{1, 0};
		SN<float, char> z{-3, 0};
		Point3D<SN<float, char>> p{x, y, z};
		SN<float, char> w{1, 10};
		std::shared_ptr<Particle3D<SN<float, char>>> pp2=std::make_shared<Particle3D<SN<float, char>>>(x, y, z, w);

		// Checking position
		BOOST_CHECK(pp2->getX()==x);
		BOOST_CHECK(pp2->getY()==y);
		BOOST_CHECK(pp2->getZ()==z);
		BOOST_CHECK(pp2->getPosition()==p);
		// Checking speed
		Vector3D<SN<float, char>> v(Point3D<SN<float, char>>{{0,0}, {0,0}, {0,0}});//v={0, 0, 0}
		BOOST_CHECK(pp2->getSpeed()==v);
		BOOST_CHECK(pp2->getRotSpeed()==v);
		// Checking points to render
		CoordinateSystem3D<SN<float, char>> coord_system;
		BOOST_CHECK(pp2->getPPoints(coord_system).size()==1);
		// Checking TimeSensitive methods
		BOOST_CHECK(pp2->getT() == 0);
		pp2->setT(1);
		pp2->apply();
	}

	BOOST_AUTO_TEST_CASE (test_getMass_default_constructor_Particle3D) { //
		SN<float, char> mass{1, 0};
		BOOST_CHECK(getMass(*pp) == mass);
	}

	BOOST_AUTO_TEST_CASE (test_getMass_constructor3_Particle3D) { //
		SN<float, char> x{-1, 0};
		SN<float, char> y{1, 0};
		SN<float, char> z{-3, 0};
		SN<float, char> w{1, 10};
		std::shared_ptr<Particle3D<SN<float, char>>> pp2=std::make_shared<Particle3D<SN<float, char>>>(x, y, z, w);
		BOOST_CHECK(getMass(*pp2) == w);
	}

	BOOST_AUTO_TEST_CASE (test_operator_plus_equal) { //
		SN<float, char> x{-1, 0};
		SN<float, char> y{1, 0};
		SN<float, char> z{-3, 0};
		Point3D<SN<float, char>> p{x, y, z};
		SN<float, char> w{1, 1};
		std::shared_ptr<Particle3D<SN<float, char>>> pp2=std::make_shared<Particle3D<SN<float, char>>>(x, y, z, w);

		*pp2+=*pp;

		SN<float, char> w_result{11, 0};
		BOOST_CHECK(getMass(*pp2) == w_result);
	}

	/*BOOST_AUTO_TEST_CASE (test_operator_not_equal) { //
		Point3D<SN<float, char>> p1={{1,2},{1,2},{1,2}};
		Point3D<SN<float, char>> p2={{-1,2},{2,2},{3,2}};
		BOOST_CHECK(p1 != p2);
	}*/


BOOST_AUTO_TEST_SUITE_END()




#endif /* PARTICLE3D_TEST_CPP_ */
