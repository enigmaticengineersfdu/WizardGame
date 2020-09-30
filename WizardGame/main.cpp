//#include <iostream>
#include "map.cpp"
#include <iostream>
#include <cstdlib>
#include <string>
#include <conio.h>
using namespace std;

int main()
{
	char inpt;
	bool gameOver = false;
	Map mp;
	mp.loadMap("MapDesign.txt");
	mp.showMap();

	//while loop to read in user input
	while (!gameOver)
	{
		//mp.loadMap("MapDesign.txt");
		//mp.showMap();

		//string clearString(500, '\n');
		//cout << "Player Stats: " << 1 << "		Level Number: " << 2 << "		Win Condition: " << endl;
		inpt = _getch();
		cout << "You entered: " << inpt << endl;



		/*C = Chest
		A = Archer
		W = Wizard
		S = Soldier

		Room on the very far right with
		"/" marks is the stairwell to the next level.*/

	}
}
/*
int main(int argv, char* argc[])
{
       //Main Menu Code
        return 0;
}*/