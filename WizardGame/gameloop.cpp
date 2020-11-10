#include <conio.h>

#include "gameloop.h"
#include "entities.h"
#include "commandmode.h"
#include "ui.h"

//Level 
static unsigned int current_level = 0;


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


        if (new_gamestate.map.new_level(new_gamestate.entity_matrix.get_player().get_location()) && current_level < gl::levels->size())
        {
                current_level += 1;
                if (current_level == gl::levels->size() - 1)
                {
                        cout << "\nYou Won!!\n" << endl;
                        playAgain();
                }
                new_gamestate.map.load_map(gl::levels[current_level]);
                new_gamestate.entity_matrix.get_player().set_location(new_gamestate.map.find_pos('^'));
                new_gamestate.entity_matrix.clear_enemy_table();
                new_gamestate.entity_matrix.set_enemies(new_gamestate.map.get_enemy_locs());
        }
        if (new_gamestate.map.health_potion(new_gamestate.entity_matrix.get_player().get_location()))
                new_gamestate.entity_matrix.get_player().set_health("---");

        new_gamestate.map.move_player('^', new_gamestate.entity_matrix.get_player().get_location());
        //new_gamestate.map.move_object(current_state.entity_matrix.get_player().get_location(), '^', new_gamestate.entity_matrix.get_player().get_location());
        //Update all enemies
        new_gamestate.entity_matrix.tick_all_enemies(new_gamestate.map);

        return new_gamestate; 
}

ent::GameState handle_atck(const gl::Input input, ent::GameState current_state) noexcept
{
        srand(time(NULL));
        /*Launches the player's attack according to their input*/
        ent::GameState new_gamestate = current_state;

        new_gamestate.entity_matrix.get_enem() = current_state.entity_matrix.get_player().attacks(input, current_state);
        new_gamestate.entity_matrix.update_table(new_gamestate.entity_matrix.get_enem());

        /*If enemy dies, remove them from the map, and update the character table*/
        if (new_gamestate.entity_matrix.get_enem().get_health().empty())
        {   
                int spawn_chance = rand() % 2;
                new_gamestate.map.remove_dead_en(new_gamestate.entity_matrix.get_enem().get_location(), spawn_chance);               
                new_gamestate.entity_matrix.reclaim_character_id(new_gamestate.entity_matrix.get_enem().id);
        }
        
        /*Checks to make sure enemy is valid before launching into it's attack*/
        else if (new_gamestate.map.closest_enem(new_gamestate.map.find_pos('^')).col != -1)
        {
                /*Attacks the player*/
                new_gamestate.entity_matrix.get_player() = current_state.entity_matrix.get_enem().attack(new_gamestate);

                if (new_gamestate.entity_matrix.get_player().get_health().empty())
                {
                        /*If player is dead, remove them from map, show next gamestate, and call replay function*/
                        new_gamestate.map.remove_dead_en(current_state.entity_matrix.get_player().get_location(), 0);
                        render_frame(new_gamestate);
                        current_level = 0;
                        playAgain();
                        std::exit(0);

                }
        }
        return new_gamestate;
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
                case gl::Input::ATCK_RIGHT:
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


