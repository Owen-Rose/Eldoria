#include "player.h"
#include <algorithm>
#include <sstream>

Player::Player(const std::string& name, const std::string& description)
    : Entity(name, description),
      inventory_capacity_(10),
      current_location_(nullptr) {
}

bool Player::addItem(std::shared_ptr<Item> item) {
    if (inventory_.size() >= inventory_capacity_) {
        return false;
    }

    inventory_.push_back(item);
    return true;
}

bool Player::removeItem(const std::string& itemName) {
    auto it = std::find_if(inventory_.begin(), inventory_.end(),
        [&itemName](const std::shared_ptr<Item>& item) {
            return item->getName() == itemName;
        });

    if (it != inventory_.end()) {
        inventory_.erase(it);
        return true;
    }
    return false;
}

std::shared_ptr<Item> Player::getItem(const std::string& itemName) const {
    auto it = std::find_if(inventory_.begin(), inventory_.end(),
        [&itemName](const std::shared_ptr<Item>& item) {
            return item->getName() == itemName;
        });

    return (it != inventory_.end()) ? *it : nullptr;
}

std::string Player::getInventoryDescription() const {
    if (inventory_.empty()) {
        return "";
    }

    std::ostringstream oss;
    for (const auto& item : inventory_) {
        oss << "- " << item->getName() << ": " << item->getDescription() << "\n";
    }
    return oss.str();
}

bool Player::useItem(const std::string& itemId) {
    auto item = getItem(itemId);
    if (!item) {
        return false;
    }

    // Check if item is usable
    auto usableItem = std::dynamic_pointer_cast<UsableItem>(item);
    if (!usableItem) {
        return false;
    }

    // Attempt to use the item
    if (!usableItem->CanUse()) {
        return false;
    }

    // Use the item
    usableItem->Use();
    return true;
}

void Player::setLocation(Location* location) {
    current_location_ = location;
}

Location* Player::getLocation() const {
    return current_location_;
}

std::string Player::getStatus() const {
    std::ostringstream oss;
    oss << "=== " << getName() << " ===\n"
        << "Current Location: " << (current_location_ ? current_location_->getName() : "Unknown") << "\n"
        << "Inventory: " << inventory_.size() << "/" << inventory_capacity_ << " items\n";
    
    return oss.str();
}

std::string Player::Examine() const {
    return Entity::Examine() + "\n" + getInventoryDescription();
}

void Player::reset() {
    inventory_.clear();
    current_location_ = nullptr;
}