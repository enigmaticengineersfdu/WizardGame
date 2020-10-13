#include <conio.h>

#include "gameloop.h"
#include "entities.h"
#include "commandmode.h"

int current_level = 0;

/**Input Handlers**/
/*Purpose: Handle movement input in the game loop.
* Preconditions: The current game state is valid.
* Postcondition: The next gamestate is returned.
* Throws: None.
* Note: Should only be called in the game loop.
*/
const ent::GameState handle_mv(const gl::Input input, const ent::GameState& current_state) noexcept 
{
        /********DOES NOTHING SO FAR********/
        return current_state; 
}


/*Purpose: To render the game screen as a string.
* Preconditions: State represents the game state to be shown.
* Postconditions: The textual representation of the state is returned as a string.
* Throws: none.
* Note: Should only be called in play_game.
*/
void render_frame(ent::GameState& state) noexcept
{
        /*****NEEDS TO BE IMPLEMENTED*****/
        //Show the Map
        state.map.show_map();
        std::cout << "Level:" << current_level + 1 << '\n';
        std::cout << "Player HP:" << state.entity_matrix.get_player().get_health() << '\n';

}

/**Function Definitions**/
void gl::play_game(const std::optional<std::string> load_path)
{
        //The current game state. Should not be modified other than inside handlers.
        ent::GameState current_state;
        //The latest input. Should not be modified other than in the gameloop.
        Input input;
        current_state.map.load_map(gl::levels[current_level]);
        ent::COORD cd = current_state.map.find_pos('^');
        render_frame(current_state);

        /*The main game loop*/
        while (true) {
                //get a single keypress input from the keyboard
                input = gl::make_input(_getch());
                //Handle the input.
                switch (input) 
                {
                case gl::Input::MV_UP:
                        cd.X -= 1;
                        if (!current_state.map.in_bounds(cd))
                                cd.X += 1;
                        break;
                case gl::Input::MV_DOWN:
                        cd.X += 1;
                        if (!current_state.map.in_bounds(cd))
                                cd.X -= 1;
                        break;
                case gl::Input::MV_LEFT:
                        cd.Y -= 1;
                        if (!current_state.map.in_bounds(cd))
                                cd.Y += 1;
                        break;
                case gl::Input::MV_RIGHT:
                        cd.Y += 1;
                        if (!current_state.map.in_bounds(cd))
                                cd.Y -= 1;
                        break;
                        //call the movement handler to handle movement.
                        handle_mv(input, current_state);
                case gl::Input::OPEN_CMD:
                        /*Call the command_mode function to run command mode.*/
                        gl::command_mode(current_state);
                        break;
                case gl::Input::INVALID:
                default:
                        continue; // If the input is invalid, obtain another input.
                }
                /*Render the current game state to the console.*/
                if (current_state.map.new_level(cd) && current_level <4)
                {
                        current_level += 1;
                        current_state.map.load_map(gl::levels[current_level]);
                        cd = current_state.map.find_pos('^');
                }
                current_state.map.move_object('^', cd);
                cout << "X: " << cd.X << " Y: " << cd.Y << endl;
                render_frame(current_state);
        }
}

const gl::Input gl::make_input(const int raw_input)
{
        switch (raw_input)
        {
        case 'w':
                return gl::Input::MV_UP;
        case 'a':
                return gl::Input::MV_LEFT;
        case 's':
                return gl::Input::MV_DOWN;
        case 'd':
                return gl::Input::MV_RIGHT;
        case '/':
                return gl::Input::OPEN_CMD;
        default:
                return gl::Input::INVALID;
        }
}


