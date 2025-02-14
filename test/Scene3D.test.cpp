/*
 * Scene3D.test.cpp
 *
 *  Created on: 7 mai 2024
 *      Author: esn
 */

#ifndef SCENE3D_TEST_CPP_

#define SCENE3D_TEST_CPP_

#include <string.h>
#include "../src/core/Scene3D.hpp"
#include "../src/geometry/Particle3D.hpp"
#include "../src/utilities/functionsParticle3D.hpp"
//#include "../src/utilities/functions_display.hpp"

#include <boost/test/unit_test.hpp>


struct FScene3D {
	FScene3D<SN<float, char>>* ps;
	
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
		//Display1<SN<float, char>> display;
	}

	BOOST_AUTO_TEST_CASE (test_add) { //
		std::unordered_set<std::shared_ptr<Particle3D<SN<float, char>>>> pparts;
		pparts=generate2DGridParticle3D(Point3D<SN<float, char>>{{2,1},{0,0},{0,0}}, SN<float, char>{2,3}, 5, SN<float, char>{1, 18});

		// Init SDL
		init();


		ps->scale=0.15;
		ps->fps=40;

		//g1.pscene->addPDisplayable(psys);// Not sure it works properly.
		for (std::shared_ptr<Particle3D<SN<float, char>>> ppart : pparts){
			ps->add(ppart);
		}
	
		BOOST_CHECK(25 == ps->getNbElements());
	}


BOOST_AUTO_TEST_SUITE_END()




#endif /* SCENE3D_TEST_CPP_ */
