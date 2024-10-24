#ifndef USABLE_ITEM_H_
#define USABLE_ITEM_H_

#include "item.h"
#include <string>
#include <functional>

/**
 * @class UsableItem
 * @brief Represents an item that can be used to perform specific actions.
 * 
 * UsableItem extends the basic Item class by adding usage functionality.
 * Each usable item can have a specific effect when used, and may have
 * requirements for when it can be used.
 */
class UsableItem : public Item {
 public:
    /**
     * @brief Function type for the use effect of an item
     * @return string describing the result of using the item
     */
    using UseEffect = std::function<std::string()>;

    /**
     * @brief Constructor creating a usable item
     * @param id the id of an Item.
     * @param name The name of the item
     * @param description The item's description
     * @param use_effect The function to be called when item is used
     */
    UsableItem(const std::string& id,
               const std::string& name, 
               const std::string& description,
               UseEffect use_effect);

    /**
     * @brief Virtual destructor
     */
    virtual ~UsableItem() = default;

    /**
     * @brief Attempt to use the item
     * @return string describing the result of using the item
     */
    virtual std::string Use();

    /**
     * @brief Check if the item can be used
     * @return true if the item can be used, false otherwise
     */
    virtual bool CanUse() const;

    /**
     * @brief Get the use description of the item
     * @return string describing how the item can be used
     */
    std::string GetUseDescription() const;

 protected:
    UseEffect use_effect_;    ///< The effect when item is used
};

/**
 * @class CrystalLens
 * @brief Specific implementation of the Crystal Lens usable item
 */
class CrystalLens : public UsableItem {
 public:
    /**
     * @brief Constructor for Crystal Lens
     */
    CrystalLens();

    /**
     * @brief Override to add specific logic for using the Crystal Lens
     * @return string describing the result of using the lens
     */
    std::string Use() override;

    /**
     * @brief Check if the Crystal Lens can be used in current context
     * @return true if the lens can be used, false otherwise
     */
    bool CanUse() const override;
};

/**
 * @class HerbalMixture
 * @brief Specific implementation of the Herbal Mixture usable item
 */
class HerbalMixture : public UsableItem {
 public:
    /**
     * @brief Constructor for Herbal Mixture
     */
    HerbalMixture();

    /**
     * @brief Override to add specific logic for using the Herbal Mixture
     * @return string describing the result of using the mixture
     */
    std::string Use() override;

    /**
     * @brief Check if the Herbal Mixture can be used in current context
     * @return true if the mixture can be used, false otherwise
     */
    bool CanUse() const override;
};

/**
 * @class StaffOfLumos
 * @brief Required for the final confrontation with Malakar
 */
class StaffOfLumos : public UsableItem {
 public:
    StaffOfLumos();
    std::string Use() override;
    bool CanUse() const override;

 private:
    bool IsInMalakarLair() const;  // Helper to check location
};

/**
 * @class EchoCrystal
 * @brief Used for solving the Echo Puzzle
 */
class EchoCrystal : public UsableItem {
 public:
    EchoCrystal();
    std::string Use() override;
    bool CanUse() const override;
    
    // Additional methods specific to the echo puzzle
    void RecordSound(const std::string& sound);
    bool HasRecordedSound() const;

 private:
    std::string recorded_sound_;
};

/**
 * @class SilverKey
 * @brief Used to open the door in Malakar's Lair
 */
class SilverKey : public UsableItem {
 public:
    SilverKey();
    std::string Use() override;
    bool CanUse() const override;

 private:
    bool IsAtMalakarDoor() const;  // Helper to check location
};

#endif  // USABLE_ITEM_H_