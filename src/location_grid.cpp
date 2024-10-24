#include "location_grid.h"

LocationGrid::LocationGrid(const std::string& name) : name_(name) {
    // Initialize grid with nullptr
    for (auto& row : grid_) {
        row.fill(nullptr);
    }
}

bool LocationGrid::setLocation(int x, int y, std::shared_ptr<Location> location) {
    if (!isValidCoordinate(x, y)) {
        return false;
    }

    grid_[y][x] = std::move(location);
    return true;
}

Location* LocationGrid::getLocation(int x, int y) const {
    if (!isValidCoordinate(x, y)) {
        return nullptr;
    }

    return grid_[y][x].get();
}

void LocationGrid::connectGridLocations() {
    for (int y = 0; y < GRID_SIZE; ++y) {
        for (int x = 0; x < GRID_SIZE; ++x) {
            if (!grid_[y][x]) continue;

            // Connect to north
            if (y > 0 && grid_[y-1][x]) {
                grid_[y][x]->addExit(Location::Direction::NORTH, grid_[y-1][x].get());
                grid_[y-1][x]->addExit(Location::Direction::SOUTH, grid_[y][x].get());
            }

            // Connect to east
            if (x < GRID_SIZE-1 && grid_[y][x+1]) {
                grid_[y][x]->addExit(Location::Direction::EAST, grid_[y][x+1].get());
                grid_[y][x+1]->addExit(Location::Direction::WEST, grid_[y][x].get());
            }
        }
    }
}

bool LocationGrid::isValidCoordinate(int x, int y) const {
    return x >= 0 && x < GRID_SIZE && y >= 0 && y < GRID_SIZE;
}
