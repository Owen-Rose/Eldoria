// puzzle.h
#ifndef PUZZLE_H_
#define PUZZLE_H_

#include <string>
#include <vector>
#include <memory>
#include <stdexcept>

/**
 * @enum PuzzleState
 * @brief Represents the current state of a puzzle
 */
enum class PuzzleState {
    UNSOLVED,      ///< Puzzle has not been attempted
    IN_PROGRESS,   ///< Puzzle is currently being solved
    SOLVED,        ///< Puzzle has been successfully solved
    FAILED         ///< Puzzle has failed (e.g., too many attempts)
};

/**
 * @class PuzzleException
 * @brief Custom exception class for puzzle-related errors
 */
class PuzzleException : public std::runtime_error {
 public:
    explicit PuzzleException(const std::string& message) 
        : std::runtime_error(message) {}
};

/**
 * @class Puzzle
 * @brief Abstract base class for all puzzles in the game
 * 
 * This class defines the interface that all puzzle types must implement.
 * It provides common functionality for state management, attempt tracking,
 * and basic puzzle operations.
 */
class Puzzle {
 public:
    /**
     * @brief Constructor for Puzzle
     * @param name The name of the puzzle
     * @param description A description of the puzzle
     * @param max_attempts Maximum number of attempts allowed (-1 for unlimited)
     * @throws std::invalid_argument if name or description is empty
     */
    Puzzle(const std::string& name, 
           const std::string& description,
           int max_attempts = -1);

    /**
     * @brief Virtual destructor
     */
    virtual ~Puzzle() = default;

    /**
     * @brief Attempt to solve the puzzle
     * @param attempt The solution attempt
     * @return true if the puzzle is solved, false otherwise
     * @throws PuzzleException if the puzzle cannot be attempted
     */
    virtual bool AttemptSolution(const std::string& attempt) = 0;

    /**
     * @brief Check if the puzzle is solved
     * @return true if the puzzle is solved
     */
    bool IsSolved() const;

    /**
     * @brief Get a hint for the puzzle
     * @return A string containing the hint
     */
    virtual std::string GetHint() const = 0;

    /**
     * @brief Check if the puzzle can be attempted
     * @return true if the puzzle can be attempted
     */
    virtual bool CanAttempt() const;

    /**
     * @brief Reset the puzzle to its initial state
     */
    virtual void Reset();

    /**
     * @brief Get the current state of the puzzle
     * @return The puzzle's current state
     */
    PuzzleState GetState() const;

    /**
     * @brief Get the name of the puzzle
     * @return The puzzle's name
     */
    std::string GetName() const;

    /**
     * @brief Get the description of the puzzle
     * @return The puzzle's description
     */
    std::string GetDescription() const;

    /**
     * @brief Get the number of attempts remaining
     * @return Number of attempts remaining (-1 for unlimited)
     */
    int GetAttemptsRemaining() const;

 protected:
    /**
     * @brief Set the puzzle's state
     * @param new_state The new state to set
     */
    void SetState(PuzzleState new_state);

    /**
     * @brief Increment the attempt counter
     * @return true if more attempts are allowed, false otherwise
     */
    bool IncrementAttempts();

    std::string name_;            ///< The name of the puzzle
    std::string description_;     ///< The description of the puzzle
    PuzzleState state_;          ///< Current state of the puzzle
    int attempts_;               ///< Number of attempts made
    int max_attempts_;           ///< Maximum number of attempts allowed

 private:
    /**
     * @brief Validate the puzzle parameters
     * @throws std::invalid_argument if parameters are invalid
     */
    void ValidateParameters();
};

#endif  // PUZZLE_H