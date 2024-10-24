#ifndef ENVIRONMENT_BUILDER_H_
#define ENVIRONMENT_BUILDER_H_

#include "location_grid.h"
#include "environment_type.h"
#include <memory>
#include <string>

/**
 * @class EnvironmentBuilder
 * @brief Factory class for creating game environments
 * 
 * This class is responsible for building complete environment grids,
 * including all locations, their descriptions, and special features
 * as specified in the game design.
 */
class EnvironmentBuilder {
 public:
    /**
     * @brief Build a complete environment based on type
     * @param type The type of environment to create
     * @return Unique pointer to the created environment
     */
    static std::unique_ptr<LocationGrid> buildEnvironment(EnvironmentType type);

 private:
    /**
     * @brief Helper class to store location creation data
     */
    struct LocationData {
        std::string name;
        std::string description;
        std::vector<std::shared_ptr<Item>> items;
        std::vector<std::shared_ptr<NPC>> npcs;
        std::shared_ptr<Puzzle> puzzle;

        LocationData(const std::string& n, const std::string& desc)
            : name(n), description(desc) {}
    };


    /**
     * @brief Create the Village of Luminara environment
     * @return Unique pointer to the created environment
     */
    static std::unique_ptr<LocationGrid> createVillageOfLuminara();

    /**
     * @brief Create the Whispering Woods environment
     * @return Unique pointer to the created environment
     */
    static std::unique_ptr<LocationGrid> createWhisperingWoods();

    /**
     * @brief Create the Crystal Caves environment
     * @return Unique pointer to the created environment
     */
    static std::unique_ptr<LocationGrid> createCrystalCaves();

    /**
     * @brief Create the Forgotten Library environment
     * @return Unique pointer to the created environment
     */
    static std::unique_ptr<LocationGrid> createForgottenLibrary();

    /**
     * @brief Create the Echoing Mountains environment
     * @return Unique pointer to the created environment
     */
    static std::unique_ptr<LocationGrid> createEchoingMountains();

    /**
     * @brief Create the Shadow Marshes environment
     * @return Unique pointer to the created environment
     */
    static std::unique_ptr<LocationGrid> createShadowMarshes();

    /**
     * @brief Create the Sanctum of Light environment
     * @return Unique pointer to the created environment
     */
    static std::unique_ptr<LocationGrid> createSanctumOfLight();

    /**
     * @brief Create Malakar's Lair environment
     * @return Unique pointer to the created environment
     */
    static std::unique_ptr<LocationGrid> createMalakarsLair();

    /**
     * @brief Create the Hidden Grove environment
     * @return Unique pointer to the created environment
     */
    static std::unique_ptr<LocationGrid> createHiddenGrove();

    /**
     * @brief Helper function to create a basic 3x3 grid
     * @param name Environment name
     * @param locations Array of location data for each grid position
     * @return Created environment grid
     */
    static std::unique_ptr<LocationGrid> createBasicGrid(
        const std::string& name,
        const std::array<std::array<LocationData, LocationGrid::GRID_SIZE>,
                        LocationGrid::GRID_SIZE>& locations);
};

#endif