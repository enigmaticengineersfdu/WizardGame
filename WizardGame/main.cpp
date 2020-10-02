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
	string level1 = "MapDesign.txt";
	mp.loadMap(level1);
	COORD cd;

	/*while loop to read in user input*/
	while (!gameOver)
	{
		mp.showMap();

		//string clearString(2, '\n');
		cout << "Player Stats: " << 1 << "		Level Number: " << 2 << "		Win Condition: " << endl;
		
		
		cd = mp.findPos('^');
		cout << "Row: " << cd.X << " Column: " << cd.Y << endl;
		
		cd.Y = cd.Y + 1;
		mp.moveObject('^', cd);
		//cout << mp.outOfBounds(cd) << endl;

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