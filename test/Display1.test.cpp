/*
 * Display1.test.cpp
 *
 *  Created on: 7 mai 2024
 *      Author: esn
 */

#ifndef DISPLAY1_TEST_CPP_

#define DISPLAY1_TEST_CPP_

#include <string.h>
#include "../src/display/Display1.hpp"
#include "../src/core/Particle3D.hpp"
#include "../src/core/functions_Particle3D.hpp"
#include "../src/display/functions_display.hpp"

#include <boost/test/unit_test.hpp>


struct FDisplay1 {
	Display1<SN<float, char>>* pd;
	
	FDisplay1() {
		BOOST_TEST_MESSAGE("setup fixture");
		initSDL();
		pd=new Display1<SN<float, char>>();
	}
	~FDisplay1() {
		BOOST_TEST_MESSAGE("teardown fixture");
		delete pd;
	}
};


BOOST_FIXTURE_TEST_SUITE (Display1_test, FDisplay1) // The name of this serie is Display1_test
	
	BOOST_AUTO_TEST_CASE (test_constructor) { //
		//Display1<SN<float, char>> display;
	}

	BOOST_AUTO_TEST_CASE (test_setT) { //
		BOOST_CHECK(false);
		std::unordered_set<std::shared_ptr<Particle3D<SN<float, char>>>> pparts;
		pparts=generate2DGridParticle3D(Point3D<SN<float, char>>{{2,1},{0,0},{0,0}}, SN<float, char>{2,3}, 5, SN<float, char>{1, 18});

		// Init SDL
		initSDL();


		pd->scale=0.15;
		pd->fps=40;

		//g1.pscene->addPDisplayable(psys);// Not sure it works properly.
		for (std::shared_ptr<Particle3D<SN<float, char>>> ppart : pparts){
			pd->renderDisplayable(ppart);
		}

		pd->setT(10);
		SDL_Delay(1000);

		BOOST_CHECK(false);


	}
	BOOST_AUTO_TEST_CASE (test_render) { //
		std::unordered_set<std::shared_ptr<Particle3D<SN<float, char>>>> pparts;
		pparts=generate2DGridParticle3D(Point3D<SN<float, char>>{{2,1},{0,0},{0,0}}, SN<float, char>{2,3}, 5, SN<float, char>{1, 18});

		// Init SDL
		initSDL();


		pd->scale=0.15;
		pd->fps=40;

		//g1.pscene->addPDisplayable(psys);// Not sure it works properly.
		for (std::shared_ptr<Particle3D<SN<float, char>>> ppart : pparts){
			pd->renderDisplayable(ppart);
		}

		SDL_Delay(1000);
		//pd->run(10);

	
	}

	BOOST_AUTO_TEST_CASE (test_run) { //
		std::unordered_set<std::shared_ptr<Particle3D<SN<float, char>>>> pparts;
		pparts=generate2DGridParticle3D(Point3D<SN<float, char>>{{2,1},{0,0},{0,0}}, SN<float, char>{2,3}, 5, SN<float, char>{1, 18});

		// Init SDL
		initSDL();


		pd->scale=0.15;
		pd->fps=40;

		//g1.pscene->addPDisplayable(psys);// Not sure it works properly.
		for (std::shared_ptr<Particle3D<SN<float, char>>> ppart : pparts){
			pd->renderDisplayable(ppart);
		}

		pd->run(10);
		SDL_Delay(1000);

	
	}


BOOST_AUTO_TEST_SUITE_END()




#endif /* DISPLAY1_TEST_CPP_ */
