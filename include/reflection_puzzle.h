// reflection_puzzle.h
#ifndef REFLECTION_PUZZLE_H_
#define REFLECTION_PUZZLE_H_

#include "puzzle.h"
#include <array>
#include <optional>
#include <vector>

/**
 * @struct Mirror
 * @brief Represents a mirror in the Light Reflection puzzle
 */
struct Mirror {
    int rotation;  ///< Rotation in degrees (0, 45, 90, 135, etc.)
    bool placed;   ///< Whether the mirror is placed on the grid
};

/**
 * @struct LightBeam
 * @brief Represents a beam of light in the puzzle
 */
struct LightBeam {
    int x, y;     ///< Current position
    int dx, dy;   ///< Direction vector
};

/**
 * @class ReflectionPuzzle
 * @brief Implementation of the Light Reflection puzzle
 * 
 * Players must place and rotate mirrors to direct a beam of light
 * to a specific target. Requires the Crystal Lens item to solve.
 */
class ReflectionPuzzle : public Puzzle {
 public:
    static const int GRID_SIZE = 5;  ///< Size of the puzzle grid

    /**
     * @brief Constructor for ReflectionPuzzle
     * @param name Puzzle name
     * @param description Puzzle description
     * @param source_x Starting X coordinate of light beam
     * @param source_y Starting Y coordinate of light beam
     * @param target_x Target X coordinate
     * @param target_y Target Y coordinate
     * @param max_mirrors Maximum number of mirrors allowed
     */
    ReflectionPuzzle(const std::string& name,
                     const std::string& description,
                     int source_x, int source_y,
                     int target_x, int target_y,
                     int max_mirrors);

    /**
     * @brief Attempt to solve the puzzle with current configuration
     * @param attempt Unused in this puzzle type
     * @return true if light beam reaches target
     */
    bool AttemptSolution(const std::string& attempt) override;

    /**
     * @brief Get hint for current puzzle state
     * @return String containing hint
     */
    std::string GetHint() const override;

    /**
     * @brief Check if puzzle can be attempted
     * @return true if Crystal Lens is present and puzzle isn't solved
     */
    bool CanAttempt() const override;

    /**
     * @brief Place a mirror on the grid
     * @param x X coordinate
     * @param y Y coordinate
     * @param rotation Initial rotation in degrees
     * @return true if mirror was placed successfully
     */
    bool PlaceMirror(int x, int y, int rotation);

    /**
     * @brief Remove a mirror from the grid
     * @param x X coordinate
     * @param y Y coordinate
     * @return true if mirror was removed successfully
     */
    bool RemoveMirror(int x, int y);

    /**
     * @brief Rotate a mirror on the grid
     * @param x X coordinate
     * @param y Y coordinate
     * @param degrees Degrees to rotate (positive or negative)
     * @return true if mirror was rotated successfully
     */
    bool RotateMirror(int x, int y, int degrees);

    /**
     * @brief Get the current light beam path
     * @return Vector of coordinates representing beam path
     */
    std::vector<std::pair<int, int>> GetBeamPath() const;

    /**
     * @brief Check if Crystal Lens is present
     * @param has_lens Whether the player has the Crystal Lens
     */
    void SetHasLens(bool has_lens);

 private:
    using Grid = std::array<std::array<std::optional<Mirror>, GRID_SIZE>, GRID_SIZE>;

    Grid grid_;                      ///< Puzzle grid containing mirrors
    int source_x_, source_y_;        ///< Light beam source coordinates
    int target_x_, target_y_;        ///< Target coordinates
    int max_mirrors_;                ///< Maximum allowed mirrors
    int placed_mirrors_;             ///< Current number of placed mirrors
    bool has_crystal_lens_;          ///< Whether player has Crystal Lens

    /**
     * @brief Calculate light beam reflection
     * @param beam Current beam state
     * @param mirror Mirror being hit
     * @return New beam direction
     */
    static LightBeam CalculateReflection(const LightBeam& beam, const Mirror& mirror);

    /**
     * @brief Validate coordinates
     * @param x X coordinate
     * @param y Y coordinate
     * @return true if coordinates are valid
     */
    static bool ValidateCoordinates(int x, int y);

    /**
     * @brief Normalize rotation angle to 0-359 range
     * @param degrees Rotation angle
     * @return Normalized angle
     */
    static int NormalizeRotation(int degrees);

    /**
     * @brief Simulate light beam path
     * @return true if beam reaches target
     */
    bool SimulateBeam() const;
};

#endif  // REFLECTION_PUZZLE_H