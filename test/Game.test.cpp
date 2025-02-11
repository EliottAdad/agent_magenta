/*
 * Game.test.cpp
 *
 *  Created on: 7 mai 2024
 *      Author: esn
 */

#ifndef GAME_TEST_CPP_

#define GAME_TEST_CPP_

#include <string.h>
#include "../src/utilities/Game.hpp"
#include "../src/geometry/Particle3D.hpp"

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE (Game_test) // The name of this serie is Game_test


BOOST_AUTO_TEST_CASE (test_constructor) { // 
	Game<SN<float, char>> game;
}

/*BOOST_AUTO_TEST_CASE (test_insert) { // 
	Oct<Particle3D<SN<float, char>>, SN<float, char>> oct;
	std::shared_ptr<Particle3D<SN<float, char>>> pp=std::make_shared<Particle3D<SN<float, char>>>();
	oct.insert(pp);
	
	for (std::shared_ptr<Particle3D<SN<float, char>>> ppart : oct.getPElements()){
		BOOST_CHECK(ppart == pp);
	}
	
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


BOOST_AUTO_TEST_SUITE_END( )




#endif /* GAME_TEST_CPP_ */
