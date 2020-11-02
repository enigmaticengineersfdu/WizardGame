#include <conio.h>

#include "gameloop.h"
#include "entities.h"
#include "commandmode.h"

//Level 
static unsigned int current_level = 0;

/**Input Handlers**/
/*Purpose: Handle movement input in the game loop.
* Preconditions: The current game state is valid.
* Postcondition: The next gamestate is returned.
* Throws: None.
* Note: Should only be called in the game loop.
*/
ent::GameState handle_mv(const gl::Input input, ent::GameState current_state) noexcept 
{     
        /*Moves the player according to their input*/
        ent::GameState new_gamestate = current_state;
        new_gamestate.entity_matrix.get_player() = current_state.entity_matrix.get_player().tick(input, current_state.map);


        if (new_gamestate.map.new_level(new_gamestate.entity_matrix.get_player().get_location()) && current_level < 4)
        {
                current_level += 1;
                new_gamestate.map.load_map(gl::levels[current_level]);
                new_gamestate.entity_matrix.get_player().set_location(new_gamestate.map.find_pos('^'));
                new_gamestate.entity_matrix.clear_enemy_table();
                new_gamestate.entity_matrix.set_enemies(new_gamestate.map.get_enemy_locs());
        }

        new_gamestate.map.move_object('^', new_gamestate.entity_matrix.get_player().get_location());

        return new_gamestate; 
}

ent::GameState handle_atck(const gl::Input input, ent::GameState current_state) noexcept
{

        /*Launches the player's attack according to their input*/
        ent::GameState new_gamestate = current_state;
        new_gamestate.entity_matrix.get_enem() = current_state.entity_matrix.get_player().attacks(input, current_state);

        new_gamestate.entity_matrix.update_table(new_gamestate.entity_matrix.get_enem());

        return new_gamestate;
}


/*Purpose: To render the game screen as a string.
* Preconditions: State represents the game state to be shown.
* Postconditions: The textual representation of the state is returned as a string.
* Throws: none.
* Note: Should only be called in play_game.
*/
void render_frame(ent::GameState& state) noexcept
{
        //Shows the Map, Level and player stats
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
        /*Setup operations before rendering the first game state.*/
        current_state.map.load_map(gl::levels[current_level]);
        current_state.entity_matrix.set_enemies(current_state.map.get_enemy_locs());
        render_frame(current_state);

        /*The main game loop*/
        while (true) {
                //get a single keypress input from the keyboard
                input = gl::make_input(_getch());
                //Handle the input.
                switch (input) 
                {
                case gl::Input::MV_UP:
                case gl::Input::MV_DOWN:
                case gl::Input::MV_LEFT:
                case gl::Input::MV_RIGHT:        
                        current_state = handle_mv(input, current_state);
                        break;
                case gl::Input::OPEN_CMD:
                        /*Call the command_mode function to run command mode.*/
                        gl::command_mode(current_state);
                        break;
                /*Handles User attack*/
                case gl::Input::ATCK_UP:
                case gl::Input::ATCK_DOWN:
                case gl::Input::ATCK_LEFT:
                case::gl::Input::ATCK_RIGHT:
                        current_state = handle_atck(input, current_state);
                        break;
                case gl::Input::INVALID:
                default:
                        continue; // If the input is invalid, obtain another input.
                }
               
               
                /*Render the current game state to the console.*/
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
        case 'i':
                return gl::Input::ATCK_UP;
        case 'j':
                return gl::Input::ATCK_LEFT;
        case 'k':
                return gl::Input::ATCK_DOWN;
        case 'l':
                return gl::Input::ATCK_RIGHT;
        default:
                return gl::Input::INVALID;
        }
}


