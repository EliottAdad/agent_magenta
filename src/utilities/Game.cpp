/*
 * Game.cpp
 *
 *  Created on: 7 nov. 2024
 *      Author: esn
 */

#include "Game.h"

Game::Game() {
	pwindow=createWindow();
	if (pwindow!=NULL){
		prenderer=createRenderer(pwindow);
	}

	pphysics=std::make_shared<Physics>();
	pscene=std::make_shared<Scene<SN<float, char>>>();
	pdisplay=std::make_shared<Display1<SN<float, char>>>(pwindow, prenderer);
	pdisplay->addPScene(pscene);					// Will render the unique scene for this game

	//fps=30;
	fpause=false;
	render();
}

Game::~Game() {
	;
}

/*Game::Game(const Game &other) {
	// TODO Auto-generated constructor stub

}*/


/**
 * Run the game for a certain number of frames
 */
bool Game::run(const unsigned int& steps){
	// The parameters to the function are put after the comma
	std::thread thread_physics(&Physics::run, pphysics, 0);
	// The parameters to the function are put after the comma
	//std::thread thread_display(&Display1<SN<float, char>>::render, pdisplay);
	while(1){
		//reads inputs.
	}
	thread_physics.join();
	//thread_display.join();

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

bool Game::render() const {
	if (pdisplay!=NULL){
		pdisplay->render();
	}

	return fpause;
}


std::string Game::to_string(const bool& spread, const bool& full_info, const unsigned char& indent) const {
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

void Game::print(const bool& spread, const bool& full_info, const unsigned char& indent) const {
	printTabs(indent);
	std::cout << this->to_string(spread, full_info, indent);
}
