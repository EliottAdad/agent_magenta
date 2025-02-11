/*
 * Physics.test.cpp
 *
 *  Created on: 7 mai 2024
 *      Author: esn
 */

#ifndef PHYSICS_TEST_CPP_

#define PHYSICS_TEST_CPP_

#include <string.h>
#include "../src/core/Physics.hpp"
#include "../src/geometry/Particle3D.hpp"

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE (Physics_test) // The name of this serie is Physics_test


BOOST_AUTO_TEST_CASE (test_constructor) { // 
	Physics ph;
}

BOOST_FIXTURE_TEST_CASE (test_insert, fixture_test_insert) { // 
	Physics ph;
}

BOOST_AUTO_TEST_CASE (test_insert) { // 
	Physics ph;
	std::shared_ptr<Particle3D<SN<float, char>>> pp=std::make_shared<Particle3D<SN<float, char>>>();
	ph.add(pp);
	
	for (std::shared_ptr<TimeSensitive> ppart : ph.get()){
		BOOST_CHECK(ppart == pp);
	}
	
}

BOOST_AUTO_TEST_CASE (test_run) { // 
	Physics ph;
	std::shared_ptr<Particle3D<SN<float, char>>> pp=std::make_shared<Particle3D<SN<float, char>>>();
	ph.add(pp);
	
	for (std::shared_ptr<TimeSensitive> ppart : ph.get()){
		BOOST_CHECK(ppart == pp);
	}
	
	ph.run(1);
	
}

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


BOOST_AUTO_TEST_SUITE_END( )




#endif /* QUAD_TEST_CPP_ */
