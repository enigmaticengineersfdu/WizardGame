#include "ui.h"
#include <string>
#include <cctype>
#include <algorithm>


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

		for (char& i : choice)
		{
			i = std::tolower(i);
		}


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

void playAgain()
{
	string choice;
	while (true)
	{
		std::cout << "\nWould you like to play again? (Yes or No)\n" << endl;

		std::cin >> choice;

		for (char& i : choice)
		{
			i = std::tolower(i);
		}

		if (choice == "yes") {
			std::cout << endl;
			startScreen();
		}
		else if (choice == "no") {
			std::exit(0);
		}
		else {
			continue;
		}
	}
	
}

