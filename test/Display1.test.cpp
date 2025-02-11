/*
 * Display1.test.cpp
 *
 *  Created on: 7 mai 2024
 *      Author: esn
 */

#ifndef DISPLAY1_TEST_CPP_

#define DISPLAY1_TEST_CPP_

#include <string.h>
#include "../src/core/Oct.hpp"
#include "../src/geometry/Particle3D.hpp"

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE (Display_test) // The name of this serie is Display_test


BOOST_AUTO_TEST_CASE (test_constructor) { // 
	Display1<SN<float, char>> display;
}

BOOST_AUTO_TEST_CASE (test_render) { // 
	std::unordered_set<std::shared_ptr<Particle3D<SN<float, char>>>> pparts;
    pparts=generate2DGridParticle3D(Point3D<SN<float, char>>{{2,1},{0,0},{0,0}}, SN<float, char>{2,3}, 5, SN<float, char>{1, 18});
    
    // Init SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0){
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[DEBUG] > %s", SDL_GetError());
        return EXIT_FAILURE;
    }
    
	Display1<SN<float, char>> display;
	
    g1.pdisplay->scale=0.15;
    g1.pdisplay->fps=40;
    //g1.pdisplay->ppoint=pparts[0];

    //g1.pscene->addPDisplayable(psys);// Not sure it works properly.
    for (std::shared_ptr<Particle3D<SN<float, char>>> ppart : pparts){
        g1.pscene->addPDisplayable(ppart);
    }
    
	display.render(10);
	

}


BOOST_AUTO_TEST_SUITE_END( )




#endif /* DISPLAY1_TEST_CPP_ */
