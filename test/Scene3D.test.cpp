/*
 * Scene3D.test.cpp
 *
 *  Created on: 7 mai 2024
 *      Author: esn
 */

#ifndef SCENE3D_TEST_CPP_

#define SCENE3D_TEST_CPP_

#include <boost/test/unit_test.hpp>
#include <string.h>

#include "../src/core/utils_Scene3D.hpp"
#include "../src/core/utils_Particle3D.hpp"



struct FScene3D {
	Scene3D<SN<float, char>>* ps;
	
	FScene3D() {
		BOOST_TEST_MESSAGE("setup fixture");
		ps=new Scene3D<SN<float, char>>();
	}
	~FScene3D() {
		BOOST_TEST_MESSAGE("teardown fixture");
		delete ps;
	}
};


BOOST_FIXTURE_TEST_SUITE (Scene3D_test, FScene3D) // The name of this serie is Scene3D_test
	
	BOOST_AUTO_TEST_CASE (test_constructor) { //
		BOOST_CHECK(ps->getNbElements()==0);
		std::shared_ptr<Particle3D<SN<float, char>>> pp=std::make_shared<Particle3D<SN<float, char>>>();
		ps->add(pp);
		BOOST_CHECK(ps->getNbElements()==1);
		//BOOST_CHECK();
	}

	BOOST_AUTO_TEST_CASE (test_add) { //
		std::unordered_set<std::shared_ptr<Particle3D<SN<float, char>>>> pparts;
		pparts=generate2DGridParticle3D(Point3D<SN<float, char>>{{2,1},{0,0},{0,0}}, SN<float, char>{2,3}, 5, SN<float, char>{1, 18});

		//g1.pscene->addPDisplayable(psys);// Not sure it works properly.
		for (std::shared_ptr<Particle3D<SN<float, char>>> ppart : pparts){
			ps->add(ppart);
		}
	
		BOOST_CHECK(25 == ps->getNbElements());
	}

	BOOST_AUTO_TEST_CASE (test_remove) { //
		std::unordered_set<std::shared_ptr<Particle3D<SN<float, char>>>> pparts;
		pparts=generate2DGridParticle3D(Point3D<SN<float, char>>{{2,1},{0,0},{0,0}}, SN<float, char>{2,3}, 5, SN<float, char>{1, 18});

		for (std::shared_ptr<Particle3D<SN<float, char>>> ppart : pparts){
			ps->add(ppart);
		}

		int i=0;
		for (std::shared_ptr<Particle3D<SN<float, char>>> ppart : pparts){
			i++;
			if (i%2==1){
				ps->remove(ppart);
			}
		}
		//printf("%d", ps->getNbElements());
		BOOST_CHECK(12 == ps->getNbElements());
	}


BOOST_AUTO_TEST_SUITE_END()




#endif /* SCENE3D_TEST_CPP_ */
