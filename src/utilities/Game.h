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
#include "../core/Scene.h"
//#include "../display/Camera.h"
#include "../display/Display1.h"

/*
 * ########
 *  Game :)
 * ########
 * Contains a scene, a physics management system, and a display.
 */
class Game {
private:
	SDL_Window* m_pwindow;				// Pointeur to the window.
	SDL_Renderer* m_prenderer;			// Pointeur to the renderer.

	Physics* m_pphysics;
	Scene* m_pscene;					// A scene
	Display1* m_pdisplay;

	unsigned int m_fps;					//Frames per second
	//unsigned int m_pps;				//Physics per second
	bool m_fpause;

public:
	Game();
	virtual ~Game();
	//Game(const Game &other);

	//SDL_Window* getPWindow();
	//SDL_Renderer* getPRenderer();
	unsigned int getFPS() const;
	void setFPS(const unsigned int& fps);
	unsigned int getPPS() const;
	void setPPS(const unsigned int& pps);
	Physics* getPPhysics();
	Scene* getPScene();

	std::unordered_set<TimeSensitive*> getPTimeSensitives();
	bool addPTimeSensitive(TimeSensitive* ptime_sensitive);

	bool run(const unsigned int& steps=1);	// Runs a certain number of frames
	bool iterate(const long double& dt);	// Renders once (à faire)
	bool render() const;					// Draws the content of the game on the screen

};

#endif /* GAME_H_ */
