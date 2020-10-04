#include "ui.h"
#include "map.cpp"
#include "gameloop.h"
#include <iostream>
#include <sstream>

void startScreen()
{
	// This will print the start screen and will lead into the game

	string choice;

	std::cin >> choice;


	while (true) {
		std::cout << "Welcome to Apostate!\nPick an option:\n" << std::endl;
		std::cout << "Play \nQuit" << std::endl;

		if (choice == "play") {
			gl::play_game;
		}
		else if (choice == "quit") {
			break;
		}
	}
}

