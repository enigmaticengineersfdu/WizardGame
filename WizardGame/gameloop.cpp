#include <conio.h>

#include "gameloop.h"


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
                        gl::handle_mv(input, current_state);
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
