#ifndef ENTITIESH
#define ENTITIESH

#include <string>
#include <fstream>
#include <unordered_map>
#include <variant>

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
        using Coord = std::pair<long int, long int>;

        /*This class is an interface for character types to derive from.
        * The two main children of this class should be Player and Enemy.
        */
        class Character
        {
        protected:
                Coord location;
        public:
                const CharacterID id;

        };

        class Player : public Character
        {

        };

        class Enemy : public Character
        {

        };

        class EntityMatrix
        {
        protected:
                std::unordered_map<ItemID, Item> item_table;
                std::unordered_map<CharacterID, Enemy> character_table;
                std::pair<CharacterID, Player> player;
        public:
                /*Purpose: To default construct objects of this type.
                * Preconditions: None.
                * Postconditions: An object of type EntityMatrix is created.
                * Throws: Does not throw exceptions.
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
