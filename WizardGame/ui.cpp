#include "ui.h"


void startScreen()
{
	// This will print the start screen and will lead into the game

	std::string choice;

	while (true) {
		std::cout << "Welcome to Apostate!\nPick an option:\n" << std::endl;
		std::cout << "Play \nQuit" << std::endl;

		std::cout << "\n*If you need instructions on how to play the game\ntype \"/\" when the game starts";
		std::cout << " then type \"help\".\n" << std::endl;

		std::cin >> choice;

		if (choice == "play") {
			gl::play_game(std::nullopt);
		}
		else if (choice == "quit") {
			break;
		}
		else {
			continue;
		}
	}
}

