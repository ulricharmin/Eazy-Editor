#pragma once

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string>
#include <vector>

class TextEditor
{
public:
	TextEditor(SDL_Window* p_window);
	void cleanUp();
	void clear();
	void display();
	void setBackground();
	void writeFile();
	void writeBuffer(std::string p_text);
	void handleInput(char p_scancode);
private:
	void readFile();
	SDL_Texture* loadTexture();
	void updateText();
private:
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	SDL_Surface* surface = nullptr;
	SDL_Texture* texture = nullptr;
	SDL_Point texData;
	TTF_Font* font = nullptr;
	SDL_Color color;
	std::string inputTextData = "";
	std::vector<std::string> inputText;
	std::string textString;
};