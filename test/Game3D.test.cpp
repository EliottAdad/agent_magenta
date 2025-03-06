/*
 * Game3D.test.cpp
 *
 *  Created on: 7 mai 2024
 *      Author: esn
 */

#ifndef GAME3D_TEST_CPP_

#define GAME3D_TEST_CPP_

#include <boost/test/unit_test.hpp>
#include <string.h>

#include "../src/utilities/Game3D.hpp"
#include "../src/core/utils_Particle3D.hpp"




struct FGame3D {
	Game3D<SN<float, char>>* pg;
	
	FGame3D() {
		BOOST_TEST_MESSAGE("setup fixture");
		pg=new Game3D<SN<float, char>>();
	}
	~FGame3D() {
		BOOST_TEST_MESSAGE("teardown fixture");
		delete pg;
	}
};



BOOST_FIXTURE_TEST_SUITE (Game3D_test, FGame3D) // The name of this serie is Game3D_test



	BOOST_AUTO_TEST_CASE (test_constructor) { // 
		//BOOST_CHECK(1 == 0);
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


BOOST_AUTO_TEST_SUITE_END()




#endif /* GAME3D_TEST_CPP_ */
