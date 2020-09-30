#include "entities.h"


/*Member Functions for the Player Class*/
ent::Player::Player(const Coord &&_location, const char &&_icon):
        Character(static_cast<size_t>(0), std::move(_location), std::move(_icon))
{
        //Body unneeded since all initialization was done in the initializer list.
}
