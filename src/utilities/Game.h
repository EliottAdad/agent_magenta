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
	unsigned char m_fps;					// Frames per second
	//unsigned int m_pps;				// Physics per second
	bool m_fpause;

public:
	SDL_Window* pwindow;				// Pointeur to the window.
	SDL_Renderer* prenderer;			// Pointeur to the renderer.
	std::shared_ptr<Physics> pphysics;
	std::shared_ptr<Scene<float, char>> pscene;					// A scene
	std::shared_ptr<Display1<float, char>> pdisplay;

	Game();
	virtual ~Game();
	//Game(const Game &other);

	//SDL_Window* getPWindow();
	//SDL_Renderer* getPRenderer();

	// Physics
	//float getSpeed() const;
	//void setSpeed(const float& speed);
	//unsigned char getPPS() const;
	//void setPPS(const unsigned char& pps);
	unsigned char getFPS() const;
	void setFPS(const unsigned char& fps);

	// Scene
	//std::unordered_set<Displayable*> getPDisplayables();//:)
	//bool addPDisplayable(std::shared_ptr<Displayable<float, char>> pdisplayable);//:)

	//Physics* getPPhysics();
	//Scene* getPScene();

	//std::unordered_set<TimeSensitive*> getPTimeSensitives();
	//bool addPTimeSensitive(std::shared_ptr<TimeSensitive> ptime_sensitive);

	//bool getFCollide() const;
	//void setFCollide(const bool& bcollide);
	bool getFPause() const;
	void setFPause(const bool& bpause);

	bool run(const unsigned int& steps=1);	// Runs a certain number of frames
	bool iterate(const float& dt);	// Renders once (à faire)
	bool render() const;					// Draws the content of the game on the screen

};

#endif /* GAME_H_ */
