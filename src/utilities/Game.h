/*
 * Game.h
 *
 *  Created on: 7 nov. 2024
 *      Author: esn
 */

#ifndef GAME_H_
#define GAME_H_

#include "../core/Physics.h"
#include "../core/Point3D.h"
#include "../display/Camera.h"
#include "../display/Display1.h"


class Game {
private:
	Physics* physics;
	Display1<Point3D>* display;
public:
	Game();
	virtual ~Game();
	//Game(const Game &other);


};

#endif /* GAME_H_ */
