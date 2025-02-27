/*
 * TimeManager.test.cpp
 *
 *  Created on: 7 mai 2024
 *      Author: esn
 */

#ifndef TIME_MANAGER_TEST_CPP_

#define TIME_MANAGER_TEST_CPP_

#include <boost/test/unit_test.hpp>
#include <string.h>

#include "../src/core/utils_TimeManager.hpp"
#include "../src/core/utils_Particle3D.hpp"



struct FTimeManager {
	TimeManager* ptm;
	
	FTimeManager() {
		BOOST_TEST_MESSAGE("setup fixture");
		ptm=new TimeManager();
	}
	~FTimeManager() {
		BOOST_TEST_MESSAGE("teardown fixture");
		delete ptm;
	}
};


BOOST_FIXTURE_TEST_SUITE (Physics_test, FPhysics) // The name of this serie is Physics_test


	/*BOOST_AUTO_TEST_CASE (test_constructor) { // 
		Physics ph;
	}*/

	BOOST_AUTO_TEST_CASE (test_insert) { // 
		//std::shared_ptr<Particle3D<SN<float, char>>> pp=std::make_shared<Particle3D<SN<float, char>>>();
		//pph->add(pp);
		
		/*for (std::shared_ptr<TimeSensitive> ppart : pph->get()){
			BOOST_CHECK(ppart == pp);
		}*/
	}

	BOOST_AUTO_TEST_CASE (test_run) { // 
		
		ptm->run(1);
		
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




#endif /* TIME_MANAGER_TEST_CPP_ */
