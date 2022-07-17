#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string>

#include "../include/Window.h"

Window::Window(const char* p_title, int p_w, int p_h) :window(nullptr) {
	window = SDL_CreateWindow(p_title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, p_w, p_h, SDL_WINDOW_SHOWN);

	if (window == nullptr) {
		std::cout << "Window failed to inititalize. SDL Error\n" << SDL_GetError();
	}
}

// Getter
SDL_Window* Window::getWindow() {
	return window;
}