#include <vector>
#include <string>
#include <fstream>
#include <iostream>
using namespace std;


struct COORD
{
	int X;
	int Y;
};

class Map
{
private:
	vector <string> room_design;
	bool out_of_bounds;
	string current_line;
	COORD cd;
public:

	Map()
	{
		room_design = {};
		current_line = "";
		cd.X = -1;
		cd.Y = -1;

	};

	void loadMap(string file_N)
	{
		/*This loads the txt file into the vector*/
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
		
	}

	void showMap()
	{
		for (int row = 0; row < room_design.size(); row++)

		{	/*Prints out each character in the row, one by one (Assumed to be faster than cout)*/
			printf("%s\n", room_design[row].c_str());
		}
		printf("\n");
	}
	
	bool outOfBounds(COORD coord)
	{
		if (room_design[cd.X][cd.Y] == '#')
			return true;
		else
			return false;
	}
	
	COORD findPos(char object)
	{

		for (int row = 0; row < room_design.size(); row++)
		{
			for (int col = 0; col < room_design[row].size(); col++)
			{
				if (room_design[row][col] == object)
				{
					cd.X = row;
					cd.Y = col;
				}
			}
		}
		return cd;
	}
		
		/*for (row = room_design.begin(); row != room_design.end(); row++)
		{
			for (int col =0; col <room_design.size(); row++)
			{
				if (room_design[row][col] == object)
					return row;
			}
		}

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
