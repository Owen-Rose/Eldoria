#include "game_world.h"
#include "environment_builder.h"

GameWorld::GameWorld()
    : currentEnvironment_(nullptr), currentLocation_(nullptr) {
    initialize();
}

void GameWorld::initialize() {
    createEnvironments();
    
    // Set starting location (Village of Luminara)
    if (!environments_.empty()) {
        currentEnvironment_ = environments_[0].get();
        currentLocation_ = currentEnvironment_->getLocation(1, 1);  // Center of grid
    }
}

bool GameWorld::move(Location::Direction direction) {
    if (!currentLocation_) return false;

    Location* nextLocation = currentLocation_->getExit(direction);
    if (!nextLocation) return false;

    // Check if we're moving to a different environment
    [[maybe_unused]] auto currentCoords = getLocationCoordinates(currentLocation_);
    auto nextCoords = getLocationCoordinates(nextLocation);

    if (!nextCoords.has_value()) {
        // Moving to a different environment
        for (const auto& env : environments_) {
            auto coords = getLocationCoordinates(nextLocation);
            if (coords.has_value()) {
                currentEnvironment_ = env.get();
                break;
            }
        }
    }

    currentLocation_ = nextLocation;
    return true;
}

std::optional<std::pair<int, int>> GameWorld::getLocationCoordinates(
    const Location* location) const {
    
    for (int y = 0; y < LocationGrid::GRID_SIZE; ++y) {
        for (int x = 0; x < LocationGrid::GRID_SIZE; ++x) {
            if (currentEnvironment_->getLocation(x, y) == location) {
                return std::make_pair(x, y);
            }
        }
    }
    return std::nullopt;
}

void GameWorld::createEnvironments() {
    // Create each environment from the game design
    environments_.push_back(createEnvironment(EnvironmentType::VILLAGE_OF_LUMINARA));
    environments_.push_back(createEnvironment(EnvironmentType::WHISPERING_WOODS));
    environments_.push_back(createEnvironment(EnvironmentType::CRYSTAL_CAVES));
    environments_.push_back(createEnvironment(EnvironmentType::FORGOTTEN_LIBRARY));
    environments_.push_back(createEnvironment(EnvironmentType::ECHOING_MOUNTAINS));
    environments_.push_back(createEnvironment(EnvironmentType::SHADOW_MARSHES));
    environments_.push_back(createEnvironment(EnvironmentType::SANCTUM_OF_LIGHT));
    environments_.push_back(createEnvironment(EnvironmentType::MALAKARS_LAIR));
    
    // Hidden Grove is initially locked
    auto hiddenGrove = createEnvironment(EnvironmentType::HIDDEN_GROVE);
    environments_.push_back(std::move(hiddenGrove));

    // Connect environments according to the game design
    connectEnvironments(
        environments_[0].get(),  // Village of Luminara
        environments_[0]->getLocation(1, 0),  // North exit
        environments_[1].get(),  // Whispering Woods
        environments_[1]->getLocation(1, 2)   // South entrance
    );

    // Add other environment connections as per the game design...
}

std::unique_ptr<LocationGrid> GameWorld::createEnvironment(EnvironmentType type) {
    return EnvironmentBuilder::buildEnvironment(type);
}

void GameWorld::connectEnvironments(
    LocationGrid* env1, Location* exit1,
    LocationGrid* env2, Location* exit2) {
    
    if (env1 && exit1 && env2 && exit2) {
        // Create one-way connections between environments
        exit1->addExit(Location::Direction::NORTH, exit2);
        exit2->addExit(Location::Direction::SOUTH, exit1);
    }
}