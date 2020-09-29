#ifndef GAMELOOPH
#define GAMELOOPH

#include <optional>
#include <string>
#include <unordered_map>

#include "entities.h"

/*The event loop namespace*/
namespace evl {
        /*Purpose: To provide the main event loop of the game
          Preconditions: save_path is a valid file path to a save file of this game.
          Postconditions: The game exits after either the player dying or saving.
        */
        void play_game(const std::optional<std::string> loaded_state);

        /*This enum represents all possible input values*/
        enum class Input
        {
                INVALID = 0, //invalid input
                MV_UP,       //movement
                MV_DOWN,     
                MV_LEFT,
                MV_RIGHT,
                OPEN_CMD,    //open command mode (to see inventory, save, quit, etc.)
        };

        /*InputHandler is an alias for const pointers to functions which will be used as input handlers.
        *They are required to have the following signature:
        * void name();
        */
        using InputHandler = void (*const)();

        std::unordered_map<Input, InputHandler> input_handlers;
        
}

#endif
