/*
 * Game.cpp
 *
 *  Created on: 7 nov. 2024
 *      Author: esn
 */

#include "Game.h"

Game::Game() {
	physics=new Physics();
	display=new Display1<Point3D>();
}

Game::~Game() {
	// TODO Auto-generated destructor stub
	delete physics;
	delete display;
}

/*Game::Game(const Game &other) {
	// TODO Auto-generated constructor stub

}*/

