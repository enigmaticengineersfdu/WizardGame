#ifndef ENTITIESH
#define ENTITIESH

#include <string>
#include <fstream>
#include <unordered_map>
#include <unordered_set>
#include <optional>
#include <variant>
#include <memory>
#include <utility>

#include "gameloop.h"

#define ID_TYPE size_t //This define makes is easier to change the type used for Item and Character IDs

namespace ent {
        /**Type Aliases**/
        /*The ID type and map key for items*/
        using ItemID = ID_TYPE;
        /*The ID type and map key for characters*/
        using CharacterID = ID_TYPE;
        /*Coordinate type used to index the Map*/
        using Coord = std::pair<int, int>;

        /**Entity classes**/
        /*This class is an interface for item types to derive from.*/
        class Item
        {
        protected:
                std::variant<Coord, CharacterID> location;
        public:
                const ItemID id;
                const char   icon;

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
                unsigned int health; //Character health. (Be careful not to underflow this value!)

                /*Protected Constructor only used to implement derived constructors.*/
                Character(const CharacterID _id, const Coord &_location, const char &_icon);
                /*Purpose: Determines if the character is dead.
                * Meant to be called from derived tick functions.
                * Preconditiions: The calling object is valid.
                * Postconditions: Returns true if the caller has 0 health and 
                * false otherwise.
                */
                bool is_dead() const;
        public:
                 const CharacterID id; //Key in characters table
                 const char icon; //What the character looks like in the UI.

                
        };

        class Player : public Character
        {
        private: 
                std::unordered_map<ItemID, Item> inventory;
        public:
                //Delete the autogen'd default constructor because its use is invalid.
                Player() = delete; 
                /*Constructor*/
                Player(const Coord &_location, const char &_icon = '^');
                /*Purpose: Allow the player to move or take other actions.
                * Preconditions: The game has started and the player character has been constructed.
                * Postconditions: The player character state for the next frame is returned.
                * Note: The result of this will need to be downcasted to Player before being inserted into the 
                * entity matrix of the next_game_state. Make absolutely certain to do this!!!
                */
                std::optional<Player> tick(const gl::Input input) const;
        };
        /*NOT YET IMPLEMENTED*/
        class Enemy : public Character
        {
        private:
                std::optional<Item> drop_item;
        public:
                //Delete the autogen'd default constructor because its use is invalid.
                Enemy() = delete;
                /*constructor*/
                Enemy(CharacterID _id, const Coord &&_location, const char &&_icon = 'X', const std::optional<Item> &&_drop_item = std::nullopt);
                /*destructor*/
                ~Enemy();
                /*Purpose: Generate enemy movements and other actions.
                * Preconditions: The calling object is valid.
                * Postconditions: A unique-ptr to the player character state for the next frame is returned.
                * Note: Check to make sure the unique_ptr isn't null! 
                * The result of this will need to be downcasted to Enemy before being inserted into the
                * entity matrix of the next_game_state. Make absolutely certain to do this!!!
                */
                std::optional<Enemy> tick(const gl::Input input) const;
        };
}

#endif
