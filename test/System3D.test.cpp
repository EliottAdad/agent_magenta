/*
 * System3D.test.cpp
 *
 *  Created on: 7 mai 2024
 *      Author: esn
 */

#ifndef SYSTEM3D_TEST_CPP_

#define SYSTEM3D_TEST_CPP_

#include <boost/test/unit_test.hpp>
#include <string.h>

#include "../src/core/utils_System3D.hpp"
#include "../src/core/utils_Particle3D.hpp"



struct FSystem3D {
	System3D<Particle3D<SN<float, char>>, SN<float, char>>* psys;
	
	FSystem3D() {
		BOOST_TEST_MESSAGE("setup fixture");
		psys=new System3D<Particle3D<SN<float, char>>, SN<float, char>>();
	}
	~FSystem3D() {
		BOOST_TEST_MESSAGE("teardown fixture");
		delete psys;
	}
};


BOOST_FIXTURE_TEST_SUITE (System3D_test, FSystem3D) // The name of this serie is System3D_test


	/*BOOST_AUTO_TEST_CASE (test_constructor) { // 
		Physics ph;
	}*/

	BOOST_AUTO_TEST_CASE (test_insert) { //
		std::shared_ptr<Particle3D<SN<float, char>>> pp=std::make_shared<Particle3D<SN<float, char>>>();
		psys->insert(pp);
		
		for (std::shared_ptr<TimeSensitive> ppart : psys->getPElements()){
			BOOST_CHECK(ppart == pp);
		}
	}

	BOOST_AUTO_TEST_CASE (test_apply) { //
		
		psys->apply();
		
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


BOOST_AUTO_TEST_SUITE_END()




#endif /* SYSTEM3D_TEST_CPP_ */
