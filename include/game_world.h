#ifndef GAME_WORLD_H_
#define GAME_WORLD_H_

#include "location_grid.h"
#include "environment_type.h"
#include <vector>
#include <memory>
#include <unordered_map>

/**
 * @class GameWorld
 * @brief GameWorld supporting grid-based environments
 */
class GameWorld {
 public:
    /**
     * @brief Constructor for GameWorld
     */
    GameWorld();

    /**
     * @brief Initialize the game world
     */
    void initialize();

    /**
     * @brief Get the current location
     * @return Pointer to the current location
     */
    Location* getCurrentLocation() const { return currentLocation_; }

    /**
     * @brief Get the current environment
     * @return Pointer to the current environment's grid
     */
    LocationGrid* getCurrentEnvironment() const { return currentEnvironment_; }

    /**
     * @brief Attempt to move in a direction within the current grid
     * @param direction The direction to move
     * @return true if movement was successful
     */
    bool move(Location::Direction direction);

    /**
     * @brief Get the coordinates of a location within its grid
     * @param location The location to find
     * @return Optional pair of coordinates, empty if not found
     */
    std::optional<std::pair<int, int>> getLocationCoordinates(const Location* location) const;

 private:
    std::vector<std::unique_ptr<LocationGrid>> environments_;  ///< All environment grids
    LocationGrid* currentEnvironment_;                         ///< Current environment
    Location* currentLocation_;                                ///< Current location within environment

    /**
     * @brief Create all game environments
     */
    void createEnvironments();

    /**
     * @brief Create a specific environment
     * @param type The type of environment to create
     * @return Unique pointer to the created environment
     */
    std::unique_ptr<LocationGrid> createEnvironment(EnvironmentType type);

    /**
     * @brief Connect two environments
     * @param env1 First environment
     * @param exit1 Exit location in first environment
     * @param env2 Second environment
     * @param exit2 Exit location in second environment
     */
    void connectEnvironments(LocationGrid* env1, Location* exit1,
                           LocationGrid* env2, Location* exit2);
};

#endif