#include <vector>
#include <string>
#include <fstream>
#include <iostream>
using namespace std;


class Map
{
private:
	vector <string> room_design;
	bool out_of_bounds;
	string current_line;
	//COORD cd;
public:
	Map()
	{
		room_design = {};
		current_line = "";

	};

	void loadMap(string file_N)
	{
		ifstream file;
		file.open(file_N);
		if (file.fail())
		{
			system("pause");
			exit(1);
		}

		while (getline(file, current_line))
		{
			room_design.push_back(current_line);
		}
		/*file.close(); function will close file by itself w/out this*/
	}

	void showMap()
	{
		for (int row = 0; row < room_design.size(); row++)

		{	/*Prints out each character in the row, one by one (Assumed to be faster than cout)*/
			printf("%s\n", room_design[row].c_str());
		}
		printf("\n");
	}
	/*
	bool outOfBounds(coord cd)
	{
		room_design;
	}*/

/*	
	Will Probaly be best in inventory class
	checks if the item that the user is trying to pick up is valid
	based on if the cell matches the item from the list

	bool isValidItem(coord cd)
	{
		if ()

	}
*/

	void pickUpItem()
	{

	}

	void dropItem()
	{

	}








};
