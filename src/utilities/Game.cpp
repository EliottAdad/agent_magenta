/*
 * Game.cpp
 *
 *  Created on: 7 nov. 2024
 *      Author: esn
 */

#include "Game.h"

Game::Game() {
	pwindow=std::shared_ptr<SDL_Window>(
			SDL_CreateWindow("Game",
					SDL_WINDOWPOS_CENTERED,
					SDL_WINDOWPOS_CENTERED,
					1200, 600,
					SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_FULLSCREEN_DESKTOP),
			SDL_DestroyWindow);
	if (pwindow!=NULL){
		prenderer=std::shared_ptr<SDL_Renderer>(
				SDL_CreateRenderer(pwindow.get(), 0, SDL_RENDERER_TARGETTEXTURE | SDL_RENDERER_ACCELERATED),
				SDL_DestroyRenderer);
	}

	pphysics=std::make_shared<Physics>();
	pscene=std::make_shared<Scene<SN<float, char>>>();
	pdisplay=std::make_shared<Display1<SN<float, char>>>(pwindow, prenderer);
	pdisplay->addPScene(pscene);					// Will render the unique scene for this game

	m_fps=30;
	//m_pps=30;
	m_fpause=false;

	//render();
}

Game::~Game() {
	;
}

/*Game::Game(const Game &other) {
	// TODO Auto-generated constructor stub

}*/


/*float Game::getSpeed() const {
	return pphysics->getSpeed();
}

void Game::setSpeed(const float& speed) {
	m_pphysics->setSpeed(speed);
}

unsigned char Game::getPPS() const {
	return m_pphysics->getPPS();
}

void Game::setPPS(const unsigned char& pps) {
	m_pphysics->setPPS(pps);
}*/

unsigned char Game::getFPS() const {
	return m_fps;
}

void Game::setFPS(const unsigned char& fps) {
	m_fps=fps;
}

/*Scene* Game::getPScene() {
	return m_pscene;
}

Physics* Game::getPPhysics() {
	return m_pphysics;
}*/

/*bool Game::addPDisplayable(std::shared_ptr<Displayable<SN<float, char>>> pdisplayable) {
	bool success=false;
	if (pdisplayable!=NULL){
		success=m_pscene->addPDisplayable(pdisplayable);
	}
	return success;
}*/

/*std::unordered_set<TimeSensitive*> Game::getPTimeSensitives() {
	return m_pphysics->getPTimeSensitives();
}*/

/*bool Game::addPTimeSensitive(std::shared_ptr<TimeSensitive> ptime_sensitive) {
	bool success=false;
	if (ptime_sensitive!=NULL){
		success=m_pphysics->addPTimeSensitive(ptime_sensitive);
	}
	return success;
}

bool Game::getFCollide() const {
	return m_pphysics->getFCollide();
}

void Game::setFCollide(const bool& fcollide) {
	m_pphysics->setFCollide(fcollide);
}*/

bool Game::getFPause() const {
	return m_fpause;
}

void Game::setFPause(const bool& fpause) {
	m_fpause=fpause;
}



/**
 * Run the game for a certain number of frames
 */
bool Game::run(const unsigned int& steps){
	std::chrono::time_point t1=std::chrono::system_clock::now();
	if (!m_fpause){
		unsigned int i(0);
		while (i<=steps){
			std::chrono::time_point t2=std::chrono::system_clock::now();
			std::chrono::duration dt=t2-t1;

			// Calls the physics
			if (dt.count()>=1/(long double)(pphysics->getPPS())*1000000000.){//The duration given by dt is in ns.
				pphysics->iterate(dt.count()/1000000000.);//The duration given by dt is in ns.
			}

			// Calls the rendering process
			if (dt.count()>=1/(long double)m_fps*1000000000.){
				render();

				t1=t2;
				if (steps!=0){//If steps is not null (allows for infinite loop when 0)
					i++;
				}
			}
		}
	}
	return m_fpause;
}

bool Game::render() const {
	if (pdisplay!=NULL){
		pdisplay->render();
	}

	return m_fpause;
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
	mes+="fps=" + to_string(m_fps);
	mes+=("fpause=" + to_string(m_fpause));
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
