#pragma once

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string>

class TextCursor
{
public:
	TextCursor();
	void drawCursor(SDL_Renderer* p_renderer);
private:
	void calculateCursorPos();
private:
	int line, col;
	SDL_Point cursorPos;
};