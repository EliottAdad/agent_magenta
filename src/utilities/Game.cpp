/*
 * Game.cpp
 *
 *  Created on: 7 nov. 2024
 *      Author: esn
 */

#include "Game.h"

Game::Game() {
	m_pwindow=SDL_CreateWindow("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 600, 600, SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN_DESKTOP);
	m_prenderer=SDL_CreateRenderer(m_pwindow, 0, SDL_RENDERER_TARGETTEXTURE);

	m_pphysics=new Physics();
	m_pscene=new Scene();
	m_pdisplay=new Display1(m_pwindow, m_prenderer);
	m_pdisplay->addPScene(m_pscene);					// Will render the unique scene for this game

	m_fps=30;
	//m_pps=30;
	m_fpause=false;
}

Game::~Game() {
	delete m_pphysics;
	delete m_pscene;
	delete m_pdisplay;
}

/*Game::Game(const Game &other) {
	// TODO Auto-generated constructor stub

}*/


unsigned int Game::getFPS() const {
	return m_fps;
}

void Game::setFPS(const unsigned int& fps) {
	m_fps=fps;
}

unsigned int Game::getPPS() const {
	return m_pphysics->getPPS();
}

void Game::setPPS(const unsigned int& pps) {
	m_pphysics->setPPS(pps);
}

Scene* Game::getPScene() {
	return m_pscene;
}

Physics* Game::getPPhysics() {
	return m_pphysics;
}

std::unordered_set<TimeSensitive*> Game::getPTimeSensitives() {
	return m_pphysics->getPTimeSensitives();
}

bool Game::addPTimeSensitive(TimeSensitive* ptime_sensitive) {
	bool success=false;
	if (ptime_sensitive!=NULL){
		success=m_pphysics->addPTimeSensitive(ptime_sensitive);
	}
	return success;
}


bool Game::run(const unsigned int& steps){
	std::chrono::time_point t1=std::chrono::system_clock::now();
	if (!m_fpause){
		unsigned int i(0);
		while (i<=steps){
			std::chrono::time_point t2=std::chrono::system_clock::now();
			std::chrono::duration dt=t2-t1;

			// Calls the physics
			if (dt.count()>=1/(long double)(m_pphysics->getPPS())*1000000000.){//The duration given by dt is in ns.
				m_pphysics->iterate(dt.count()/1000000000.);//The duration given by dt is in ns.
			}

			// Calls the rendering process
			if (dt.count()>=1/(long double)m_fps*1000000000.){
				render();

				t1=t2;
				if (steps!=0){//If steps is not null
					i++;
				}
			}
		}
	}
	return m_fpause;
}

bool Game::render() const {
	// Fill the background with the background color
	SDL_SetRenderDrawColor(m_pdisplay->getPRenderer(), m_pdisplay->getPBkgdColor()->r, m_pdisplay->getPBkgdColor()->g, m_pdisplay->getPBkgdColor()->b, m_pdisplay->getPBkgdColor()->a);
	SDL_RenderClear(m_pdisplay->getPRenderer());

	m_pdisplay->render();

	SDL_RenderPresent(m_pdisplay->getPRenderer());

	return m_fpause;
}
