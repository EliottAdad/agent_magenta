/*
 * SN.test.cpp
 *
 *  Created on: 7 mai 2024
 *      Author: esn
 */

#ifndef SN_TEST_CPP_

#define SN_TEST_CPP_

#include <boost/test/unit_test.hpp>
#include <string.h>

#include "../src/core/utils_SN.hpp"


BOOST_AUTO_TEST_SUITE (SN_test) // le nom de la série de test est SN_test


BOOST_AUTO_TEST_CASE (test_constructor_default) { // 
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

BOOST_AUTO_TEST_CASE (test_constructor) { // 
	SN<float, char> nb1(1, -1);
	SN<double, char> nb2(1, -1);
	SN<int, char> nb3(1, -1);
	SN<float, float> nb4(1, -1);
	SN<int, int> nb5(1, -1);
	BOOST_CHECK(nb1.m == 1 && nb1.e == -1);
	BOOST_CHECK(nb2.m == 1 && nb2.e == -1);
	BOOST_CHECK(nb3.m == 1 && nb3.e == -1);
	BOOST_CHECK(nb4.m == 1 && nb4.e == -1);
	BOOST_CHECK(nb5.m == 1 && nb5.e == -1);
}

BOOST_AUTO_TEST_CASE (test_constructor2) { // 
	SN<float, char> nb1(12);
	SN<double, char> nb2(12);
	SN<int, char> nb3(12);
	SN<float, float> nb4(12);
	SN<int, int> nb5(12);
	/*print(nb1);
	printf("\n");
	print(nb2);
	printf("\n");
	print(nb3);
	printf("\n");
	print(nb4);
	printf("\n");
	print(nb5);
	printf("\n");*/
	BOOST_CHECK(nb1.m == (float)1.2 && nb1.e == (char)1);
	BOOST_CHECK(nb2.m == (double)1.2 && nb2.e == (char)1);
	BOOST_CHECK(nb3.m == (int)1 && nb3.e == (char)1);
	BOOST_CHECK(nb4.m == (float)1.2 && nb4.e == (float)1);
	BOOST_CHECK(nb5.m == (int)1 && nb5.e == (int)1);
}

BOOST_AUTO_TEST_CASE (test_constructor_copy) { // 
	SN<float, char> nb1(12);
	SN<float, char> nb1_c(nb1);
	SN<double, char> nb2(12);
	SN<double, char> nb2_c(nb2);
	SN<int, char> nb3(12);
	SN<int, char> nb3_c(nb3);
	SN<float, float> nb4(12);
	SN<float, float> nb4_c(nb4);
	SN<int, int> nb5(12);
	SN<int, int> nb5_c(nb5);
	BOOST_CHECK(nb1 == nb1_c);
	BOOST_CHECK(nb2 == nb2_c);
	BOOST_CHECK(nb3 == nb3_c);
	BOOST_CHECK(nb4 == nb4_c);
	BOOST_CHECK(nb5 == nb5_c);
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

BOOST_AUTO_TEST_CASE (test_to_m_type) { // 
	SN<float, char> nb1(12.1);
	SN<double, char> nb2(12.1);
	SN<int, char> nb3(12);
	SN<float, float> nb4(12.1);
	SN<int, int> nb5(12);
	BOOST_CHECK((float)12.1 == nb1.to_m_type());
	BOOST_CHECK((double)12.1 == nb2.to_m_type());
	BOOST_CHECK((int)10 == nb3.to_m_type());
	BOOST_CHECK((float)12.1 == nb4.to_m_type());
	BOOST_CHECK((int)10 == nb5.to_m_type());
}

BOOST_AUTO_TEST_CASE (test_operator_equal) { // 
	SN<float, char> nb1={1, 2};
	SN<float, char> nb2={3, 2};
	
	SN<float, char> nb2=nb1;
	BOOST_CHECK(nb2 == nb1);
	
	SN<float, char> nb2=(float)0.1;
	BOOST_CHECK(nb2.m == (float)1);
	BOOST_CHECK(nb2.e == (char)-1);
	
	SN<float, char> nb2=(int)1;
	BOOST_CHECK(nb2.m == (float)1);
	BOOST_CHECK(nb2.e == (char)-1);
}




BOOST_AUTO_TEST_CASE (test_operator_equal) { // 
	SN<float, char> nb1={1, 2};
	SN<float, char> nb2={1, 2};
	BOOST_CHECK(nb1 == nb2);
}

BOOST_AUTO_TEST_CASE (test_operator_equal_m_type) { // 
	SN<float, char> nb1={1, 2};
	SN<float, char> nb2={1, -2};
	BOOST_CHECK(nb1 == (float)100);
	BOOST_CHECK(nb2 == (float)0.01);
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
	SN<float, char> nb2={7, 20};
	SN<float, char> rslt1={-6, 20};

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
