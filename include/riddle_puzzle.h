#ifndef RIDDLE_PUZZLE_H_
#define RIDDLE_PUZZLE_H_

#include "puzzle.h"
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>

/**
 * @class RiddlePuzzle
 * @brief A puzzle type that presents a riddle to be solved
 * 
 * This class implements a simple riddle puzzle where the player
 * must provide the correct answer to solve it. The answer checking
 * is case-insensitive and supports multiple correct answers.
 */
class RiddlePuzzle : public Puzzle {
 public:
    /**
     * @brief Constructor for RiddlePuzzle
     * @param name The name of the puzzle
     * @param description The riddle text
     * @param answers Vector of acceptable answers
     * @param hint Optional hint for the puzzle
     * @param max_attempts Maximum number of attempts (-1 for unlimited)
     */
    RiddlePuzzle(const std::string& name,
                 const std::string& description,
                 const std::vector<std::string>& answers,
                 const std::string& hint = "",
                 int max_attempts = 3);

    /**
     * @brief Attempt to solve the riddle
     * @param attempt The attempted answer
     * @return true if the answer is correct
     */
    bool AttemptSolution(const std::string& attempt) override;

    /**
     * @brief Get a hint for the riddle
     * @return The hint string
     */
    std::string GetHint() const override;

 private:
    std::vector<std::string> correct_answers_;  ///< List of acceptable answers
    std::string hint_;                         ///< Hint for the puzzle

    /**
     * @brief Normalize a string for comparison
     * @param str The string to normalize
     * @return The normalized string (lowercase, trimmed)
     */
    static std::string NormalizeString(const std::string& str);
};

#endif  // RIDDLE_PUZZLE_H