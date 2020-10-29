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
        id(_id), location(_location), icon(_icon), health("---")
{
        //Body unneeded since all initialization was done in the initializer list.
}

bool ent::Character::is_dead() const
{
        return health == " ";
}

const std::string ent::Character::get_health() const
{
        return health;
}

void ent::Character::set_health(string h)
{
        health = h;
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
ent::Player::Player(Coord _location, const char &&_icon):
        Character(0, _location, _icon), inventory()
{
        //Body unneeded since all initialization was done in the initializer list.
}

ent::Player ent::Player::tick(const gl::Input input, const ent::Map &curr_map) const
{
        //currently just returns a copy of the current object.
        //will be improved upon a lot
        //currently doesn't even take user input. 
        ent::Player next_player = *this;
        next_player.location = curr_map.find_pos(next_player.icon);

        switch (input)
        {
        case gl::Input::MV_UP:
                next_player.location.row -= 1;
                if (!curr_map.in_bounds(next_player.location))
                        next_player.location.row += 1;
                        break;
        case gl::Input::MV_DOWN:
                next_player.location.row += 1;
                if (!curr_map.in_bounds(next_player.location))
                        next_player.location.row -= 1;
                        break;
        case gl::Input::MV_LEFT:
                next_player.location.col -= 1;
                if (!curr_map.in_bounds(next_player.location))
                        next_player.location.col += 1;
                        break;
        case gl::Input::MV_RIGHT:
                next_player.location.col += 1;
                if (!curr_map.in_bounds(next_player.location))
                        next_player.location.col -= 1;
                break;
        }

        return next_player;
}

void ent::Player::attack(const gl::Input input, struct GameState current_state)
{
        this->location = current_state.map.find_pos(this->icon);
        ent::Coord atck = location;
        cout << "Location: " << location.row << " " << location.col << endl;
        int count = 3;
        //Enemy en();
        //int health = ent::Enemy::get_health();
        //int health = 

        switch (input)
        { 
        case gl::Input::ATCK_UP:
                atck.row --;
                while (!current_state.map.in_bounds(atck) && count >0)
                {
                        atck.row--;
                        count--;
                }
                cout << "(Up)";
                break;
        case gl::Input::ATCK_LEFT:
                atck.col -=1;
                while (!current_state.map.in_bounds(atck) && count > 0)
                {
                        atck.col--;
                        count--;
                }
                cout << "(Left)";
                break;
        case gl::Input::ATCK_DOWN:
                atck.row ++;
                while (!current_state.map.in_bounds(atck) && count > 0)
                {
                        atck.row++;
                        count--;
                }
                cout << "(Down)";
                break;
        case gl::Input::ATCK_RIGHT:
                atck.col ++;
                while (!current_state.map.in_bounds(atck) && count > 0)
                {
                        atck.col++;
                        count--;
                }
                cout << "(Right)";
                break;
        }
        if (!current_state.map.in_bounds(atck))
        {
                atck.row = -1;
                atck.col = -1;
        }
        cout<< " Attacked: " << atck.row << " " << atck.col << endl; 
        //health.pop_back(); Testing deletion of player's health after attack. Function works as intended
}

void ent::Player::operator=(Player p)
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
        character_table(), character_id_pool(), player(Player(map.find_pos('^'), '^'))
{
        //Put 10 ids in both id pools
        for (size_t i = 1; i < 11; ++i) {
                character_id_pool.push(i);
        }
}

const ent::CharacterID ent::EntityMatrix::request_character_id() noexcept
{
        //Replenish the id pools if need be.
        if (character_id_pool.empty()) 
                replenish_id_pools();
        //Return the next available ID after removing it from the pool.
        CharacterID id = character_id_pool.front();
        character_id_pool.pop();
        return id;
}

void ent::EntityMatrix::reclaim_character_id(const ItemID& id) noexcept
{
        //Return the id to the pool of available ids. 
        character_id_pool.push(id);
}

//std::optional<ent::EntityMatrix> ent::EntityMatrix::generate_next(const gl::Input input, const ent::Map &curr_map)
//{
//        //Copy the current EM.
//        auto next = *this;
//        /*Call the tick function of everything in it to generate the next.*/
//        //Enemies
//        for (auto enemy_pair : this->character_table) {
//                auto next_enemy = enemy_pair.second.tick(input, *(this->player));
//                if (next_enemy)
//                        next.character_table.insert(std::pair(enemy_pair.first, *next_enemy));
//        }
//        //Player
//        auto next_player_val = this->player->tick(input, curr_map, this->player);
//        if (next_player_val) {
//                next.player = *next_player_val;
//        }
//        else {
//                next.player = std::nullopt;
//        }
//        return next;
//}

void ent::EntityMatrix::operator=(EntityMatrix &em)
{
        this->character_table = em.character_table;
        this->character_id_pool = em.character_id_pool;
        this->player = em.player;
}

ent::Player &ent::EntityMatrix::get_player()
{
        return player;
}

void ent::EntityMatrix::set_enemies(std::vector<Coord> enemy_locs)
{
        CharacterID curr_id;
        for (Coord loc : enemy_locs) {
                curr_id = this->request_character_id();
                this->character_table.insert(std::pair(curr_id, Enemy(curr_id, std::move(loc))));
        }
}

std::optional<ent::CharacterID> ent::EntityMatrix::get_enemy_by_loc(const ent::Coord loc) const noexcept
{
        //search the enemy table. O(n) time.
        for (auto enemy_pair : character_table) {
                if (enemy_pair.second.get_location() == loc)
                        return enemy_pair.first;
        }
        //If no enemy is found at the indicated location then return nothing.
        return std::nullopt;
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

void ent::Enemy::move(const gl::Input input)
{
        /*Need to fix Map::move_object to return a bool and take a character ID
        * before implementing this.
        */
}

ent::Enemy::Enemy(CharacterID _id, const Coord _location, const char&& _icon)
        :Character(_id, _location, _icon), spawn_pt(_location)
{
        //No body needed
}

std::optional<ent::Enemy> ent::Enemy::tick(const gl::Input input, const Player& player) const
{
        //Copy the calling object to create the new version.
        auto next = *this;
        /*If the player is within range start moving toward them. If not then do nothing.*/
        if (next.location.distance(player.get_location()) < detection_distance)
                next.move(input); //start moving toward the player
        return next;
}
