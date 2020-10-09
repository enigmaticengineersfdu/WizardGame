#ifndef COMMANDMODEH
#define COMMANDMODEH

#include "entities.h"

namespace gl {
        /*Purpose: Implement command mode.
        * Preconditions: The game loop is in a valid state.
        * Postconditions: Varies depending on the specific commands entered.
        */
        void command_mode(const ent::GameState& gs) noexcept;
}

#endif