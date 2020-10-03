#include "ui.h"
#include <iostream>
#include <sstream>

std::string render()
{
	// This will print the start screen

	int choice;
	
	std::cout << "Welcome to Apostate!\nPick an option:\n" << std::endl;

	std::cout << "1) Start\n2) Exit" << std::endl;

	std::cin >> choice;

	switch (choice)
		case 1:

			break;
		case 2:
			exit;
		default:
			std::cout << "Sorry, incorrect input" << std::endl;

}