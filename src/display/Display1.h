/*
 * Display1.h
 *
 *  Created on: 4 juin 2024
 *      Author: esn
 */

#ifndef DISPLAY1_H_
#define DISPLAY1_H_

#include <set>
#include <SDL2/SDL.h>
#include "../core/LSN.h"
#include "../core/Point3D.h"
#include "../core/Line3D.h"
#include "../display/Displayable.h"
#include "../utilities/Printable.h"
#include "../core/Scene.h"


/*
 * ############
 *  Display1 :)
 * ############
 * Orthographic projection
 * Choices between (x-y), (y-z), (z-x).
 * Display any object having x, y, z.
 */
class Display1 : public Printable {
private:
	Point3D* m_ppoint;					// Pointeur to the center of display.
	char m_display;						// The point of view from which it is projected (1, 2, 3).
	long double m_scale;				// Ratio d_pixels/d_meters
	std::set<Scene*> m_pscenes;			// Pointeurs to the scenes that are rendered in the display.

	SDL_Color* m_pbkgd_color;			// Pointeur to the background color.
	SDL_Color* m_pdraw_color;			// Pointeur to the render color.
	SDL_Window* m_pwindow;				// Pointeur to the window.
	SDL_Renderer* m_prenderer;			// Pointeur to the renderer.

	bool m_delp;
	bool m_delw;
	bool m_delr;
	bool m_fclear;

public:
	Display1();
	Display1(Point3D* ppoint);
	Display1(SDL_Window* pwindow, SDL_Renderer* prenderer);
	virtual ~Display1();
	//Display1(const Display1 &other);

	Point3D* getPPoint();
	void setPPoint(Point3D* ppoint, const bool& delp=false);
	void setPoint(Point3D& point, const bool& delp=true);
	char getDisplay() const;
	void setDisplay(const char& display);
	long double getScale() const;
	void setScale(long double m_scale);
	SDL_Color* getPBkgdColor();
	void setBkrdColor(int r, int g, int b, int a);
	SDL_Color* getPDrawColor();
	void setDrawColor(int r, int g, int b, int a);
	SDL_Window* getPWindow();
	SDL_Renderer* getPRenderer();
	//void setDrawColor(int r, int g, int b, int a);
	std::set<Scene*> getPScenes() const;
	void addPScene(Scene* pscene);

	bool render() const;
	bool render(Scene* pscene) const;
	bool render(Displayable* pdisplayable) const;
	void renderPoints(std::set<Point3D*> ppoints) const;//:)
	void renderPoint(Point3D* ppoint) const;//:)
	void renderLines(std::set<Line3D*> plines) const;//:)
	void renderLine(Line3D* pline) const;//:)

	virtual std::string to_string(const bool& spread=false, const bool& full_info=false, const unsigned char& indent=0) const;// :)
	virtual void print(const bool& spread=false, const bool& full_info=false, const unsigned char& indent=0) const;// :)
};


#endif /* DISPLAY1_H_ */
