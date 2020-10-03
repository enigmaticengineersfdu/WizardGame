#include "entities.h"

/*Member functions of the Character class*/
ent::Character::Character(const CharacterID _id, const Coord &_location, const char &_icon):
        id(_id), location(_location), icon(_icon), health(100)
{
        //Body unneeded since all initialization was done in the initializer list.
}

bool ent::Character::is_dead() const
{
        return health == 0;
}

/*Member functions of the Player class*/
ent::Player::Player(const Coord &_location, const char &_icon):
        Character(0, _location, _icon), inventory()
{
        //Body unneeded since all initialization was done in the initializer list.
}

std::optional<ent::Player> ent::Player::tick(const gl::Input input) const
{
        //currently just returns a copy of the current object.
        //will be improved upon a lot
        //currently doesn't even take user input. 
        return *this;
}

ent::Item::Item(const ItemID _id, const std::variant<Coord, CharacterID> _location, const char _icon):
        id(_id), location(_location), icon(_icon)
{
        //No body needed
}

bool ent::Item::operator==(const Item& other) const
{
        //Two items are the same if they have the same id.
        return id == other.id;
}
