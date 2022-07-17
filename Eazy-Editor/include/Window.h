#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <string>

class Window
{
public:
	Window(const char* p_title, int p_w, int p_h);
	SDL_Window* getWindow();
private:
	SDL_Window* window = nullptr;
};