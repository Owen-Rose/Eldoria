// location.h
#ifndef LOCATION_H_
#define LOCATION_H_

#include "entity.h"
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>

class Item;
class NPC;
class Puzzle;

/**
 * @class Location
 * @brief Represents a single location in the game world
 * 
 * Locations are connected to other locations through exits in cardinal directions,
 * can contain items and NPCs, and may have associated puzzles.
 */
class Location {
 public:
    /**
     * @brief Direction enumeration for exits
     */
    enum class Direction {
        NORTH,
        EAST,
        SOUTH,
        WEST
    };

    /**
     * @brief Constructor for Location
     * @param name The name of the location
     * @param description A detailed description of the location
     */
    Location(const std::string& name, const std::string& description);

    /**
     * @brief Get the location's name
     * @return The name of the location
     */
    std::string getName() const { return name_; }

    /**
     * @brief Get the location's description
     * @return The description of the location
     */
    std::string getDescription() const { return description_; }

    /**
     * @brief Add an exit to another location
     * @param direction The direction of the exit
     * @param location Pointer to the connected location
     * @return true if exit was added successfully
     */
    bool addExit(Direction direction, Location* location);

    /**
     * @brief Get the location connected in a given direction
     * @param direction The direction to check
     * @return Pointer to the connected location, nullptr if no exit exists
     */
    Location* getExit(Direction direction) const;

    /**
     * @brief Add an item to the location
     * @param item Shared pointer to the item to add
     */
    void addItem(std::shared_ptr<Item> item);

    /**
     * @brief Remove an item from the location
     * @param itemName Name of the item to remove
     * @return Shared pointer to the removed item, nullptr if not found
     */
    std::shared_ptr<Item> removeItem(const std::string& itemName);

    /**
     * @brief Add an NPC to the location
     * @param npc Shared pointer to the NPC to add
     */
    void addNPC(std::shared_ptr<NPC> npc);

    /**
     * @brief Get all items in the location
     * @return Vector of items in the location
     */
    const std::vector<std::shared_ptr<Item>>& getItems() const { return items_; }

    /**
     * @brief Get all NPCs in the location
     * @return Vector of NPCs in the location
     */
    const std::vector<std::shared_ptr<NPC>>& getNPCs() const { return npcs_; }

    /**
     * @brief Set the location's puzzle
     * @param puzzle Shared pointer to the puzzle
     */
    void setPuzzle(std::shared_ptr<Puzzle> puzzle);

    /**
     * @brief Get the location's puzzle
     * @return Shared pointer to the puzzle, nullptr if none exists
     */
    std::shared_ptr<Puzzle> getPuzzle() const { return puzzle_; }

    /**
     * @brief Generate a detailed description of the location including items and NPCs
     * @return String containing the full description
     */
    std::string getFullDescription() const;

 private:
    std::string name_;                       ///< Name of the location
    std::string description_;                ///< Description of the location
    std::unordered_map<Direction, Location*> exits_;  ///< Map of exits to other locations
    std::vector<std::shared_ptr<Item>> items_;        ///< Items in the location
    std::vector<std::shared_ptr<NPC>> npcs_;          ///< NPCs in the location
    std::shared_ptr<Puzzle> puzzle_;                  ///< Associated puzzle
};

#endif