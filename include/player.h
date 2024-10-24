#ifndef PLAYER_H_
#define PLAYER_H_

#include "entity.h"
#include "usable_item.h"
#include "location.h"
#include "item.h"
#include <memory>
#include <vector>
#include <string>

/**
 * @class Player
 * @brief Represents the player character in the game
 *
 * This class handles all player-specific functionality including inventory
 * management, item usage, and location tracking. It extends the base Entity
 * class with features needed for player interaction in a puzzle-based
 * adventure game.
 */
class Player : public Entity
{
public:
    /**
     * @brief Constructor for Player
     * @param name The player's name
     * @param description The player's description
     */
    Player(const std::string &name, const std::string &description);

    /**
     * @brief Virtual destructor
     */
    virtual ~Player() = default;

    /**
     * @brief Add an item to the player's inventory
     * @param item The item to add
     * @return true if the item was added successfully
     */
    bool addItem(std::shared_ptr<Item> item);

    /**
     * @brief Remove an item from the player's inventory
     * @param itemId The ID of the item to remove
     * @return true if the item was removed successfully
     */
    bool removeItem(const std::string &itemId);

    /**
     * @brief Get an item from the player's inventory
     * @param itemId The ID of the item to get
     * @return Shared pointer to the item, nullptr if not found
     */
    std::shared_ptr<Item> getItem(const std::string &itemId) const;

    /**
     * @brief Check if player has a specific item
     * @param itemId The ID of the item to check
     * @return true if the player has the item
     */
    bool hasItem(const std::string &itemId) const;

    /**
     * @brief Get a description of the player's inventory
     * @return String containing inventory description
     */
    std::string getInventoryDescription() const;

    /**
     * @brief Use an item from the inventory
     * @param itemId The ID of the item to use
     * @return true if the item was used successfully
     */
    bool useItem(const std::string &itemId);

    /**
     * @brief Set the player's current location
     * @param location Pointer to the new location
     */
    void setLocation(Location *location);

    /**
     * @brief Get the player's current location
     * @return Pointer to the current location
     */
    Location *getLocation() const;

    /**
     * @brief Get the player's current status
     * @return String containing player status information
     */
    std::string getStatus() const;

    /**
     * @brief Examine the player and their inventory
     * @return String containing examination results
     */
    std::string Examine() const override;

    /**
     * @brief Reset the player to initial state
     */
    void reset();

private:
    size_t inventory_capacity_;                    ///< Maximum inventory size
    std::vector<std::shared_ptr<Item>> inventory_; ///< Player's inventory
    Location *current_location_;                   ///< Player's current location
};

#endif // PLAYER_H_