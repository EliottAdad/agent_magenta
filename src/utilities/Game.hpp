/*
 * Game.hpp
 *
 *  Created on: 7 nov. 2024
 *      Author: esn
 */

#ifndef GAME_HPP_

#define GAME_HPP_

#include <memory>
#include <unordered_set>
#include <thread>

#include "../core/Physics.hpp"
#include "../core/Point3D.hpp"
#include "../core/Scene.hpp"
#include "../display/Display1.hpp"
#include "Printable.hpp"
#include "functions_display.hpp"

/*
 * ###########
 *  Game<T> :)
 * ###########
 * Contains a scene, a physics management system, and a display.
 */
template<typename T> class Game : public Printable {
public:
	bool fpause;

	std::shared_ptr<WINDOW> pwindow;				// Pointeur to the window.
	std::shared_ptr<RENDERER> prenderer;			// Pointeur to the renderer.
	std::shared_ptr<Physics> pphysics;
	std::shared_ptr<Scene<T>> pscene;					// A scene
	std::shared_ptr<Display1<T>> pdisplay;

	Game();
	virtual ~Game();
	//Game(const Game& game);

	bool run(const unsigned int& steps=1);	// Runs a certain number of frames
	//bool iterate(const float& dt);	// Renders once (à faire)
	bool render() const;					// Draws the content of the game on the screen

	// From Printable
	virtual std::string to_string(const bool& spread=false, const bool& full_info=false, const unsigned char& indent=0) const;// :)
	virtual void print(const bool& spread=false, const bool& full_info=false, const unsigned char& indent=0) const;// :)
};


template<typename T> Game<T>::Game() {
	pwindow=createWindow();
	if (pwindow!=NULL){
		prenderer=createRenderer(pwindow);
	}

	pphysics=std::make_shared<Physics>();
	pscene=std::make_shared<Scene<SN<float, char>>>();
	pdisplay=std::make_shared<Display1<T>>(pwindow, prenderer);
	pdisplay->addPScene(pscene);					// Will render the unique scene for this game

	//fps=30;
	fpause=false;
	//render();
}

template<typename T> Game<T>::~Game() {
	;
}

/*Game::Game(const Game &other) {
	// TODO Auto-generated constructor stub

}*/


/**
 * Run the game for a certain number of frames
 */
template<typename T> bool Game<T>::run(const unsigned int& steps){
	SDL_Event event;
	bool quit=false;
	// The parameters to the function are put after the comma
	std::thread thread_physics(&Physics::run, pphysics, 0);
	// The parameters to the function are put after the comma
	std::thread thread_display(&Display1<T>::run, pdisplay, 0);
	while(!quit){
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
	}
	thread_physics.join();
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

template<typename T> bool Game<T>::render() const {
	if (pdisplay!=NULL){
		pdisplay->render();
	}

	return fpause;
}


template<typename T> std::string Game<T>::to_string(const bool& spread, const bool& full_info, const unsigned char& indent) const {
	std::string mes=((spread)?"\n" : "");
	mes+=to_stringTabs(indent);

	mes+="GAME[";
	std::stringstream ss;
	ss << this;
	mes+=ss.str();
	mes+="]:\n";
	mes+=to_stringTabs(indent+1);
	//mes+="fps=" + to_string(fps);
	mes+=("fpause=" + to_string(fpause));
	mes+=((spread)?"\n" : "");

	if (full_info){
		//mes+=pscene->to_string(spread, full_info, indent+1);
		//mes+=pphysics->to_string(spread, full_info, indent+1);
	}

	return mes;
}

template<typename T> void Game<T>::print(const bool& spread, const bool& full_info, const unsigned char& indent) const {
	printTabs(indent);
	std::cout << this->to_string(spread, full_info, indent);
}

#endif /* GAME_HPP_ */
