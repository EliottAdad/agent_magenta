/*
 * functions_display.hpp
 *
 *  Created on: 28 janv. 2025
 *      Author: esn
 */
 
#ifndef FUNCTIONS_DISPLAY_HPP_

#define FUNCTIONS_DISPLAY_HPP_

#include <memory>
#include <SDL2/SDL.h>

#define WINDOW SDL_Window
#define RENDERER SDL_Renderer
#define COLOR SDL_Color



int initSDL();// Init SDL

std::shared_ptr<WINDOW> createWindow();
std::shared_ptr<RENDERER> createRenderer(std::shared_ptr<WINDOW> pwindow);


std::shared_ptr<COLOR> createColor();
std::shared_ptr<COLOR> createColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a=1);

void changeRenderDrawColor(std::shared_ptr<RENDERER> prenderer, std::shared_ptr<COLOR> pcolor);
void fillRendererWithColor(std::shared_ptr<RENDERER> prenderer, std::shared_ptr<COLOR> pcolor);

void drawPointRenderer(std::shared_ptr<RENDERER> prenderer, int x, int y);

void displayChangesRenderer(std::shared_ptr<RENDERER> prenderer);






//####################Definitions

/**
 * Init SDL
 */
inline int initSDL(){
    if (SDL_Init(SDL_INIT_VIDEO) < 0){
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[DEBUG] > %s", SDL_GetError());
        return EXIT_FAILURE;
    }
    return 0;
}

/**
 * Quit SDL
 */
inline void quitSDL(){
    SDL_Quit();
}

inline std::shared_ptr<WINDOW> createWindow() {
	return std::shared_ptr<SDL_Window>(
			SDL_CreateWindow("Game",
					SDL_WINDOWPOS_CENTERED,
					SDL_WINDOWPOS_CENTERED,
					1200, 600,
					SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_FULLSCREEN_DESKTOP),
			SDL_DestroyWindow);
}

inline std::shared_ptr<RENDERER> createRenderer(std::shared_ptr<WINDOW> pwindow){
	return std::shared_ptr<SDL_Renderer>(
					SDL_CreateRenderer(pwindow.get(), 0, SDL_RENDERER_TARGETTEXTURE | SDL_RENDERER_ACCELERATED),
					SDL_DestroyRenderer);
}

inline std::shared_ptr<COLOR> createColor() {
	return std::make_shared<SDL_Color>(SDL_Color{0, 0, 0, 0});
}

inline std::shared_ptr<COLOR> createColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
	return std::make_shared<SDL_Color>(SDL_Color{r, g, b, a});
}


inline void changeRenderDrawColor(std::shared_ptr<RENDERER> prenderer, std::shared_ptr<COLOR> pcolor) {
	SDL_SetRenderDrawColor(prenderer.get(), pcolor->r, pcolor->g, pcolor->b, pcolor->a); // Chooses the background color.
}

inline void fillRendererWithColor(std::shared_ptr<RENDERER> prenderer, std::shared_ptr<COLOR> pcolor) {
	SDL_SetRenderDrawColor(prenderer.get(), pcolor->r, pcolor->g, pcolor->b, pcolor->a); // Chooses the background color.
	SDL_RenderClear(prenderer.get()); // Fill the canvas with the background color
}

inline void drawPointRenderer(std::shared_ptr<RENDERER> prenderer, int x, int y){
	SDL_RenderDrawPoint(prenderer.get(), x, y);
}


/**
 * Renderer is actualized.
 */
inline void displayChangesRenderer(std::shared_ptr<RENDERER> prenderer) {
	SDL_RenderPresent(prenderer.get());
	//SDL_SetRenderDrawColor(prenderer.get(), pcolor->r, pcolor->g, pcolor->b, pcolor->a); // Chooses the background color.
	//SDL_RenderClear(prenderer.get()); // Fill the canvas with the background color
}


 #endif /* FUNCTIONS_DISPLAY_HPP_ */
