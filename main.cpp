#include "Map.cpp"
#include <iostream>
#include <cstdlib>
#include <string>
#include <conio.h>
using namespace std;

int main()
{
	char inpt;
	int ROW_L, COLUMN_L;
	bool gameOver = false;
	Map mp;
	mp.loadMap("MapDesign.txt");
	mp.showMap();

	//while loop to read in user input
	while (!gameOver)
	{
		inpt = _getch();
		//Clears string
		//string clearString(100, '\n');
		cout << "You entered: " << inpt << endl;
	}



	return 0;
};