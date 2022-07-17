#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string>

#include "../include/TextCursor.h"

TextCursor::TextCursor() {
	
}

void TextCursor::drawCursor(SDL_Renderer* p_renderer) {
	SDL_Rect fillRect = {};
	SDL_SetRenderDrawColor(p_renderer, 1, 1, 1, 0.3);
	SDL_RenderFillRect(p_renderer, &fillRect);
}

void TextCursor::calculateCursorPos() {

}