/*
 * functions_display.h
 *
 *  Created on: 28 janv. 2025
 *      Author: esn
 */
 
#ifndef FUNCTIONS_DISPLAY_H_

#define FUNCTIONS_DISPLAY_H_

#include <memory>
#include <SDL2/SDL.h>

#define WINDOW SDL_Window
#define RENDERER SDL_Renderer
#define COLOR SDL_Color


 
std::shared_ptr<WINDOW> createWindow();
std::shared_ptr<RENDERER> createRenderer(std::shared_ptr<WINDOW> pwindow);


std::shared_ptr<COLOR> createColor();
std::shared_ptr<COLOR> createColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a=1);

void changeRenderDrawColor(std::shared_ptr<RENDERER> prenderer, std::shared_ptr<COLOR> pcolor);
void fillRendererWithColor(std::shared_ptr<RENDERER> prenderer, std::shared_ptr<COLOR> pcolor);

void drawPointRenderer(std::shared_ptr<RENDERER> prenderer, int x, int y);

void displayChangesRenderer(std::shared_ptr<RENDERER> prenderer);


 #endif /* FUNCTIONS_DISPLAY_H_ */
