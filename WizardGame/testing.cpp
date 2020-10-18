#include "commandmode.h"
#include "entities.h"
//#include "commandmode.cpp"
#include<assert.h>
#include <iostream>
#include <string>
#include <sstream>
#include <cctype>
#include <cstdlib>
#include <fstream>



int main() {

	/*ent::GameState testing;		//Tests command_mode function
	gl::command_mode(testing);*/	

	//make_command(std::move("help"));	//Tests make_command function



/* Setting coordinates to use for the set_location function.

	ent::Coord coordinates;
	coordinates.X = 30;
	coordinates.Y = 30;

*/

/* Creating a test game state and test input.

	ent::GameState testState;
	gl::Input testInput;

*/

/* Testing the get_player, set_player, get_location functions.

	testInput = gl::Input::MV_UP;

	auto player = testState.entity_matrix.get_player();
	testState.entity_matrix.get_player().set_location(coordinates);
	testState.entity_matrix.get_player().get_location();

*/

	//player.tick(testInput, testState, 0);	//Tests the tick function.


	//testState.map.move_object('^', testState.entity_matrix.get_player().get_location()); //Tests move_object function.

	//test();

	return 0;
}