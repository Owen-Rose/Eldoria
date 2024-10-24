// item.h
#ifndef ITEM_H_
#define ITEM_H_

#include "entity.h"
#include <string>
#include <memory>

class Location;

/**
 * @class Item
 * @brief Represents an item in the game that can be picked up and used.
 */
class Item : public Entity {
 public:
    /**
     * @brief Constructor creating an item
     * @param id Unique identifier for the item
     * @param name The name of the item
     * @param description A detailed description of the item
     */
    Item(const std::string& id, const std::string& name, const std::string& description);

    /**
     * @brief Virtual destructor
     */
    virtual ~Item() = default;

    /**
     * @brief Get the unique identifier of the item
     * @return The item's ID
     */
    std::string GetItemId() const;

    /**
     * @brief Attempt to pick up the item
     * @return true if the item was successfully picked up
     */
    virtual bool PickUp();

    /**
     * @brief Attempt to drop the item
     * @return true if the item was successfully dropped
     */
    virtual bool Drop();

    /**
     * @brief Set the current location of the item
     * @param location Pointer to the new location
     */
    void SetLocation(Location* location);

    /**
     * @brief Get the current location of the item
     * @return Pointer to the current location
     */
    Location* GetLocation() const;

    /**
     * @brief Examine the item
     * @return String containing examination results
     */
    std::string Examine() const override;

 private:
    std::string item_id_;           ///< Unique identifier for the item
    Location* current_location_;    ///< Current location of the item
};

#endif  // ITEM_H_