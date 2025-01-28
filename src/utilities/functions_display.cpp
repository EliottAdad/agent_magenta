/*
 * functions_display.cpp
 *
 *  Created on: 28 janv. 2025
 *      Author: esn
 */
 
#include "functions_display.h"

std::shared_ptr<WINDOW> createWindow() {
	return std::shared_ptr<SDL_Window>(
			SDL_CreateWindow("Game",
					SDL_WINDOWPOS_CENTERED,
					SDL_WINDOWPOS_CENTERED,
					1200, 600,
					SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_FULLSCREEN_DESKTOP),
			SDL_DestroyWindow);
}

std::shared_ptr<RENDERER> createRenderer(std::shared_ptr<WINDOW> pwindow){
	return std::shared_ptr<SDL_Renderer>(
					SDL_CreateRenderer(pwindow.get(), 0, SDL_RENDERER_TARGETTEXTURE | SDL_RENDERER_ACCELERATED),
					SDL_DestroyRenderer);
}

std::shared_ptr<COLOR> createColor() {
	return std::make_shared<SDL_Color>(SDL_Color{0, 0, 0, 0});
}

std::shared_ptr<COLOR> createColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
	return std::make_shared<SDL_Color>(SDL_Color{r, g, b, a});
}


void changeRenderDrawColor(std::shared_ptr<RENDERER> prenderer, std::shared_ptr<COLOR> pcolor) {
	SDL_SetRenderDrawColor(prenderer.get(), pcolor->r, pcolor->g, pcolor->b, pcolor->a); // Chooses the background color.
}

void fillRendererWithColor(std::shared_ptr<RENDERER> prenderer, std::shared_ptr<COLOR> pcolor) {
	SDL_SetRenderDrawColor(prenderer.get(), pcolor->r, pcolor->g, pcolor->b, pcolor->a); // Chooses the background color.
	SDL_RenderClear(prenderer.get()); // Fill the canvas with the background color
}

void drawPointRenderer(std::shared_ptr<RENDERER> prenderer, int x, int y){
	SDL_RenderDrawPoint(prenderer.get(), x, y);
}


/**
 * Renderer is actualized.
 */
void displayChangesRenderer(std::shared_ptr<RENDERER> prenderer) {
	SDL_RenderPresent(prenderer.get());
	//SDL_SetRenderDrawColor(prenderer.get(), pcolor->r, pcolor->g, pcolor->b, pcolor->a); // Chooses the background color.
	//SDL_RenderClear(prenderer.get()); // Fill the canvas with the background color
}

