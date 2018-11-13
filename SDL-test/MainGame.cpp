#include <iostream>
#include "MainGame.h"
#include "Errors.h"

MainGame::MainGame() {
	_window = nullptr;
	_screenWidth = 1024;
	_screenHeight = 768;
	_gameState = GameState::PLAY;
}

MainGame::~MainGame() {
}

void MainGame::run() {
	initSystems();
	_sprite.init(-1.0f, -1.0f, 2.0f, 2.0f);
	gameLoop();
}

void MainGame::initSystems() {
	//Initialise SDL
	SDL_Init(SDL_INIT_EVERYTHING);
	_window = SDL_CreateWindow("Graphics Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _screenWidth, _screenHeight, SDL_WINDOW_OPENGL);
	
	if (_window == nullptr) {
		fatalError("SDL Window could not be created!");
	}

	SDL_GLContext ctx = SDL_GL_CreateContext(_window);

	if (ctx == nullptr) {
		fatalError("SDL_GL context could not be created!");
	}

	GLenum error = glewInit();

	if (error != GLEW_OK) {
		fatalError("Could not initialise glew!");
	}

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	glClearColor(0.0f, 0.0f, 1.0f, 1.0f);

	initShaders();
}

void MainGame::initShaders() {
	_colourProgram.compileShaders("Shaders/colourShading.vert", "Shaders/colourShading.frag");
	_colourProgram.addAttribute("vertexPosition");
	_colourProgram.addAttribute("vertexColour");
	_colourProgram.linkShaders();
}

void MainGame::gameLoop() {
	while (_gameState != GameState::EXIT) {
		processInput();
		drawGame();
	}
}

void MainGame::processInput() {
	SDL_Event evnt;
	while (SDL_PollEvent(&evnt)) {
		switch (evnt.type) {
		case SDL_QUIT:
			_gameState = GameState::EXIT;
			break;
		case SDL_MOUSEMOTION:
			std::cout << evnt.motion.x << ' ' << evnt.motion.y << '\n';
			break;
		}
	}
}

void MainGame::drawGame() {
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	_colourProgram.use();

	_sprite.draw();

	_colourProgram.unuse();

	SDL_GL_SwapWindow(_window);
}