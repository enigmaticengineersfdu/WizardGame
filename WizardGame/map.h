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
		void loadMap(string file_N);
		void showMap();
		bool outOfBounds(COORD cd);
		COORD findPos(char object);
		void moveObject(char object, COORD pos);


	};

}
#endif