#include <vector>
#include <string>
#include <fstream>
#include <iostream>
using namespace std;


class Map
{
private:
	vector <string> room_Info;
	bool outOfBounds;
public:
	Map() 
	{
		room_Info = {};

	};

	void loadMap(string file_N)
	{
		ifstream file;
		file.open(file_N);
		if (file.fail())
		{
			system("pause");
			exit(1);
		}

		string current_Line;

		while (getline(file, current_Line))
		{
			room_Info.push_back(current_Line);
		}
		/*file.close(); function will close file by itself w/out this*/
	}

	void showMap()
	{
		for (int row = 0; row < room_Info.size(); row++)
		{
			printf("%s\n", room_Info[row].c_str()); //*Assumed to be faster than cout*
		}
		printf("\n");
	}

	bool outOfBounds()
	{
		for (int row = 0; row < room_Info.size(); row++)
		{
			if ()
		}
	}

	




};
