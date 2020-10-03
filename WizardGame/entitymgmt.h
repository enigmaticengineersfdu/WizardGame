#ifndef ENTITYMGMTH
#define ENTITYMGMTH

#include <unordered_map>
#include <unordered_set>

#include "entities.h"

namespace ent {
        /**Entity Management Classes**/
        class EntityMatrix
        {
        private:
                std::unordered_map<ItemID, Item> item_table;
                std::unordered_set<ItemID> item_id_pool;
                std::unordered_map<CharacterID, Enemy> character_table;
                std::unordered_set<CharacterID> character_id_pool;
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
                //Map         map;

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
