/*
 * Display1.h
 *
 *  Created on: 4 juin 2024
 *      Author: esn
 */

#ifndef DISPLAY1_H_
#define DISPLAY1_H_

#include <set>
#include "SDL2/SDL.h"
#include "Point3D.h"
#include "Line3D.h"

/*
 * ############
 *  Display1 :)
 * ############
 * Orthographic projection
 * Choices between (x-y), (y-z), (z-x).
 */
class Display1 {
private:
	SDL_Window* m_pwindow;				// Pointeur to the window.
	SDL_Renderer* m_prenderer;			// Pointeur to the renderer.
	bool m_fclear;
public:
	Display1();
	virtual ~Display1();
	//Display1(const Display1 &other);

	void renderPoints(std::set<Point3D*> ppoints);//:)
	void renderPoint(Point3D* ppoint);//:)
	void renderLines(std::set<Line3D*> plines);//:)
	void renderLine(Line3D* pline);//:)
};

#endif /* DISPLAY1_H_ */
