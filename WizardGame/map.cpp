#include "map.h"
using namespace ent;


	Map::Map()
	{
		room_design = {};
		current_line = "";
		cd.X = -1;
		cd.Y = -1;

	}

	void Map::loadMap(string file_N)
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

	void Map::showMap()
	{
		for (int row = 0; row < room_design.size(); row++)
		{	
			/*Prints out each character in the row, one by one (Assumed to be faster than cout)*/
			printf("%s\n", room_design[row].c_str());
		}
		printf("\n");
	}
	
	bool Map::outOfBounds(COORD coord)
	{
		if (room_design[cd.X][cd.Y] == '#')
			return true;
		else
			return false;
	}
	
	COORD Map::findPos(char object)
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

	void Map::moveObject(char object, COORD pos)
	{
			cd = findPos(object);
			room_design[cd.X][cd.Y] = '.';
			room_design[pos.X][pos.Y] = object;	

	}
