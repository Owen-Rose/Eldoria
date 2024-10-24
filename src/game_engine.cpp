#include "game_engine.h"
#include "npc.h"
#include "usable_item.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <algorithm>

GameEngine::GameEngine() 
    : running_(false), 
      gameWorld_(nullptr),
      currentPlayer_(nullptr) {
}

void GameEngine::run() {
    initialize();
    running_ = true;

    // Display welcome message and initial location
    displayWelcomeMessage();
    displayCurrentLocation();

    // Main game loop
    while (running_) {
        processTurn();
    }

    std::cout << "\nThank you for playing Eldoria: Shadows of Malakar!\n";
}

void GameEngine::initialize() {
    try {
        // Initialize game world
        gameWorld_ = std::make_unique<GameWorld>();
        
        // Initialize player (will be expanded in future phases)
        currentPlayer_ = std::make_unique<Player>("Aric", "A courageous adventurer destined to save Eldoria.");
        
        // Ensure initialization was successful
        if (!gameWorld_->getCurrentLocation()) {
            throw std::runtime_error("Failed to initialize starting location");
        }
    } catch (const std::exception& e) {
        std::cerr << "Initialization error: " << e.what() << std::endl;
        running_ = false;
    }
}

void GameEngine::processTurn() {
    try {
        std::cout << "\n> ";
        auto command = commandParser_.getCommand();

        if (command.isValid) {
            executeCommand(command);
        } else {
            std::cout << "Invalid command. Type 'help' for a list of commands.\n";
        }
    } catch (const std::exception& e) {
        std::cerr << "Error processing turn: " << e.what() << std::endl;
    }
}

void GameEngine::executeCommand(const CommandParser::Command& command) {
    try {
        if (command.action == "quit") {
            stop();
            return;
        }

        // Handle movement commands
        if (command.action == "go" || command.action == "move") {
            handleMovement(command);
            return;
        }

        // Handle look commands
        if (command.action == "look") {
            displayCurrentLocation();
            return;
        }

        // Handle examine commands
        if (command.action == "examine") {
            handleExamine(command);
            return;
        }

        // Handle item-related commands
        if (command.action == "take" || command.action == "pickup") {
            handlePickup(command);
            return;
        }

        if (command.action == "drop") {
            handleDrop(command);
            return;
        }

        if (command.action == "inventory" || command.action == "inv") {
            displayInventory();
            return;
        }

        if (command.action == "use") {
            handleUse(command);
            return;
        }

        // Handle help command
        if (command.action == "help") {
            displayHelp();
            return;
        }

        std::cout << "Unknown command. Type 'help' for available commands.\n";
    } catch (const std::exception& e) {
        std::cerr << "Error executing command: " << e.what() << std::endl;
    }
}

void GameEngine::handleMovement(const CommandParser::Command& command) {
    if (command.arguments.empty()) {
        std::cout << "Go where? Please specify a direction (north, south, east, west).\n";
        return;
    }

    const std::string& direction = command.arguments[0];
    Location::Direction dir;

    // Convert string direction to enum
    if (direction == "north") dir = Location::Direction::NORTH;
    else if (direction == "south") dir = Location::Direction::SOUTH;
    else if (direction == "east") dir = Location::Direction::EAST;
    else if (direction == "west") dir = Location::Direction::WEST;
    else {
        std::cout << "Invalid direction. Please use: north, south, east, or west.\n";
        return;
    }

    // Attempt movement
    if (gameWorld_->move(dir)) {
        std::cout << "You move " << direction << ".\n";
        displayCurrentLocation();
    } else {
        std::cout << "You cannot go that way.\n";
    }
}

