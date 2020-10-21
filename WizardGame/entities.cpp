#include "entities.h"
#include <unordered_set>

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
ent::Character::Character(const CharacterID _id, Coord _location, const char &_icon):
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

const ent::Coord ent::Character::get_location() const
{
    return this->location;
}

void ent::Character::set_location(const Coord loc)
{
        this->location = loc;
}

/*Member functions of the Player class*/
ent::Player::Player(Coord _location, const char &_icon):
        Character(0, _location, _icon), inventory()
{
        //Body unneeded since all initialization was done in the initializer list.
}

std::optional <ent::Player> ent::Player::tick(const gl::Input input, struct GameState current_state)
{
 
        //currently just returns a copy of the current object.
        //will be improved upon a lot
        //currently doesn't even take user input. 
        Player play1 = current_state.entity_matrix.get_player();
        this->location = current_state.map.find_pos(this->icon);

        switch (input)
        {
        case gl::Input::MV_UP:
                location.X -= 1;
                if (!current_state.map.in_bounds(location))
                        location.X += 1;
                        break;
        case gl::Input::MV_DOWN:
                location.X += 1;
                if (!current_state.map.in_bounds(location))
                        location.X -= 1;
                        break;
        case gl::Input::MV_LEFT:
                location.Y -= 1;
                if (!current_state.map.in_bounds(location))
                        location.Y += 1;
                        break;
        case gl::Input::MV_RIGHT:
                location.Y += 1;
                if (!current_state.map.in_bounds(location))
                        location.Y -= 1;
                break;
        }

        return play1;
}

void ent::Player::attack(const gl::Input input, struct GameState current_state)
{
        this->location = get_location();

        switch (input)
        { 
        case gl::Input::ATCK_UP:
                cout<< "Location: " << location.X  << " " << location.Y << endl;
                cout << "Attcaked: " << location.X - 3 << " " << location.Y << endl;
                break;
        case gl::Input::ATCK_LEFT:
                break;
        case gl::Input::ATCK_DOWN:
                break;
        case gl::Input::ATCK_RIGHT:
                break;
        }
}

void ent::Player::operator=(Player& p)
{
        this->id = p.id;
        this->icon = p.icon;
        this->health = p.health;
        this->inventory = p.inventory;
        this->location = p.location;
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
        item_table(), item_id_pool(), character_table(), character_id_pool(), player(map.find_pos('^'), '^')
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

void ent::EntityMatrix::operator=(EntityMatrix &em)
{
        this->item_table = em.item_table;
        this->item_id_pool = em.item_id_pool;
        this->character_table = em.character_table;
        this->character_id_pool = em.character_id_pool;
        this->player = em.player;
}

ent::Player& ent::EntityMatrix::get_player()
{
        return player;
}

ent::GameState::GameState():
        map(), entity_matrix(map)
{
}

void ent::GameState::operator=(GameState gs)
{
        this->map = gs.map;
        this->entity_matrix = gs.entity_matrix;
}


