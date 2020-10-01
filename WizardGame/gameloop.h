#ifndef GAMELOOPH
#define GAMELOOPH

#include <iostream>
#include <optional>
#include <string>
#include <unordered_map>

#include "entities.h"

/*The event loop namespace*/
namespace gl {
        /*Purpose: To provide the main event loop of the game
          Preconditions: save_path is a valid file path to a save file of this game.
          Postconditions: The game exits after either the player dying or saving.
        */
        void play_game(const std::optional<std::string> load_path);

        /*This enum represents all possible input values.
        * All values equate with the ASCII value of the keypress they represent.
        */
        enum class Input
        {
                INVALID  =  0 , //invalid input
                MV_UP    = 'w', //movement
                MV_DOWN  = 's',     
                MV_LEFT  = 'a',
                MV_RIGHT = 'd',
                OPEN_CMD = ':', //open command mode (to see inventory, save, quit, etc.)
        };
        
        /*InputHandler is an alias for const pointers to functions which will be used as input handlers.
        * They are required to have the following signature:
        * void name();
        */
        using InputHandler = void (*const)();

        /*Purpose: Creates the input handler table where the event loop will look for input handler functions.
        * The actual input handlers will not expose a public interface here but their addresses will be hard-coded
        * into the table in the body of this function.
        */
        const std::unordered_map<Input, InputHandler> make_handler_table();
}

#endif
