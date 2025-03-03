/*
 * Display3D.test.cpp
 *
 *  Created on: 7 mai 2024
 *      Author: esn
 */

#ifndef DISPLAY3D_TEST_CPP_

#define DISPLAY3D_TEST_CPP_

#include <boost/test/unit_test.hpp>
#include <string.h>

#include "../src/display/utils_Display3D.hpp"
#include "../src/core/utils_Particle3D.hpp"
#include "../src/display/functions_display.hpp"



struct FDisplay3D {
	Display3D<SN<float, char>>* pd;
	
	FDisplay3D() {
		BOOST_TEST_MESSAGE("setup fixture");
		initSDL();
		pd=new Display3D<SN<float, char>>();
	}
	~FDisplay3D() {
		BOOST_TEST_MESSAGE("teardown fixture");
		delete pd;
	}
};


BOOST_FIXTURE_TEST_SUITE (Display3D_test, FDisplay3D) // The name of this serie is Display3D_test
	
	BOOST_AUTO_TEST_CASE (test_constructor) { //
		//Display1<SN<float, char>> display;
	}

	BOOST_AUTO_TEST_CASE (test_setT) { //
		//BOOST_CHECK(false);
		std::unordered_set<std::shared_ptr<Particle3D<SN<float, char>>>> pparts;
		pparts=generate2DGridParticle3D(Point3D<SN<float, char>>{{2,1},{0,0},{0,0}}, SN<float, char>{2,3}, 5, SN<float, char>{1, 18});

		// Init SDL
		initSDL();


		pd->scale=0.15;
		pd->fps=40;

		//g1.pscene->addPDisplayable(psys);// Not sure it works properly.
		for (std::shared_ptr<Particle3D<SN<float, char>>> ppart : pparts){
			pd->renderDisplayable(*ppart);
		}

		pd->setT(10);
		//SDL_Delay(1000);
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
			pd->renderDisplayable(*ppart);
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
			pd->renderDisplayable(*ppart);
		}

		pd->run(10);
		SDL_Delay(1000);

	
	}


BOOST_AUTO_TEST_SUITE_END()




#endif /* DISPLAY3D_TEST_CPP_ */
