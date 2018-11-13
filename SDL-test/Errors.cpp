#include "Errors.h"
#include <iostream>
#include <cstdlib>
#include <SDL/SDL.h>

void fatalError(std::string errString) {
	std::cout << errString << '\n';
	std::printf("Enter any key to quit...");
	int tmp;
	std::cin >> tmp;
	SDL_Quit();
	exit(1);
}