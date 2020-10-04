#include <conio.h>

#include "gameloop.h"
#include "entities.h"

/**Input Handlers**/
/*Purpose: Handle movement input in the game loop.
* Preconditions: The current game state is valid.
* Postcondition: The next gamestate is returned.
* Throws: None.
* Note: Should only be called in the game loop.
*/
const ent::GameState handle_mv(const gl::Input input, const ent::GameState& current_state) noexcept 
{
        return ent::GameState();
}

/*Function Definitions*/
void gl::play_game(const std::optional<std::string> load_path)
{
        //The current game state. Should not be modified other than inside handlers.
        ent::GameState current_state;
        //The latest input. Should not be modified other than in the gameloop.
        Input input;

        /*The main game loop*/
        while (true) {
                //get a single keypress input from the keyboard
                input = gl::make_input(_getch());
                //Handle the input.
                switch (input) 
                {
                case gl::Input::MV_UP: //Intentional fallthrough because all movement is handled by one function.
                case gl::Input::MV_DOWN:
                case gl::Input::MV_LEFT:
                case gl::Input::MV_RIGHT:
                        //call the movement handler to handle movement.
                        handle_mv(input, current_state);
                        break;
                case gl::Input::INVALID:
                default:
                        continue;
                }
                /*Render the current game state to the console.*/
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
        default:
                return gl::Input::INVALID;
        }
}


