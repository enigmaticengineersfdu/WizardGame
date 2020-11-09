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
		Coord(int _row = -1, int _col = -1);
		unsigned int distance(const Coord other) const noexcept;
		bool operator==(const Coord &other) const noexcept;
		bool operator!=(const Coord& other) const noexcept;
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
		bool in_bounds(Coord cd) const noexcept;
		Coord find_pos(char object) const;
		bool move_object(const Coord curr_pos, const char icon, const Coord new_pos) noexcept;
		bool new_level(Coord Coord);
		bool health_potion(Coord Coord);
		bool enemy_loc(Coord Coord) const;
		void remove_dead_en(Coord Coord, int spawn);
		std::vector<Coord> get_enemy_locs() const;
		Coord attack_loc(Coord loc, char obj);
		Coord closest_enem(Coord loc);
	};

}
#endif