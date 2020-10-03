#ifndef ENTITYMGMTH
#define ENTITYMGMTH

#include <unordered_map>
#include <queue>

#include "gameloop.h"
#include "entities.h"
#include "map.h"

namespace ent {
        /**Entity Management Classes**/
        class EntityMatrix
        {
        private:
                std::unordered_map<ItemID, Item>       item_table;       //Contains all items in play.
                std::queue<ItemID>                     item_id_pool;     //Contains all available ItemIDs.
                std::unordered_map<CharacterID, Enemy> character_table;  //Contains all enemies in play.
                std::queue<CharacterID>                character_id_pool;//Contains all available CharacterIDs.
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
                EntityMatrix() noexcept;

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
                void reclaim_character_id(const ItemID &id) noexcept;
                /*Purpose: To create the next iteration of the EntityMatrix.
                * Preconditions: The calling object is valid and the player is alive. 
                * Postconditions: The next iteration of the EntityMatrix is created.
                * Note: Meant to be called in the handler functions of the game loop.
                * Internally calls the tick functions of all contained entities.
                */
                std::optional<EntityMatrix> generate_next(const gl::Input input) const;
        };

        struct GameState
        {
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
        };
}

#endif
