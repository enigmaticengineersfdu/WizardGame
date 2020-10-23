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
		int ROW;
		int COL;
	};
	class Map
	{
	private:
		vector <string> room_design;
		string current_line;
		Coord cd;

	public:
		Map();
		void load_map(string file_N);
		void show_map();
		bool in_bounds(Coord cd);
		Coord find_pos(char object);
		void move_object(char object, Coord pos);
		bool new_level(Coord Coord);
		bool enemy_loc(Coord Coord);


	};

}
#endif