#include "ui.h"


void startScreen()
{
	// This will print the start screen and will lead into the game

	std::string choice;

	std::cin >> choice;


	while (true) {
		std::cout << "Welcome to Apostate!\nPick an option:\n" << std::endl;
		std::cout << "Play \nQuit" << std::endl;

		if (choice == "play") {
			gl::play_game(std::nullopt);
		}
		else if (choice == "quit") {
			break;
		}
	}
}

