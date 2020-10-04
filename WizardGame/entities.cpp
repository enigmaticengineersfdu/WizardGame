#include "entities.h"

/*Member Functions of the Item class*/
ent::Item::Item(const ItemID _id, const std::variant<Coord, CharacterID> _location, const char _icon) :
        id(_id), location(_location), icon(_icon)
{
        //No body needed
}

bool ent::Item::operator==(const Item& other) const
{
        //Two items are the same if they have the same id.
        return id == other.id;
}

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

const unsigned int ent::Character::get_health() const
{
        return health;
}

/*Member functions of the Player class*/
ent::Player::Player(const Coord _location, const char &_icon):
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


void ent::EntityMatrix::replenish_id_pools() noexcept
{
        /*Create a set of all CharacterIDs in the character_table and id pool.
        * Determine the maximum value and then generate sequential values greater than that.
        * Repeat for both CharacterIDs and ItemIDs.
        */
        std::unordered_set<CharacterID> used_ids;
}

ent::EntityMatrix::EntityMatrix(Map &map) noexcept :
        item_table(), item_id_pool(), character_table(), character_id_pool(), player(std::pair(map.find_pos('^').X, map.find_pos('^').Y))
{
        //Put 10 ids in both id pools
        for (size_t i = 1; i < 11; ++i) {
                item_id_pool.push(i);
                character_id_pool.push(i);
        }
}

const ent::CharacterID ent::EntityMatrix::request_character_id() noexcept
{
        //Replenish the id pools if need be.
        if (character_id_pool.empty()) replenish_id_pools();
        //Return the next available ID after removing it form the pool.
        CharacterID id = character_id_pool.front();
        character_id_pool.pop();
        return id;
}

void ent::EntityMatrix::reclaim_character_id(const ItemID& id) noexcept
{
        //Return the id to the pool of available ids. 
        character_id_pool.push(id);
}

const ent::Player& ent::EntityMatrix::get_player() const
{
        return player;
}
