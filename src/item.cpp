#include "item.h"

Item::Item(const std::string& id, const std::string& name, const std::string& description)
    : Entity(name, description), item_id_(id), current_location_(nullptr) {}

std::string Item::GetItemId() const {
    return item_id_;
}

bool Item::PickUp() {
    if (current_location_ == nullptr) {
        return false;
    }
    // Additional logic will be added when inventory system is implemented
    return true;
}

bool Item::Drop() {
    if (current_location_ == nullptr) {
        return false;
    }
    // Additional logic will be added when inventory system is implemented
    return true;
}

void Item::SetLocation(Location* location) {
    current_location_ = location;
}

Location* Item::GetLocation() const {
    return current_location_;
}

std::string Item::Examine() const {
    return Entity::Examine() + "\nID: " + item_id_;
}