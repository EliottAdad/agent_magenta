/*
 * SN.test.cpp
 *
 *  Created on: 7 mai 2024
 *      Author: esn
 */

#ifndef SN_TEST_CPP_

#define SN_TEST_CPP_

#include <string.h>
#include "../src/core/SN.h"

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE (SN_test) // le nom de la série de test est SN_test


BOOST_AUTO_TEST_CASE (test_constructor) { // 
	SN<float, char> nb1;
	SN<double, char> nb2;
	SN<int, char> nb3;
	SN<float, float> nb4;
	SN<int, int> nb5;
	BOOST_CHECK(nb1.m == 0 && nb1.e == 0);
	BOOST_CHECK(nb2.m == 0 && nb2.e == 0);
	BOOST_CHECK(nb3.m == 0 && nb3.e == 0);
	BOOST_CHECK(nb4.m == 0 && nb4.e == 0);
	BOOST_CHECK(nb5.m == 0 && nb5.e == 0);
}

BOOST_AUTO_TEST_CASE (test_recal) { // 
	SN<float, char> nb1={10, 2};
	nb1.recal();
	BOOST_CHECK(nb1.m == 1 && nb1.e == 3);
	
	nb1=SN<float, char>{-10, 2};
	nb1.recal();
	BOOST_CHECK(nb1.m == -1 && nb1.e == 3);
	
	nb1=SN<float, char>{-1000, -2};
	nb1.recal();
	BOOST_CHECK(nb1.m == -1 && nb1.e == 1);
	
	nb1=SN<float, char>{1, -1};
	nb1.recal();
	BOOST_CHECK(nb1.m == 1 && nb1.e == -1);
	
	nb1=SN<float, char>{0.1, -2};
	nb1.recal();
	BOOST_CHECK(nb1.m == 1 && nb1.e == -3);
	
	nb1=SN<float, char>{0.02, 3};
	nb1.recal();
	BOOST_CHECK(nb1.m == 2 && nb1.e == 1);
	//nb1.print(true, true, 0);					//////////////////////////////
}

BOOST_AUTO_TEST_CASE (test_operator_equal) { // 
	SN<float, char> nb1={1, 2};
	SN<float, char> nb2={1, 2};
	BOOST_CHECK(nb1 == nb2);
}

BOOST_AUTO_TEST_CASE (test_operator_not_equal) { // 
	SN<float, char> nb1={1, 2};
	SN<float, char> nb3={7, 2};
	BOOST_CHECK(nb1 != nb3);
}

BOOST_AUTO_TEST_CASE (test_operator_plus_equal) { // 
	SN<float, char> nb1={1, 20};
	SN<float, char> nb2={7, 19};
	SN<float, char> rslt={1.7, 20};

	nb1+=nb2;								//{1.7,20}
	
	BOOST_CHECK(nb1 == rslt);
}

BOOST_AUTO_TEST_CASE (test_operator_minus_equal) { // 
	SN<float, char> nb1={1, 20};
	SN<float, char> nb2={9.9, 19};
	SN<float, char> rslt1={1, 18};

	nb1-=nb2;
	//nb1.print(true, true, 0);				//////////////////////////////////////
	BOOST_CHECK(nb1 == rslt1);
	
}

BOOST_AUTO_TEST_CASE (test_operator_mult_equal) { // 
	SN<float, char> nb1={1, 20};
	SN<float, char> nb2={7, 19};
	SN<float, char> rslt={7, 39};

	nb1*=nb2;								//{7,39}
	
	BOOST_CHECK(nb1 == rslt);
}


BOOST_AUTO_TEST_SUITE_END( )



#endif /* SN_TEST_CPP_ */