void GameEngine::handleExamine(const CommandParser::Command& command) {
    if (command.arguments.empty()) {
        std::cout << "What would you like to examine?\n";
        return;
    }

    Location* currentLoc = gameWorld_->getCurrentLocation();
    if (!currentLoc) {
        std::cout << "Error: Cannot examine items in invalid location.\n";
        return;
    }

    // Combine remaining arguments for multi-word items
    std::string itemName;
    for (size_t i = 0; i < command.arguments.size(); ++i) {
        itemName += command.arguments[i];
        if (i < command.arguments.size() - 1) itemName += " ";
    }

    // Check inventory first
    auto inventoryItem = currentPlayer_->getItem(itemName);
    if (inventoryItem) {
        std::cout << inventoryItem->getDescription() << "\n";
        return;
    }

    // Check location items
    const auto& items = currentLoc->getItems();
    auto it = std::find_if(items.begin(), items.end(),
        [&itemName](const std::shared_ptr<Item>& item) {
            return item->getName() == itemName;
        });

    if (it != items.end()) {
        std::cout << (*it)->getDescription() << "\n";
        return;
    }

    // Check NPCs
    const auto& npcs = currentLoc->getNPCs();
    auto npcIt = std::find_if(npcs.begin(), npcs.end(),
        [&itemName](const std::shared_ptr<NPC>& npc) {
            return npc->getName() == itemName;
        });

    if (npcIt != npcs.end()) {
        std::cout << (*npcIt)->getDescription() << "\n";
        return;
    }

    std::cout << "You don't see that here.\n";
}

void GameEngine::handlePickup(const CommandParser::Command& command) {
    if (command.arguments.empty()) {
        std::cout << "What would you like to take?\n";
        return;
    }

    Location* currentLoc = gameWorld_->getCurrentLocation();
    if (!currentLoc) {
        std::cout << "Error: Cannot take items in invalid location.\n";
        return;
    }

    // Combine multi-word item names and convert to lowercase for comparison
    std::string itemName;
    for (size_t i = 0; i < command.arguments.size(); ++i) {
        itemName += command.arguments[i];
        if (i < command.arguments.size() - 1) itemName += " ";
    }

    // Debug information
    std::cout << "Debug: Looking for item '" << itemName << "'\n";
    const auto& items = currentLoc->getItems();
    std::cout << "Debug: Location has " << items.size() << " items:\n";
    for (const auto& item : items) {
        std::cout << "Debug: Found '" << item->getName() << "' in location\n";
    }

    // Convert item name to lowercase for case-insensitive comparison
    std::string lowerItemName = itemName;
    std::transform(lowerItemName.begin(), lowerItemName.end(), 
                  lowerItemName.begin(), ::tolower);

    // Find the item in the current location
    auto it = std::find_if(items.begin(), items.end(),
        [&lowerItemName](const std::shared_ptr<Item>& item) {
            std::string itemNameLower = item->getName();
            std::transform(itemNameLower.begin(), itemNameLower.end(), 
                         itemNameLower.begin(), ::tolower);
            return itemNameLower == lowerItemName;
        });

    if (it != items.end()) {
        if (currentPlayer_->addItem(*it)) {
            if (currentLoc->removeItem((*it)->getName())) {
                std::cout << "Taken: " << (*it)->getName() << "\n";
            } else {
                std::cout << "Error: Failed to remove item from location\n";
                currentPlayer_->removeItem((*it)->getName()); // Rollback
            }
        } else {
            std::cout << "You can't carry any more items.\n";
        }
    } else {
        std::cout << "You don't see that here.\n";
    }
}

void GameEngine::handleDrop(const CommandParser::Command& command) {
    if (command.arguments.empty()) {
        std::cout << "What would you like to drop?\n";
        return;
    }

    Location* currentLoc = gameWorld_->getCurrentLocation();
    if (!currentLoc) {
        std::cout << "Error: Cannot drop items in invalid location.\n";
        return;
    }

    // Combine multi-word item names
    std::string itemName;
    for (size_t i = 0; i < command.arguments.size(); ++i) {
        itemName += command.arguments[i];
        if (i < command.arguments.size() - 1) itemName += " ";
    }

    // Find the item in player's inventory
    auto item = currentPlayer_->getItem(itemName);
    if (item) {
        currentLoc->addItem(item);
        currentPlayer_->removeItem(itemName);
        std::cout << "Dropped: " << itemName << "\n";
    } else {
        std::cout << "You don't have that item.\n";
    }
}

