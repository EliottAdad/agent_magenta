/*
 * Game3D.hpp
 *
 *  Created on: 7 nov. 2024
 *      Author: esn
 */

#ifndef GAME3D_HPP_

#define GAME3D_HPP_

#include <memory>
#include <unordered_set>
#include <thread>

#include "../core/Physics.hpp"
#include "../core/Point3D.hpp"
#include "../core/Scene3D.hpp"
#include "../display/Display1.hpp"
//#include "../display/Display2.hpp"
//#include "Printable.hpp"
#include "functions_display.hpp"

/*
 * #############
 *  Game3D<T> :)
 * #############
 * Contains a scene, a physics management system, and a display.
 */
template<typename T> class Game3D {
public:
	bool fpause;

	std::shared_ptr<WINDOW> pwindow;				// Pointeur to the window.
	std::shared_ptr<RENDERER> prenderer;			// Pointeur to the renderer.
	std::shared_ptr<Physics> pphysics;
	std::shared_ptr<Scene3D<T>> pscene;					// A scene
	std::shared_ptr<Display1<T>> pdisplay;

	Game3D();
	virtual ~Game3D();
	//Game3D(const Game3D& game);

	bool run(const unsigned int& steps=1);	// Runs a certain number of frames
	//bool iterate(const float& dt);	// Renders once (à faire)
	bool render() const;					// Draws the content of the game on the screen
};





template<typename T> inline Game3D<T>::Game3D() {
	pwindow=createWindow();
	if (pwindow!=NULL){
		prenderer=createRenderer(pwindow);
	}

	pphysics=std::make_shared<Physics>();
	pscene=std::make_shared<Scene3D<SN<float, char>>>();
	pdisplay=std::make_shared<Display1<T>>(pwindow, prenderer);
	pdisplay->addPScene(pscene);					// Will render the unique scene for this game

	//fps=30;
	fpause=false;
	//render();
}

template<typename T> inline Game3D<T>::~Game3D() {
	;
}

/*Game::Game(const Game &other) {
	// TODO Auto-generated constructor stub

}*/


/**
 * Run the game for a certain number of frames
 */
template<typename T> inline bool Game3D<T>::run(const unsigned int& steps){
	SDL_Event event;
	bool quit=false;
	// The parameters to the function are put after the comma
	//std::thread thread_physics(&Physics::run, pphysics, 0);
	std::thread thread_display(&Display1<T>::run, pdisplay, 0);
	/*while(!quit){
		//reads inputs.
		switch (event.type){
			case SDL_QUIT:
				quit = true;
				break;
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym){
					case SDLK_LEFT:  quit=true; break;
					//case SDLK_RIGHT: x++; break;
					//case SDLK_UP:    y--; break;
					//case SDLK_DOWN:  y++; break;
				}
				break;
		}
		if (quit){
			std::terminate();
		}
	}*/
	//thread_physics.join();
	thread_display.join();

	/*
	std::chrono::time_point t1=std::chrono::system_clock::now();
	if (!fpause){
		unsigned int i(0);
		while (i<=steps){
			std::chrono::time_point t2=std::chrono::system_clock::now();
			std::chrono::duration dt=t2-t1;

			// Calls the physics
			if (dt.count()>=1/(long double)(pphysics->pps)*1000000000.){//The duration given by dt is in ns.
				pphysics->iterate(dt.count()/1000000000.);//The duration given by dt is in ns.
			}

			// Calls the rendering process
			if (dt.count()>=1/(long double)fps*1000000000.){
				//printf("FPS:%f\n", 1000000000./dt.count());

				render();

				t1=t2;
				if (steps!=0){//If steps is not null (allows for infinite loop when 0)
					i++;
				}
			}
		}
	}*/
	return fpause;
}

template<typename T> inline bool Game3D<T>::render() const {
	if (pdisplay!=NULL){
		pdisplay->render();
	}

	return fpause;
}



#endif /* GAME3D_HPP_ */
