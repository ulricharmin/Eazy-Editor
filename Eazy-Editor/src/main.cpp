#define SDL_MAIN_HANDLED
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <vector>

#include "../include/Window.h"
#include "../include/TextEditor.h"

using namespace std;

const int WINDOW_HEIGHT = 720;
const int WINDOW_WIDTH = 1280;
bool clicked = false;

int main(int argc, const char* argv[]) {

	if (SDL_Init(SDL_INIT_VIDEO < 0)) {
		cout << "SDL could not initialize. SDL Error\n" << SDL_GetError();
	}
	if (!IMG_Init(IMG_INIT_JPG)) {
		cout << "IMG could not initialize. SDL Error\n" << IMG_GetError();
	}
	if (!IMG_Init(IMG_INIT_PNG)) {
		cout << "IMG could not initialize. SDL Error\n" << IMG_GetError();
	}

	Window window("Eazy-Editor v1.0", WINDOW_WIDTH, WINDOW_HEIGHT);

	TextEditor textEditor(window.getWindow());

	SDL_SetWindowResizable(window.getWindow(), SDL_TRUE);

	bool appRunning = true;

	SDL_Event event;

	const Uint8* keystates = SDL_GetKeyboardState(NULL);
	std::string inputText;

	while (appRunning) {
		while (SDL_PollEvent(&event)) {
			SDL_StartTextInput();
			switch (event.type) {
			case SDL_QUIT:
				appRunning = false;
				textEditor.writeFile();
				break;
			case SDL_TEXTINPUT:
				inputText += event.text.text;
				if (inputText.length() > 0) {
					textEditor.writeBuffer(inputText);
					inputText = "";
					std::cout.flush();
				}
				break;
			case SDL_KEYDOWN:
				char keyDown = event.key.keysym.scancode;
				textEditor.handleInput(keyDown);
				break;
			}
		}

		textEditor.clear();

		textEditor.setBackground();

		textEditor.display();
	}

	textEditor.cleanUp();
	SDL_Quit();

	return 0;
}