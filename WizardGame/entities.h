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

#define ID_TYPE size_t //This define makes is easier to change the type used for Item and Character IDs

namespace ent {
        /*The ID type and map key for items*/
        using ItemID = const ID_TYPE;
        /*The ID type and map key for characters*/
        using CharacterID = const ID_TYPE;

        /*This class is an interface for item types to derive from.*/
        class Item
        {
        protected:
                std::variant<Coord, CharacterID> location;
        public:
                const ItemID id;
                const char   icon;
        };

        /*This is a placeholder type. Will need to be replaced*/
        using Coord = std::pair<int, int>;

        /*This class is an interface for character types to derive from.
        * The two main children of this class should be Player and Enemy.
        */
        class Character
        {
        protected:
                Coord location; //location on the Map

                /*Protected Constructor only used to implement derived constructors.*/
                Character(CharacterID _id, const Coord&& _location, const char&& _icon);
        public:
                const CharacterID id; //Key in characters table
                const char icon; //What the character looks like in the UI.

                /*Overloads of this virtual function in derived classes should 
                 *return the next character state in each frame of the game loop.
                */
                virtual std::unique_ptr<Character> tick() = 0; 
                /*Destructor 
                 *Needed to return ids to free pool
                */
                virtual ~Character() = 0;
        };

        class Player : public Character
        {
        private: 
                std::unordered_set<Item> inventory;
        public:
                //Delete the autogen'd default constructor because its use is invalid.
                Player() = delete; 
                /*Constructor*/
                Player(const Coord &&_location, const char &&_icon = '^');
                /*Destructor*/
                ~Player();
                /*Purpose: Allow the player to move or take other actions.
                * Preconditions: The game has started and the player character has been constructed.
                * Postconditions: The player character state for the next frame is returned.
                * Note: The result of this will need to be downcasted to Player before being inserted into the 
                * entity matrix of the next_game_state. Make absolutely certain to do this!!!
                */
                std::unique_ptr<Character> tick();
        };

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
                std::unique_ptr<Character> tick();
        };

        class EntityMatrix
        {
        private:
                std::unordered_map<ItemID, Item> item_table;
                std::unordered_set<ItemID> item_id_pool;
                std::unordered_map<CharacterID, Enemy> character_table;
                std::unordered_set<CharacterID> item_id_pool;
                Player player;
                
        public:
                /*Purpose: To default construct objects of this type.
                * Preconditions: None.
                * Postconditions: An object of type EntityMatrix is created.
                * Throws: Does not throw.
                */
                EntityMatrix() noexcept;
        };

        struct GameState
        {
                EntityMatrix entity_matrix;
                Map         map;

                /*Purpose: To serialize the current game state to a file on disk.
                * Preconditions: The calling object is valid.
                * Postconditions: A representation of the calling object is written to disk.
                * Throws: std::runtime_error if the file cannot be created or already exists.
                */
                void save(const std::string filepath);
                /*Purpose: To populate the calling object using data from a file.
                * Preconditions: There is a valid file with the specified path that contains save data for this game.
                * Postconditions: A representation of the calling object is written to disk.
                * Throws: std::runtime_error if the specified file cannot be opened.
                */
                void load(const std::string filepath);
        };
}

#endif
