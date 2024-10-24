#ifndef LOCATION_GRID_H_
#define LOCATION_GRID_H_

#include "location.h"
#include <array>
#include <memory>
#include <optional>

/**
 * @class LocationGrid
 * @brief Represents a 3x3 grid of locations within an environment
 * 
 * This class implements the grid-based location system required by the
 * game design, where each environment consists of a 3x3 grid of
 * interconnected locations.
 */
class LocationGrid {
 public:
    static const int GRID_SIZE = 3;  ///< Size of the grid (3x3)

    /**
     * @brief Constructor for LocationGrid
     * @param name Name of the environment this grid represents
     */
    explicit LocationGrid(const std::string& name);

    /**
     * @brief Set a location in the grid
     * @param x X coordinate (0-2)
     * @param y Y coordinate (0-2)
     * @param location The location to place
     * @return true if location was set successfully
     */
    bool setLocation(int x, int y, std::shared_ptr<Location> location);

    /**
     * @brief Get a location from the grid
     * @param x X coordinate
     * @param y Y coordinate
     * @return Pointer to the location, nullptr if invalid coordinates
     */
    Location* getLocation(int x, int y) const;

    /**
     * @brief Get the name of this environment
     * @return The environment name
     */
    std::string getName() const { return name_; }

    /**
     * @brief Connect this grid's locations internally
     * Sets up connections between adjacent locations in the grid
     */
    void connectGridLocations();

 private:
    std::string name_;  ///< Name of this environment
    std::array<std::array<std::shared_ptr<Location>, GRID_SIZE>, GRID_SIZE> grid_;  ///< The 3x3 grid

    /**
     * @brief Validate grid coordinates
     * @param x X coordinate
     * @param y Y coordinate
     * @return true if coordinates are valid
     */
    bool isValidCoordinate(int x, int y) const;
};

#endif