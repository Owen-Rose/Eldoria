#include "location.h"
#include "item.h"
#include "npc.h"
#include "puzzle.h"
#include <algorithm>
#include <sstream>

Location::Location(const std::string& name, const std::string& description)
    : name_(name), description_(description) {}

bool Location::addExit(Direction direction, Location* location) {
    // Don't allow null locations or overwriting existing exits
    if (location == nullptr || exits_.find(direction) != exits_.end()) {
        return false;
    }
    
    exits_[direction] = location;
    return true;
}

Location* Location::getExit(Direction direction) const {
    auto it = exits_.find(direction);
    return (it != exits_.end()) ? it->second : nullptr;
}

void Location::addItem(std::shared_ptr<Item> item) {
    if (item) {
        items_.push_back(item);
        item->SetLocation(this);
    }
}

std::shared_ptr<Item> Location::removeItem(const std::string& itemName) {
    auto it = std::find_if(items_.begin(), items_.end(),
                          [&itemName](const std::shared_ptr<Item>& item) {
                              return item->getName() == itemName;
                          });
    
    if (it != items_.end()) {
        auto item = *it;
        items_.erase(it);
        item->SetLocation(nullptr);
        return item;
    }
    return nullptr;
}

void Location::addNPC(std::shared_ptr<NPC> npc) {
    if (npc) {
        npcs_.push_back(npc);
    }
}

void Location::setPuzzle(std::shared_ptr<Puzzle> puzzle) {
    puzzle_ = puzzle;
}

std::string Location::getFullDescription() const {
    std::stringstream desc;
    
    // Basic description
    desc << description_ << "\n";

    // List items
    if (!items_.empty()) {
        desc << "\nYou can see:";
        for (const auto& item : items_) {
            desc << "\n- " << item->getName();
        }
    }

    // List NPCs
    if (!npcs_.empty()) {
        desc << "\n\nPresent here:";
        for (const auto& npc : npcs_) {
            desc << "\n- " << npc->getName();
        }
    }

    // List exits
    if (!exits_.empty()) {
        desc << "\n\nExits:";
        for (const auto& [direction, location] : exits_) {
            switch (direction) {
                case Direction::NORTH:
                    desc << "\n- North"; break;
                case Direction::SOUTH:
                    desc << "\n- South"; break;
                case Direction::EAST:
                    desc << "\n- East"; break;
                case Direction::WEST:
                    desc << "\n- West"; break;
            }
            desc << " (to " << location->getName() << ")";
        }
    }

    // Mention puzzle if present
    if (puzzle_) {
        desc << "\n\nThere appears to be a puzzle here: " << puzzle_->GetName();
    }

    return desc.str();
}