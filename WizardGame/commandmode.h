#ifndef COMMANDMODEH
#define COMMANDMODEH

#include "entities.h"

namespace gl {
        //The location of the help and credits files relative to the game executable.
        static const char* const help_path = "help.txt";
        static const char* const credits_path = "credits.txt";

        /*Purpose: Implement command mode.
        * Preconditions: The game loop is in a valid state.
        * Postconditions: Varies depending on the specific commands entered.
        */
        void command_mode(const ent::GameState& gs) noexcept;
}

void test();

#endif