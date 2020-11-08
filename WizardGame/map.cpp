#include "map.h"
using namespace ent;


	//Default constrcutor of the map class
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
	
	/*Returns true if location is in bounds (empty placeholder or player can advance to next
	level)*/
	bool ent::Map::in_bounds(Coord Coord) const noexcept
	{
		if (room_design[Coord.row][Coord.col] == '.' || room_design[Coord.row][Coord.col] == '*'
			|| room_design[Coord.row][Coord.col] == '+')
			return true;
		else
			return false;
	}

	/*returns true if the player is able to move onto the next
	level*/
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

	bool ent::Map::health_potion(Coord Coord)
	{
		if (room_design[Coord.row][Coord.col] == '+')
		{
			return true;
		}
		else
			return false;
	}
	/*Assuming given pos is the pos of the enemy that just died, it makes the
	given location an empty space '.'*/
	void ent::Map::remove_dead_en(Coord pos, int spawn)
	{
		if ((room_design[pos.row][pos.col] == 'A') && spawn == 1)
		{
			room_design[pos.row][pos.col] = '+';
		}
		else
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

	/*If inputted coordinate is where an enemy is located, returns true*/
	bool ent::Map::enemy_loc(Coord Coord) const
	{
		/*Try to somehow have a list of all enemies ids to check if player hits valid enemy*/
		return room_design[Coord.row][Coord.col] == 'A';
	}

	/*Given the icon of the object, the map (vector) is searched by row and col to determine
	* the loc of the object
	*/
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

	/*Given the current position and proposed location of the object, the object is searched for in
	* the map. If the proposed location is in bounds, the current loc of object becomes
	* an empty space, and the object's pos becomes new loc
	* */
	bool ent::Map::move_object(const Coord curr_pos, const char icon, const Coord new_pos) noexcept
	{
		//only make the move if the bounds check succeeds
		if (in_bounds(curr_pos) && curr_pos != new_pos) {
			//erase the character at the old location
			room_design.at(curr_pos.row).at(curr_pos.col) = '.';
			//draw the character at the new location
			room_design.at(new_pos.row).at(new_pos.col) = icon;

			return true;//indicates a successful move
		}
		else return false;//indicates no move. 
	}

	ent::Coord::Coord(int _row, int _col):
		row(_row), col(_col)
	{
		//No body needed.
	}

	//According to the location of the player, returns the closet enemy within set grid location 5x5
	Coord ent::Map::closest_enem(Coord loc)
	{
		bool flag = false;

		for (int row = loc.row - 4; row < loc.row + 5; row++)
		{
			for (int col = loc.col - 4; col < loc.col + 5; col++)
			{
				if (room_design[row][col] == 'A')
					return { row, col };
				if (row == (room_design.size() - 1) || col == (room_design[row].size() - 1))
				{
					flag = true;
					break;
				}
						
			}
			if (flag)
				break;
		}
		return { -1,-1 };
	}

	/*Returns the best attacking location for enemy, if player
	is within attacking range.*/
	Coord ent::Map::attack_loc(Coord loc, char obj)
	{
		int col = loc.col - 3;
		for (int row = loc.row-3; row < loc.row + 4; row++)
		{
			/*Trying to form t coordinate system for attacks*/
			if (room_design[row][loc.col] == obj)
				return { row, loc.col };
			else if (room_design[loc.row][col] == obj)
				return { loc.row, col };
			col++;
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

	bool ent::Coord::operator!=(const Coord& other) const noexcept
	{
		return row != other.row or col != other.col;
	}
