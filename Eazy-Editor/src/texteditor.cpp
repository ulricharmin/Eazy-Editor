#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>
#include <fstream>
#include <filesystem>

#include "../include/TextEditor.h"
#include "../include/TextCursor.h"

TextEditor::TextEditor(SDL_Window* p_window) :window(p_window) {
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	if (renderer == nullptr) {
		std::cout << "Renderer failed to initialize. SDL Error\n" << SDL_GetError();
	}

	if (TTF_Init() < 0)
	{
		std::cout << "SDL_ttf could not initialize! SDL_ttf Error:\n" << TTF_GetError();
	}

	font = TTF_OpenFont("fonts/PressStart2P-Regular.ttf", 15);
	if (font == nullptr) {
		std::cout << "Failed to load font." << std::endl;
	}

	color = { 255, 255, 255 };
	readFile();
}

void TextEditor::cleanUp() {
	SDL_DestroyWindow(window);
	SDL_DestroyTexture(texture);
	SDL_FreeSurface(surface);
	TTF_CloseFont(font);
	TTF_Quit();
}

void TextEditor::clear() {
	SDL_RenderClear(renderer);
	SDL_DestroyTexture(texture);
}

SDL_Texture* TextEditor::loadTexture() {
	texture = nullptr;
	surface = nullptr;

	updateText();

	surface = TTF_RenderUTF8_Blended_Wrapped(font, textString.c_str(), color, NULL);
	if (surface == nullptr && inputTextData.length() < 0) {
		std::cout << "Unable to load surface! SDL_Error\n" << SDL_GetError();
	}
	else {
		texture = SDL_CreateTextureFromSurface(renderer, surface);
		SDL_FreeSurface(surface);
	}

	return texture;
}

void TextEditor::display() {
	SDL_Texture* tex = loadTexture();
	SDL_QueryTexture(tex, NULL, NULL, &texData.x, &texData.y);
	SDL_Rect dstrect = { 30, 15, texData.x, texData.y };
	SDL_RenderCopy(renderer, tex, NULL, &dstrect);
	SDL_RenderPresent(renderer);
}

void TextEditor::readFile() {
	std::string line;
	std::ifstream file("test.txt");
	if (file.is_open()) {
		while (std::getline(file, line)) {
			if (!file.eof()) {
				inputText.push_back(line+"\n");
			}
			else {
				inputText.push_back(line);
			}
		}
		file.close();
	}
	else {
		std::cout << "Could not open file." << std::endl;
	}
	updateText();
}

void TextEditor::writeFile() {
	std::ofstream file;
	file.open("test.txt");
	if (file.is_open()) {
		updateText();
		file << textString;
		file.close();
	}
}

void TextEditor::writeBuffer(std::string p_text) {
	if (inputText.size()>0) {
		inputText.back().append(p_text);
	}
	else {
		inputText.push_back(p_text);
	}
}

void TextEditor::handleInput(char p_scancode) {
	if (p_scancode == SDL_SCANCODE_RETURN) {
		writeBuffer("\n");
	}
	else if (p_scancode == SDL_SCANCODE_BACKSPACE) {
		if (inputText.size() > 0) {
			// nlcr sind 2 zeichen
			if (inputText.back().length() > 0) {
				inputText.back().pop_back();
			}
			else {
				inputText.pop_back();
			}
		}
	}
}

void TextEditor::updateText() {
	textString = "";
	for (std::string line : inputText) {
		textString.append(line);
	}
}

// Mutator
void TextEditor::setBackground() {
	SDL_SetRenderDrawColor(renderer, 0, 39, 46, 1);
	SDL_RenderClear(renderer);
}