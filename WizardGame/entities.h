#ifndef ENTITIESH
#define ENTITIESH

#include "gameloop.h"
#include "map.h"

#include <string>
#include <fstream>
#include <unordered_map>
#include <optional>
#include <variant>
#include <memory>
#include <queue>
#include <iostream>

#define ID_TYPE size_t //This define makes is easier to change the type used for Item and Character IDs

namespace ent {
        /**Type Aliases**/
        /*The ID type and map key for items*/
        using ItemID = ID_TYPE;
        /*The ID type and map key for characters*/
        using CharacterID = ID_TYPE;
        /*COORDinate type used to index the Map*/
        //using Coord = Coord;

        /**Entity classes**/
        /*This class is an interface for item types to derive from.*/
        class Item
        {
        protected:
                std::variant<Coord, CharacterID> location;
        public:
                ItemID id;
                char   icon;

                /*Constructor*/
                Item(const ItemID _id, const std::variant<Coord, CharacterID> _location, const char _icon = '^');

                bool operator==(const Item& other)const;
        };

        
        /*This class is an interface for character types to derive from.
        * The two main children of this class should be Player and Enemy.
        */
        class Character
        {
        protected:
                Coord location; //location on the Map
                std::string health; //Character health.

                /*Protected Constructor only used to implement derived constructors.*/
                Character(const CharacterID _id, Coord _location, const char &_icon);
                /*Purpose: Determines if the character is dead.
                * Meant to be called from derived tick functions.
                * Preconditiions: The calling object is valid.
                * Postconditions: Returns true if the caller has 0 health and 
                * false otherwise.
                */
                bool is_dead() const;
        public:
                 CharacterID id; //Key in characters table
                 char icon; //What the character looks like in the UI.

                 const std::string get_health() const;
                 const Coord get_location() const;
                 void set_location(const Coord loc);
                 void set_health(std::string h);
                
        };

        class Player : public Character
        {
        private: 
                std::unordered_map<ItemID, Item> inventory;
        public:
                Player() = default;
                /*Constructor*/
                Player(Coord _location, const char &_icon = '^');
                /*Purpose: Allow the player to move or take other actions.
                * Preconditions: The game has started and the player character has been constructed.
                * Postconditions: The player character state for the next frame is returned.
                * Note: The result of this will need to be downcasted to Player before being inserted into the 
                * entity matrix of the next_game_state. Make absolutely certain to do this!!!
                */
                std::optional <ent::Player> tick(const gl::Input input, struct GameState current_state);
                void attack(const gl::Input input, struct GameState current_state);

                void operator=(Player& p);


        };
        /*NOT YET IMPLEMENTED*/
        class Enemy : public Character
        {
        public:
                /*constructor*/
                Enemy(CharacterID _id, const Coord &&_location, const char &&_icon = 'A');
                /*destructor*/
                //~Enemy();
                /*Purpose: Generate enemy movements and other actions.
                * Preconditions: The calling object is valid.
                * Postconditions: A unique-ptr to the player character state for the next frame is returned.
                * Note: Check to make sure the unique_ptr isn't null! 
                * The result of this will need to be downcasted to Enemy before being inserted into the
                * entity matrix of the next_game_state. Make absolutely certain to do this!!!
                */
                std::optional<Enemy> tick(const gl::Input input) const;
        };
        /**Entity Management Classes**/
        class EntityMatrix
        {
        private:
                //std::unordered_map<ItemID, Item>       item_table;       //Contains all items in play.
                //std::queue<ItemID>                     item_id_pool;     //Contains all available ItemIDs.
                std::unordered_map<CharacterID, Enemy> character_table;  //Contains all enemies in play.
                std::queue <CharacterID> character_id_pool;//Contains all available CharacterIDs.
                Player player;

                /*Purpose: To add more ids to the id pools if they become empty.
                * Preconditions: Either of the id pools is empty.
                * Postconditions: The empty id pool(s) are replenished with 10 ids.
                * Throws: Does not throw.
                * Note: Meant to be called by member functions of this class that create new entities.
                */
                void replenish_id_pools() noexcept;
        public:
                /*Purpose: To default construct objects of this type.
                * Preconditions: None.
                * Postconditions: An object of type EntityMatrix is created.
                * Throws: Does not throw.
                */
                EntityMatrix(Map &map) noexcept;

                /*Purpose: To assign a unique ItemID to an item.
                * Preconditions: The calling object must be valid.
                * Postconditions: A unique ItemID is returned.
                * Throws: None.
                * Note: Meant to be called in the constructor of an Item.
                */
                const ItemID request_item_id() noexcept;
                /*Purpose: Reclaims the ItemID of an Item that is being removed from play.
                * Preconditions: The Item whose ID is to be reclaimed is being removed from play this tick.
                * and will not exist in the next tick.
                * Throws: None.
                * Note: Meant to be called in the tick function of an Item. (Not in the destructor!!!)
                */
                void reclaim_item_id(const ItemID id) noexcept;
                /*Purpose: To assign a unique CharacterID to a Character.
                * Preconditions: The calling object must be valid.
                * Postconditions: A unique CharacterID is returned.
                * Throws: None.
                * Note: Meant to be called in the constructor of a Character.
                */
                const CharacterID request_character_id() noexcept;
                /*Purpose: Reclaims the CharacterID of a Character that is being removed from play.
                * Preconditions: The Character whose ID is to be reclaimed is being removed from play this tick.
                * and will not exist in the next tick.
                * Throws: None.
                * Note: Meant to be called in the tick function of a Character. (Not in the destructor!!!)
                */
                void reclaim_character_id(const CharacterID& id) noexcept;
                /*Purpose: To create the next iteration of the EntityMatrix.
                * Preconditions: The calling object is valid and the player is alive.
                * Postconditions: The next iteration of the EntityMatrix is created.
                * Note: Meant to be called in the handler functions of the game loop.
                * Internally calls the tick functions of all contained entities.
                */
                std::optional<EntityMatrix> generate_next(const gl::Input input) const;

                void operator=(EntityMatrix &em);

                Player& get_player();

                void set_enemies(std::vector<Coord> enemy_locs);
        };

        struct GameState
        {
                GameState();
                EntityMatrix entity_matrix;//The entity matrix contains the state of all entities in play.
                Map          map;          //Contains map state.

                /*Purpose: To serialize the current game state to a file on disk.
                * Preconditions: The calling object is valid.
                * Postconditions: A representation of the calling object is written to disk.
                * Throws: std::runtime_error if the file cannot be created or already exists.
                */
                //void save(const std::string filepath);
                /*Purpose: To populate the calling object using data from a file.
                * Preconditions: There is a valid file with the specified path that contains save data for this game.
                * Postconditions: A representation of the calling object is written to disk.
                * Throws: std::runtime_error if the specified file cannot be opened.
                */
                //void load(const std::string filepath);
                
                void operator=(GameState gs);
        };
}

#endif
