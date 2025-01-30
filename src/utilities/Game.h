/*
 * Game.h
 *
 *  Created on: 7 nov. 2024
 *      Author: esn
 */

#ifndef GAME_H_

#define GAME_H_

#include <memory>
#include <unordered_set>

#include "../core/Physics.h"
#include "../core/Point3D.h"
#include "../core/Scene.h"
#include "../display/Display1.h"
#include "Printable.h"
#include "functions_display.h"

/*
 * ########
 *  Game :)
 * ########
 * Contains a scene, a physics management system, and a display.
 */
class Game : public Printable {
public:
	unsigned char fps;					// Frames per second
	bool fpause;

	std::shared_ptr<WINDOW> pwindow;				// Pointeur to the window.
	std::shared_ptr<SDL_Renderer> prenderer;			// Pointeur to the renderer.
	std::shared_ptr<Physics> pphysics;
	std::shared_ptr<Scene<SN<float, char>>> pscene;					// A scene
	std::shared_ptr<Display1<SN<float, char>>> pdisplay;

	Game();
	virtual ~Game();
	//Game(const Game &other);

	bool run(const unsigned int& steps=1);	// Runs a certain number of frames
	bool iterate(const float& dt);	// Renders once (à faire)
	bool render() const;					// Draws the content of the game on the screen

	virtual std::string to_string(const bool& spread=false, const bool& full_info=false, const unsigned char& indent=0) const;// :)
	virtual void print(const bool& spread=false, const bool& full_info=false, const unsigned char& indent=0) const;// :)
};

#endif /* GAME_H_ */
