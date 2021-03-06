#ifndef GAMELOOPH
#define GAMELOOPH

#include <iostream>
#include <optional>
#include <string>
#include <unordered_map>

/*The event loop namespace*/
namespace gl {

        static const std::string levels[5] = {"MapDesign.txt", "MapDesign2.txt", "MapDesign3.txt",
                "MapDesign4.txt", "MapDesign5.txt"};

        /*Purpose: To provide the main event loop of the game
          Preconditions: save_path is a valid file path to a save file of this game.
          Postconditions: The game exits after either the player dies or saves and exits.
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
                OPEN_CMD = '/', //open command mode (to see inventory, save, quit, etc.)
                ATCK_UP  = 'i', //attack
                ATCK_DOWN  = 'k',
                ATCK_LEFT  = 'j',
                ATCK_RIGHT = 'l',
        };

        /*Purpose: Converts and input value as a char into a member of the input enum
        * validating it in the process. 
        * Preconditions: The int argument represents a valid keyboard input.
        * Postconditions: The resulting Input value is returned. 
        */
        const Input make_input(const int raw_input);
}

#endif
