/*
 * Quad.test.cpp
 *
 *  Created on: 7 mai 2024
 *      Author: esn
 */

#ifndef QUAD_TEST_CPP_

#define QUAD_TEST_CPP_

#include <boost/test/unit_test.hpp>
#include <string.h>

#include "../src/core/2D/Quad.hpp"
#include "../src/geometry/Particle3D.hpp"



struct FQuad {
	Quad<Particle3D<SN<float, char>>, SN<float, char>>* pquad;
	
	FQuad() {
		BOOST_TEST_MESSAGE("setup fixture");
		pquad=new Quad<Particle3D<SN<float, char>>, SN<float, char>>();
	}
	~FQuad() {
		BOOST_TEST_MESSAGE("teardown fixture");
		delete pquad;
	}
};



BOOST_FIXTURE_TEST_SUITE (Quad_test, FQuad) // The name of this serie is Quad_test


	BOOST_AUTO_TEST_CASE (test_constructor) { //
		Point3D<SN<float, char>> p(SN<float, char>{0,0}, SN<float, char>{0,0}, SN<float, char>{0,0});
		BOOST_CHECK(pquad->getBarycenter() == p);
		BOOST_CHECK(pquad->getPoint() == p);

		BOOST_CHECK(pquad->isLeaf() == true);
		BOOST_CHECK(pquad->isEmpty() == true);
	}

	BOOST_AUTO_TEST_CASE (test_insert) { //
		std::shared_ptr<Particle3D<SN<float, char>>> pp=std::make_shared<Particle3D<SN<float, char>>>();
		pquad->insert(pp);

		for (std::shared_ptr<Particle3D<SN<float, char>>> ppart : pquad->getPElements()){
			BOOST_CHECK(ppart == pp);
		}

	}

	BOOST_AUTO_TEST_CASE (test_isEmpty) { //

		BOOST_CHECK(true == pquad->isEmpty());

		std::shared_ptr<Particle3D<SN<float, char>>> pp1=std::make_shared<Particle3D<SN<float, char>>>();
		pquad->insert(pp1);
		/*std::shared_ptr<Particle3D<SN<float, char>>> pp2=std::make_shared<Particle3D<SN<float, char>>>(SN<float, char>{1,0}, SN<float, char>{-1,0}, SN<float, char>{1,0}, SN<float, char>{1,6});
		poct->insert(pp2);*/

		BOOST_CHECK(false == pquad->isEmpty());

		std::shared_ptr<Particle3D<SN<float, char>>> pp2=std::make_shared<Particle3D<SN<float, char>>>();
		pquad->insert(pp2);

		BOOST_CHECK(false == pquad->isEmpty());

		pquad->empty();

		BOOST_CHECK(true == pquad->isEmpty());
	}

	BOOST_AUTO_TEST_CASE (test_empty) { //
		std::shared_ptr<Particle3D<SN<float, char>>> pp1=std::make_shared<Particle3D<SN<float, char>>>();
		std::shared_ptr<Particle3D<SN<float, char>>> pp2=std::make_shared<Particle3D<SN<float, char>>>(SN<float, char>{1,0}, SN<float, char>{-1,0}, SN<float, char>{1,0}, SN<float, char>{1,6});

		pquad->insert(pp1);
		BOOST_CHECK(1 == pquad->getPElements().size());
		BOOST_CHECK(1 == pquad->getNB_QUADS());

		pquad->insert(pp2);
		BOOST_CHECK(2 == pquad->getPElements().size());
		BOOST_CHECK(3 == pquad->getNB_QUADS());

		pquad->empty();

		BOOST_CHECK(0 == pquad->getPElements().size());
		BOOST_CHECK(1 == pquad->getNB_QUADS());
	}

	BOOST_AUTO_TEST_CASE (test_getPElements) { //
		std::shared_ptr<Particle3D<SN<float, char>>> pp1=std::make_shared<Particle3D<SN<float, char>>>();
		pquad->insert(pp1);

		BOOST_CHECK(1 == pquad->getPElements().size());

		pquad->empty();

		std::shared_ptr<Particle3D<SN<float, char>>> pp2=std::make_shared<Particle3D<SN<float, char>>>(SN<float, char>{1,0}, SN<float, char>{-1,0}, SN<float, char>{1,0}, SN<float, char>{1,6});
		pquad->insert(pp1);
		pquad->insert(pp2);

		BOOST_CHECK(2 == pquad->getPElements().size());

		pquad->empty();

		std::shared_ptr<Particle3D<SN<float, char>>> pp3=std::make_shared<Particle3D<SN<float, char>>>();
		pquad->insert(pp1);
		auto ppart=pquad->insert(pp3);
		if (ppart!=NULL){
			ppart->print();
		}
		BOOST_CHECK(0 == pquad->getPElements().size());//PROBLEM should't work (cannot insert 2 p at origin(exact same coords)
		//BOOST_CHECK(1 == poct->getPElements().size());
		BOOST_CHECK(2 == pquad->getPElements().size());//  Should work
	}

	BOOST_AUTO_TEST_CASE (test_remove) { //
		std::shared_ptr<Particle3D<SN<float, char>>> pp=std::make_shared<Particle3D<SN<float, char>>>();

		BOOST_CHECK(pquad->remove(pp) == false);
		pquad->insert(pp);
		BOOST_CHECK(pquad->remove(pp) == true);
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




#endif /* QUAD_TEST_CPP_ */
