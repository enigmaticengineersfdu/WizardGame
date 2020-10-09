#ifndef MAP
#define MAP

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
using namespace std;

namespace ent
{
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
		Map();
		void load_map(string file_N);
		void show_map();
		bool in_bounds(COORD cd);
		COORD find_pos(char object);
		void move_object(char object, COORD pos);


	};

}
#endif