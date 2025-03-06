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
	PropertySet<Particle3D<SN<float, char>>, float>* ppsf;
	
	FPropertySet() {
		BOOST_TEST_MESSAGE("setup fixture");
		pps=new PropertySet<Particle3D<SN<float, char>>, SN<float, char>>();
		ppsf=new PropertySet<Particle3D<SN<float, char>>, float>();
	}
	~FPropertySet() {
		BOOST_TEST_MESSAGE("teardown fixture");
		delete pps;
		delete ppsf;
	}
};


BOOST_FIXTURE_TEST_SUITE (PropertySet_test, FPropertySet) // The name of this serie is PropertySet_test

	BOOST_AUTO_TEST_CASE (test_add) { // 
		// SN
		pps->add("mass", std::make_shared<SN<float, char>>());
		pps->add("charge", std::make_shared<SN<float, char>>(1, 0));

		// Float
		ppsf->add("mass", 0.);
		ppsf->add("charge", 1.5);
	}
	
	BOOST_AUTO_TEST_CASE (test_get) { // 
		SN<float, char> nb1(0, 0);
		SN<float, char> nb2(1, 0);
		pps->add("mass", std::make_shared<SN<float, char>>());
		pps->add("charge", std::make_shared<SN<float, char>>(1, 0));
		BOOST_CHECK(nb1 == *pps->getP("mass"));
		BOOST_CHECK(nb2 == *pps->getP("charge"));
		// Float
		ppsf->add("mass", 0);
		ppsf->add("charge", 1.5);
		BOOST_CHECK(0 == ppsf->get("mass"));
		BOOST_CHECK(1.5 == ppsf->get("charge"));
	}

	BOOST_AUTO_TEST_CASE (test_target) { // 
		Particle3D<SN<float, char>> p;
		pps->ptarget=&p;
		
		BOOST_CHECK(pps->ptarget == &p);
	}


BOOST_AUTO_TEST_SUITE_END()




#endif /* PROPERTYSET_TEST_CPP_ */
