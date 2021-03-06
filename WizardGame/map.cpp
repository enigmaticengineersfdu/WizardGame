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
			std::cerr << "The map files could not be found.\n";
			//Reading a throwaway is much more portable and performant than 
			//std::system("pause")
			/*char throwaway;
			std::cin >> throwaway;*/
			//Negative exit codes indicate errors.
			std::exit(-1);
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
			/*Prints out each character in the row. (cout is idiomatic C++ and is faster than mixing printf, puts, and cout)*/
			std::cout << room_design[row] << '\n';
		}
		std::cout << std::endl;
	}
	
	bool ent::Map::in_bounds(Coord Coord) const noexcept
	{
		if (room_design[Coord.row][Coord.col] == '.' || room_design[Coord.row][Coord.col] == '*' )
			return true;
		else
			return false;
	}

	bool ent::Map::new_level(Coord Coord)
	{
		if (room_design[Coord.row][Coord.col] == '*')
		{
			room_design.clear();
			return true;
		}
		else
			return false;
	}
	void ent::Map::remove_dead_en(Coord pos)
	{
		room_design[pos.row][pos.col] = '.';

	}
	std::vector<Coord> ent::Map::get_enemy_locs() const
	{
		std::vector<Coord> locs;
		Coord curr_coord(0,0);

		for (int row = 0; row < room_design.size(); ++row) {
			for (int col = 0; col < room_design[row].length(); ++col) {
				curr_coord.row = row;
				curr_coord.col = col;
				if (enemy_loc(curr_coord))
					locs.push_back(curr_coord);
			}
		}
		return locs;
	}
	bool ent::Map::enemy_loc(Coord Coord) const
	{
		/*Try to somehow have a list of all enemies ids to check if player hits valid enemy*/
		return room_design[Coord.row][Coord.col] == 'A';
	}
	
	Coord ent::Map::find_pos(char object) const
	{
		Coord cd(0, 0);
		for (int row = 0; row < room_design.size(); row++)
		{
			for (int col = 0; col < room_design[row].size(); col++)
			{
				if (room_design[row][col] == object)
				{
					cd.row = row;
					cd.col = col;
				}
			}
		}
		return cd;
	}

	bool ent::Map::move_object(char object, Coord pos)
	{
		if (in_bounds(pos)) {
			Coord cd = find_pos(object);
			room_design[cd.row][cd.col] = '.';
			room_design[pos.row][pos.col] = object;
		}
		return in_bounds(pos);
	}

	ent::Coord::Coord(int _row, int _col):
		row(_row), col(_col)
	{
		//No body needed.
	}

	////According to the location of the player, returns the closet enemy within attacking distance
	//Coord ent::Map::closest_enem(Coord loc)
	//{

	//}

	/*Returns the best attacking location for enemy, if possible
	Given the player's location*/
	Coord ent::Map::attack_loc(Coord loc, char obj)
	{
		for (int row = loc.row; row < loc.row + 2; row++)
		{
			for (int col = loc.col; col < loc.col + 2; col++)
			{
				if (room_design[row][col] == obj)
					return { row, col };
			}
		}
		return { -1,-1 };
	}

	unsigned int ent::Coord::distance(const Coord other) const noexcept
	{
		/*These variables represent the lengths a and b legs of the right
		* triangle formed by the x and y values of the two ordered pairs.
		*/
		unsigned int a, b;
		a = this->row - other.row;
		b = this->col - other.col;
		/*The Euclidean distance between the two points is computed using
		* the Pythagorean theorem. 
		*/
		return std::sqrt(std::pow(a, 2) + pow(b, 2));
	}

	bool ent::Coord::operator==(const Coord &other) const noexcept
	{
		return row == other.row && col == other.col;
	}
