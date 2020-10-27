#ifndef MAP
#define MAP

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
using namespace std;

namespace ent
{
	struct Coord
	{
		int row;
		int col;
		//Constructor
		Coord(int _row, int _col);
		unsigned int distance(const Coord other) const noexcept;
		bool operator==(const Coord &other) const noexcept;
	};
	class Map
	{
	private:
		vector <string> room_design;
		string current_line;
	public:
		Map();
		void load_map(string file_N);
		void show_map() const;
		bool in_bounds(Coord cd);
		Coord find_pos(char object) const;
		bool move_object(char object, Coord pos);
		bool new_level(Coord Coord);
		bool enemy_loc(Coord Coord) const;
		std::vector<Coord> get_enemy_locs() const;
	};

}
#endif