void GameEngine::handleUse(const CommandParser::Command& command) {
    if (command.arguments.empty()) {
        std::cout << "What would you like to use?\n";
        return;
    }

    // Combine multi-word item names
    std::string itemName;
    for (size_t i = 0; i < command.arguments.size(); ++i) {
        itemName += command.arguments[i];
        if (i < command.arguments.size() - 1) itemName += " ";
    }

    auto item = currentPlayer_->getItem(itemName);
    if (!item) {
        std::cout << "You don't have that item.\n";
        return;
    }

    // Try to cast to UsableItem
    auto usableItem = std::dynamic_pointer_cast<UsableItem>(item);
    if (!usableItem) {
        std::cout << "You can't use that item.\n";
        return;
    }

    if (usableItem->CanUse()) {
        std::cout << usableItem->Use() << "\n";
    } else {
        std::cout << "You can't use that item here.\n";
    }
}

void GameEngine::displayInventory() {
    std::cout << "\n=== Inventory ===\n";
    std::string inventoryDesc = currentPlayer_->getInventoryDescription();
    if (inventoryDesc.empty()) {
        std::cout << "Your inventory is empty.\n";
    } else {
        std::cout << inventoryDesc << "\n";
    }
}

void GameEngine::displayCurrentLocation() {
    Location* currentLoc = gameWorld_->getCurrentLocation();
    if (!currentLoc) {
        std::cout << "Error: Invalid location!\n";
        return;
    }

    // Display location header
    std::cout << "\n" << std::string(50, '=') << "\n";
    std::cout << std::setw(25) << currentLoc->getName() << "\n";
    std::cout << std::string(50, '=') << "\n";

    // Display description
    std::cout << currentLoc->getDescription() << "\n\n";

    // Display exits
    std::cout << "Exits:";
    if (currentLoc->getExit(Location::Direction::NORTH)) std::cout << " north";
    if (currentLoc->getExit(Location::Direction::EAST)) std::cout << " east";
    if (currentLoc->getExit(Location::Direction::SOUTH)) std::cout << " south";
    if (currentLoc->getExit(Location::Direction::WEST)) std::cout << " west";
    std::cout << "\n";

    // Display items in location
    const auto& items = currentLoc->getItems();
    if (!items.empty()) {
        std::cout << "\nYou see:";
        for (const auto& item : items) {
            std::cout << "\n- " << item->getName();
        }
        std::cout << "\n";
    }

    // Display NPCs in location
    const auto& npcs = currentLoc->getNPCs();
    if (!npcs.empty()) {
        std::cout << "\nPresent here:";
        for (const auto& npc : npcs) {
            std::cout << "\n- " << npc->getName();
        }
        std::cout << "\n";
    }
}

void GameEngine::displayHelp() {
    std::cout << "\n=== AVAILABLE COMMANDS ===\n\n"
              << "Movement:\n"
              << "  go [direction]  - Move in specified direction (north, south, east, west)\n"
              << "  move [direction]- Alternative to 'go'\n\n"
              << "Environment:\n"
              << "  look           - Look around your current location\n"
              << "  examine [item] - Look at a specific item or feature\n\n"
              << "Item Management:\n"
              << "  take/pickup [item] - Pick up an item\n"
              << "  drop [item]    - Drop an item from your inventory\n"
              << "  inventory/inv  - Show your inventory\n"
              << "  use [item]     - Use an item\n\n"
              << "System:\n"
              << "  help           - Show this help message\n"
              << "  quit           - Exit the game\n\n";
}

void GameEngine::displayWelcomeMessage() {
    std::cout << "\n" << std::string(60, '*') << "\n"
              << "Welcome to Eldoria: Shadows of Malakar\n"
              << "A text adventure game\n"
              << std::string(60, '*') << "\n\n"
              << "Type 'help' for a list of commands.\n\n";
}

void GameEngine::stop() {
    running_ = false;
}

bool GameEngine::isRunning() const {
    return running_;
}