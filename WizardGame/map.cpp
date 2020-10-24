#include "map.h"
using namespace ent;


	ent::Map::Map()
	{
		room_design = {};
		current_line = "";
	}

	void ent::Map::load_map(string file_N)
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

	void ent::Map::show_map() const
	{
		for (int row = 0; row < room_design.size(); row++)
		{	
			/*Prints out each character in the row, one by one (Assumed to be faster than cout)*/
			printf("%s\n", room_design[row].c_str());
		}
		printf("\n");
	}
	
	bool ent::Map::in_bounds(Coord Coord)
	{
		if (room_design[Coord.ROW][Coord.COL] == '.' || room_design[Coord.ROW][Coord.COL] == '*' )
			return true;
		else
			return false;
	}

	bool ent::Map::new_level(Coord Coord)
	{
		if (room_design[Coord.ROW][Coord.COL] == '*')
		{
			room_design.clear();
			return true;
		}
		else
			return false;
	}
	std::vector<Coord> ent::Map::get_enemy_locs() const
	{
		std::vector<Coord> locs;

		for (int y = 0; y < room_design.size(); ++y) {
			for (int x = 0; x < room_design[y].length(); ++x) {
				if (enemy_loc({ x, y }))
					locs.push_back({ x, y });
			}
		}
		return locs;
	}
	bool ent::Map::enemy_loc(Coord Coord) const
	{
		/*Try to somehow have a list of all enemies ids to check if player hits valid enemy*/
		if (room_design[Coord.ROW][Coord.COL] == 'A')  
			return true;
		else
			return false;
	}
	
	Coord ent::Map::find_pos(char object) const
	{
		Coord cd;
		for (int row = 0; row < room_design.size(); row++)
		{
			for (int col = 0; col < room_design[row].size(); col++)
			{
				if (room_design[row][col] == object)
				{
					cd.ROW = row;
					cd.COL = col;
				}
			}
		}
		return cd;
	}

	void ent::Map::move_object(char object, Coord pos)
	{
		Coord cd = find_pos(object);
		room_design[cd.ROW][cd.COL] = '.';
		room_design[pos.ROW][pos.COL] = object;

	}