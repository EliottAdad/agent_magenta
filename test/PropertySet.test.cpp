/*
 * PropertySet.test.cpp
 *
 *  Created on: 7 mai 2024
 *      Author: esn
 */

#ifndef PROPERTYSET_TEST_CPP_

#define PROPERTYSET_TEST_CPP_

#include <boost/test/unit_test.hpp>
#include <string.h>

#include "../src/core/utils_PropertySet.hpp"
#include "../src/core/utils_Particle3D.hpp"
#include "../src/core/utils_SN.hpp"



struct FPropertySet {
	PropertySet<Particle3D<SN<float, char>>, SN<float, char>>* pps;
	
	FPropertySet() {
		BOOST_TEST_MESSAGE("setup fixture");
		pps=new PropertySet<Particle3D<SN<float, char>>, SN<float, char>>();
	}
	~FPropertySet() {
		BOOST_TEST_MESSAGE("teardown fixture");
		delete pps;
	}
};


BOOST_FIXTURE_TEST_SUITE (PropertySet_test, FPropertySet) // The name of this serie is PropertySet_test

	BOOST_AUTO_TEST_CASE (test_insert) { // 
		pps->add("mass", std::make_shared<SN<float, char>>());
	}

	BOOST_AUTO_TEST_CASE (test_target) { // 
		Particle3D<SN<float, char>> p;
		pps->ptarget=&p;
		
		BOOST_CHECK(pps->ptarget == &p);
	}


BOOST_AUTO_TEST_SUITE_END()




#endif /* PROPERTYSET_TEST_CPP_ */
